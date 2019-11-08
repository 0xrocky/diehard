/* Interfaccia per liste bidirezionali di Item */

#ifndef BID_LIST_H
#define BID_LIST_H

#include "itemkey.h"

/* Ho scelto di implementare tutte le strutture seguenti qui in bid_list.h anzichè nel file bid_list.c, per rendere accessibili le teste delle liste, o meglio il tipo Elemento, con i suoi campi, perchè queste le devo utilizzare per esempio nell'implementazione dei grafi, nelle visite, e quindi devo potervi accedere: nel momento in cui includo quest'interfaccia in un'altra struttura (come appunto il caso dei grafi), posso utilizzare tutto ciò che implemento qui in quel file (cosa che non avrei potuto fare se avessi implementato lo struct list_node, Elemento e struct_list in bid_list.c, nonostante questi ultimi tre tipi non li utilizzo proprio qui in bid_list.h */

/*******************************************************************************
* "struct list_node" è un tipo strutturato che rappresenta i nodi della lista: *
* contiene l'item, più 2 puntatori dello stesso tipo, che puntano uno al nodo  *
* successivo, l'altro al nodo precedente.			       	       *
* 									       *
* Item è l'informazione contenuta nel nodo, che può essere di qualunque tipo   *
* (modificabile in item.c).						       *
*******************************************************************************/
struct list_node{
	Item value;
	struct list_node *next, *prev;
};

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct list_node" nel tipo "*Elemento".     *
* Elemento è un tipo puntatore alla struttura struct list_node.		       *
*******************************************************************************/
typedef struct list_node *Elemento;

/*******************************************************************************
* La lista è una struttura dati contenente un puntatore alla testa della lista,*
* un puntatore alla coda della lista, e un counter aggiornato ai nodi presenti *
* nella struttura. head punta alla testa: se NULL la lista è vuota, altrimenti *
* head è il puntatore (l'indirizzo) al primo elemento. 			       *
*******************************************************************************/
struct list{
	int count;			/* numero di elementi della lista */
	Elemento head;			/* puntatore alla testa della lista */
	Elemento tail;			/* puntatore alla coda della lista */
};

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct list" nel tipo "*List".	       *
* List è un puntatore al tipo strutturato struct list.	       	       	       *
*******************************************************************************/
typedef struct list *List;


/*******************************************************************************
* List bid_list_create(): funzione che inizializza una lista, cioè restituisce *
*			 un puntatore ad una lista vuota.		       *
*******************************************************************************/
List bid_list_create(void);

/*******************************************************************************
* int bid_list_insert_head( List, Item ):				       *
* funzione che esegue l'inserimento di un Item in testa alla lista: se l'esito *
* è andato a buon fine, viene restituito 1 come flag.			       *
*******************************************************************************/
int bid_list_insert_head( List, Item );

/*******************************************************************************
* int bid_list_insert_tail( List, Item ):				       *
* funzione che esegue l'inserimento di un Item in coda alla lista: se l'esito  *
* è andato a buon fine, viene restituito 1 come flag.			       *
*******************************************************************************/
int bid_list_insert_tail( List, Item );

/*******************************************************************************
* int bid_list_numMember( List ): funzione che restituisce il numero di	       *
* 				  elementi nella lista.		 	       *
*******************************************************************************/
int bid_list_numMember( List );

/*******************************************************************************
* Item bid_list_hasMember( List, Item ): funzione che cerca un Item nella      *
*					 lista, restituendolo se lo trova      *
*******************************************************************************/
Item bid_list_hasMember( List, Item );

/*******************************************************************************
* void bid_list_printList( List ): stampa gli elementi della lista dalla testa *
*******************************************************************************/
void bid_list_printList( List );

/*******************************************************************************
* void bid_list_printInv( List ): stampa gli elementi della lista dalla coda   *
*******************************************************************************/
void bid_list_printInv( List );

/*******************************************************************************
* void bid_list_delete( List, Item ): cancella l'Item passato come argomento   *
* 				      nella lista, se presente.		       *
*******************************************************************************/
void bid_list_delete( List, Item );

/*******************************************************************************
* void bid_list_destroy( List ): distruzione dell'intera lista.		       *
*******************************************************************************/
void bid_list_destroy( List );

/*******************************************************************************
* Item *bid_list_toArray( List, int ): funzione che, data una lista di n Item, *
*				       costruisce un array di n Item.	       *
*******************************************************************************/
Item *bid_list_toArray( List, int );

/*******************************************************************************
* Item *bid_list_arrayToList(List, int): funzione che, dato un array di n Item,*
*				         costruisce una lista di n Item.       *
*******************************************************************************/
List bid_list_arrayToList( Item *, int );

/*******************************************************************************
* Item **bid_list_createArrPointer( List ): costruisce, a partire dalla lista, *
* 				   un array di puntatori agli Item della lista *
*******************************************************************************/
Item **bid_list_createArrPointer( List );

#endif
