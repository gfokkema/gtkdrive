#ifndef WIZARD_MM_H_
#define WIZARD_MM_H_

#include <gtkmm.h>

typedef struct {
  Gtk::Widget            *widget;
  Glib::ustring          title;
  Gtk::AssistantPageType type;
  gboolean               complete;
} PageInfo;

class GtkDriveAssistant : public Gtk::Assistant
{
public:
  /* Constructor */
  GtkDriveAssistant ();
  virtual ~GtkDriveAssistant ();

  /* Members */
  void get_result (bool& state,
                   Glib::ustring& text);
private:
  /* Signals */
  void on_assistant_cancel ();
  void on_assistant_page_2 ();
  void on_assistant_page_3 ();

  /* Members */
  Gtk::Grid  m_page_1;
  Gtk::Label m_page_1_label;
  Gtk::Grid  m_page_2;
  Gtk::Label m_page_2_label;
  Gtk::Entry m_page_2_entry;
  Gtk::Grid  m_page_3;
  Gtk::Label m_page_3_label;
  Gtk::Entry m_page_3_entry;
  Gtk::Grid  m_page_4;
  Gtk::Label m_page_4_label;
  Gtk::Grid  m_page_5;
  Gtk::Label m_page_5_label;
};

#endif /* WIZARD_MM_H_ */
