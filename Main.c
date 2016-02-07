#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "lib/util.h"

GtkWidget *window, *button;

//--------------------------Estruturas-------------------------------//
struct Data /* Essa estrutura define data */
{
	int dia,mes,ano;
};

typedef struct Data Data;

struct Vendedor /* Essa estrutura define um vendedor*/
{
	int id,idade;
	char nome[50],sexo[10],cpf[15];
};
typedef struct Vendedor Vendedor;

struct Venda /* Essa estrutura define uma venda */
{
	int id,vendedorId;
	Data data;
	float valor;
	char descricao[255];
};
typedef struct Venda Venda;
//--------------------------Estruturas-------------------------------//

//-------------------Protótipo das Funções---------------------------//
FILE * lerArquivo (char path[]);
int lerVendedores(Vendedor * vendedores,FILE * arquivo);
//-------------------Protótipo das Funções---------------------------//

void button_click(GtkWidget* button, GtkWindow *window){
  alert_info(window, "teste");
  char message_erro[300];
  sprintf(message_erro, "Um mensagem de teste: %d", 1290);
  alert_error(window, message_erro);
}

int main(int argc, char *argv[]){

  gtk_init (&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size((gpointer) window, 800, 400);
  g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), (gpointer) window);
	
  button = gtk_button_new_with_mnemonic("Alert");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_click), (gpointer) window);

  gtk_container_add(GTK_CONTAINER(window), button);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}