#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "data.h"

#define VENDA_FILE "Vendedores.txt"
#define UI_CADASTRO_VENDAS_FILE "ui/cadastro_vendas.glade"

GObject *window_vendas, *txt_vendedor, *txt_descricao, *txt_valor, *txt_data, *txt_mes, *txt_ano;
GtkBuilder *builder_venda; 
struct Venda /* Essa estrutura define uma venda */
{
	int id,vendedorId;
	Data data;
	float valor;
	char descricao[255];
};
typedef struct Venda Venda;

void btn_save_venda(GtkWidget* button, GtkWindow *this_window);
void open_new_vendas();
void list_vendas();
int salvar_venda(Venda venda);
int incr_venda();