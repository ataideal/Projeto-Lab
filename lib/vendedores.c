#include "vendas.h"
#include "vendedores.h"

extern int quantidade_vendedores;
extern int quantidade_vendas;
extern Venda vendas[300];
extern Vendedor vendedores[10];


void btn_buscar_relatorio_geral(){
  
  const gchar *mes;
  GtkTreeIter iter;
  if(store != NULL) gtk_list_store_clear (store);

  store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);

  combo_mes = gtk_builder_get_object(builder_relatorio_geral, "comboboxtext1");
  tree_relatorio_geral = gtk_builder_get_object(builder_relatorio_geral, "treeview1");
  mes = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_mes));
  
  int __mes = 1;

  if(strcmp("DEZEMBRO", (char *) mes) == 0){
    __mes = 12;
  }else if(strcmp("NOVEMBRO", (char *) mes) == 0){
    __mes = 11;
  }else if(strcmp("OUTUBRO", (char *) mes) == 0){
    __mes = 10;
  }else if(strcmp("SETEMBRO", (char *) mes) == 0){
    __mes = 9;
  }else if(strcmp("AGOSTO", (char *) mes) == 0){
    __mes = 8;
  }else if(strcmp("JULHO", (char *) mes) == 0){
    __mes = 7;
  }else if(strcmp("JUNHO", (char *) mes) == 0){
    __mes = 6;
  }else if(strcmp("MAIO", (char *) mes) == 0){
    __mes = 5;
  }else if(strcmp("ABRIL", (char *) mes) == 0){
    __mes = 4;
  }else if(strcmp("MARÇO", (char *) mes) == 0){
    __mes = 3;
  }else if(strcmp("FEVEREIRO", (char *) mes) == 0){
    __mes = 2;
  }else if(strcmp("JANEIRO", (char *) mes) == 0){
    __mes = 1;
  }
  printf("%d\n", __mes);
  int vet_vendedores[30],aux_quant=0,aux_maior = 0, i, j;
  for (i=0;i<quantidade_vendedores;i++){
    for (j=0;j<quantidade_vendas;j++){
      if (vendedores[i].id == vendas[j].vendedorId && vendas[j].data.mes == __mes){
          aux_quant++;
      }
    }
    vet_vendedores[i] = aux_quant;
    gtk_list_store_append (store, &iter);
    gtk_list_store_set(store, &iter, 0, vendedores[i].nome, 1, vet_vendedores[i], -1); 
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(tree_relatorio_geral), GTK_TREE_MODEL (store));
}

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

void open_relatorio_total_vendas_geral(){
  builder_relatorio_geral = gtk_builder_new();
  gtk_builder_add_from_file(builder_relatorio_geral, UI_RELATORIO_GERAL_FILE, NULL);
  GObject *window_relatorio, *buscar;
  buscar = gtk_builder_get_object(builder_relatorio_geral, "btn_buscar");
  window_relatorio = gtk_builder_get_object(builder_relatorio_geral, "window1");
  
  gtk_window_present (GTK_WINDOW(window_relatorio));
  g_signal_connect(G_OBJECT(buscar), "clicked", G_CALLBACK(btn_buscar_relatorio_geral), (gpointer) window_relatorio);
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