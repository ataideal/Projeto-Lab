#include <stdio.h>
#include <string.h>
//--------------------------Estruturas-------------------------------//
struct Data /* Essa estrutura define data */
{
	char dia[3],mes[3],ano[5];
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
int lerVendas(Venda * vendas,FILE * arquivo);
//-------------------Protótipo das Funções---------------------------//

int main (){
	FILE *arquivo;
	/* --- Usando arquivo para ler os vendedores --- */
	arquivo = lerArquivo("Vendedores.txt");
	Vendedor vendedores[10];
	int quant_vendedores = lerVendedores(vendedores,arquivo);
	fclose(arquivo);
	/*----------------------------------------------*/

	/* --- Usando arquivo para ler as vendas --- */
	arquivo = lerArquivo("Vendas.txt");
	Venda vendas[10];
	int quant_vendas = lerVendas(vendas,arquivo);
	fclose(arquivo);
	/*-------------------------------------------*/
     

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

int lerVendedores(Vendedor * vendedores,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendedores, faz o parse de cada vendedor do arquivo para o vetor, e retorna quantidade total de vendedores*/
	int i=0;
	while((fscanf(arquivo,"%d %d %s %s %s\n", &vendedores[i].id, &vendedores[i].idade, vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf))!=EOF ){
			//printf ("%d %d %s %s %s",vendedores[i].id, vendedores[i].idade, vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf);
			i++;
	}
	return i;
}

int lerVendas(Venda * vendas,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendas, faz o parse de cada venda do arquivo para o vetor, e retorna quantidade total de vendas*/
	int i=0;
	//fscanf(arquivo,"%d %d %s %s %s\n", &vendas[i].id, &vendas[i].vendedorId, vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano);
	while((fscanf(arquivo,"%d %d %s %s %s %f\n", &vendas[i].id, &vendas[i].vendedorId, vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano,&vendas[i].valor))!=EOF ){
		fgets (vendas[i].descricao,255,arquivo);
		//printf ("%d %d %s %s %s %f %s", vendas[i].id, vendas[i].vendedorId, vendas[i].data.dia, vendas[i].data.mes, vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
		i++;
	}
			
	return i;
}
//---------------------------Funções--------------------------------//