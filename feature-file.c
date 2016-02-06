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
	FILE *arquivo;
	arquivo = lerArquivo("Vendedores.txt");
	
	Vendedor vendedores[10];
	int quant_vendedores = lerVendedores(vendedores,arquivo);
	fclose(arquivo);
     
	return 0;
}

//---------------------------Funções--------------------------------//
FILE * lerArquivo (char path[]){ /* Esta função recebe como parametro a url do arquivo, faz a leitura do arquivo e retorna o ponteiro para função principal*/
	FILE *fp;
    	fp = fopen (path, "r");
    	if (fp == NULL) {
       		printf ("Houve um erro ao abrir o arquivo.\n");
       		return NULL;
    	}
    	//printf ("Arquivo lido com sucesso\n");
    	return fp;
}

int lerVendedores(Vendedor * vendedores,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendedores, e faz o parse de cada vendedor do arquivo para o vetor e retorna quantidade total de vendedores*/
	int i=0;
	while((fscanf(arquivo,"%d %d %s %s %s\n", &vendedores[i].id, &vendedores[i].idade, vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf))!=EOF )
			i++;
	return i;
}
//---------------------------Funções--------------------------------//