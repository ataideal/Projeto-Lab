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
  vendedor.id = incr_vendedor();
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