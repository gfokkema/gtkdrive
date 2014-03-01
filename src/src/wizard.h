#ifndef WIZARD_H_
#define WIZARD_H_

typedef struct {
	GtkWidget				*widget;
	gint					index;
	const gchar				*title;
	GtkAssistantPageType	type;
	gboolean				complete;
} PageInfo;


#endif /* WIZARD_H_ */
