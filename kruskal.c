/*
	Name: Rabah Zeineddine
	Author: Rabah Zeineddine
	Date: 20/11/17 14:41
	Description: Kruskal Code.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct aresta{
	int nome;
	int origem;
	int destino;
	int custo;
}Aresta;

typedef struct grafo{
	int V;
	int A;
	Aresta *arestas;
}Grafo;

int main(int argc,char *argv[]){
	/* Iremos resolver o exercicio com vertices e arestas a seguir */
	/*
		        V1
			 / |  \
		     /  |   \
		    3   |    \
		   /    |     \
		 V2     4      \
		 | \    |       \
		 |  \   |        \  
		 |   4  |        V5
		 8    \ |        /
		 |	   V3     /
		 |    /  \     2
		 |   8    9   /
		 |  /      \ /
		V4         V6
		           /
				  3
				 /
				V7  
	*/
	
	int V; /* O numero de vertices que o Grafo tem. */
	int A; /* O numero de arestas que o Grafo tem. */
	
	Grafo G;
	V = 7; A = 9;

}
