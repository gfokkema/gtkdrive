#ifndef DRIVE_WRAPPER_H_
#define DRIVE_WRAPPER_H_

/* Start forward declarations */
namespace google_drive_api {
  class DriveService;
}
namespace googleapis {
  class Auth;
  namespace client {
    class HttpTransportLayerConfig;
  }
}
/* End forward declarations */


namespace googleapis {

class GtkDrive
{
public:
  GtkDrive  ();
  ~GtkDrive ();
  void about ();
  void dir ();
private:
  Auth                             *p_auth;
  client::HttpTransportLayerConfig *p_config;
  google_drive_api::DriveService   *p_service;
};

}

#endif
