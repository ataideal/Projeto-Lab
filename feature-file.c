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
int lerVendas(Venda * vendas,FILE * arquivo);
int incr_vendedor();
void salvarVendedor(Vendedor vendedor,Vendedor * vendedores,int * quant_vendedores);
int incr_vendedor();
void salvarVenda(Venda venda,Venda * vendas,int * quant_vendas);
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

	int i;
	for(i = 0;i<quant_vendedores;i++){
		printf ("Vendedores id:%d\n",vendedores[i].id);
		printf ("Nome: %s\nIdade: %d\nSexo: %s\nCpf:%s\n",vendedores[i].nome,vendedores[i].idade,vendedores[i].sexo,vendedores[i].cpf);
	}

	for(i = 0;i<quant_vendas;i++){
		printf ("Vendas id:%d\n",vendas[i].id);
		printf ("Vendedor id: %d\nData: %d/%d/%d\nValor: %f\nDescricao: %s\n",vendas[i].vendedorId,vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
	}
	
    /* ----- MENU ----*/
	int opMenu;
    do
    {
    	system ("cls");
        printf ("Digite a opcao desejada:\n");
        printf ("1 - Cadastrar vendedor\n");
        printf ("2 - Cadastrar venda\n");
        printf ("3 - Consultar as vendas de um funcionario em um determinado mes\n");
        printf ("4 - Consultar o total das vendas de um determinado vendedor\n");
        printf ("5 - Mostrar o numero do vendedor que mais vendeu em um determinado mes\n");
        printf ("6 - Mostrar o numero do mes com mais vendas\n");
        printf ("7 - Listar Vendedores\n");
        printf ("8 - Listar Vendas\n");
        printf ("0 - Finalizar o programa\n");

        printf ("Opcao:  ");
        scanf ("%d", &opMenu);
        getchar();
        system ("cls");

        int i=0;
        int j=0;
        int vendedorId;
        Vendedor vend; //Struct - Vendedor , vend variavel
        Venda venda;
        switch (opMenu){
            case 0:
                printf ("Saindo do menu.");
                break;
            case 1:
                printf ("---Cadastre o vendedor---\n");
                printf ("Digite o nome do vendedor: ");
                scanf (" %[^\n]",vend.nome);
                printf ("Digite a idade: ");
                scanf ("%d",&vend.idade);
                getchar();
                printf ("Digite o sexo: ");
                scanf ("%s",vend.sexo);
                printf ("Digite o cpf: ");
                scanf ("%s",vend.cpf);
                vend.id = incr_vendedor();
                salvarVendedor(vend,vendedores,&quant_vendedores);
                getch();
                break;
            case 2:
                printf ("---Cadastre a venda---\n");

				/* --- Exemplo de como salvar uma venda --- */
				printf ("Digite a data da venda (dd/mm/aaaa): ");
				scanf ("%d/%d/%d",&venda.data.dia,&venda.data.mes,&venda.data.ano);
				printf ("Digite o valor da venda: ");
				scanf ("%f",&venda.valor);
				printf ("Digite o id do vendedor: ");
				scanf ("%d",&venda.vendedorId);
				getchar();
				printf ("Digite a descricao da venda: ");
				scanf ("%[^\n]",venda.descricao);
				venda.id = incr_venda();
				salvarVenda(venda,vendas,&quant_vendas);
				getch();
				/*------------------------------------------*/
                break;
            case 3:
                printf ("---Consulta das vendas de um vendedor num determinado mes---\n");
                printf ("Digite o mes: ");
                int mes;
                scanf ("%d",&mes);
                printf ("Digite o id do vendedor: ");
                scanf("%d",&vendedorId);
                system("cls");
                printf ("---Vendas do vendedor %d no mes %d---\n",vendedorId,mes);
                j=0;
                for (i=0;i<quant_vendas;i++){
                	if (vendas[i].vendedorId == vendedorId && vendas[i].data.mes == mes){
                		printf ("Venda id: %d\nData: %d/%d/%d\nValor: %f\nDescricao: %s\n",vendas[i].id,vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
                		j=1;
                	}
                }
                if (j==0)
                	printf ("Este vendedor nao teve vendas nesse determinado mes!");
                getch();
                break;
            case 4:
                printf ("---Consulte o total de vendas de um vendedor---\n");
                printf ("Digite o id do vendedor: ");
                scanf ("%d",&vendedorId);
                system("cls");
                printf ("---Vendas do vendedor %d ---\n",vendedorId);
                j=0;
                for (i=0;i<quant_vendas;i++){
                	if (vendas[i].vendedorId == vendedorId){
                		printf ("Venda id: %d\nData: %d/%d/%d\nValor: %f\nDescricao: %s\n",vendas[i].id,vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
                		j=1;
                	}
                }
                if (j==0)
                	printf ("Este vendedor nao teve vendas!");
                getch();
                break;
            case 5:
                break;
            case 6:
            	printf ("Numero do mês com mais vendas:");
                break;
			case 7:
				printf ("Lista de Vendedores - %d\n",quant_vendedores);
				for(i = 0;i<quant_vendedores;i++){
					printf ("Vendedores id: %d\n",vendedores[i].id);
					printf ("Nome: %s\nIdade: %d\nSexo: %s\nCpf:%s\n",vendedores[i].nome,vendedores[i].idade,vendedores[i].sexo,vendedores[i].cpf);
					printf ("\n");
				}
				getch();
	            break;
            case 8:
                printf ("Lista de Vendas - %d\n",quant_vendas);
                for(i = 0;i<quant_vendas;i++){
					printf ("Vendas id:%d\n",vendas[i].id);
					printf ("Vendedor id: %d\nData: %d/%d/%d\nValor: %f\nDescricao: %s\n",vendas[i].vendedorId,vendas[i].data.dia,vendas[i].data.mes,vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
					printf ("\n");
                }
                getch();
                break;
            default:
                printf ("Opção inválida!");
        }
        printf ("\n");
    } while (opMenu!=0);
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
	while((fscanf(arquivo,"%d %d %s %s%[^\n]\n", &vendedores[i].id, &vendedores[i].idade ,vendedores[i].sexo,vendedores[i].cpf, vendedores[i].nome))!=EOF ){
			//fgets(vendedores[i].nome,50,arquivo);
			printf ("%d %d %s %s %s\n",vendedores[i].id, vendedores[i].idade, vendedores[i].nome,vendedores[i].sexo,vendedores[i].cpf);
			i++;
	}
	return i;
}

int lerVendas(Venda * vendas,FILE * arquivo){ /* Esta função recebe o arquivo e o vetor de vendas, faz o parse de cada venda do arquivo para o vetor, e retorna quantidade total de vendas*/
	int i=0;
	while((fscanf(arquivo,"%d %d %d %d %d %f%[^\n]\n", &vendas[i].id, &vendas[i].vendedorId, &vendas[i].data.dia,&vendas[i].data.mes,&vendas[i].data.ano,&vendas[i].valor,vendas[i].descricao))!=EOF ){
		//fgets (vendas[i].descricao,255,arquivo);
		printf ("%d %d %d %d %d %f %s\n", vendas[i].id, vendas[i].vendedorId, vendas[i].data.dia, vendas[i].data.mes, vendas[i].data.ano,vendas[i].valor,vendas[i].descricao);
		i++;
	}
	return i;
}

int incr_vendedor(){ /*Esta função incrementa o id do vendedor e o retorna */
	FILE * fp = fopen ("incr_vendedor.txt", "r");
	int incr;
	fscanf(fp,"%d",&incr);
	//printf ("%d\n",incr);
	incr++;
	freopen("incr_vendedor.txt", "w+",fp);
	fprintf (fp,"%d",incr);
	fclose(fp);
	return incr;
}

void salvarVendedor(Vendedor vendedor,Vendedor * vendedores,int * quant_vendedores){ /*Esta função recebe um vendedor e o escreve no arquivo */
	//Atualizando vetor de vendedores
	int aux = (*quant_vendedores);
	vendedores[aux].id = vendedor.id;
	vendedores[aux].idade = vendedor.idade;
	strcpy(vendedores[aux].sexo,vendedor.sexo);
	strcpy(vendedores[aux].cpf,vendedor.cpf);
	strcpy(vendedores[aux].nome,vendedor.nome);
	//Atualizado quantidade de vendedores
	(*quant_vendedores) = (*quant_vendedores) + 1;
	//Salvando no arquivo
	FILE * fp = fopen ("Vendedores.txt","a");
	int flag=fprintf (fp,"%d %d %s %s %s\n",vendedor.id, vendedor.idade,vendedor.sexo,vendedor.cpf,vendedor.nome);
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
	//printf ("%d\n",incr);
	incr++;
	freopen("incr_venda.txt", "w+",fp);
	fprintf (fp,"%d",incr);
	fclose(fp);
	return incr;
}

void salvarVenda(Venda venda,Venda * vendas,int * quant_vendas){ /*Esta função recebe um venda e o escreve no arquivo */
	//Atualizando vetor de vendas
	int aux = (*quant_vendas);
	vendas[aux].id = venda.id;
	vendas[aux].vendedorId = venda.vendedorId;
	vendas[aux].data.dia = venda.data.dia;
	vendas[aux].data.mes = venda.data.mes;
	vendas[aux].data.ano = venda.data.ano;
	vendas[aux].valor = venda.valor;
	strcpy(vendas[aux].descricao,venda.descricao);
	//Atualizado quantidade de vendas
	(*quant_vendas) = (*quant_vendas) + 1;

	FILE * fp = fopen ("Vendas.txt","a");
	int flag=fprintf (fp,"%d %d %d %d %d %f %s\n",venda.id, venda.vendedorId, venda.data.dia, venda.data.mes, venda.data.ano,venda.valor,venda.descricao);
	fclose(fp);

	if (flag<0)
		printf ("Erro ao salvar!\n");
	else{
		printf ("Venda cadastrado com sucesso!\n");
	}
}

//---------------------------Funções--------------------------------//
