#include <iostream>

#include "googleapis/client/auth/file_credential_store.h"
#include "googleapis/client/data/openssl_codec.h"
#include "google/drive_api/drive_service.h"

#include "auth_wrapper.h"

namespace googleapis {

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::operator<<;

using client::FileCredentialStoreFactory;
using client::HttpTransport;
using client::OAuth2AuthorizationFlow;
using client::OAuth2Credential;
using client::OAuth2RequestOptions;
using client::OpenSslCodecFactory;
using client::StatusCanceled;
using client::StatusInvalidArgument;
using client::StatusOk;
using util::Status;

using google_drive_api::DriveService;

/****************************************
 *            STATIC METHODS            *
 ****************************************/
static Status PromptShellForAuthorizationCode(
		OAuth2AuthorizationFlow* flow,
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

static Status ValidateUserName(const string& name)
{
	if (name.find("/") != string::npos)
	{
		return StatusInvalidArgument("UserNames cannot contain '/'");
	} else if (name == "." || name == "..") {
		return StatusInvalidArgument(StrCat("'", name, "' is not a valid UserName"));
	}
	return StatusOk();
}

/****************************************
 *           CLASS: AuthWrapper         *
 ****************************************/
scoped_ptr<OAuth2AuthorizationFlow> AuthWrapper::flow_;

Status AuthWrapper::Startup(HttpTransport *transport_)
{
	Status status;

	// Set up OAuth 2.0 flow for getting credentials to access personal data.
	const StringPiece client_secrets_file = "client_secret.json";
	flow_.reset(OAuth2AuthorizationFlow::MakeFlowFromClientSecretsPath(client_secrets_file, transport_, &status));
	if (!status.ok()) return status;

	// Configure OAuth2 flow (Scope, Redir, AuthCode)
	flow_->set_default_scopes(DriveService::SCOPES::DRIVE);
	flow_->mutable_client_spec()->set_redirect_uri(OAuth2AuthorizationFlow::kOutOfBandUrl);
	flow_->set_authorization_code_callback(
			NewPermanentCallback(&PromptShellForAuthorizationCode, flow_.get()));

	string home_path;
	status = FileCredentialStoreFactory::GetSystemHomeDirectoryStorePath(&home_path);
	if (status.ok())
	{
		FileCredentialStoreFactory store_factory(home_path);
		OpenSslCodecFactory* openssl_factory = new OpenSslCodecFactory;
		status = openssl_factory->SetPassphrase(flow_->client_spec().client_secret());
		if (!status.ok()) return status;
		store_factory.set_codec_factory(openssl_factory);
		flow_->ResetCredentialStore(store_factory.NewCredentialStore("DriveSample", &status));
	}
	return status;
}

Status AuthWrapper::Authorize(OAuth2Credential *credential_)
{
	cout << "Enter a user id: " << endl;
	string id;
	std::getline(cin, id);
	if (!id.empty())
	{
		util::Status status = ValidateUserName(id);
		if (!status.ok())
		{
			return status;
		}
	}

	OAuth2RequestOptions options;
	options.user_id = id;
	Status status = flow_->RefreshCredentialWithOptions(options, credential_);
	if (!status.ok()) return status;

	credential_->set_flow(flow_.get());
	cout << "Authorized " << id << endl;
	return StatusOk();
}

}
