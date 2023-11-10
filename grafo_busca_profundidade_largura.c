#include <stdio.h>
#include <stdlib.h>

struct Node {
		int vertice;
		struct Node* proximo;
};

struct Grafo {
		int numVertices;
		int* visitado;
		int* fila;
		int frente;
		int tras;
		struct Node** listasAdj;
};

// Algoritmo DFS
void DFS(struct Grafo* grafo, int vertice) {
		struct Node* listaAdj = grafo->listasAdj[vertice];
		struct Node* temp = listaAdj;

		grafo->visitado[vertice] = 1;
		printf("Visitado %d \n", vertice);

		while (temp != NULL) {
				int verticeConectado = temp->vertice;

				if (grafo->visitado[verticeConectado] == 0) {
						DFS(grafo, verticeConectado);
				}
				temp = temp->proximo;
		}
}

// Algoritmo BFS
void BFS(struct Grafo* grafo, int vertice) {
		grafo->visitado[vertice] = 1;
		printf("Visitado %d \n", vertice);

		grafo->fila[++grafo->tras] = vertice;

		while (grafo->frente <= grafo->tras) {
				vertice = grafo->fila[grafo->frente++];

				struct Node* temp = grafo->listasAdj[vertice];
				while (temp) {
						int verticeConectado = temp->vertice;

						if (grafo->visitado[verticeConectado] == 0) {
								printf("Visitado %d \n", verticeConectado);
								grafo->visitado[verticeConectado] = 1;
								grafo->fila[++grafo->tras] = verticeConectado;
						}
						temp = temp->proximo;
				}
		}
}

// Criar um nó
struct Node* criarNo(int v) {
		struct Node* novoNo = malloc(sizeof(struct Node));
		novoNo->vertice = v;
		novoNo->proximo = NULL;
		return novoNo;
}

// Criar grafo
struct Grafo* criarGrafo(int vertices) {
		struct Grafo* grafo = malloc(sizeof(struct Grafo));
		grafo->numVertices = vertices;

		grafo->listasAdj = malloc(vertices * sizeof(struct Node*));

		grafo->visitado = malloc(vertices * sizeof(int));
		grafo->fila = malloc(vertices * sizeof(int));
		grafo->frente = 0;
		grafo->tras = -1;

		int i;
		for (i = 0; i < vertices; i++) {
				grafo->listasAdj[i] = NULL;
				grafo->visitado[i] = 0;
		}
		return grafo;
}

// Adicionar aresta
void adicionarAresta(struct Grafo* grafo, int origem, int destino) {
		// Adicionar aresta de origem para destino
		struct Node* novoNo = criarNo(destino);
		novoNo->proximo = grafo->listasAdj[origem];
		grafo->listasAdj[origem] = novoNo;

		// Adicionar aresta de destino para origem
		novoNo = criarNo(origem);
		novoNo->proximo = grafo->listasAdj[destino];
		grafo->listasAdj[destino] = novoNo;
}

// Imprimir o grafo
void imprimirGrafo(struct Grafo* grafo) {
		int v;
		for (v = 0; v < grafo->numVertices; v++) {
				struct Node* temp = grafo->listasAdj[v];
				printf("\n Lista de adjacencia do vertice %d\n ", v);
				while (temp) {
						printf("%d -> ", temp->vertice);
						temp = temp->proximo;
				}
				printf("\n");
		}
}

int main() {
		struct Grafo* grafo = criarGrafo(10);
		adicionarAresta(grafo, 0, 1);
		adicionarAresta(grafo, 1, 2);
		adicionarAresta(grafo, 1, 4);
		adicionarAresta(grafo, 2, 3);
		adicionarAresta(grafo, 2, 4);
		adicionarAresta(grafo, 2, 9);
		adicionarAresta(grafo, 3, 4);
		adicionarAresta(grafo, 4, 5);
		adicionarAresta(grafo, 4, 6);
		adicionarAresta(grafo, 4, 7);
		adicionarAresta(grafo, 5, 6);
		adicionarAresta(grafo, 7, 8);
		adicionarAresta(grafo, 7, 9);

		imprimirGrafo(grafo);

		printf("\nBusca em profundidade - DFS:\n");
		DFS(grafo, 0);

		// Reinicializa visitados para a BFS
		for (int i = 0; i < grafo->numVertices; i++) {
				grafo->visitado[i] = 0;
		}

	struct Grafo* grafo2 = criarGrafo(15);
	adicionarAresta(grafo2, 0, 1);
	adicionarAresta(grafo2, 0, 2);
	adicionarAresta(grafo2, 1, 3);
	adicionarAresta(grafo2, 1, 4);
	adicionarAresta(grafo2, 1, 5);
	adicionarAresta(grafo2, 3, 6);
	adicionarAresta(grafo2, 3, 7);
	adicionarAresta(grafo2, 5, 8);
	adicionarAresta(grafo2, 5, 9);
	adicionarAresta(grafo2, 7, 10);
	adicionarAresta(grafo2, 7, 11);
	adicionarAresta(grafo2, 7, 12);
	adicionarAresta(grafo2, 9, 13);
	adicionarAresta(grafo2, 9, 14);
	
	imprimirGrafo(grafo2);

	printf("\nBusca em largura - BFS:\n");
	BFS(grafo2, 1);

		return 0;
}