#include "vendas.h"

void btn_salvar_venda(GtkWidget *button, GtkWindow *this_window){
	const gchar *valor, *descricao, *vendedor;

	descricao = gtk_entry_get_text(GTK_ENTRY(txt_descricao));

}

void open_new_vendas(){
	builder_vendas = gtk_builder_new();
	gtk_builder_add_from_file(builder_vendas, UI_CADASTRO_VENDAS_FILE, NULL);
	window_vendas = gtk_builder_get_object(builder_vendas, "cadastro_vendas");
	btn_salvar = gtk_builder_get_object(builder_vendas, "btn_salvar");
	g_signal_connect(btn_salvar, "clicked", G_CALLBACK(btn_salvar_venda), (gpointer) window_vendas); 
}

void list_vendas(){
	
}