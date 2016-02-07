#include "util.h"

void alert_info(GtkWindow* parent, char* message){
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Atenção");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void alert_error(GtkWindow* parent, char* message){
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}