#include "vendas.h"
#include <locale.h>

extern int quantidade_vendas;
extern Venda vendas[300];
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


	//printf ("VALOR CHAR: %s\nVALOR FLOAT: %f\n", (char*)valor,new.valor);	
	setlocale(LC_ALL,"C");
	//printf("\n****** Verificando a localidade corrente ********\n\n");
 	//printf ("Localidade corrente: %s\n", setlocale(LC_ALL,NULL) );


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
	builder_venda = gtk_builder_new (); 
  	gtk_builder_add_from_file(builder_venda, UI_CADASTRO_VENDAS_FILE, NULL);
  	GObject *window_vendas, *save_venda;
  	save_venda = gtk_builder_get_object(builder_venda, "btn_salvar");
  	window_vendas = gtk_builder_get_object(builder_venda, "cadastro_venda");
  	gtk_window_present (GTK_WINDOW(window_vendas));
  	g_signal_connect(G_OBJECT(save_venda), "clicked", G_CALLBACK(btn_salvar_venda), (gpointer) window_vendas);
}

void open_mes_com_mais_vendas(GtkWidget *button, GtkWindow *this_window){
	
	GtkTreeIter iter;

	builder_relatorio_meses = gtk_builder_new (); 
	gtk_builder_add_from_file(builder_relatorio_meses, UI_RELATORIO_MESES_VENDAS_FILE, NULL);
	GObject *window_relatorio_meses;
	window_relatorio_meses = gtk_builder_get_object(builder_relatorio_meses, "window1");
	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
	tree_relatorio_meses = gtk_builder_get_object(builder_relatorio_meses, "treeview1");
	label = gtk_builder_get_object(builder_relatorio_meses, "label1");

	int mes_vendas[13],maior_mes=0, i, j;
    char mes[13][20] = {"", "JANEIRO", "FEVEREIRO", "MARÇO", "ABRIL", "MAIO", "JUNHO", "JULHO", "AGOSTO", "SETEMBRO", "OUTUBRO", "NOVEMBRO", "DEZEMBRO"};

    for(i = 1; i <= 12; i++){
    	mes_vendas[i] = 0;
    }

    for (j=0;j<quantidade_vendas;j++){
    	mes_vendas[vendas[j].data.mes]++;
    }
    for (i=1;i<=12;i++){
    	if(mes_vendas[i]>maior_mes)
    		maior_mes = mes_vendas[i];
    }
    char msg[100];
    for (i=1;i<=12;i++){
    	if(mes_vendas[i] == maior_mes){
    		sprintf(msg, "Mês com mais vendas foi: %s com %d vendas.", mes[i], mes_vendas[i]);
    		gtk_label_set_text(GTK_LABEL(label), msg);
    	}
    		
    	gtk_list_store_append(store, &iter);
    	gtk_list_store_set(store, &iter, 0, mes[i], 1, mes_vendas[i], -1);
    }


    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_relatorio_meses), GTK_TREE_MODEL(store));

    gtk_window_present(GTK_WINDOW(window_relatorio_meses));
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