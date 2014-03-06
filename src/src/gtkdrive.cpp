#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/client/transport/http_transport.h"
#include "google/drive_api/drive_api.h"

#include "auth.h"
#include "gtkdrive.h"

#include "googleapis/base/scoped_ptr.h"
using googleapis::scoped_ptr;

using namespace googleapis::client;
using namespace googleapis::util;
using namespace google_drive_api;

GtkDrive::GtkDrive ()
: p_auth    (0),
  p_config  (new HttpTransportLayerConfig),
  p_service (0)
{
  HttpTransportFactory *factory = new CurlHttpTransportFactory (p_config);
  p_config->ResetDefaultTransportFactory (factory);

  // Initialize Auth
  p_auth = new Auth(p_config->NewDefaultTransportOrDie());
  p_auth->Init();
  p_auth->Authorize();

  // Initialize DriveService()
  Status status;
  p_service = new DriveService(p_config->NewDefaultTransport(&status));
}

GtkDrive::~GtkDrive ()
{
  delete p_service;
  delete p_auth;
  delete p_config;
}

void Display(const File& entry) {
  std::cout << "ID: " << entry.get_title() << std::endl;
}

void Display(const ChildReference& entry) {
  std::cout << "ID: " << entry.get_id() << std::endl;
}

void
GtkDrive::about ()
{
  AboutResource_GetMethod *method = new AboutResource_GetMethod(p_service, p_auth->GetCredential());
  About *about = About::New();
  method->ExecuteAndParseResponse(about);

  std::cout << "---About---"<< std::endl;
  std::cout << about->get_name() << std::endl;
  std::cout << about->get_rootFolderId() << std::endl;
}

void
GtkDrive::dir ()
{
  //TODO: error checking
  FilesResource_ListMethod *method = new FilesResource_ListMethod(p_service, p_auth->GetCredential());
  FileList *file_list = FileList::New();
  method->ExecuteAndParseResponse(file_list);

  const JsonCppArray<File>& items = file_list->get_items();
  typename JsonCppArray<File>::const_iterator it = items.begin();
  for (it; it != items.end(); ++it) {
    Display(*it);
  }

  ChildrenResource_ListMethod *method2 = new ChildrenResource_ListMethod(p_service, p_auth->GetCredential(), "0AOxO5N3UwJg-Uk9PVA");
  ChildList *children = ChildList::New();
  method2->ExecuteAndParseResponse(children);

  const JsonCppArray<ChildReference>& childitems = children->get_items();
  typename JsonCppArray<ChildReference>::const_iterator it2 = childitems.begin();
  for (it2; it2 != childitems.end(); ++it2) {
    Display(*it2);
  }
}


//FilesResource_ListMethod *method = new FilesResource_ListMethod(p_service, p_auth->GetCredential());
//FileList *files = new FileList(FileList::New());
//method->ExecuteAndParseResponse(files);
//std::cout << method->http_response()->status().error_message() << std::endl;
