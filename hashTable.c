/* implementazione di hashTable.h */

#include <stdio.h>
#include "my_alloc_IO.h"
#include "arrays.h"
#include "bist_itemkey.h"
#include "hashTable.h"

/* Definisco un nuovo tipo strutturato con i seguenti campi */

struct hashtable{
	int size;		/* dimensione-limite massima della mia tabella (ovvero la fine) */
	Config *configurazioni; /* array di puntatori a possibili configurazioni */
};

/******************************************************************************/
HashTable hashtable_create( Capacita C, int N ){			/* N sarebbe il numero di contenitori gestiti */
	int i, temp; 
	HashTable new = my_malloc( sizeof(struct hashtable) );  	/* creo in memoria lo spazio per una tabella */
	new->size = 1; 
	for( i = 0; i < N; i++ ){ 
		temp = C[i] + 1; 					/* leggo le capacità dei singoli contenitori */
		new->size *= temp;					/* size è il prodotto delle permutazioni di tutte le n capacità */
	}								/* ovvero è il limite massimo di possibili configurazioni */
	new->configurazioni = my_malloc( new->size*sizeof(Config *) ); 	/* creo lo spazio per size puntatori a configuzioni */
	for( i = 0; i < new->size; i++ )
		new->configurazioni[i] = my_malloc( sizeof(Config) );
	return new;
}
/******************************************************************************/
/* Ad ogni configurazione inserita nell'albero associo un id; poi in hashtable->configurazioni[id] inserisco un puntatore alla corrispondente configurazione. Questo richiede un tempo O(1). */

void hashtable_insert( HashTable hash, Config A ){
	hash->configurazioni[return_ID()] = A;
}
/******************************************************************************/
void hashtable_destroy( HashTable hash ){
	/*int i;
	for( i = 0; i < hash->size; i++ )	Le varie configurazioni vengono già deallocate con la distruzione dell'albero: devo solo deallocare
		my_free( hash->configurazioni[i] ); i puntatori ad esse */
	my_free( hash->configurazioni );
	my_free( hash );	
}
/******************************************************************************/
void hashtable_print( HashTable hash, int N ){
	int i;
	for( i = 0; i <= return_ID(); i++ ){
		printf("%d) ",i);
		printArray( hash->configurazioni[i], N );
	}
	printf("\n");
}
/******************************************************************************/
/* Procedura inversa rispetto a hashtable_insert: dato un id, accedo alla sua configurazione in O(1) (proprio perchè hashtable è un array di puntatori). */

Config hashtable_get_config( HashTable hash, int n ){
	return hash->configurazioni[n];
}
/*******************************************************************************
Questa procedura sistema lo spazio utilizzato per creare la hashTable, riallocandolo esattamente per ID puntatori a quante configurazioni possibili sono riuscito a generare dalle singole capacità inserite dall'utente. Conosco però ID solo alla fine di set_All(), dopo tutte le possibili generazioni di nuove configurazioni. Quindi prima creo una tabella al massimo delle sue dimensioni possibili, e poi la rialloco, per liberare lo spazio inutilizzato. Da notare che ID è aggiornata al primo id disponibile: ho quindi utilizzato tutti gli ID da 0 a ID-1. Sono sicuro di allocare uno spazio giusto. */

void hashtable_sistema( HashTable hash ){
	hash->size = ID;
	hash->configurazioni = my_realloc( hash->configurazioni,ID*sizeof(Config *) );
}
/******************************************************************************/
/* Funzione che ritorna la "massima dimensione" generabile da una certa sequenza inserita dall'utente. Dato che effettuo questo calcolo in hashtable_create, e dato che utilizzo questo espediente della creazione di "massima dimensione" anche per il grafo di id, che poi rialloco, sarebbe stupido eseguire due volte lo stesso calcolo ( che costa O( prodotti*N_contenitori ); quindi passerò size a graph_create. */ 

int hash_get_size( HashTable hash ){
	return hash->size;
}
