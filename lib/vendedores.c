#include "vendedores.h"

void btn_salvar_vendedor(GtkWidget* button, GtkWindow *this_window){
  //aplicar logica de no máximo 10 vendedores
  //if count vendedor < 10
  Vendedor new;
  const gchar nome, sexo, cpf, nasc_dia, nasc_mes, nasc_ano;

  nome = gtk_entry_get_text(GTK_ENTRY(txt_nome));
  cpf = gtk_entry_get_text(GTK_ENTRY(txt_cpf));
  sexo = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_sexo));
  
  new.nome = (char *) nome;
  new.sexo = (char *) sexo;
  new.cpf = (char *) cpf;
  new.data_nasc.dia = nasc_dia;
  new.data_nasc.mes = nasc_mes;
  new.data_nasc.ano = nasc_ano;

  //colocar aqui para salvar vendedor

  alert_info(this_window, "Salvo com sucesso!");
  gtk_widget_destroy(GTK_WIDGET(this_window));
}

void open_new_vendedor(){
  GtkBuilder *builder; 
  builder = gtk_builder_new (); 
  gtk_builder_add_from_file(builder, UI_FILE, NULL);
  GObject *window_vendedores, *save_vendedor;
  save_vendedor = gtk_builder_get_object(builder, "btn_salvar");
  txt_nome = gtk_builder_get_object(builder, "txt_nome");
  combo_sexo = gtk_builder_get_object(builder, "cmb_sexo");
  window_vendedores = gtk_builder_get_object(builder, "cadastro_vendedores");
  gtk_window_present (GTK_WINDOW(vendedores));
  g_signal_connect(G_OBJECT(save_vendedor), "clicked", G_CALLBACK(btn_salvar_vendedor), (gpointer) window_vendedores);
}