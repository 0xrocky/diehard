/* Libreria di funzioni pensate per array di interi. */

#ifndef ARRAY_H
#define ARRAY_H

/*******************************************************************************
* void generaArray: genera un array a caso di interi di dimensione n,          *
* 		    a partire dal puntatore passato come argomento             *
*******************************************************************************/
void generaArray( int arr[], int n );


/*******************************************************************************
* void printArray: stampa l'array di interi di dimensione n                    *
* 		   passato come argomento                                      *
*******************************************************************************/
void printArray( int arr[], int n );


/*******************************************************************************
* int sommaArray: ritorna la somma dell'array di interi di dimensione n        *
* 		  passato come argomento                                       *
*******************************************************************************/
int sommaArray( int arr[], int n );

/*******************************************************************************
* int *leggiArray(): legge un array di interi dinamicamente, senza chiedere    *
* una dimensione specifica. Rialloca lo spazio necessario automaticamente.     *
* N.B.: alla fine *count contiene gli interi effettivamente letti	       *
*******************************************************************************/
int *leggiArray( int *count );

/*******************************************************************************
* int *read_arr_knowing_length( int length ): legge "length" interi.	       *
*******************************************************************************/
int *read_arr_knowing_length( int length );

/*******************************************************************************
* void printSpaces( int spaces ): stampa tanti spazi quanti vengono passati    *
*				  come argomento.			       *
*******************************************************************************/
void printSpaces( int spaces );

/*******************************************************************************
* int max_capacita( int n, int *arr ): funzione che restituisce l'intero       *
* massimo tra quelli presenti nell'array.				       *
*******************************************************************************/
int max_capacita( int n, int *arr );

#endif
