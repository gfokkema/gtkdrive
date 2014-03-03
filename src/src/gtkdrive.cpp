#include <gtkmm.h>

#include "googleapis/client/transport/curl_http_transport.h"
#include "googleapis/client/transport/http_transport.h"

#include "gtkdrive.h"
#include "wizard.h"

using namespace googleapis::client;
using Glib::RefPtr;
using Gtk::Application;

namespace googleapis {

GtkDrive::GtkDrive ()
: p_config  (new HttpTransportLayerConfig),
  p_service (0)
{
  HttpTransportFactory *factory = new CurlHttpTransportFactory (p_config);
  p_config->ResetDefaultTransportFactory (factory);
}

GtkDrive::~GtkDrive ()
{
  delete p_config;
  //delete p_service;
}

void
GtkDrive::Startup (Glib::RefPtr<Application> app)
{
  // TODO: Only tart auth dialog if no user stored
  Wizard wizard(p_config->NewDefaultTransportOrDie());
  app->run(wizard);
  // Initialize DriveService()
  //p_service = new DriveService(p_config->NewDefaultTransport(&status));
}

}
