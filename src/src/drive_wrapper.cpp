#include "googleapis/client/transport/curl_http_transport.h"

#include "drive_wrapper.h"

namespace googleapis {

using std::cout;
using std::endl;

using client::HttpTransport;
using client::HttpTransportLayerConfig;
using client::JsonCppArray;
using client::StatusOk;

using google_drive_api::DriveService;
using google_drive_api::FileList;
using google_drive_api::File;
using google_drive_api::FilesResource_ListMethod;

/****************************************
 *          STATIC FUNCTIONS            *
 ****************************************/
void Display(const File file) {
	cout << file.get_title() << endl;
}

void DisplayList(const FileList list) {
	const JsonCppArray<File>& items = list.get_items();
	for (typename JsonCppArray<File>::const_iterator it = items.begin(); it != items.end(); ++it) {
		Display(*it);
	}
}

/****************************************
 *          CLASS: DriveWrapper         *
 ****************************************/
scoped_ptr<AuthWrapper>					DriveWrapper::auth_;
scoped_ptr<HttpTransportLayerConfig>	DriveWrapper::config_;
scoped_ptr<DriveService>				DriveWrapper::service_;

DriveWrapper::DriveWrapper()
{
	// Set up HttpTransportLayer.
	config_.reset(new HttpTransportLayerConfig);
	client::HttpTransportFactory* factory =	new client::CurlHttpTransportFactory(config_.get());
	config_->ResetDefaultTransportFactory(factory);

	auth_.reset(new AuthWrapper);
	auth_->Startup(config_->NewDefaultTransportOrDie());
	auth_->Authorize(&credential_);

	util::Status status;
	// Initialize DriveService()
	service_.reset(new DriveService(config_->NewDefaultTransport(&status)));
}

void DriveWrapper::dir() {
	scoped_ptr<FilesResource_ListMethod> method(service_->get_files().NewListMethod(&credential_));
	scoped_ptr<FileList> drive_list(FileList::New());
	if (!method->ExecuteAndParseResponse(drive_list.get()).ok()) {
		//DisplayError(method.get());
		cout << "something went wrong..." << endl;
		return;
	}
	DisplayList(*drive_list);
}

}
