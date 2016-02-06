#include <stdio.h>
#include <string.h>
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

int main (){
	


	return 0;
}