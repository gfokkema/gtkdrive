#include <gtk/gtk.h>

#include "wizard.h"

static gboolean
delete_event (GtkWidget *widget,
              GdkEvent  *event,
              gpointer  data)
{
  gtk_main_quit ();
  return FALSE;
}


int
main (int argc,
      char *argv[])
{
  GtkWidget *assistant;
  guint     i;

  PageInfo page[5] = {
      { NULL, -1, "Introduction",      GTK_ASSISTANT_PAGE_INTRO,    TRUE },
      { NULL, -1, "Your account",      GTK_ASSISTANT_PAGE_CONTENT,  FALSE },
      { NULL, -1, "Your confirmation", GTK_ASSISTANT_PAGE_CONTENT,  FALSE },
      { NULL, -1, "Overview",          GTK_ASSISTANT_PAGE_PROGRESS, FALSE },
      { NULL, -1, "Confirm",           GTK_ASSISTANT_PAGE_CONFIRM,  TRUE },
  };

  gtk_init (&argc, &argv);

  assistant = gtk_assistant_new ();
  gtk_widget_set_size_request (assistant, 450, 300);
  gtk_window_set_title        (GTK_WINDOW (assistant), "Set up your Google Drive account");
  g_signal_connect            (G_OBJECT (assistant), "delete-event",
                               G_CALLBACK (delete_event), NULL);
  g_signal_connect            (G_OBJECT (assistant), "cancel",
                               G_CALLBACK (delete_event), NULL);

  page[0].widget = gtk_label_new ("This wizard will help you configure\n"\
                                  "your Google Drive account for use in GTK Drive.\n"\
                                  "Click next to continue.");
  page[1].widget = gtk_label_new ("Content 1");
  page[2].widget = gtk_label_new ("Content 2");
  page[3].widget = gtk_label_new ("Overview");
  page[4].widget = gtk_label_new ("Confirm");

  for (i = 0; i < 5; i++)
  {
    page[i].index = gtk_assistant_append_page (GTK_ASSISTANT (assistant), page[i].widget);
    gtk_assistant_set_page_title    (GTK_ASSISTANT (assistant), page[i].widget, page[i].title);
    gtk_assistant_set_page_type     (GTK_ASSISTANT (assistant), page[i].widget, page[i].type);
    gtk_assistant_set_page_complete (GTK_ASSISTANT (assistant), page[i].widget, page[i].complete);
  }

  gtk_widget_show_all (assistant);
  gtk_main();

  return 0;
}
