#include "vendas.h"
#include "vendedores.h"

extern int quantidade_vendedores;
extern int quantidade_vendas;
extern Venda * vendas;
extern Vendedor vendedores[10];

void open_relatorio_total_vendas_vendedor(){

}

void btn_buscar_total_vendas_vendedor(){

}

void btn_buscar_relatorio_geral(){
  
  const gchar *mes;
  GtkTreeIter iter;
  if(store != NULL) gtk_list_store_clear (store);

  store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);

  combo_mes = gtk_builder_get_object(builder_relatorio_geral, "comboboxtext1");
  tree_relatorio_geral = gtk_builder_get_object(builder_relatorio_geral, "treeview1");
  mes = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_mes));
  
  int __mes = retornar_mes_valor((char *) mes);

  
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


  // ---- Validações ----
  int bissexto=0;
  if (( new.data_nasc.ano % 4 == 0 && new.data_nasc.ano  % 100 != 0 ) || new.data_nasc.ano  % 400 == 0)
    bissexto=1;
  int flag_mes;
  if(new.data_nasc.mes == 1 ||new.data_nasc.mes == 3 ||new.data_nasc.mes == 5 ||new.data_nasc.mes == 7 || new.data_nasc.mes == 8 || new.data_nasc.mes == 10 || new.data_nasc.mes == 12)
    flag_mes=2;
  else if (new.data_nasc.mes == 4 ||new.data_nasc.mes == 6 ||new.data_nasc.mes == 9 ||new.data_nasc.mes == 11)
    flag_mes=1;
  else
    flag_mes=0;

  int digito=0,i;
  int a = strlen(new.cpf);
  for (i=0;i<a;i++){
      if(isdigit(new.cpf[i]))
        digito++;
  }


  if(digito!=11)
    alert_error(this_window,"Verifique o cpf! (somente numeros)");
  else if (quantidade_vendedores ==10)
    alert_error(this_window,"Já existem 10 vendedores!");
  else if (new.data_nasc.ano<=0)
    alert_error(this_window,"Corriga o ano de nascimento!");
  else if (new.data_nasc.mes <1  ||  new.data_nasc.mes > 12)
    alert_error(this_window,"Corriga o mês de nascimento!");
  else if ((new.data_nasc.dia<1 || new.data_nasc.dia>31 && flag_mes==2) || (new.data_nasc.dia<1 || new.data_nasc.dia>30 && flag_mes==1) || (new.data_nasc.dia<1 || new.data_nasc.dia>28 && flag_mes==0 && bissexto==1) || (new.data_nasc.dia<1 || new.data_nasc.dia>27 && flag_mes==0 && bissexto==0))
    alert_error(this_window,"Corriga o dia de nascimento!");
  else{
    //colocar aqui para salvar vendedor
      if(salvar_vendedor(new) >= 0){
        alert_info(this_window, "Salvo com sucesso!");
      }else{
        alert_info(this_window, "Erro ao salvar!");
      }
      gtk_widget_destroy(GTK_WIDGET(this_window));
  }  

}

void open_new_vendedor(){
  builder_vendedor = gtk_builder_new (); 
  gtk_builder_add_from_file(builder_vendedor, UI_CADASTRO_VENDEDOR_FILE, NULL);
  GObject *window_vendedores, *save_vendedor;
  save_vendedor = gtk_builder_get_object(builder_vendedor, "btn_salvar");
  window_vendedores = gtk_builder_get_object(builder_vendedor, "cadastro_vendedores");
  gtk_window_set_position(GTK_WINDOW(window_vendedores), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_present (GTK_WINDOW(window_vendedores));
  g_signal_connect(G_OBJECT(save_vendedor), "clicked", G_CALLBACK(btn_salvar_vendedor), (gpointer) window_vendedores);
}

void open_relatorio_total_vendas_geral(){
  builder_relatorio_geral = gtk_builder_new();
  gtk_builder_add_from_file(builder_relatorio_geral, UI_RELATORIO_GERAL_FILE, NULL);
  GObject *window_relatorio, *buscar;
  buscar = gtk_builder_get_object(builder_relatorio_geral, "btn_buscar");
  window_relatorio = gtk_builder_get_object(builder_relatorio_geral, "window1");
  gtk_window_set_position(GTK_WINDOW(window_relatorio), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_present (GTK_WINDOW(window_relatorio));
  g_signal_connect(G_OBJECT(buscar), "clicked", G_CALLBACK(btn_buscar_relatorio_geral), (gpointer) window_relatorio);
}

void open_list_vendedor(){
  builder_vendedor = gtk_builder_new (); 
  gtk_builder_add_from_file(builder_vendedor, UI_LIST_VENDEDOR_FILE, NULL);
  GObject *window_vendedores, *label, *tree;
  window_vendedores = gtk_builder_get_object(builder_vendedor, "window1");
  tree = gtk_builder_get_object(builder_vendedor, "treeview1");
  label = gtk_builder_get_object(builder_vendedor, "label1");
  gtk_window_set_position(GTK_WINDOW(window_vendedores), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_title(GTK_WINDOW(window_vendedores), "Listar Vendedores");
  gtk_window_present (GTK_WINDOW(window_vendedores));

  char msg[100];
  
  int i;

  sprintf(msg, "Total de vendedores: %d", quantidade_vendedores);

  gtk_label_set_text(GTK_LABEL(label), msg);

  GtkListStore *_store;
  GtkTreeIter iter;

  _store = gtk_list_store_new(5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  for (i=0;i<quantidade_vendedores;i++){
    char data_nasc[11];
    sprintf(data_nasc, "%d/%d/%d", vendedores[i].data_nasc.dia, vendedores[i].data_nasc.mes, vendedores[i].data_nasc.ano);
    gtk_list_store_append (_store, &iter);
    gtk_list_store_set(_store, &iter, 0, vendedores[i].id, 1, vendedores[i].nome, 2, data_nasc, 3, vendedores[i].sexo, 4, vendedores[i].cpf, -1);      
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(_store));
}

void open_list_vendas_vendedor_mes(){
  builder_vendedor = gtk_builder_new (); 
  gtk_builder_add_from_file(builder_vendedor, UI_RELATORIO_VENDEDOR_MES_FILE, NULL);
  GObject *window_vendedores, *save_vendedor;
  buscar_mes = gtk_builder_get_object(builder_vendedor, "btn_buscar");
  window_vendedores = gtk_builder_get_object(builder_vendedor, "window1");
  gtk_window_set_position(GTK_WINDOW(window_vendedores), GTK_WIN_POS_CENTER_ALWAYS);
  txt_nome_auto = gtk_builder_get_object(builder_vendedor, "entry1");
  entry_comp = gtk_entry_completion_new();
  
  GtkTreeIter iter;
  if(store != NULL) gtk_list_store_clear (store);

  store = gtk_list_store_new(1, G_TYPE_STRING);

  int i;

  for (i=0;i<quantidade_vendedores;i++){
    char msg[300];
    sprintf(msg, "%s - %d", vendedores[i].nome, vendedores[i].id);
    //printf("%s\n", msg);
    gtk_list_store_append (store, &iter);
    gtk_list_store_set(store, &iter, 0, msg, -1); 
  }
  
  gtk_entry_completion_set_model(entry_comp, GTK_TREE_MODEL(store));
  txt_nome_auto = gtk_builder_get_object(builder_vendedor, "entry1");
  gtk_entry_completion_set_text_column(entry_comp, 0);
  gtk_entry_set_completion(GTK_ENTRY(txt_nome_auto), entry_comp);
  gtk_window_present (GTK_WINDOW(window_vendedores));
  g_signal_connect(G_OBJECT(buscar_mes), "clicked", G_CALLBACK(relatorio_total_vendas_vendedor_mes), (gpointer) window_vendedores);
}

void relatorio_total_vendas_vendedor_mes(GtkWidget* button, GtkWindow *this_window){

  const gchar *mes, *nome;

  GtkTreeIter iter;
  GtkListStore *_store;

  _store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_FLOAT);

  combo_mes = gtk_builder_get_object(builder_vendedor, "comboboxtext1");
  mes = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_mes));
  nome = gtk_entry_get_text(GTK_ENTRY(txt_nome_auto));
  tree_relatorio_meses = gtk_builder_get_object(builder_vendedor, "treeview1");

  if(mes == NULL){
    alert_info(this_window, "Necessário escolher o mês");
    return ;
  }else if(strcmp((char *) nome, "") == 0){
    alert_info(this_window, "Escolha um vendedor");
    return ;
  }

  printf("%s\n", mes);
  int __mes = retornar_mes_valor((char *) mes);
  int i, j = 0;
  int id;
  char id_aux[300];
  char * aux = (char *) nome;
  for(i = (strrchr(aux, '-') - aux) + 2; i <= strlen(aux)-1 ; i++){
    id_aux[j] = aux[i];
    j++;
  }
  id_aux[j] = '\0';
  
  id = atoi(id_aux);
  printf("%d\n", id);
  printf("%d\n", __mes);
  for (i=0;i<quantidade_vendedores;i++){
    for (j=0;j<quantidade_vendas;j++){
      if (id == vendas[j].vendedorId && id == vendedores[i].id && vendas[j].data.mes == __mes){
        gtk_list_store_append (_store, &iter);
        gtk_list_store_set(_store, &iter, 0, vendas[j].descricao, 1, vendas[j].valor, -1);      
      }
    }
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(tree_relatorio_meses), GTK_TREE_MODEL(_store));
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

  vendedor.id = incr_vendedor();
  vendedores[quantidade_vendedores] = vendedor;
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

int incr_vendedor(){ /*Esta função incrementa o id do vendedor e o retorna */
  FILE * fp = fopen ("incr_vendedor.txt", "r");
  int incr;
  fscanf(fp,"%d",&incr);
  //printf ("%d\n",incr);
  incr++;
  freopen("incr_vendedor.txt", "w+",fp);
  fprintf (fp,"%d",incr);
  fclose(fp);
  return incr;
}