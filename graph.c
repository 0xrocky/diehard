/* Implementazione di un grafo orientato di interi, ovvero di id delle configurazioni . */

#include <stdio.h>
#include "arrays.h"
#include "bist_itemkey.h"     /* Mi serve ID, dichiarata in bist_itemkey.h */
#include "bist_Tree.h"
#include "my_alloc_IO.h"
#include "bid_list.h"	      /* Includo bid_list.h, che contiene l'implementazione di una lista bidirezionale (con puntatore a testa e coda della lista) */
#include "graph.h"
#include "queue.h"
#include "hashTable.h"
#include "contenitore.h"

/* Definisco un nuovo tipo strutturato con i seguenti campi */
struct graph{
   int n_V, m_E;	/* n_V = num vertici, m_E = num lati */
   List *array_list;	/* Array di liste */
};

void graph_visitDFS(Graph, int *, int); /* Funzione ricorsiva di visita in profondità, di supporto a chiamaDFS (per questo non compare nell'interfaccia) */

/******************************************************************************/
Graph graph_create( int n ){
	Graph g = my_malloc( sizeof(struct graph) );
	g->n_V = n;
	g->m_E = 0;
	g->array_list = my_malloc( n*sizeof(List) );
	int i;
	for( i = 0; i < n; i++ ) g->array_list[i] = bid_list_create();
	return g;
}
/******************************************************************************/
void graph_destroy( Graph g ){
	if( g ){
		int i = 0;
		for( ; i < g->n_V; i++ )
			bid_list_destroy( g->array_list[i] );
		my_free( g->array_list );
		my_free( g );
	}
}
/******************************************************************************/
void graph_vertexinsert ( Graph g ) {
	if( g ){
		g->array_list = my_realloc( g->array_list, (g->n_V+1)*sizeof(List) );
		g->array_list[g->n_V] = bid_list_create();
		g->n_V++;
	}
}
/******************************************************************************/
void graph_edgeinsert( Graph g, int v, int w ){
	if( g ){
		if ( bid_list_insert_tail(g->array_list[v], w) ) /* Per convenzione inserisco in coda alla lista, tanto è uguale: ha uno stesso costo */
			g->m_E++;				 /* perchè ha puntatore alla testa e alla coda. N.B.: l'inserimento in lista controlla */
	}	/* che non venga inserito due volte uno stesso oggetto: quindi incremento il numero dei lati se e solo se l'inserimento restituisce 1 */
}
/******************************************************************************/
Graph graph_read(void){
	int x, y, i, l;
	printf("Inserisci il numero dei nodi\n");
	scanf("%d",&x);
	Graph g = graph_create(x);
	printf("\nInserisci il numero dei lati\n");
	scanf("%d",&l);
	printf("\nInserisci la coppia di nodi che vuoi collegare con un lato, separata da un trattino (es.: x-y)\n");
	for( i = 0; i < l; i++ ){
		scanf("%d-%d", &x, &y);
		graph_edgeinsert( g, x, y );
	}
	return g;	
}
/******************************************************************************/
void graph_print( Graph g ){
	if( g ){
		printf("Il grafo ha %d nodi e %d lati\n", g->n_V, g->m_E);
		int i = 0;
		for( ; i < g->n_V; i++ ){
			printf("%d: ",i);
			bid_list_printList( g->array_list[i] );
		}
	}
}
/*******************************************************************************
Questa procedura sistema lo spazio utilizzato per creare il grafo, riallocandolo esattamente per gli di configurazioni possibili che sono riuscito a generare dalle singole capacità inserite dall'utente. Da notare che ID è aggiornata al primo id disponibile: ho quindi utilizzato tutti gli ID da 0 a ID-1  e ID rappresenta l'esatta quantità delle configurazioni generate. */ 

void graph_sistema( Graph g ){
	g->n_V = ID;
	g->array_list = my_realloc( g->array_list,ID*sizeof(List) );
}
/******************************************************************************/
void chiamaDFS( Graph g ){
	printf("\nVisita in profondità\n_V");
	/* marche[] è un vettore che indica se un nodo è già stato visitato(1) o meno(0): per questo alla sua creazione, lo pongo tutto a 0. */
	int *marche = my_calloc( (g->n_V),sizeof(int) );
	int s = g->array_list[0]->head->value;
	printf("%d ", s );
	graph_visitDFS( g, marche, s );
	printf("\n");
}

void graph_visitDFS( Graph g, int *M, int v ){
		M[ v ] = 1;	/* Ho accesso alla marca di un nodo, usando proprio il nodo che è un intero, come indice nel vettore. */
		Elemento temp = g->array_list[v]->head;
		while( temp ){
			int w = temp->value;
			if( M[ w ] == 0 ){
				printf("%d ", w );
				graph_visitDFS( g, M, w );
			}
			temp = temp->next;
		}
}
/******************************************************************************/
void graph_visitBFS( Graph g ){
	printf("\nVisita in ampiezza\n_V");
	Queue coda = queue_create();			 /* Attraverso l'uso della coda, simulo una ricorsione per spostarmi in ampiezza */
	int *marche = my_calloc( (g->n_V),sizeof(int) ); /* vdi sopra commenti su marche */
	int v = g->array_list[0]->head->value, w; 	 /* Prima lista, primo elemento, valore */
	marche[ v ] = 1;
	printf("%d ", v );
	queue_enqueue( coda, v );			/* Sicuramente entro almeno una volta nel ciclo, perchè ho introdotto v */
	while( !queue_isEmpty( coda ) ){
		v = queue_dequeue( coda );
		Elemento temp = g->array_list[v]->head;
		while( temp ){
			w = temp->value;		/* w è il primo nodo nella lista di adiacenza di w */
			if( marche[ w ] == 0 ){
				marche[ w ] = 1;	/* lo marco */
				queue_enqueue( coda, w );	/* lo stampo */
				printf("%d ", w );	/* lo metto nella coda */
			} temp = temp->next;		/* E così scorro tutta la lista di adiacenza di v */
		}
	} my_free( marche );
}
/******************************************************************************/
/* Funzione ricorsiva che si basa su una visita in profondità del grafo, partendo dal nodo "attuale". Disegnata appositamente per "configurazioni".
Per tutti i nodi presenti nella lista di adiacenza del nodo attuale, io richiamo ricorsivamente la funzione, decrmentando la distanza d, ovvero il numero di mosse che ha inserito l'utente. Quando arriverò al caso limite, ovvero una distanza pari a 1, allora stamperò tutti i nodi adiacenti a quello qui sono arrivato, scorrendo la sua lista di adiacenza.
Tengo traccia dei nodi visitati con il vettore marche, che inizializzo già dentro configurazioni( d ), prima di chiamare la funzione ricorsiva graph_config: ho accesso alla marca di un nodo, usando proprio il nodo, che è un intero, come indice nel vettore.
Inoltre ho bisogno di un controllo aggiuntivo per un numero di mosse molto alto: devo comunque stampare al massimo tutti i nodi presenti nel grafo, e solo una volta. 
Il costo di graph_config è dato principalmente dal costo dello scorrere tutte le liste di adiacenza. Quindi O(somma delle lunghezze delle liste di adiacenza di ogni nodo v del grafo), ovvero O(sommatoria(#L(v))), = O(m_E). 
Lo spazio richiesto è quello per lo stack usato dalla ricorsione, che deve tenere traccia dei nodi: O(n_V).*/

int graph_config( int *capac, HashTable hash, Graph g, int attuale, int d, int *marche, int N ){
	Elemento temp;
	int *config, printed = 0;
	if ( d == 1 ){
		for( temp = g->array_list[attuale]->head; temp; temp = temp->next ){
			if( marche[ temp->value ] == 0 ){	/* Se non ho ancora stampato quel nodo */
				config = hashtable_get_config( hash, temp->value );  /* Recupero la sua configurazione associata dalla table: costo O(1). */
				visualizza( capac, config, N );	/* Stampo */
				marche[ temp->value ] = 1;	/* Marco il nodo */
				printed++;			/* Aggiorno la quantità di nodi stampati */
			}
		}
	}
	else{ 
		for( temp = g->array_list[attuale]->head; temp; temp = temp->next){
			printed += graph_config( capac, hash, g, temp->value, d-1, marche, N );
			if( printed >= g->n_V ) break;		/* Controllo aggiuntivo */
		}
	}
	return printed;
}
/******************************************************************************/
/* Procedura che misura le distanze dei nodi dal nodo v, che corrisponde alla configurazione dove si trova l'utente. L’algoritmo esegue una esplorazione in ampiezza del grafo diretto G a partire dal nodo v, calcolando così le distanze di tutti i nodi da v. Tali distanze sono memorizzate in un vettore dist[], che ha per indici i nodi del grafo. Il calcolo delle distanze si ottiene applicando proprio un attraversamento in ampiezza: il procedimento è basato sull’utilizzo della coda. Nel caso peggiore, sia il tempo di calcolo che lo spazio di memoria richiesti dall’algoritmo
sono O(n_V + m_E), cioè O(somma dei nodi e dei lati). */

void ampiezza( Capacita cap, HashTable hash, Graph g, int v, int d, int N ){
	Queue coda = queue_create();		/* Attraverso l'uso della coda, simulo una ricorsione per spostarmi in ampiezza */
	queue_enqueue( coda, v );
	int *dist = my_calloc( (g->n_V),sizeof(int) ), *config = NULL;
	int w, z;
	for( w = 0; w < g->n_V; w++ ) dist[ w ] = 0;
	dist[ v ] = 0;
	Elemento temp;
	while( !queue_isEmpty( coda ) ){	/* Sicuramente entro almeno una volta nel ciclo, perchè ho introdotto v */
		w = queue_dequeue( coda );
		temp = g->array_list[w]->head;
		while( temp ){
			z = temp->value;
			if( dist[ z ] == 0 ){
				dist[ z ] = dist[ w ] + 1;
				queue_enqueue( coda, z );
			} temp = temp->next;
		}
	}
	
	/* Fase di stampa: scorro tutto il vettore delle distanze, e quando ne trovo una == d, vi accedo tramite la mia hashTable, e stampo la config. */
	for( w = 0; w < g->n_V; w++ ){
		if( dist[ w ] == d ){
			config = hashtable_get_config( hash, w );
			visualizza( cap, config, N );
		}
	}
	my_free( dist );		/* Dealloco il vettore delle distanze */
	queue_destroy( coda );		/* Distruggo la coda */
}
