#include "vendas.h"
#include <locale.h>

extern int quantidade_vendas;
void btn_salvar_venda(GtkWidget *button, GtkWindow *this_window){
	const gchar *vendedorId, *descricao, *valor, *dia, *mes, *ano;

	Venda new;
	txt_descricao = gtk_builder_get_object(builder_venda, "txt_descricao");
	txt_valor = gtk_builder_get_object(builder_venda, "txt_valor");
	txt_data = gtk_builder_get_object(builder_venda, "txt_data");
	txt_mes = gtk_builder_get_object(builder_venda, "txt_mes");
	txt_ano = gtk_builder_get_object(builder_venda, "txt_ano");

	descricao =  gtk_entry_get_text(GTK_ENTRY(txt_descricao));
	valor = gtk_entry_get_text(GTK_ENTRY(txt_valor));
	dia =  gtk_entry_get_text(GTK_ENTRY(txt_data));
	mes =  gtk_entry_get_text(GTK_ENTRY(txt_mes));
	ano =  gtk_entry_get_text(GTK_ENTRY(txt_ano));

	sprintf(new.descricao, "%s", (char *)descricao);
	new.valor = atof((char*)valor);
	new.data.dia = atoi((char*)dia);
	new.data.mes = atoi((char*)mes);
	new.data.ano = atoi((char*)ano);  


	printf ("VALOR CHAR: %s\nVALOR FLOAT: %f\n", (char*)valor,new.valor);	
	setlocale(LC_ALL,"C");
	printf("\n****** Verificando a localidade corrente ********\n\n");
 	printf ("Localidade corrente: %s\n", setlocale(LC_ALL,NULL) );


	new.vendedorId = 1;

	int bissexto=0;
  	if (( new.data.ano % 4 == 0 && new.data.ano  % 100 != 0 ) || new.data.ano  % 400 == 0)
    	bissexto=1;
  	int flag_mes;
  	if(new.data.mes == 1 ||new.data.mes == 3 ||new.data.mes == 5 ||new.data.mes == 7 || new.data.mes == 8 || new.data.mes == 10 || new.data.mes == 12)
    	flag_mes=2;
  	else if (new.data.mes == 4 ||new.data.mes == 6 ||new.data.mes == 9 ||new.data.mes == 11)
    	flag_mes=1;
 	else
    	flag_mes=0;


    if (valor <= 0)	
    	alert_error(this_window,"Corriga o Valor!");
    else if (new.data.ano<=0)
   		alert_error(this_window,"Corriga o ano!");
    else if (new.data.mes <1  ||  new.data.mes > 12)
    	alert_error(this_window,"Corriga o mês!");
    else if ((new.data.dia<1 || new.data.dia>31 && flag_mes==2) || (new.data.dia<1 || new.data.dia>30 && flag_mes==1) || (new.data.dia<1 || new.data.dia>28 && flag_mes==0 && bissexto==1) || (new.data.dia<1 || new.data.dia>27 && flag_mes==0 && bissexto==0))
    	alert_error(this_window,"Corriga o dia!");
    else{
	    if(salvar_venda(new) >= 0){
	      alert_info(this_window, "Salvo com sucesso!");
	    }else{
	      alert_info(this_window, "Erro ao salvar!");
	    }
	    gtk_widget_destroy(GTK_WIDGET(this_window));
    }

	 

}

void open_new_vendas(){
<<<<<<< HEAD

	builder_venda = gtk_builder_new (); 
  	gtk_builder_add_from_file(builder_venda, UI_CADASTRO_VENDAS_FILE, NULL);
  	GObject *window_venda, *save_venda;
  	save_venda = gtk_builder_get_object(builder_venda, "btn_salvar");
  	window_venda = gtk_builder_get_object(builder_venda, "cadastro_vendas");
  	gtk_window_present (GTK_WINDOW(window_venda));
  	g_signal_connect(G_OBJECT(save_venda), "clicked", G_CALLBACK(btn_salvar_venda), (gpointer) window_venda);
=======
	builder_vendas = gtk_builder_new();
	gtk_builder_add_from_file(builder_vendas, UI_CADASTRO_VENDAS_FILE, NULL);
	window_vendas = gtk_builder_get_object(builder_vendas, "cadastro_vendas");
	btn_salvar = gtk_builder_get_object(builder_vendas, "btn_salvar");
	g_signal_connect(btn_salvar, "clicked", G_CALLBACK(btn_salvar_venda), (gpointer) window_vendas); 
>>>>>>> 0779fcb66b6051c51f2225141eedc3935f887bf9
}

void list_vendas(){
	
}

int salvar_venda(Venda venda){ /*Esta função recebe um venda e o escreve no arquivo */
	//Atualizando vetor de vendas
	/*int aux = (*quant_vendas);
	vendas[aux].id = venda.id;
	vendas[aux].vendedorId = venda.vendedorId;
	vendas[aux].data.dia = venda.data.dia;
	vendas[aux].data.mes = venda.data.mes;
	vendas[aux].data.ano = venda.data.ano;
	vendas[aux].valor = venda.valor;
	strcpy(vendas[aux].descricao,venda.descricao);
	*/
	//Atualizado quantidade de vendas
	venda.id = incr_venda();
	quantidade_vendas ++;

	int is_ok = -1;
	FILE * fp = fopen ("Vendas.txt","a");
	if(fp != NULL){
		is_ok=fprintf (fp,"%d %d %d %d %d %f %s\n",venda.id, venda.vendedorId, venda.data.dia, venda.data.mes, venda.data.ano,venda.valor,venda.descricao);
	}
	fclose(fp);

	return is_ok;
}

int incr_venda(){ /*Esta função incrementa o id da venda e o retorna */
  FILE * fp = fopen ("incr_venda.txt", "r");
  int incr;
  fscanf(fp,"%d",&incr);
  //printf ("%d\n",incr);
  incr++;
  freopen("incr_venda.txt", "w+",fp);
  fprintf (fp,"%d",incr);
  fclose(fp);
  return incr;
}