#ifndef DRIVE_WRAPPER_H_
#define DRIVE_WRAPPER_H_

#include "googleapis/client/auth/oauth2_authorization.h"

/* Start forward declarations */
namespace google_drive_api {
  class DriveService;
}
namespace googleapis {
  namespace client {
    class HttpTransportLayerConfig;
  }
}
namespace Gtk {
  class Application;
}
/* End forward declarations */


namespace googleapis {

class GtkDrive
{
public:
  GtkDrive  ();
  ~GtkDrive ();

  void Startup (Glib::RefPtr<Gtk::Application> app);
private:
  client::HttpTransportLayerConfig *p_config;
  google_drive_api::DriveService   *p_service;

  client::OAuth2Credential          m_credential;
};

}

#endif
