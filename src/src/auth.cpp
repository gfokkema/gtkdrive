#include <iostream>

#include "googleapis/client/auth/oauth2_authorization.h"
#include "googleapis/client/auth/file_credential_store.h"
#include "googleapis/client/data/openssl_codec.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"
#include "google/drive_api/drive_service.h"

#include "auth.h"
#include "wizard.h"

using namespace std;
using namespace googleapis::client;
using namespace googleapis::util;
using namespace google_drive_api;

namespace googleapis {

Auth::Auth (HttpTransport *transport)
: m_client_secret ("client_secret.json"),
  p_flow          (0),
  p_transport     (transport)
{
}

Auth::~Auth ()
{
}

Status
Auth::Startup()
{
  Status status;
  string home_path;

  p_flow = OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath (m_client_secret, p_transport, &status);
  if (!status.ok()) return status;

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

void
Auth::SetCallback (Wizard *wizard)
{
  p_flow->set_default_scopes  (DriveService::SCOPES::DRIVE);
  p_flow->mutable_client_spec ()->set_redirect_uri (OAuth2AuthorizationFlow::kOutOfBandUrl);
  p_flow->set_authorization_code_callback (NewPermanentCallback (wizard, &Wizard::on_authorization, p_flow) );
}

Status
Auth::Authorize (OAuth2Credential *credential, string id)
{
  OAuth2RequestOptions options;
  options.user_id = id;

  Status status = p_flow->RefreshCredentialWithOptions(options, credential);
  if (status.ok())
  {
    credential->set_flow(p_flow);
    cout << "Authorized " << options.user_id << endl;
  }

  return status;
}

}
