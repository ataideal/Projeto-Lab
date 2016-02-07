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
int incr_vendedor();
void salvarVendedor(Vendedor vendedor);
int incr_vendedor();
void salvarVenda(Venda venda);
//-------------------Protótipo das Funções---------------------------//

int main (){
	FILE *arquivo;
	/* --- Usando arquivo para ler os vendedores --- */
	arquivo = lerArquivo("Vendedores.txt");
	Vendedor vendedores[30];
	int quant_vendedores = 0;
	quant_vendedores = lerVendedores(vendedores,arquivo);
	fclose(arquivo);
	/*----------------------------------------------*/

	/* --- Usando arquivo para ler as vendas --- */
	arquivo = lerArquivo("Vendas.txt");
	Venda vendas[30];
	int quant_vendas = 0;
	quant_vendas = lerVendas(vendas,arquivo);
	fclose(arquivo);
	/*-------------------------------------------*/
    /* ----- MENU ----*/

    int opMenu;


    do
    {
        printf ("Digite a opção desejada:\n");
        printf ("1 - Cadastrar vendedor.\n");
        printf ("2 - Cadastrar venda.\n");
        printf ("3 - Consultar as vendas de um funcionário em um determinado mês\n");
        printf ("4 - Consultar o total das vendas de um determinado vendedor\n");
        printf ("5 - Mostrar o número do vendedor que mais vendeu em um determinado mês\n");
        printf ("6 - Mostrar o número do mês com mais vendas\n");
        printf ("0 - Finalizar o programa");

        printf ("Opção:  ");
        scanf ("%d", &opMenu);

        system ("cls");

        int i;
        Vendedor vend; //Struct - Vendedor , vend variavel

        switch (opMenu){


            case 0:
                printf ("Saindo do menu.");
                break;
            case 1:

                printf ("Cadastre o vendedor:");
                printf ("Digite o nome do vendedor: ");
                scanf ("%s",vend.nome); //vend variavel, nome dentro da struct
                printf ("Digite a idade: ");
                scanf ("%d",&vend.idade);
                vend.id = incr_vendedor();
                salvarVendedor(vend);
                break;
            case 2:
                printf ("Cadastre a venda:");
                break;
            case 3:
                printf ("Consulta das vendas do funcionário desse mês.");
                break;
            case 4:
                printf ("Consulte o total de vendas de um vendedor.");
                break;
            case 5:
                break;
            case 6:

                printf ("Lista de Vendas ");
                for (i=0;i<quant_vendas;i++){
                    printf ("Venda %d",i+1);
                    printf ("Id da venda %d",vendas[i].id);
                    printf ("Data da venda %s/%s/%s",vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano);

                }
                printf ("Numero do mês com mais vendas:");
                break;
            default:
                printf ("Opção inválida!");
            }
        printf ("\n");
    } while (opMenu!=0);



    /*-------------------------------------------*/

    /* --- Exemplo de como salvar um vendedor --- */
    /*
	vend.idade = 15;
	strcpy(vend.nome,"Ataide Neto");
	strcpy(vend.sexo,"Masc");
	strcpy(vend.cpf,"102030");
    */
	/*--------------------------------------------*/

	/* --- Exemplo de como salvar uma venda --- */
	Venda venda;
	venda.id = incr_venda();
	venda.vendedorId = 1;
	strcpy(venda.data.dia,"01");
	strcpy(venda.data.mes,"02");
	strcpy(venda.data.mes,"2015");
	venda.valor = 200.5;
	strcpy(venda.descricao,"nois vende ou num vende clã?");
	salvarVenda(venda);
	/*------------------------------------------*/

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
	while((fscanf(arquivo,"%d %d %s %s\n", &vendedores[i].id, &vendedores[i].idade ,vendedores[i].sexo,vendedores[i].cpf))!=EOF ){
			fgets(vendedores[i].nome,50,arquivo);
			//printf ("%d %d %s %s %s",vendedores[i].id, vendedores[i].idade, vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf);
			i++;
	}
	return i;
}

int lerVendas(Venda * vendas,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendas, faz o parse de cada venda do arquivo para o vetor, e retorna quantidade total de vendas*/
	int i=0;
	while((fscanf(arquivo,"%d %d %s %s %s %f\n", &vendas[i].id, &vendas[i].vendedorId, vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano,&vendas[i].valor))!=EOF ){
		fgets (vendas[i].descricao,255,arquivo);
		//printf ("%d %d %s %s %s %f %s", vendas[i].id, vendas[i].vendedorId, vendas[i].data.dia, vendas[i].data.mes, vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
		i++;
	}

	return i;
}

int incr_vendedor(){ /*Esta função incrementa o id do vendedor e o retorna */
	FILE * fp = fopen ("incr_vendedor.txt", "r");
	int incr;
	fscanf(fp,"%d",&incr);
	printf ("%d\n",incr);
	incr++;
	freopen("incr_vendedor.txt", "w+",fp);
	fprintf (fp,"%d",incr);
	fclose(fp);
	return incr;
}

void salvarVendedor(Vendedor vendedor){ /*Esta função recebe um vendedor e o escreve no arquivo */
	FILE * fp = fopen ("Vendedores.txt","a");
	int flag=fprintf (fp,"\n%d %d %s %s\n%s",vendedor.id, vendedor.idade,vendedor.sexo,vendedor.cpf,vendedor.nome);
	fclose(fp);

	if (flag<0)
		printf ("Erro ao salvar!\n");
	else
		printf ("Vendedor cadastrado com sucesso!\n");

}

int incr_venda(){ /*Esta função incrementa o id da venda e o retorna */
	FILE * fp = fopen ("incr_venda.txt", "r");
	int incr;
	fscanf(fp,"%d",&incr);
	printf ("%d\n",incr);
	incr++;
	freopen("incr_venda.txt", "w+",fp);
	fprintf (fp,"%d",incr);
	fclose(fp);
	return incr;
}

void salvarVenda(Venda venda){ /*Esta função recebe um venda e o escreve no arquivo */
	FILE * fp = fopen ("Vendas.txt","a");
	int flag=fprintf (fp,"\n%d %d %s %s %s %f\n%s",venda.id, venda.vendedorId, venda.data.dia, venda.data.mes, venda.data.ano,venda.valor,venda.descricao);
	fclose(fp);

	if (flag<0)
		printf ("Erro ao salvar!\n");
	else
		printf ("Venda cadastrado com sucesso!\n");

}
//---------------------------Funções--------------------------------//
