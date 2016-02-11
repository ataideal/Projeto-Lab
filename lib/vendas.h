#include <stdio.h>
#include "data.h"

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