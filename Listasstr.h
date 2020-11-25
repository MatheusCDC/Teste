#include <string.h>
#define TAM 8

typedef struct
{
	char nome[30];
	int nr;
}Elem;

typedef struct
{
	Elem M[TAM];
	int Fim;	
} Lista;

void Linit(Lista *L)
{
	L->Fim=0;
}

void Lins(Lista *L, Elem X)
{
	if (L->Fim<TAM) //a lista não está cheia
	{
		int i=L->Fim;
		
		while (i>0 and strcmp(X.nome,L->M[i-1].nome)<0)
		{
			strcpy(L->M[i].nome,L->M[i-1].nome);
			L->M[i].nr=L->M[i-1].nr;
			i--;
		}
		strcpy(L->M[i].nome,X.nome);
		L->M[i].nr=X.nr;
		L->Fim++;
	}
	
}

//char Lrem(Lista *L,Elem X)
//{
//	int i=0;
//	
//	while ((i<L->Fim)&&(strcmp(X,L->M[i])>0))
//		i++;
//	if((i<L->Fim)&&(!strcmp(X,L->M[i])))
//	{
//		while (i<(L->Fim-1))
//		{
//			strcpy(L->M[i],L->M[i+1]);
//			i++;
//		}
//		L->Fim--;
//		return 1;
//	}
//	else 
//		return 0;
//}


	

