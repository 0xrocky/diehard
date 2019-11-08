/* Implementazione dell'interfaccia per la struttura dati CODA (queue.h) */

#include "itemkey.h"
#include "my_alloc_IO.h"
#include "queue.h"

/*******************************************************************************
* "struct queue_node" è un tipo strutturato che rappresenta i nodi della coda: *
* contiene l'item e un puntatore dello stesso tipo, che punta al nodo 	       *
* successivo. Item è l'informazione contenuta nel nodo, che può essere di      *
* qualunque tipo (modificabile in item.c).				       *
*******************************************************************************/
struct queue_node {
	Item value;
	struct queue_node *next;
};

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct queue_node" nel tipo "*Node".        *
* Node è un tipo puntatore alla struttura struct queue_node.		       *
*******************************************************************************/
typedef struct queue_node *Node;

/*******************************************************************************
* La coda è una struttura dati contenente un puntatore alla testa della coda,  *
* un puntatore alla coda della coda, e un counter aggiornato ai nodi presenti  *
* nella struttura.							       *
*******************************************************************************/
struct queue {	
	int count;				/* campo count che rappresenta il numero degli elementi in coda */
	Node h, t;				/* campo "h" è un puntatore alla testa della queue, campo "t" è un puntatore alla fine della queue */
};

/******************************************************************************/
Queue queue_create(void){
	Queue que = my_malloc( sizeof(struct queue) );	/* Alloco lo spazio per una nuova queue */
	que->count = 0;					/* Inizializzo a 0 il campo count */
	que->h = NULL;					/* I campi h,t (puntatori) vengono inizializzati a NULL */
	que->t = NULL;
	return que;
}
/******************************************************************************/
int queue_isEmpty( Queue q ){
	return ( q->count == 0 ) ? 1 : 0 ;		/* Se il campo count è = 0 allora la queue è vuota e ritorno 1. Altrimenti ritorno 0 */
}
/******************************************************************************/
void queue_enqueue( Queue q, Item i ){
	Node n = my_malloc( sizeof(struct queue_node) );/* Alloco lo spazio per un nuovo nodo della coda */
	n->value = i;					/* Assegno al campo value del nodo creato l'Item passato come argomento */
	n->next = NULL;					/* Il campo next del nodo creato verrà inizializzato a NULL */
	if( q->count == 0 )				/* Se la queue è vuota, allora faccio puntare la testa della queue al nodo creato */
		q->h = n;
	else q->t->next = n;	     /* Altrimenti la testa non si tocca, mentre il campo next del puntatore alla fine della queue punterà al nodo creato */
	q->t = n;					/* In ogni caso faccio puntare il puntatore alla fine della queue al nuovo nodo creato */
	q->count++;					/* Incremento il numero di Item presenti nella queue */
}
/******************************************************************************/
Item queue_dequeue( Queue q ){
	if ( !queue_isEmpty(q) ) {
		Node p = q->h;
		if( p->next )	    /* Se la coda contiene più di un Item, allora faccio puntare la testa della queue al prossimo Item */
			q->h = p->next;										      
		else{		    /* Se la coda contiene un solo Item, allora i campi h,t verranno impostati a NULL perchè la queue sarà poi resa vuota */
			q->h = NULL;	/* dall'estrazione dell'unico Item */
			q->t = NULL;
		}
		Item first = p->value;			/* Estraggo l'Item dalla coda */
		//destroyItem( p->value );		/* Se dealloco lo spazio occupato dall'Item, first punta a chissà cosa */
		my_free( p );				/* Invece libero p perchè lo voglio comunque togliere dalla coda */
		q->count--;				/* Decremento il contatore degli Item presenti nella queue e si ritorna l'Item estratto */
		return first;
	}
	return NULL_Item;				/* Se la coda è vuota, ritorno PER CONVENZIONE il valore NULL_Item */
}
/******************************************************************************/
/* N.B.: Questa funzione NON cancella la queue, ma la svuota soltanto */
void queue_makeEmpty( Queue q ){
	Node p = q->h;
	while( p ){					/* Scorro la queue a partire dalla testa e dealloco lo spazio occupato da ogni Item */
		q->h = q->h->next;
		destroyItem( p->value );
		my_free( p );				/* Dealloco lo spazio occupato da ogni nodo */
		p = q->h;
	}
	q->t = NULL;
	q->count = 0;					/* Reimposto t a NULL (h lo è già) e anche il contatore degli Item presenti a 0 */
}
/******************************************************************************/
Item queue_front( Queue q ){
	return ( !queue_isEmpty(q) ) ? q->h->value : NULL_Item ; /* Se la coda è vuota, ritorno PER CONVENZIONE il valore NULL_Item */
}
/******************************************************************************/
int queue_numMember( Queue q ){
	return q->count;
}
/******************************************************************************/
void queue_print( Queue q ){
	Node p = q->h;
	while( p ){
		printlnItem( p->value );
		p = p->next;
	}
}
/******************************************************************************/
void queue_destroy( Queue q ){
	queue_makeEmpty( q );					/* Dopo aver svuotato la coda, dealloco lo spazio occupato dalla stessa */
	my_free( q );
}
/******************************************************************************/
/* Data una coda di n Item costruisce un array di n Item. N.B.: questa funzione NON CANCELLA la coda passata come argomento  */
Item *queue_2array( Queue q ){
	Item *arr = my_malloc( q->count*sizeof(Item) );		/* Alloco lo spazio per un array di n Item */
	int i = 0;
	Node p = q->h;		
	while (p) {					        /* A partire dalla testa, scorro gli Item presenti nella queue inserendoli nell'array */
		arr[i++] = p->value;
		p = p->next;
	}
	return arr;						/* Ritorno il puntatore all'inizio dell'array di Item */
}
/******************************************************************************/
/* Dato un array di n Item costruisce una coda di n Item. N.B.: questa funzione NON CANCELLA l'array passato come argomento */
Queue queue_array2queue( Item *a, int n ){
	Queue b = queue_create();				/* Creo una nuova queue */
	int i = 0;
	while( i < n )						/* A partire dall'inizio dell'array, inserisco nella queue gli Item */
		queue_enqueue(b, a[i++]);
	return b;						/* Restituisco il puntatore alla queue creata */
}
