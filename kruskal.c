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

/* Assinaturas */
void criarGrafo(Grafo *G,int V,int A);
void adicionarAresta(Grafo G,int origem,int destino,int custo);



void criarGrafo(Grafo *G,int V,int A){
	int i;
	Aresta* arestas;
	
	arestas = (Aresta*) malloc(sizeof(Aresta) * A);
	
	for(i = 0; i < A; i++){
		arestas[i].nome = i;
		arestas[i].origem = -1;
		arestas[i].destino = 999;
		arestas[i].custo = 0;
	}
	
	(*G).V = V;
	(*G).A = A;
	(*G).arestas = arestas;
}

void adicionarAresta(Grafo G,int origem,int destino, int custo){
	int i;
	
	/* Percorrer ate a ultima posicao sem aresta inicializada. */
	for( i = 0 ; i < G.A && G.arestas[i].origem != -1; i++);
	
	if( i < G.A ){
		G.arestas[i].origem = origem - 1; /* -1 para comecar do 0, para que o FindSet funciona com sets de 0. */
		G.arestas[i].destino = destino - 1;
		G.arestas[i].custo = custo;
	}
}

int main(int argc,char *argv[]){
/* Iremos resolver o exercicio com vertices e arestas a seguir */
/*              V1
              / |  \
            /   |   \
           3    |    \
          /     |     \
         V2     4      \
         | \    |       \
         |  \   |        \  
         |   4  |        V5
         8    \ |        /
         |     V3       /
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
	
	criarGrafo(&G,V,A); /* Criar e inicializar o Grafo vazio */
	
	adicionarAresta(G,1,2,3); /* Adicionar aresta com Vertice 1 como origem, Vertice 2 como destino e com custo 3*/

}
