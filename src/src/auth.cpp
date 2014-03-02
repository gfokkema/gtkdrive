#include <iostream>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/auth/file_credential_store.h"
#include "googleapis/client/data/openssl_codec.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"
#include "google/drive_api/drive_service.h"

#include "auth.h"
#include "wizard-mm.h"

namespace googleapis {

using namespace std;
using namespace client;
using namespace util;

using google_drive_api::DriveService;

Auth::Auth (HttpTransport *transport)
: m_client_secret ("client_secret.json"),
  p_transport     (transport),
  p_flow          (0)
{
}

Auth::~Auth ()
{
  delete p_transport;
}

Status
Auth::Startup()
{
  Status status;
  string home_path;

  p_flow = OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath (m_client_secret, p_transport, &status);
  if (!status.ok()) return status;

  p_flow->set_default_scopes  (DriveService::SCOPES::DRIVE);
  p_flow->mutable_client_spec ()->set_redirect_uri (OAuth2AuthorizationFlow::kOutOfBandUrl);
  p_flow->set_authorization_code_callback (NewPermanentCallback (Auth::getAuthorization, p_flow) );

  status = FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&home_path);
  if (status.ok())
  {
    FileCredentialStoreFactory store_factory (home_path);
    OpenSslCodecFactory *openssl_factory = new OpenSslCodecFactory;
    status = openssl_factory->SetPassphrase (p_flow->client_spec ().client_secret () );
    if (!status.ok()) return status;
    store_factory.set_codec_factory (openssl_factory);
    p_flow->ResetCredentialStore (store_factory.NewCredentialStore ("DriveSample", &status) );
  }
  return status;
}

Status
Auth::Authorize(OAuth2Credential *credential)
{
  OAuth2RequestOptions options;
  options.user_id = "gerlof.fokkema";

  Status status = p_flow->RefreshCredentialWithOptions(options, credential);
  if (status.ok())
  {
    credential->set_flow(p_flow);
    cout << "Authorized " << options.user_id << endl;
  }

  return status;
}

Status
Auth::getAuthorization (OAuth2AuthorizationFlow* flow,
                        const OAuth2RequestOptions& options,
                        string* authorization_code)
{
  string url = flow->GenerateAuthorizationCodeRequestUrlWithOptions(options);
  cout << "Enter the following URL into a browser:\n" << url << endl;
  cout << endl;
  cout << "Enter the browser's response to confirm authorization: ";

  authorization_code->clear();
  cin >> *authorization_code;
  if (authorization_code->empty())
  {
    return StatusCanceled("Canceled");
  } else {
    return StatusOk();
  }
}

}
