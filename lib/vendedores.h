#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "data.h"

#define VENDEDOR_FILE "Vendedores.txt"
#define UI_CADASTRO_VENDEDOR_FILE "ui/cadastro_vendedores.glade"
#define UI__FILE ""

GtkBuilder *builder_vendedor; 
GObject *txt_nome, *combo_sexo, *txt_cpf, *txt_dia, *txt_mes, *txt_ano, *txt_valor;

struct Vendedor /* Essa estrutura define um vendedor*/
{
	int id;
	Data data_nasc;
	char nome[50],sexo[10],cpf[15];
};
typedef struct Vendedor Vendedor;

void btn_save_vendedor(GtkWidget* button, GtkWindow *this_window);
void open_new_vendedor();
void open_edit_vendedor();
void open_list_vendedor();
void delete_vendedor();
void relatorio_total_vendas_vendedor();
int salvar_vendedor(Vendedor vendedor);