#include <iostream>

#include "wizard-mm.h"

using namespace Gtk;

GtkDriveAssistant::GtkDriveAssistant ()
{
  set_title ("GtkDriveAssistant example");
  set_default_size (400, 300);

  Label *label1 = new Label ("This wizard will help you set up your\n"\
                            "Google Drive account for use with GtkDrive");
  Label *label2 = new Label ("Please enter your account name");
  Label *label3 = new Label ("Please enter your confirmation code");
  Label *label4 = new Label ("This is an overview of your settings");
  Label *label5 = new Label ("Please confirm your settings");

  PageInfo page[5] = {
      { label1, "Introduction",      ASSISTANT_PAGE_INTRO,    true },
      { label2, "Your account",      ASSISTANT_PAGE_CONTENT,  false },
      { label3, "Your confirmation", ASSISTANT_PAGE_CONTENT,  false },
      { label4, "Overview",          ASSISTANT_PAGE_PROGRESS, false },
      { label5, "Confirm",           ASSISTANT_PAGE_CONFIRM,  true },
  };

  for (int i = 0; i < 5; i++)
  {
    append_page       (*page[i].widget);
    set_page_type     (*page[i].widget, page[i].type);
    set_page_title    (*page[i].widget, page[i].title);
    set_page_complete (*page[i].widget, page[i].complete);
  }

  signal_cancel ().connect (
      sigc::mem_fun(*this, &GtkDriveAssistant::on_assistant_cancel));

  show_all_children ();
}

GtkDriveAssistant::~GtkDriveAssistant ()
{
}

void GtkDriveAssistant::on_assistant_cancel()
{
  std::cout << "Cancel was clicked" << std::endl;
  hide ();
}

int
main (int    argc,
      char** argv)
{
  Glib::RefPtr<Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.gtkdrive");

  GtkDriveAssistant assistant;
  return app->run (assistant);
}
