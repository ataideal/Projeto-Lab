#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "lib/util.h"
#include "lib/vendedores.h"
#include "lib/vendas.h"

#define UI_FILE "ui/principal.glade" 

int incr_venda();
int incr_vendedor();

int lerVendedores(Vendedor * vendedores,FILE * arquivo);
int lerVendas(Venda * vendas,FILE * arquivo);

int quantidade_vendedores;

GtkBuilder *builder;
GObject *window, *btn_cadastro_vendedor, *btn_cadastro_vendedor2, *btn_cadastro_vendas, *btn_cadastro_vendedor3;

int main(int argc, char *argv[]){
  
  quantidade_vendedores = 0;
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


int ler_vendedores(Vendedor * vendedores,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendedores, faz o parse de cada vendedor do arquivo para o vetor, e retorna quantidade total de vendedores*/
  int i=0;
  while((fscanf(arquivo,"%d %d %d %d %s %s%[^\n]\n", &vendedores[i].id, &vendedores[i].data_nasc.dia, &vendedores[i].data_nasc.mes, &vendedores[i].data_nasc.ano ,vendedores[i].sexo,vendedores[i].cpf, vendedores[i].nome))!=EOF ){
      //fgets(vendedores[i].nome,50,arquivo);
      printf ("%d %d %d %d %s %s %s\n",vendedores[i].id, &vendedores[i].data_nasc.dia, &vendedores[i].data_nasc.mes, vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf);
      i++;
  }
  return i;
}

int ler_vendas(Venda * vendas,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendas, faz o parse de cada venda do arquivo para o vetor, e retorna quantidade total de vendas*/
  int i=0;
  while((fscanf(arquivo,"%d %d %d %d %d %f%[^\n]\n", &vendas[i].id, &vendas[i].vendedorId, &vendas[i].data.dia,&vendas[i].data.mes,&vendas[i].data.ano,&vendas[i].valor,vendas[i].descricao))!=EOF ){
    //fgets (vendas[i].descricao,255,arquivo);
    printf ("%d %d %d %d %d %f %s\n", vendas[i].id, vendas[i].vendedorId, vendas[i].data.dia, vendas[i].data.mes, vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
    i++;
  }
  return i;
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