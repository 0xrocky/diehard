/* Interfaccia dei grafi */

# ifndef GRAPH_H
# define GRAPH_H

#include "hashTable.h"

/* Il grafo orientato (così come la lista bidirezionale con cui è implementato e la coda per le visite) utilizza come item interi: questi interi sarebbero gli id, a cui corrospondono le configurazioni generate dalle singole capacità inserite dall'utente: queste capacità sono una quantità esattamente ID (poichè io incremento ID ad ogni inserimento nell'albero binario, e l'albero controlla che non vengano inseriti due oggetti con stessa chiave, ovvero con stessa configurazione). Quindi io, non conoscendo il numero dei nodi del grafo al momento della sua creazione (che avviene in case N nel main, assieme alle altre strutture), eseguo la stessa procedura che per hashTable: alloco per il grafo uno spazio massimo pari a hash->size (perchè in hash->size, per creare la Table, faccio già il calcolo della quantità massima delle mie permutazioni). So di certo che il numero di configurazioni generabili dalle capacità che inserisce l'utente, è certamente minore del prodotto di tutte le capacità(+1 per contare anche lo zero come stadio possibile di un contenitore in una configurazione). So già che non userò tutto questo spazio, così per il grafo come per la mia tabella: quindi ho creato due procedure sistema (una per la table, l'altra per il grafo), che riallochino esattamente uno spazio pari a ID interi per il grafo (puntatori per la table), così da liberare lo spazio allocato alla creazione della struttura, ma non utilizzato perchè era in più. Questo è più vantaggioso che effettuare ID realloc, ognuna al momento di un inserimento di un id nel grafo (e nella table un puntatore a configurazione) per aver inserito una nuova configurazione nell'albero. */

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct graph" nel tipo "*Graph". Nella      *
* interfaccia utilizzo SOLO il tipo Graph, e non struct graph, che invece      *
* definisco nell'implementazione( perchè appunto lo uso lì ). Graph è un       *
* puntatore al tipo strutturato struct graph		       		       *
*******************************************************************************/
typedef struct graph *Graph;


/*******************************************************************************
* Graph graph_create( int n ): crea un grafo con n nodi			       *
*******************************************************************************/
Graph graph_create( int n );

/*******************************************************************************
* void graph_destroy( Graph g ): distrugge il grafo g			       *
*******************************************************************************/
void graph_destroy( Graph g );

/*******************************************************************************
* void graph_vertexinsert ( Graph g ): inserisce un nodo nel grafo	       *
*******************************************************************************/
void graph_vertexinsert ( Graph g );

/*******************************************************************************
* void graph_edgeinsert(Graph g, int v, int w): inserisce l’arco (v,w) nel     *
*						grafo g			       *
*******************************************************************************/
void graph_edgeinsert( Graph g, int v, int w );

/*******************************************************************************
* Graph graph_read( void ): legge da standard input un grafo		       *
*			    (specificare il formato!!)		       	       *
*******************************************************************************/
Graph graph_read( void );

/*******************************************************************************
* void graph_print( Graph g ): stampa su standard output un grafo	       *
*			       (specificare il formato!!)	       	       *
*******************************************************************************/
void graph_print( Graph g );

/*******************************************************************************
* void graph_sistema( Graph g ): rialloca uno spazio corretto per le 	       *
* configurazioni generate con le capacità inserite dall'utente.                *
*******************************************************************************/
void graph_sistema( Graph g );

/*******************************************************************************
* void chiamaDFS( Graph g ): visita in profondità del grafo g	       	       *
*******************************************************************************/
void chiamaDFS( Graph g );

/*******************************************************************************
* void graph_visitBFS( Graph g ): visita in ampiezza del grafo g	       *
*******************************************************************************/
void graph_visitBFS( Graph g );

/*******************************************************************************
* int graph_config( Capacita, hash, g, int, int, int *, int ): procedura       *
* ricorsiva di appoggio a configurazioni, che si basa su una visita in         *
* profondità.							               *
*******************************************************************************/
int graph_config( Capacita cap, HashTable hash, Graph g, int attuale, int mosse, int *marche, int N );

/*******************************************************************************
* void ampiezza( ): procedura di visita in ampiezza che calcola le distanze    *
* del grafo da un nodo v, e stampa quelle uuguali a d.	          	       *
*******************************************************************************/
void ampiezza( Capacita cap, HashTable hash, Graph g, int v, int d, int N );

#endif
