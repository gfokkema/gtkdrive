#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/client/transport/http_transport.h"
#include "googleapis/client/util/status.h"
#include "google/drive_api/drive_api.h"

#include "auth.h"
#include "gtkdrive.h"
#include "wizard-mm.h"

namespace googleapis {

using client::HttpTransportLayerConfig;
using client::StatusOk;
using util::Status;

GtkDrive::GtkDrive ()
: p_config  (new HttpTransportLayerConfig),
  p_service (0)
{
  client::HttpTransportFactory *factory = new client::CurlHttpTransportFactory (p_config);
  p_config->ResetDefaultTransportFactory (factory);
  p_auth = new Auth (p_config->NewDefaultTransportOrDie());
}

GtkDrive::~GtkDrive ()
{
  delete p_auth;
  delete p_config;
  //delete p_service;
}

Status
GtkDrive::Startup ()
{

  p_auth->Startup();
  p_auth->Authorize(&m_credential);

  // Initialize DriveService()
  //p_service = new DriveService(p_config->NewDefaultTransport(&status));

  return StatusOk();
}

}
