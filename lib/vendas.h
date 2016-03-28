#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "data.h"

#define VENDAS_FILE "Vendas.txt"
#define UI_CADASTRO_VENDAS_FILE "ui/cadastro_venda.glade"
#define UI_RELATORIO_MESES_VENDAS_FILE "ui/relatorio_meses_vendas.glade"
#define UI_LIST_VENDAS_FILE "ui/lista_vendas.glade"

GObject *window_vendas, *txt_vendedor, *txt_descricao, *txt_valor, *txt_data, *txt_mes, *txt_ano, *tree_relatorio_meses, *label,*txt_nome_auto;
GtkBuilder *builder_venda, *builder_relatorio_meses; 
GtkListStore *store;
GtkEntryCompletion *entry_comp;

struct Venda /* Essa estrutura define uma venda */
{
	int id, vendedorId;
	Data data;
	float valor;
	char descricao[255];
};
typedef struct Venda Venda;

void btn_salvar_venda(GtkWidget* button, GtkWindow *this_window);
void open_new_vendas();
void open_mes_com_mais_vendas();
void open_list_vendas();
int salvar_venda(Venda venda);
int incr_venda();
