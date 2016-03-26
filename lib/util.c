#include <stdio.h>
#include <string.h>
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

int retornar_mes_valor(char* mes){
  int __mes = 1;

  if(strcmp("DEZEMBRO", mes) == 0){
    __mes = 12;
  }else if(strcmp("NOVEMBRO", mes) == 0){
    __mes = 11;
  }else if(strcmp("OUTUBRO", mes) == 0){
    __mes = 10;
  }else if(strcmp("SETEMBRO", mes) == 0){
    __mes = 9;
  }else if(strcmp("AGOSTO", mes) == 0){
    __mes = 8;
  }else if(strcmp("JULHO", mes) == 0){
    __mes = 7;
  }else if(strcmp("JUNHO", mes) == 0){
    __mes = 6;
  }else if(strcmp("MAIO", mes) == 0){
    __mes = 5;
  }else if(strcmp("ABRIL", mes) == 0){
    __mes = 4;
  }else if(strcmp("MARCO", mes) == 0){
    __mes = 3;
  }else if(strcmp("FEVEREIRO", mes) == 0){
    __mes = 2;
  }else if(strcmp("JANEIRO", mes) == 0){
    __mes = 1;
  }

  return __mes;
}