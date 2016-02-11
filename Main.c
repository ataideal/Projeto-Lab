#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "lib/util.h"
#include "lib/vendedores.h"
#include "lib/vendas.h"

#define UI_FILE "ui/principal.glade" 

GtkBuilder *builder;
GObject *window, *btn_cadastro_vendedor, *btn_cadastro_vendedor2, *btn_cadastro_vendas, *btn_cadastro_vendedor3;

int main(int argc, char *argv[]){

  gtk_init (&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, UI_FILE, NULL);

  window = gtk_builder_get_object(builder, "window_principal");
  gtk_window_set_default_size((gpointer) GTK_WINDOW(window), 500, 400);
  g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), (gpointer) window);
	
  btn_cadastro_vendedor = gtk_builder_get_object(builder, "btn_cadastro_vendedor");
  g_signal_connect(G_OBJECT(btn_cadastro_vendedor), "clicked", G_CALLBACK(open_new_vendedor), (gpointer) window);

  btn_cadastro_vendas = gtk_builder_get_object(builder, "btn_cadastro_vendas");
  g_signal_connect(G_OBJECT(btn_cadastro_vendas), "clicked", G_CALLBACK(open_new_vendas), (gpointer) window);

  btn_cadastro_vendedor2 = gtk_builder_get_object(builder, "btn_cadastro_vendedor2");
  g_signal_connect(G_OBJECT(btn_cadastro_vendedor2), "clicked", G_CALLBACK(list_vendas), (gpointer) window);

  btn_cadastro_vendedor2 = gtk_builder_get_object(builder, "btn_cadastro_vendedor3");
  g_signal_connect(G_OBJECT(btn_cadastro_vendedor3), "clicked", G_CALLBACK(relatorio_total_vendas_vendedor), (gpointer) window);

  gtk_window_present(GTK_WINDOW(window));

  gtk_main();

  return 0;
}