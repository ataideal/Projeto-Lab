#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "data.h"

#define VENDEDOR_FILE "Vendedores.txt"
#define UI_CADASTRO_VENDEDOR_FILE "ui/cadastro_vendedores.glade"
#define UI_RELATORIO_GERAL_FILE "ui/relatorio_mes_geral.glade"

GtkBuilder *builder_vendedor, *builder_relatorio_geral; 
GObject *txt_nome, *combo_sexo, *txt_cpf, *txt_dia, *txt_mes, *txt_ano, *txt_valor;
GObject *combo_mes, *tree_relatorio_geral;
GtkListStore *store;

struct Vendedor /* Essa estrutura define um vendedor*/
{
	int id;
	Data data_nasc;
	char nome[50], sexo[10], cpf[15];
};
typedef struct Vendedor Vendedor;

void btn_save_vendedor(GtkWidget* button, GtkWindow *this_window);
void open_new_vendedor();
void open_edit_vendedor();
void open_list_vendedor();
void delete_vendedor();
void relatorio_total_vendas_vendedor();
<<<<<<< HEAD
int salvar_vendedor(Vendedor vendedor);
int incr_vendedor();
=======
void open_relatorio_total_vendas_geral();
void btn_buscar_relatorio_geral();
int salvar_vendedor(Vendedor vendedor);
>>>>>>> 0779fcb66b6051c51f2225141eedc3935f887bf9
