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

int ler_vendedores(FILE * arquivo);
int ler_vendas(FILE * arquivo);

FILE * ler_arquivo (char path[]);

int max_vendas = 1;

int quantidade_vendedores, quantidade_vendas;

Vendedor vendedores[10];
Venda * vendas;

GtkBuilder *builder;
GObject *window, *btn_cadastro_vendedor, *btn_cadastro_vendedor2, *btn_cadastro_vendas, *btn_cadastro_vendedor3;

int main(int argc, char *argv[]){

  GObject *btn_menu_item_cadastro_vendedor, *btn_menu_item_cadastro_vendas, *btn_sair, *btn_menu_mes_vendas, *btn_menu_mais_vendeu, *btn_menu_vendas_mes;

  vendas = (Venda*)malloc(sizeof(Venda)*max_vendas);
  quantidade_vendas = ler_vendas(ler_arquivo(VENDAS_FILE));
  quantidade_vendedores = ler_vendedores(ler_arquivo(VENDEDOR_FILE));

  gtk_init (&argc, &argv);

  

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, UI_FILE, NULL);

  window = gtk_builder_get_object(builder, "window_principal");

  gtk_window_set_default_size((gpointer) GTK_WINDOW(window), 500, 400);
  gtk_window_set_title (GTK_WINDOW(window), "Sistema de Vendas");  
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

  g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), (gpointer) window);
	
  btn_menu_item_cadastro_vendedor = gtk_builder_get_object(builder, "item_cadastrar_vendedor");
  g_signal_connect(G_OBJECT(btn_menu_item_cadastro_vendedor), "activate", G_CALLBACK(open_new_vendedor), (gpointer) window);

  btn_menu_item_cadastro_vendas = gtk_builder_get_object(builder, "item_cadastro_vendas");
  g_signal_connect(G_OBJECT(btn_menu_item_cadastro_vendas), "activate", G_CALLBACK(open_new_vendedor), (gpointer) window);

  btn_menu_mes_vendas = gtk_builder_get_object(builder, "item_mes_vendas");
  g_signal_connect(G_OBJECT(btn_menu_mes_vendas), "activate", G_CALLBACK(open_mes_com_mais_vendas), (gpointer) window);

  btn_menu_mais_vendeu = gtk_builder_get_object(builder, "item_mais_vendeu");
  g_signal_connect(G_OBJECT(btn_menu_mais_vendeu), "activate", G_CALLBACK(open_relatorio_total_vendas_geral), (gpointer) window);//mudar aqui

  btn_menu_vendas_mes = gtk_builder_get_object(builder, "item_vendas");
  g_signal_connect(G_OBJECT(btn_menu_vendas_mes), "activate", G_CALLBACK(open_list_vendas_vendedor_mes), (gpointer) window);//mudar aqui

  btn_sair = gtk_builder_get_object(builder, "imagemenuitem5");
  g_signal_connect(G_OBJECT(btn_sair), "activate", G_CALLBACK(gtk_main_quit), (gpointer) window);

  btn_cadastro_vendedor = gtk_builder_get_object(builder, "btn_cadastro_vendedor");
  g_signal_connect(G_OBJECT(btn_cadastro_vendedor), "clicked", G_CALLBACK(open_new_vendedor), (gpointer) window);

  btn_cadastro_vendas = gtk_builder_get_object(builder, "btn_cadastro_vendas");
  g_signal_connect(G_OBJECT(btn_cadastro_vendas), "clicked", G_CALLBACK(open_new_vendas), (gpointer) window);

  btn_cadastro_vendedor2 = gtk_builder_get_object(builder, "btn_cadastro_vendedor2");
  g_signal_connect(G_OBJECT(btn_cadastro_vendedor2), "clicked", G_CALLBACK(open_mes_com_mais_vendas), (gpointer) window);

  btn_cadastro_vendedor3 = gtk_builder_get_object(builder, "btn_cadastro_vendedor3");
  g_signal_connect(G_OBJECT(btn_cadastro_vendedor3), "clicked", G_CALLBACK(open_list_vendas_vendedor_mes), (gpointer) window);

  gtk_window_present(GTK_WINDOW(window));

  gtk_main();

  return 0;
}

FILE * ler_arquivo (char path[]){ /* Esta função recebe como parametro a url do arquivo, faz a leitura do arquivo e retorna o ponteiro para função principal*/
  FILE *fp;
      fp = fopen (path, "r");
      if (fp == NULL) {
          printf ("Houve um erro ao abrir o arquivo.\n");
          return NULL;
      }
      //printf ("Arquivo lido com sucesso\n");
      return fp;
}


int ler_vendedores(FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendedores, faz o parse de cada vendedor do arquivo para o vetor, e retorna quantidade total de vendedores*/
  int i=0;
  printf ("Vendedores:\n");
  while((fscanf(arquivo,"%d %d %d %d %s %s %[^\n]", &vendedores[i].id, &vendedores[i].data_nasc.dia, &vendedores[i].data_nasc.mes, &vendedores[i].data_nasc.ano ,vendedores[i].sexo,vendedores[i].cpf, vendedores[i].nome))!=EOF ){
      //fgets(vendedores[i].nome,50,arquivo);
      printf ("%d %d %d %d %s %s %s\n",vendedores[i].id, vendedores[i].data_nasc.dia, vendedores[i].data_nasc.mes, vendedores[i].data_nasc.ano,vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf);
      i++;
  }
  return i;
}

int ler_vendas(FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendas, faz o parse de cada venda do arquivo para o vetor, e retorna quantidade total de vendas*/
  int i=0;
  printf ("Vendas:\n");
  while((fscanf(arquivo,"%d %d %d %d %d %f %[^\n]", &vendas[i].id, &vendas[i].vendedorId, &vendas[i].data.dia,&vendas[i].data.mes,&vendas[i].data.ano,&vendas[i].valor,vendas[i].descricao))!=EOF ){
    //fgets (vendas[i].descricao,255,arquivo);
    printf ("%d %d %d %d %d %f %s\n", vendas[i].id, vendas[i].vendedorId, vendas[i].data.dia, vendas[i].data.mes, vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
    i++;

    while(i >= max_vendas){
      max_vendas+=1;
      vendas = (Venda*)realloc(vendas,sizeof(Venda)*max_vendas);
    }
  }
  return i;
}

