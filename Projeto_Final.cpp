#include<iostream>
#include<string.h>
#include<locale.h>
#include<windows.h>
#include "listasstr.h"


struct reg
{
	char nome[30];
	char tel[20];
	char nome_filme[30];
	char endereco[50];
	char status;
	//char tel_loc[30] = "(35)3292-7055";
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void gerararqtxt(FILE *);
void excluir(FILE *);
void relatorioord(FILE *);

int main()
{
	setlocale(LC_ALL,"");
	int op;
	FILE *arq;

	if ((arq = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados.dat", "wb+")) == NULL)
		{
			printf("\nFalha ao abrir o arquivo!\n");
			system("pause");
		}
	}

	do
	{
		system("CLS");
		printf("\n============ Locação de Filme ==========");
		printf("\n| 1.Opção de filmes                    |\n");
		printf("\n| 2.Consultar                          |\n");
		printf("\n| 3.Gerar Lista de Filmes Alugados     |\n");
		printf("\n| 4.Excluir                            |\n");
		printf("\n| 5. Relatorio Ordenado                |\n");
		printf("\n| 6. Sair				 |\n");
		printf("============== Filmes Locados: %d ======\n", tamanho(arq));
		
		printf("Opção: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1: //cadastrar novo contato
			cadastrar(arq);
			break;
		case 2: //consultar contato por código
			consultar(arq);
			break;
		case 3: //gera arquivo txt com todos os contatos
			gerararqtxt(arq);
			break;
		case 4:
			excluir(arq);
			break;
		case 5:
			relatorioord(arq);
			break;
		case 6: fclose(arq);
			
		}
	} while (op != 6);
}

void cadastrar(FILE *arq)
{ 
	reg contato; 
	char confirma;

	contato.status = ' ';
	
	fflush(stdin);
	setlocale(LC_ALL,"");
	printf("Seleção do filme: \n");
	printf("\nNúmero do registro: %d\n\n", tamanho(arq) +1);
	printf("Top 5 do mês \n\n");
	printf("Rei Leão \n");
	printf("Sherek\n");
	printf("As tranças de um careca \n");
	printf("Poeira em alto mar \n");
	printf("Robô copo 2  \n\n");
	printf("Nome Completo....: ");
	gets(contato.nome);
	printf("Telefone.........:");
	gets(contato.tel);
	printf("Nome do Filme....:");
	gets(contato.nome_filme);
	printf("Endereço.........:");
	gets(contato.endereco);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\n gravando ....\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
	system("pause");
}

void consultar(FILE *arq)
{ 
	reg contato; 
	setlocale(LC_ALL,"");
	contato.status = ' ';
	int nr; 
	printf("\nConsulta pelo número de registro do filme \n");
	printf("\nInforme o número de registro do filme....:");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr > 0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		printf("\nNome.........:%s", contato.nome);
		printf("\nTelefone.....:%s", contato.tel);
		printf("\nNome do filme:%s\n", contato.nome_filme);
		printf("\nStatus do Arquivo: %c\n", contato.status);
		
	}
	else
	{ 
		printf("\nNúmero de registro inválido!\n");
	}
	system("pause");
}

void excluir(FILE *arq)
{
	setlocale(LC_ALL,"");
	reg contato;
	char confirma;
	int nr;
	
	printf("\nInforme o código do registro para excluir\n");
	scanf("%d",&nr);
	printf("\n");
	printf("\n\n");
	if((nr<= tamanho(arq)) && (nr>0))
	{
		fseek(arq,(nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato,sizeof(reg), 1,arq);
		if(contato.status == ' ')
		{
			printf("\nNome.......:%s", contato.nome);
			printf("\nTelefone.......:%s", contato.tel);
			printf("\nNome do filme.......:%s", contato.nome_filme);
			printf("\nConfirma a exclusão: <s/n>\n");
			getchar();
			printf("\n");
			printf("\n\n");
			printf("\nConfirma a exclusão: <s/n>\n");
			scanf("%c", &confirma);
	 	
			if (toupper(confirma) == 'S')
			{
				//fflush(stdin);
				printf("\n excluindo ....\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';		
				fwrite(&contato, sizeof(reg), 1, arq);

			}
			
			else
			{
				printf("\n");
			}
		}

			else
			{
				printf("Registro Inexistente!\n");
			}

	}
	
	else
	{
		printf("\nNúmero de registro inválido!\n");
	}
	system("pause");
	
}

void gerararqtxt(FILE *arq)
{
	setlocale(LC_ALL,"");
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomearq);
	strcat(nomearq, ".txt");
	
	FILE *arqtxt = fopen(nomearq, "w");
	
	if (!arqtxt)
	{
		printf("\nNão foi possível criar esse arquivo!\n");
		system("pause");
	}

	fprintf(arqtxt, "Nome                Filme                Tel                Status\n");
	fprintf(arqtxt, "==================================================================\n");
	int nr; 
	reg contato;
	for (nr = 0; nr < tamanho(arq); nr++)
	{
		fseek(arq, nr * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		fprintf(arqtxt, "%-20s%-20s%-20s %c\n", contato.nome, contato.nome_filme, contato.tel, contato.status);
	}
		fprintf(arqtxt,"==============================================================\n");
		fclose(arqtxt);
		printf("Relatorio gerado com sucesso.\n");
		system("PAUSE");
}

void relatorioord(FILE *arq)
{
	Lista L;
	Linit(&L);
	int nr;
	reg contato;
	Elem X;
	for (nr=0;nr<tamanho(arq);nr++)
	{
		fseek(arq,nr*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		strcpy(X.nome,contato.nome);
		X.nr=nr;
		Lins(&L,X);
	}
	FILE *arqtxt=fopen("RelatorioOrdenado.txt","w");

	fprintf(arqtxt,"Relatorio de Cadastros Ordenados\n\n");
	fprintf(arqtxt, "Nome                Filme                Tel                Status\n");
	fprintf(arqtxt, "==================================================================\n");
	int c;
	for (c=0;c<tamanho(arq);c++)
	{
		nr=L.M[c].nr;
		fseek(arq,nr*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		fprintf(arqtxt, "%-20s%-20s%-20s %c\n", contato.nome, contato.nome_filme, contato.tel, contato.status);
	}
		fprintf(arqtxt,"==============================================================\n");
		fclose(arqtxt);
		printf("Relatorio gerado com sucesso.\n");
		system("PAUSE");

}


int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}



