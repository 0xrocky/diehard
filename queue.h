/* Interfaccia per la struttura dati CODA (queue): gli oggetti sono inseriti e rimossi attraverso una politica FIFO(FirstInFirstOut) */

#ifndef QUEUE_H
#define QUEUE_H

#include "itemkey.h"

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct queue" nel tipo "*Queue".	       *
* Nell'interfaccia utilizzo SOLO il tipo Queue, e non struct queue, che invece *
* definisco nell'implementazione( perchè appunto lo uso SOLO lì).	       *
* Queue è un puntatore al tipo strutturato struct queue.	       	       *
*******************************************************************************/
typedef struct queue *Queue;


/*******************************************************************************
* Queue queue_create(): funzione che crea una queue, restituendo un puntatore  *
*******************************************************************************/
Queue queue_create(void);

/*******************************************************************************
* int queue_is_empty(Queue): restituisce 1 se la coda è vuota, 0 altrimenti    *
*******************************************************************************/
int queue_isEmpty( Queue );

/*******************************************************************************
* void queue_make_empty(Queue): svuota la coda, distruggendo gli item contenuti*
*				e dealloca lo spazio dedicato alla coda.       *
*******************************************************************************/
void queue_makeEmpty( Queue );

/*******************************************************************************
* void queue_enqueue(Queue , Item): inserisce l'item in coda.	       	       *
*******************************************************************************/
void queue_enqueue( Queue, Item );

/*******************************************************************************
* Item queue_dequeue(Queue): estrae il valore in cima alla coda (lo restituisce*
* 			     e lo cancella dalla coda).		       	      *
*******************************************************************************/
Item queue_dequeue( Queue );

/*******************************************************************************
* Item queue_front(Queue): restituisce il primo item in cima alla coda senza   *
*			   cancellarlo.	       	       	      	       	       *
*******************************************************************************/
Item queue_front( Queue );

/*******************************************************************************
* int queue_length(Queue): restituisce il numero di elementi nella queue.      *
*******************************************************************************/
int queue_numMember( Queue );

/*******************************************************************************
* void queue_print(Queue): stampa la coda.      			       *
*******************************************************************************/
void queue_print( Queue );

/*******************************************************************************
* void queue_destroy(Queue): distrugge la coda.	    		       	       *
*******************************************************************************/
void queue_destroy( Queue );

/*******************************************************************************
* Item *queue_2array(Queue): 						       *
* costruisce un array di n Item a partire da una coda di n Item   	       *
*******************************************************************************/
Item *queue_2array( Queue );

/*******************************************************************************
* Queue queue_array2queue(Item *, int): 				       *
* Costruisce una coda di n Item a partire da un array di n Item    	       *
*******************************************************************************/
Queue queue_array2queue( Item *, int );

#endif
