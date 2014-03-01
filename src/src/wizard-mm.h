#ifndef WIZARD_MM_H_
#define WIZARD_MM_H_

#include <gtkmm.h>

typedef struct {
  Gtk::Widget            *widget;
  Glib::ustring          title;
  Gtk::AssistantPageType type;
  const gboolean         complete;
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
  void on_assistant_apply ();
  void on_assistant_cancel ();
  void on_assistant_close ();
  void on_assistant_prepare (GtkWidget* widget);
  void on_entry_changed ();

  /* Members */
};

#endif /* WIZARD_MM_H_ */
