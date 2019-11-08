/*Versioni personali delle allocazioni: prevedono come argomento solo il numero di elementi, e non già il prodotto con il numero di byte. E controllano già l'autenticità del pointer ritornato. ... Inoltre, funzioni di lettura da STDI, che leggono una parola o una linea terminata dal carattere a capo. */

#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

/*******************************************************************************
* void *my_malloc: controlla l'autenticità del puntatore ritornato: se questo  *
* 		 è NULL, il programma stampa un messaggio d'errore ed esce     *
*									       *
* alloca un blocco di memoria di size byte e restituisce un puntatore          *
* all’inizio di tale blocco. "size_t" è un tipo definito nella libreria        *
* standard (di solito corrisponde ad unsigned int );			       *
* il blocco di memoria allocato può contenere valori di tipo diverso, il       *
* puntatore di tipo generico void* permette di gestire tutti i casi.           *
*******************************************************************************/
void *my_malloc( size_t size );

/*******************************************************************************
* void *my_realloc: controlla l'autenticità del puntatore ritornato: se questo *
*		 è NULL, il programma stampa un messaggio d'errore ed esce     *
*									       *
* ridimensiona lo spazio puntato da p alla nuova dimensione size e	       *
* restituisce il puntatore al primo elemento (oppure NULL).		       *
*******************************************************************************/
void *my_realloc( void *p, size_t size );

/*******************************************************************************
* void *my_calloc: controlla l'autenticità del puntatore ritornato: se questo  *
*		 è NULL, il programma stampa un messaggio d'errore ed esce     *
*									       *
* alloca spazio per un array di n elementi, ciascuno di dimensione size, li    *
* inizializza a 0 e restituisce il puntatore al primo elemento (oppure NULL)   *
*******************************************************************************/
void *my_calloc( size_t nmemb, size_t size );

/*******************************************************************************
* void *free: libera spazio di memoria allocato da p                           *
*******************************************************************************/
void my_free( void *p );

/*******************************************************************************
* char *read_word(void): legge una parola da StandardInput (fino al primo      *
*			 carattere non alfabetico) memorizzandola in una       *
*			 stringa di dimensione opportuna allocata	       *
*			 dinamicamente. Restituisce un puntatore ad essa.      *
* 									       *
* N.B.: Alla fine della parola mette '\0'(come primo carattere se ciò che      *
* viene letto non è una parola, ma punteggiatura o spazi o \n)                 *
*******************************************************************************/
char *read_word(void);

/*******************************************************************************
* char *read_line(void): legge una linea di testo da StandardInput (una        *
*                     	 sequenza di caratteri, terminata da \n) e la memorizza*
*                     	 in una stringa di dimensione opportuna allocata       *
*                     	 dinamicamente. Restituisce un puntatore ad essa.      *
*******************************************************************************/
char *read_line(void);

#endif
