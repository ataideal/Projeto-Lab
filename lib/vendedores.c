#include "vendedores.h"

extern int quantidade_vendedores;

void btn_salvar_vendedor(GtkWidget* button, GtkWindow *this_window){
  //aplicar logica de no máximo 10 vendedores
  //if count vendedor < 10
  Vendedor new;
  const gchar *nome, *sexo, *cpf, *nasc_dia, *nasc_mes, *nasc_ano;
  txt_nome = gtk_builder_get_object(builder_vendedor, "txt_nome");
  txt_cpf = gtk_builder_get_object(builder_vendedor, "txt_cpf");
  combo_sexo = gtk_builder_get_object(builder_vendedor, "cmb_sexo");
  txt_dia = gtk_builder_get_object(builder_vendedor, "txt_data");
  txt_mes = gtk_builder_get_object(builder_vendedor, "txt_mes");
  txt_ano = gtk_builder_get_object(builder_vendedor, "txt_ano");

  nome = gtk_entry_get_text(GTK_ENTRY(txt_nome));
  cpf = gtk_entry_get_text(GTK_ENTRY(txt_cpf));
  sexo = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_sexo));
  nasc_dia =  gtk_entry_get_text(GTK_ENTRY(txt_dia));
  nasc_mes =  gtk_entry_get_text(GTK_ENTRY(txt_mes));
  nasc_ano =  gtk_entry_get_text(GTK_ENTRY(txt_ano));

  sprintf(new.nome, "%s", (char *)nome);
  sprintf(new.sexo, "%s", (char *)sexo);
  sprintf(new.cpf, "%s", (char *)cpf);
  new.data_nasc.dia = atoi((char*)nasc_dia);
  new.data_nasc.mes = atoi((char*)nasc_mes);
  new.data_nasc.ano = atoi((char*)nasc_ano);

  //colocar aqui para salvar vendedor
  if(salvar_vendedor(new) >= 0){
    alert_info(this_window, "Salvo com sucesso!");
  }else{
    alert_info(this_window, "Erro ao salvar!");
  }
  gtk_widget_destroy(GTK_WIDGET(this_window));
}

void open_new_vendedor(){
  builder_vendedor = gtk_builder_new (); 
  gtk_builder_add_from_file(builder_vendedor, UI_CADASTRO_VENDEDOR_FILE, NULL);
  GObject *window_vendedores, *save_vendedor;
  save_vendedor = gtk_builder_get_object(builder_vendedor, "btn_salvar");
  window_vendedores = gtk_builder_get_object(builder_vendedor, "cadastro_vendedores");
  gtk_window_present (GTK_WINDOW(window_vendedores));
  g_signal_connect(G_OBJECT(save_vendedor), "clicked", G_CALLBACK(btn_salvar_vendedor), (gpointer) window_vendedores);
}

void open_list_vendedor(){

}

void relatorio_total_vendas_vendedor(){
 
}

int salvar_vendedor(Vendedor vendedor){ /*Esta função recebe um vendedor e o escreve no arquivo */
  //Atualizando vetor de vendedores
  // int aux = (*quant_vendedores);
  // vendedores[aux].id = vendedor.id;
  // vendedores[aux].idade = vendedor.idade;
  // strcpy(vendedores[aux].sexo,vendedor.sexo);
  // strcpy(vendedores[aux].cpf,vendedor.cpf);
  // strcpy(vendedores[aux].nome,vendedor.nome);
  // strcpy(vendedores[aux].nome,"\n");
  //Atualizado quantiade de vendedores
  vendedor.id = quantidade_vendedores + 1;
  quantidade_vendedores += 1;
  //Salvando no arquivo
  int is_ok = -1;
  FILE * fp_vendedores = fopen ("Vendedores.txt","a");
  if(fp_vendedores != NULL){
    is_ok = fprintf (fp_vendedores,"%d %d %d %d %s %s %s\n", vendedor.id, vendedor.data_nasc.dia, vendedor.data_nasc.mes, vendedor.data_nasc.ano, vendedor.sexo,vendedor.cpf,vendedor.nome);
    fclose(fp_vendedores);
  }
  return is_ok;
}