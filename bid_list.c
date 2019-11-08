/* Implementazione di bid_list.h */

#include <stdio.h>
#include "itemkey.h"
#include "my_alloc_IO.h"
#include "bid_list.h"

/* Prototipo della funzione ausiliaria bid_list_seeker */
Elemento bid_list_seeker( List l, Item n );

/******************************************************************************/
List bid_list_create(void){
	List lista = my_malloc ( sizeof (struct list) ); /* Creo una lista con 0 elementi e i puntatori alla testa/coda inizializzati a NULL */
	lista->count = 0;
	lista->head = NULL;
	lista->tail = NULL;
	return lista; 					/* Restituisco la lista creata */
}
/******************************************************************************/
int bid_list_insert_head( List l, Item n ){
	if( bid_list_hasMember(l, n) != -1 ) return 0; 			 /* Se l'elemento è già presente in lista, restituisci 0 ed esci */
	else{
		Elemento new = my_malloc ( sizeof(struct list_node) );   /* Altrimenti alloca spazio per un nuovo nodo */
		new->value = n; 					 /* Assegna l'Item passato come argomento al campo value del nodo creato */
		new->prev = NULL;					 /* Poni a NULL il puntatore prev al nodo precedente */
		new->next = l->head;					 /* Fai puntare il campo next del nuovo nodo alla testa ATTUALE della lista */
		if( bid_list_numMember(l) == 0 )       /* Se non ci sono elementi nella lista, allora fai puntare la coda della lista al nuovo nodo */
			l->tail = new;
		else l->head->prev = new;              /* Altrimenti fai puntare il campo prev del nodo puntato attualmente dalla testa al nuovo nodo */
		l->head = new;						 /* In ogni caso aggiorna la testa della lista */
		l->count++;						 /* Incrementa il numero di elementi della lista */
	}
	return 1;							 /* Restituisci 1 come flag positivo */
}
/******************************************************************************/
int bid_list_insert_tail( List l, Item n ){
	if ( bid_list_hasMember(l, n) != -1 ) return 0;			/* Se l'elemento è già presente in lista, restituisci 0 ed esci */
	else{
		Elemento new = my_malloc ( sizeof(struct list_node) );  /* Altrimento alloca spazio per un nuovo nodo */
		new->value = n;						/* Assegna l'Item passato come argomento al campo value del nodo creato */
		new->next = NULL;					/* Poni a NULL il puntatore next al nodo successivo */
		new->prev = l->tail;					/* Fai puntare il campo prev del nuovo nodo alla coda ATTUALE della lista */
		if( bid_list_numMember(l) == 0 )	/* Se non ci sono elementi nella lista, allora fai puntare la testa della lista al nuovo nodo */
			l->head = new;
		else l->tail->next = new;		/* Altrimenti fai puntare il campo next del nodo puntato attualmente dalla coda al nuovo nodo */
		l->tail = new;						/* In ogni caso aggiorna la coda della lista */
		l->count++;						/* Incrementa il numero di elementi della lista */
	}
	return 1;							/* restituisci 1 come flag positivo */
}
/******************************************************************************/
int bid_list_numMember( List l ){
	return l->count;
}
/******************************************************************************/
/* Cerca un Item nella lista e lo restituisce se lo trova. Se l'Item non è presente in lista, per convenzione si restituisce il valore NULL_Item. N.B.: in una lista di n elementi, vengono eseguiti O(n) confronti per trovare un item, quindi un tempo pari a O(n). In questa lista, in ogni caso mi fermo a cercare sino alla metà, perchè cerco sia all'inizio che alla fine ad ogni iterazione: eseguo comunque al massimo O(n) confronti, ma il tempo sarà pari a O(n/2), che è comunque O(n) nel criterio uniforme (le costanti moltiplicative non si considerano negli ordini di grandezza). */

Item bid_list_hasMember( List l, Item n ){
	Elemento h = l->head;
	Elemento t = l->tail;
	Key k = key( n );
	int i = 0;
	int j = bid_list_numMember(l) / 2;
	while( (h) && (t) && (i++ <= j) ){ 		/* scorro la lista dalla testa (in avanti) e dalla coda (all'indietro) confrontando le chiavi */
		if( cmp( key(h->value), k ) == 0 )	/* Se la chiave coincide, allora ho trovato l'Item cercato e lo restituisco al chiamante */
			return h->value;
		if( cmp( key(t->value), k ) == 0 )
			return t->value;
		h = h->next;
		t = t->prev;
	}
	return NULL_Item;				 /* Altrimenti restituisco NULL_Item */
}
/******************************************************************************/
void bid_list_printList( List l ){
	Elemento p = l->head;
	while( p ){					/* Scorro gli elementi della lista a partire dalla testa, e li stampo via via */
		printItem( p->value );
		p = p->next;
	}
	printf("\n");
}
/******************************************************************************/
void bid_list_printInv( List l ){
	Elemento t = l->tail;
	while( t ){					/* Scorro gli elementi della lista a partire dalla coda, e li stampo via via */
		printItem( t->value );
		t = t->prev;
	}
}
/******************************************************************************/
void bid_list_delete( List l, Item n ){
	Elemento found = bid_list_seeker(l, n);	/* Se il nodo contenente l'Item passato come argomento non esiste in lista, non fare nulla */
	if( found ){				/* Altrimenti si hanno 3 casi: */
		if(!found->prev){		/* 1) Se l'Item è nel primo nodo della lista, devo aggiornare opportunamente la testa della lista */
			l->head = found->next;
			l->head->prev = NULL;
		} else if(!found->next){	/* Se l'Item è nell'ultimo nodo della lista, devo aggiornare opportunamente la coda della lista */
			l->tail = found->prev;
			l->tail->next = NULL;
		} else{				/* Altrimenti l'Item si trova in un nodo "interno" alla lista, quindi devo prendere il nodo precedente e */
			Elemento a = found->prev; 						      /* quello successivo ed aggiornarli opportunamente */
			Elemento b = found->next;
			a->next = b;
			b->prev = a;
		}
		destroyItem( found->value );	/* In ogni caso cancella il nodo dalla lista */
		my_free( found );			
		l->count--;			/* Decrementa il numero di elementi presenti in lista */
	}
}
/******************************************************************************/
/* Questa funzione, nel caso in cui non trova il nodo contenente l'Item, restituisce per convenzione il valore NULL. N.B.: questa è una funzione di supporto alla funzione bid_list_delete: la funzione è quasi identica a bid_list_hasMember, ritorna però il puntatore al nodo (se trovato). */
	   
Elemento bid_list_seeker( List l, Item n ){
	Elemento h = l->head;
	Elemento t = l->tail;
	Key k = key( n );
	int i = 0;
	int j = bid_list_numMember(l) / 2;
	while( (h) && (t) && (i++ <= j) ){
		if( cmp( key(h->value), k ) == 0 ) return h;
		if( cmp( key(t->value), k ) == 0 ) return t;
		h = h->next;
		t = t->prev;
	}
	return NULL;
}
/******************************************************************************/
void bid_list_destroy( List l ){
	while( l->head ){		/* Scorro la lista, cancellando di volta in volta l'elemento in testa */
		Elemento p = l->head;
		destroyItem( p->value );
		my_free( p );
		l->head = l->head->next;
	}
	my_free( l );			/* Libero lo spazio occupato dalla lista */
}
/******************************************************************************/
/* Data una lista di n Item costruisce un array di n Item. N.B.: questa funzione NON CANCELLA la lista passata come argomento */

Item *bid_list_toArray( List l, int n ){
	Item *arr = my_malloc( n*sizeof(Item) );		/* Alloco lo spazio per un array di n Item */
	int num_elem = 0;
	Elemento p = l->head;
	while( num_elem < n ){					/* Inserisco, scorrendo la lista partendo dalla testa, ogni Item nell'array */
		arr[num_elem++] = p->value;
		p = p->next;
	}
	return arr;						/* Restituisco un puntatore alla prima posizione dell'array */
}
/******************************************************************************/
/* Dato un array di n Item costruisce una lista di n Item. N.B.: questa funzione NON CANCELLA l'array passato come argomento */

List bid_list_arrayToList( Item *arr, int n ){
	List l = bid_list_create();				/* Creo una lista vuota */
	int i = 0;
	while( n-- > 0 ) bid_list_insert_head( l, arr[i++] );	/* Inserisco nella lista un elemento dell'array per volta */
	return l;
}
/******************************************************************************/
/* Questa funzione è utile se gli Item sono oggetti ORDINABILI. L'intenzione è quella di passare poi l'array creato ad una procedura di ordinamento, che quindi, agendo sui puntatori, ordini l'array, o meglio, i valori puntati da ogni cella dell'array (cioè i singoli item nella lista), e quindi la lista. */

Item **bid_list_createArrPointer( List l ){
	Item **prov = my_malloc( l->count*sizeof(Item *) ); 	/* Alloco lo spazio necessario per mantenere un array di puntatori ad Item */
	int i = 0;
	Elemento p = l->head;
	while( i < l->count ){					/* SCorro gli Item della lista */
		prov[i++] = &(p->value);			/* Assegno alla posizione attuale dell'array l'indirizzo dell'Item corrente */
		p = p->next;
	}
	return prov;
}
