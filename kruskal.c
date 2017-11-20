/*
	Authores: Rabah Zeineddine
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

typedef struct set{
	int p;
	int rank;
}Set;

/* Assinaturas */
void criarGrafo(Grafo *G,int V,int A);
void adicionarAresta(Grafo G,int origem,int destino,int custo);
void imprimirGrafo(Grafo G,int n);
void mergeSort(Aresta *A, int p, int r);
void merge(Aresta *A, int p, int q, int r);
void imprimirSets(int v);
void kruskal(Grafo G);
void MakeSet(int v);
int FindSet(int v);
void Link(int x,int y);
void Union(int x,int y);

/* Variavel Global Para manter o formato do codigo do Cormen. */
Set *sets;



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

void imprimirGrafo(Grafo G,int n){
	int i;
	printf("\n\nVertice Origem    |");
	for( i = 0 ; i< n ; i++)
		printf("  V%d ", G.arestas[i].origem + 1 );
	printf("\nVertice Destino   |");
	for( i = 0 ; i < n ; i++ )
		printf("  V%d ", G.arestas[i].destino + 1);
	printf("\n     Custo        |");
	for( i = 0 ; i < n ; i++)
		printf("  %d  ", G.arestas[i].custo);
}

void mergeSort( Aresta *A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

/* Método merge() usado no MergeSort. */
void merge(Aresta *A, int p, int q, int r) {
    int i,j,k,n1,n2;
    
    n1 = q - p + 1; 
    n2 = r - q;
    
    Aresta L[n1];
    Aresta R[n2];
    
    for (i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for(j = 0; j < n2; j++) {
        R[j] = A[q + j + 1];
    }
    L[ n1 ].custo = 99999999;
    R[n2].custo = 99999999;
    
    i = 0;
    j = 0;
    for(k = p; k <= r  ; k++) {
        if(L[i].custo <= R[j].custo ) {
            A[k] = L[i];
            i = i + 1;
        } else {
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void MakeSet(int v){
	sets[v].p = v;
	sets[v].rank = 0;
}

int FindSet(int v){
  if(v != sets[v].p)
    sets[v].p = FindSet(sets[v].p);
  return sets[v].p;
}

void Link(int x,int y){
  if(sets[x].rank > sets[y].rank)
    sets[y].p = x;
  else{
    sets[x].p = y;
    if(sets[x].rank == sets[y].rank)
      sets[y].rank++;
  }
}

void Union(int x, int y){
  Link(FindSet(x),FindSet(y));
}

void imprimirSets(int v){
  int i;
  printf("\n\nP  : ");
  for( i = 0 ; i < v; i++)
   printf(" %d ", sets[i].p);
  printf("\nSet: ");
  for( i = 0 ; i < v; i++)
    printf(" %d ",i);
  
}

void kruskal(Grafo G){
	int a; /* Uma variavel de indice usada para percorrer as arestas. */
	int i; /* Uma variavel de indice usada para adicionar a aresta no resultado. */
	int v; /* Uma variavel de indice usasda para percorrer as vertices. */
	int x; /* Uma variavel usada para salvar o representante da vertice origem de uma aresta. */
	int y; /* Uma variavel usada para salvar o representante da vertice destino de uma aresta. */
	
	Aresta *resultado; /* Um vetor de struct aresta que tera as arestas que nao formam circuito. */
	
	resultado = (Aresta*) malloc(sizeof(Aresta) * G.V ); /* Alocar memoria para o resultado, no maximo o tamanho das verticies que temos. */
	
	sets = (Set*) malloc(sizeof(Set) * G.V); /* Alocar memoria para os Sets */
	
	/* Criar sets para todas as vertices existentes */
	for( v = 0 ; v < G.V ; v++ )
		MakeSet(v);
	
	printf("\n\nTabela dos conjuntos inicialmente inicializados.");
	imprimirSets(G.V); 
  	 
	
	/* Ordenar as arestas usando merge sort, pelo Custo de cada aresta */
	mergeSort(G.arestas, 0 , G.A - 1);
	
	/* Percorrer todas as arestas e verificar se cada aresta forma um circuito ou nao
		Caso forme um circuito descarta, caso contrario, adiciona no resultado.
	*/
	for( a = 0 ; a < G.A ; a++ ){
		x = FindSet(G.arestas[a].origem);  /* Encontrar o representante da vertice origem da aresta a. */
		y = FindSet(G.arestas[a].destino); /* Econtrar o representatne da vertice destino da aresta a */
		
		if(x != y){
			resultado[i++] = G.arestas[a];
			Union(x,y);
		}
	}
	
	G.arestas = resultado;
	printf("\n\nApos a execucao do algoritmo Kruskal");
	printf("\n\nArestas e Vertices da arvore geradora");
	imprimirGrafo(G, i);
	printf("\n\nTabela dos conjuntos");
	imprimirSets(G.V); 
	
}	



int main(int argc,char *argv[]){
/* Iremos resolver o exercicio com vertices e arestas a seguir */
/*              V1
              / |  \
            /   |   \
           3    |    \
          /     |     7
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
	adicionarAresta(G,2,3,4);
  	adicionarAresta(G,3,1,4);
  	adicionarAresta(G,2,4,8);
  	adicionarAresta(G,4,3,8);
  	adicionarAresta(G,3,6,9);
  	adicionarAresta(G,6,5,2);
  	adicionarAresta(G,6,7,3);
  	adicionarAresta(G,5,1,7);
  	
  	printf("\nArestas e vertices pre-cadastrados antes da execucao do algoritmo Kruskal.");
  	imprimirGrafo(G,G.A);
  	printf("\n\n___________________________________________________________________________");
  	printf("\n\nExecucao do algoritmo Kruskal.");
  	
  	kruskal(G);
  	
  	/* Apos o Kruskal , o grafo deve ser a seguir */
  	/*
                V1
              /    \
            /       \
           3         \
          /           7
         V2            \
         | \            \
         |  \            \  
         |   4           V5
         8    \          /
         |     V3       /
         |             2
         |            /
         |           /
         V4         V6
                   /
                  3
                 /
               V7  
	*/
}
