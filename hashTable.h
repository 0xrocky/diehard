/* Interfaccia de */

# ifndef HASH_H
# define HASH_H

#include "bist_itemkey.h"

/* Gli oggetti della hashTable sono sostanzialmente puntatori alle configurazioni. Dato un id, la mia table mi permette di accedere ad una configurazione. Questo per allocare UNA SOLA VOLTA in memoria lo spazio per una possibile configurazione. Ho scelto di implementare la tabella come un vettore, per le caratteristiche proprie dell'array: l'accesso diretto, che costa O(1). Questo, a discapito di effettuare una crezione di una tabella di dimensioni "massime", ed eseguire poi una realloc, solo al momento della conoscenza effettiva del numero di configurazioni create (che avviene alla fine di set_all).
Avrei potuto scegliere di utilizzare una lista, dove non avrei dovuto utilizzare realloc: ma in una lista avrei dovuto costruire degli item appositi, che avessero anche loro id, oltre che puntatore a configurazione; inoltre, e soprattutto, avrei dovuto scorrere tutta lista alla ricerca dell'id cercato, ed avrei avuto quindi un costo di O(n) ogni volta si fosse presentata la necessità di accedere ad una configurazione, dato un id, sia per effettuare una ricerca che un inserimento.
Ma a me la tabella serve proprio per accedere alle configurazioni, è la sua funzione principale.
Invece, sfruttando il fatto che ho definito ID come variabile globale, e quindi ho sempre pieno accesso a questa, posso sfruttarla accedendo direttamente alla posizione desiderata, eseguendo un'operazione tipo hashTable->configurazioni[id]. Questo, ripeto, a scapito di un costo x*O(realloc), perchè per creare la mia hashTable calcolo il numero massimo di configurazioni possibili, eseguendo il prodotto di tutte le mie capacità (limite massimo certamente irraggiungibile: sto creando più spazio di quello che me ne serve!). Una volta che avrò generato tutte le mie possibili configurazioni, in base alle capacità inserite dall'utente, con una funzione sistema apposta per la mia table, successivamente, deallocherò lo spazio inutilizzato. */

/* Capacita è un tipo puntatore ad int: lo definisco nell'interfaccia, poichè ne avrò bisogno in più file.c, e ne potrò disporre includendo questo .h */
typedef int *Capacita;
/* N.B.: Capacita è esattamente lo stesso tipo di Config: per chiarezza mentale ho però creato i due tipi (Capacita qui, Config in bist_item.h), per parlare dell'array delle capacità massime, piuttosto che delle attuali configurazioni. Naturalmente, definisco entrambi i tipi nell'header e non nel .c perchè ne ho bisogno in quasi tutti i files del progetto. */

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct hashtable" nel tipo "*HashTable".    *
* Nell'interfaccia utilizzo SOLO il tipo HashTable, e non struct hashtable, che*
* definisco nell'implementazione( perchè appunto lo uso lì ). HashTable è un   *
* tipo puntatore al tipo strutturato struct hashtable       		       *
*******************************************************************************/
typedef struct hashtable *HashTable;

/*******************************************************************************
* HashTable hashtable_create(): crea una nuova tabella hash vuota	       *
*******************************************************************************/
HashTable hashtable_create( Capacita C, int N );

/*******************************************************************************
* void hashtable_destroy( HashTable h ): distrugge la tabella hash	       *
*******************************************************************************/
void hashtable_destroy( HashTable h );

/*******************************************************************************
* void hashtable_insert(HashTable hash, Config A):			       *
* inserisce nella tabella hash un puntatore ad una configurazione dei          *
* contenitori, inserita nell'albero binario. 				       *
*******************************************************************************/
void hashtable_insert( HashTable hash, Config A );

/*******************************************************************************
* void hashtable_print( HashTable h ): stampa la tabella hash	       	       *
*******************************************************************************/
void hashtable_print( HashTable hash, int N );

/*******************************************************************************
* Config hashtable_get_config(HashTable hash,int n): restituisce la 	       *
* configurazione puntata alla posizione n                                      *
*******************************************************************************/
Config hashtable_get_config( HashTable hash, int n );

/*******************************************************************************
* void hashtable_sistema( HashTable hash ): rialloca uno spazio corretto per   *
* le configurazioni generate con le capacità inserite dall'utente.             *
*******************************************************************************/
void hashtable_sistema( HashTable hash );

/*******************************************************************************
* int hash_get_size( HashTable hash ): restituisce il campo size di hash       *
*******************************************************************************/
int hash_get_size( HashTable hash );

#endif
