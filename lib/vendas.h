#include <stdio.h>
#include "data.h"

#define UI_CADASTRO_VENDAS_FILE "ui/cadastro_vendas.glade"

GObject *window_vendas, *txt_vendedor, *txt_descricao, *txt_data, *txt_mes, *txt_ano;

struct Venda /* Essa estrutura define uma venda */
{
	int id,vendedorId;
	Data data;
	float valor;
	char descricao[255];
};
typedef struct Venda Venda;

void open_new_vendas();
void list_vendas();