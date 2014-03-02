#include <iostream>

#include "wizard-mm.h"

using namespace Gtk;

GtkDriveAssistant::GtkDriveAssistant ()
: m_page_1_label ("This wizard will help you set up your\n"\
                  "Google Drive account for use with GtkDrive"),
  m_page_2_label ("Please enter your account name"),
  m_page_3_label ("Please enter your confirmation code"),
  m_page_4_label ("This is an overview of your settings"),
  m_page_5_label ("Please confirm your settings")
{
  set_title ("GtkDriveAssistant example");
  set_default_size (400, 300);

  /* Set up page 1 */
  append_page       (m_page_1);
  set_page_title    (m_page_1, "Introduction");
  set_page_type     (m_page_1, ASSISTANT_PAGE_INTRO);
  set_page_complete (m_page_1, true);
  m_page_1.add      (m_page_1_label);

  /* Set up page 2 */
  append_page       (m_page_2);
  set_page_title    (m_page_2, "Your account");
  m_page_2.set_orientation (ORIENTATION_VERTICAL);
  m_page_2.add      (m_page_2_label);
  m_page_2.add      (m_page_2_entry);
  m_page_2_entry.signal_changed ().connect (
      sigc::mem_fun(*this, &GtkDriveAssistant::on_assistant_page_2));

  /* Set up page 3 */
  append_page       (m_page_3);
  set_page_title    (m_page_3, "Your confirmation");
  m_page_3.set_orientation (ORIENTATION_VERTICAL);
  m_page_3.add      (m_page_3_label);
  m_page_3.add      (m_page_3_entry);
  m_page_3_entry.signal_changed ().connect (
      sigc::mem_fun(*this, &GtkDriveAssistant::on_assistant_page_3));

  /* Set up page 4 */
  append_page       (m_page_4);
  set_page_title    (m_page_4, "Overview");
  set_page_type     (m_page_4, ASSISTANT_PAGE_PROGRESS);
  set_page_complete (m_page_4, true);
  m_page_4.add      (m_page_4_label);

  /* Set up page 5 */
  append_page       (m_page_5);
  set_page_title    (m_page_5, "Confirm");
  set_page_type     (m_page_4, ASSISTANT_PAGE_CONFIRM);
  set_page_complete (m_page_4, true);
  m_page_5.add      (m_page_5_label);

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

void GtkDriveAssistant::on_assistant_page_2()
{
  Glib::ustring account = m_page_2_entry.get_text();
  Glib::ustring::size_type atindex  = account.find_first_of ('@');
  Glib::ustring::size_type dotindex = account.find_last_of ('.');
  if (atindex  != account.npos &&
      dotindex != account.npos &&
      dotindex >  atindex &&
      dotindex <  account.length() - 2)
  {
    set_page_complete (m_page_2, true);
  }
  else
  {
    set_page_complete (m_page_2, false);
  }
}

void GtkDriveAssistant::on_assistant_page_3()
{
  set_page_complete(m_page_3, true);
}

int
main (int    argc,
      char** argv)
{
  Glib::RefPtr<Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.gtkdrive");

  GtkDriveAssistant assistant;
  return app->run (assistant);
}
