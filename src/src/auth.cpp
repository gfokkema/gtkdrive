#include <iostream>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/auth/file_credential_store.h"
#include "googleapis/client/data/openssl_codec.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"
#include "google/drive_api/drive_service.h"

#include "auth.h"

using namespace googleapis::client;
using namespace googleapis::util;
using google_drive_api::DriveService;

namespace googleapis {

Auth::Auth (HttpTransport *transport)
: m_client_secret ("client_secret.json"),
  p_flow          (0),
  p_transport     (transport)
{
}

Auth::~Auth ()
{
  delete p_flow;
}

Status
Auth::Init()
{
  Status status;
  string home_path;

  // Initialize authorization flow and callback
  p_flow = OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath (m_client_secret, p_transport, &status);
  if (!status.ok()) return status;
  p_flow->set_default_scopes  (DriveService::SCOPES::DRIVE);
  p_flow->mutable_client_spec ()->set_redirect_uri (OAuth2AuthorizationFlow::kOutOfBandUrl);
  p_flow->set_authorization_code_callback (NewPermanentCallback (this, &Auth::Callback) );

  // Initialize credential store
  status = FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&home_path);
  if (status.ok())
  {
    FileCredentialStoreFactory store_factory (home_path);
    OpenSslCodecFactory *openssl_factory = new OpenSslCodecFactory;
    status = openssl_factory->SetPassphrase (p_flow->client_spec ().client_secret () );
    if (!status.ok()) return status;
    store_factory.set_codec_factory (openssl_factory);
    p_flow->ResetCredentialStore (store_factory.NewCredentialStore ("GtkDrive", &status) );
  }
  return status;
}

Status
Auth::Authorize (string id)
{
  OAuth2RequestOptions options;
  options.user_id = id;

  Status status = p_flow->RefreshCredentialWithOptions(options, &m_credential);
  if (status.ok())
  {
    m_credential.set_flow(p_flow);
    std::cout << "Authorized " << options.user_id << std::endl;
  }
  return status;
}

Status
Auth::Callback (const OAuth2RequestOptions& options,
                string* authorization_code)
{
  string url = p_flow->GenerateAuthorizationCodeRequestUrlWithOptions(options);

  // TODO: pop up dialog for authorization code
  std::cout << "Please navigate to:" << std::endl;
  std::cout << url << std::endl;
  std::cout << "And enter your authorization code." << std::endl;

  std::cin >> *authorization_code;

  if (authorization_code->empty())
    return StatusCanceled("Canceled");
  else
    return StatusOk();
}

}
