/*******************************************************************************
* Interfaccia per l'oggetto Item con chiave di tipo Key                        *
*                                                                              *
* N.B: i tipi sono definiti qui, anche se dipendono dall'implementazione!      *
*******************************************************************************/

#ifndef ITEM_H
#define ITEM_H

#define SWITCH_ITEM 1 /* Variabile da modificare in base al tipo voluto */

/* Definizione dei tipi - vanno modificate a seconda dell'implementazione! */

#if SWITCH_ITEM == 1   /* TIPO INTERO */

typedef int Key;
#define NULL_Key -1
typedef Key Item;
#define NULL_Item -1
#endif

#if SWITCH_ITEM == 2   /* TIPO OCCORRENZA */

typedef char *Key;
#define NULL_Key NULL
struct occorrenza{
	Key word;
	int num;
};
#define NULL_Item NULL
typedef struct occorrenza *Item;
#endif

/* Prototitpi di funzione - NON VANNO MAI MODIFICATI */

/*******************************************************************************
* Item newItem(Key k): nel caso di interi,                                     *
*		       newItem(k) restituisce proprio Key k *                  *
*******************************************************************************/
Item newItem( Key k ); 		

/*******************************************************************************
* void destroyItem(Item i): nel caso di interi,                                *
*		       	    destroyItem(i) non fa nulla                        *
*******************************************************************************/
void destroyItem( Item i ); 	

/*******************************************************************************
* void printItem( Item i ): Stampa l'oggetto i                                 *
*******************************************************************************/
void printItem( Item i );

/*******************************************************************************
* void printlnItem( Item i ): Stampa l'oggetto i e va a capo                   *
*******************************************************************************/
void printlnItem( Item i );

/*******************************************************************************
* Key key(Item i): Restituisce la chiave dell'oggetto i:                       *
*		   se Item intero, allora la chiave coincide con i:            *
*		   la chiave è l'oggetto stesso                                *
*******************************************************************************/
Key key( Item i );

/*******************************************************************************
* int cmp( Key k1, Key k2 ): Confronta la prima chiave k1 con la seconda k2    *
*******************************************************************************/
int cmp( Key k1, Key k2 );

/*******************************************************************************
* void printKey(Key k): Stampa la chiave k                      	       *
*******************************************************************************/
void printKey( Key k );

/*******************************************************************************
* void printlnKey(Key k): Stampa la chiave k e va a capo         	       *
*******************************************************************************/
void printlnKey( Key k );

#endif
