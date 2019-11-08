/*******************************************************************************
* Implementazione dell'interfaccia bist_itemkey.h                              *
* N.B: per semplicità i tipi sono definiti in bist_itemkey.h                   *
*******************************************************************************/

#include <stdio.h>
#include "bist_itemkey.h"
#include "arrays.h"
#include "my_alloc_IO.h"

void inizialize_ID(){ ID = 0; } /* inizializza la variabile globale ID a 0, perchè è più comodo associare già 0 al primo item inserito nell'albero */
/******************************************************************************/
void add_ID(){ ID++; }
/******************************************************************************/
int return_ID(){ return ID-1; } /* la variabile globale ID viene automaticamente incrementata ad ogni inserimento nell'albero: occorre decrementarla di 1 					   per inserire nella posizione corretta di hashTable la config appena inserita nell'albero */
/******************************************************************************/
Bist_Item newBist_Item( Bist_Key k, int N  ){
	/* Solo dopo una ricerca nell'albero (costo O(log ID) ),che darà esito negativo, allora allocherò spazio per una nuova configurazione. */
	Bist_Item it = my_malloc( sizeof(struct configurazione) );
	it->livello = my_malloc( N*sizeof(int) );
	int i;
	for( i = 0; i < N; i++ ) it->livello[i] = k[i];
	it->id = ID;
	return it;
}
/******************************************************************************/
void destroyBist_Item( Bist_Item i ){
	my_free(i->livello);
	my_free(i);
}
/******************************************************************************/
void printBist_Item( Bist_Item i, int N ){
	printf("ID %d - Configurazione ",i->id);
	printArray( i->livello, N );	
}
/******************************************************************************/
void printlnBist_Item( Bist_Item i, int N ){
	printBist_Item( i, N );
	printf("\n");
}
/******************************************************************************/
Bist_Key bist_key( Bist_Item i ){
	return i->livello;
}
/*******************************************************************************
Questa "comparazione" tra array di interi avviene scorrendo i singoli elementi dei due array: mi fermo appena trovo un numero in posizione i nel primo array che sia diverso dall' i-esimo nel secondo array. Prescisamente restituirò una qtà negativa non appena trovo un i-esimo numero del primo array minore del secondo, o viceversa una qtà positiva. Se scorrendo tutti e due gli array (che hanno per forza stessa lunghezza, in quanto pari alla qtà di contenitori gestita dall'utente), non ho trovato un numero i diverso dall'altro, i due array sono uguali: quindi restituisco 0.
N.B.: questo è un tentativo di comparazione che vuole cercare di bilanciare al meglio un albero di ricerca binaria di configurazioni, per ottenere una ricerca che si avvicini il più possibile ad un costo O(log n) dove n = nodi inseriti. Infatti, se avessi scelto come chiave degli item dei nodi il loro id (cosa che potrebbe risultare più intuitiva forse) l'albero sarebbe comunque venuto uno schifo, completamente sbilanciato a destra, e la ricerca sarebbe stata esattamente O(n) (tanto quanto una lista!), in quanto gli id vanno in crescendo, da 0 a n-1. Non sarebbero quindi state sfruttate le proprietà di un albero di ricerca binaria! ... 
Avrei potuto utilizzare una funzione random per assegnare l'id, anzichè utilizzare una funzione crescente: per esempio, includere l'header time.h inizializzare il seme srand e poi generare numeri. Ma sarebbero stati solo numeri pseudo-casuali, in quanto non posso avere la certezza al 100% che dopo n inserimenti, venga generato un id n+1-esimo diverso da tutti gli n precedenti, nonostante io abbia una configurazione n+1-esima diversa da tutte le n precedenti. Non posso quindi fare affidamento su srand. ... 
Escludendo quindi la funzione random, mi rimane una "funzione crescente" che sono sicuro al 100% generi numeri da 0 a n-1 tutti diversi. Dovendo adottare questa funzione per generare gli id, ho scelto di adottare come chiavi le configurazioni. In questo modo l'albero è ugualmente sbilanciato a destra (già partendo dalla radice, perchè come primo inserimento io inserisco un nodo con un item che ha una chiave 0[C1]...0[Cn]: tutti gli inserimenti successivi avverranno nel sottoalbero di destra). Ma comunque è molto meno sbilanciato che con l'altra ipotesi d'implementazione (id come chiavi), quindi è un ottimo compromesso che fa costare la mia ricerca quasi O(log n)! */

int bist_cmp( Bist_Key k1, Bist_Key k2, int N ){
	int i;
	for( i = 0; i < N; i++ ){
		if( k1[i] < k2[i] ) return -1;
		if( k1[i] > k2[i] ) return 1;
	}
	return 0;
}
/******************************************************************************/
void printBist_Key( Bist_Key k, int N ){
	printf("Configurazione ");
	printArray( k, N );	
}
/******************************************************************************/
void printlnBist_Key( Bist_Key k, int N ){
	printBist_Key( k, N );
	printf("\n");
}
