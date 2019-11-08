#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "arrays.h"
#include "my_alloc_IO.h"
#define LIM 101
#define INIT_SIZE 5

/******************************************************************************/
/* Prima di generare l'array, inizializzarlo con n: int a[n] */
void generaArray( int arr[], int n ){
	int i;
	srand(time(NULL));
	for( i = 0; i < n; i++ ) arr[ i ] = ( rand() % LIM );
	/* l'array sarà riempito di numeri compresi tra 0 a 100 */
}
/******************************************************************************/
void printArray( int arr[], int n ){
	int i;
	for( i = 0; i < n; i++ ) printf("%d ",arr[ i ]);
	printf("\n");
}
/******************************************************************************/
int sommaArray( int arr[], int n ){
	int i, somma = 0;
	for( i = 0; i < n; i++ ) somma += arr[ i ];
	return somma;
}
/******************************************************************************/
/* L'idea è quella di leggere un'intera riga (tramite la funzione read_word). Tokenizzarla e usare poi un vettore d'appoggio, per copiarvi solo numeri interi, convertendoli da char in interi nel vettore da restituire, tramite la funzione atoi. Dopo ogni chiamata la funzione strtok scrive in w un carattere terminatore al posto del carattere successivo al token (per fissarne appunto la fine), rendendo cosi' w praticamente inutilizzabile: per questo preservo l'origine del buffer letto in temp, al fine di deallocarlo. Con questa funzione ritorno il puntatore all'array di interi letti, e inizializzo una variabile, passata attraverso il suo indirizzo per riferimento, al numero di interi letti effettivamente. */

int *leggiArray( int *count ){
	*count = 0;
	int size = INIT_SIZE, *new = my_calloc( size,sizeof(int) );	/* L'utente non inserirà una capacità 0: dal primo 0 in poi è robaccia */
	char *w = read_line(), *temp = w, *copia = strtok(w, "\n\t\r\b ");
	
 	while( copia != NULL ){ 	/* Quando non ci sono piu' token il valore restituito e' il puntatore nullo */
		if( *count == size ){ 	/* Fase di riallocazione di new, array di interi */
			size += 1;	/* E' già difficile che l'utente gestisca 5 contenitori: per mia scelta, tengo basso l'incremento quindi */
			new = my_realloc( new, size*sizeof(int) );
		}
		new[(*count)++] = atoi( copia );
		copia = strtok(NULL, "\n\t\r\b ");
	}
	my_free( temp );
	return new;
}
/******************************************************************************/
/* Funzione creata appositamente per leggere l'input di raggiungibile(a): sarebbe svantaggioso utilizzare ancora leggiArray( int *count ), quando count ormai lo conosco, perchè è la quantità dei contenitori gestiti dall'utente. Meglio evitare la riallocazione dinamica, se possibile, visto che so quando fermarmi a leggere */

int *read_arr_knowing_length( int length ){
	int i, temp, *new = my_malloc( length*sizeof(int) );
	for( i = 0; i < length; i++ ){
		scanf("%d",&temp);
		if( temp >= 0 ) new[i] = temp;
	}
	return new;
}
/******************************************************************************/
void printSpaces( int spaces ){
	int i;
	for( i = 0; i < spaces; i++ ) printf(" ");
	printf("*");
}
/******************************************************************************/
int max_capacita( int n, int *arr ){
	int i, max = arr[0];
	for( i = 1; i < n; i++ )
		if( max < arr[i] ) max = arr[i];
	return max;
}
