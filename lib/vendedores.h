#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "data.h"

#define VENDEDOR_FILE "Vendedores.txt"
#define UI_CADASTRO_VENDEDOR_FILE "ui/cadastro_vendedores.glade"
#define UI_RELATORIO_GERAL_FILE "ui/relatorio_mes_geral.glade"
#define UI_RELATORIO_VENDEDOR_MES_FILE "ui/relatorio_mes.glade"

GtkBuilder *builder_vendedor, *builder_relatorio_geral; 
GObject *txt_nome, *combo_sexo, *txt_cpf, *txt_dia, *txt_mes, *txt_ano, *txt_valor;
GObject *combo_mes, *tree_relatorio_geral, *buscar_mes, *txt_nome_auto, *tree_relatorio_meses;
GtkListStore *store;
GtkEntryCompletion *entry_comp;

struct Vendedor /* Essa estrutura define um vendedor*/
{
	int id;
	Data data_nasc;
	char nome[128], sexo[10], cpf[15];
};
typedef struct Vendedor Vendedor;

void btn_save_vendedor(GtkWidget* button, GtkWindow *this_window);
void open_new_vendedor();
void open_edit_vendedor();
void open_list_vendedor();
void delete_vendedor();
void relatorio_total_vendas_vendedor();
int incr_vendedor();
void open_relatorio_total_vendas_geral();
void btn_buscar_relatorio_geral();
void open_list_vendas_vendedor_mes();
void relatorio_total_vendas_vendedor_mes();
int salvar_vendedor(Vendedor vendedor);
