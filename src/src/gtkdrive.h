#ifndef DRIVE_WRAPPER_H_
#define DRIVE_WRAPPER_H_

#include "googleapis/client/auth/oauth2_authorization.h"
#include "gtkmm.h"

/* Start forward declarations */
namespace google_drive_api {
  class DriveService;
}
namespace googleapis {
  class Auth;
  namespace client {
    class HttpTransportLayerConfig;
    class OAuth2Credential;
  }
}
/* End forward declarations */


namespace googleapis {

class GtkDrive : public Gtk::Window
{
public:
  GtkDrive ();
  ~GtkDrive ();

  util::Status Startup ();
private:
  Auth                             *p_auth;
  client::HttpTransportLayerConfig *p_config;
  google_drive_api::DriveService   *p_service;

  client::OAuth2Credential          m_credential;
};

}

#endif
