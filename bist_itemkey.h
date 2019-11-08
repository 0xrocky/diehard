/*******************************************************************************
* Interfaccia per l'oggetto Bist_Item con chiave di tipo Bist_Key              *
* i bist_item sono item ad uso ESCLUSIVO dell'albero binario di ricerca!: gli  *
* altri item, definiti in itemkey.h, sono classici interi, e vengono utilizzati*
* dalle altre strutture, che hanno come oggetti gli id associati alle conf.    *
*******************************************************************************/

#ifndef BIST_ITEM_H
#define BIST_ITEM_H

/* L'idea implementativa del mio progetto si basa su un albero binario di ricerca, su una hashtable e su grafo. Ho associato ad ogni configugarazione un id: ID rappresenta sempre il prossimo ID disponibile, da associare ad una prossima configurazione.
L'albero serve per cercare le configurazioni, struttura ottimale con un costo i O(log n configurazioni), e data una configurazione, mi permette di risalire al suo id. La hashtable fa esattamente l'operazione inversa: dato un id, mi permette di risalire alla sua configurazione. Il grafo, di id, evidenzia le connessioni possibili tra le varie configurazioni, che si vengono a creare con UNA operazione elementare. */

int ID;		   /* Variabile globale che terrà conto delle configurazioni inserite nell'albero. Rappresenta la funzione che associa un id a una configurazione. Essendo un valore comune e condiviso in tutto il progetto, ed essendo anche una semplice variabile intera, ho deciso di dichiarare ID come variabile globale.
N.B.: non posso usare il campo length dell'albero, perchè ho bisogno di assegnare ad un item già un'id, a prescindere dalla creazione dell'albero. In pratica nell'implementazione dei nodi dell'albero non posso già avere accesso ai suoi campi, perchè ancora non esiste! Sarebbe un controsenso. Quindi utilizzo una variabile globale, che incremento ad ogni nuovo inserimento di un item nell'albero. Essendo una quantità che cambia durante il corso del programma ad ogni nuovo inserimento nell'albero, ho deciso di dichiarare ID qui nell'interfaccia degli oggetti dell'albero. Siccome ne ho bisogno praticamente in tutti i file .c, ho deciso di dichiararla come variabile globale nell'header, inizializzarla a 0 al momento della creazione dell'albero, e incrementarla man mano con ogni inserimento. */

/* Config è un tipo puntatore ad int: lo definisco nell'interfaccia, poichè ne avrò bisogno in più file.c, e ne potrò disporre includendo questo .h */
typedef int *Config;

typedef Config Bist_Key;	/* La chiave negli alberi è una configurazione assumibile dai contenitori */
#define NULL_Bist_Key NULL
struct configurazione{		/* Una struct configurazione è un tipo che definisce una configurazione dei contenitori, e il suo id associato */
	Bist_Key livello;
	int id;			/* L'id di ogni nodo verrà definito da ID, subito prima di incrementare ID naturalmente */
};
typedef struct configurazione *Bist_Item; /* Gli Item nell'albero sono puntatori a configurazioni */
#define NULL_Bist_Item NULL

/* Prototipi di funzione - NON VANNO MAI MODIFICATI */

/*******************************************************************************
* void inizialize_ID(): inizializza la variabile globale ID     	       *
* void add_ID(): 	incrementa automaticamente la variabile globale ID     *
* int return_ID(): 	restituisce la variabile globale ID 		       *                       
*******************************************************************************/
void inizialize_ID();
void add_ID();
int return_ID();

/*******************************************************************************
* Bist_Item newBist_Item(Bist_Key k): crea un nuovo item apposito per alberi   *
*******************************************************************************/
Bist_Item newBist_Item( Bist_Key k, int N  ); 		

/*******************************************************************************
* void destroyBist_Item(Bist_Item i): dealloca un item, apposito per alberi    *
*******************************************************************************/
void destroyBist_Item( Bist_Item i ); 	

/*******************************************************************************
* void printBist_Item( Bist_Item i ): Stampa l'oggetto i                       *
*******************************************************************************/
void printBist_Item( Bist_Item i, int N );

/*******************************************************************************
* void printlnBist_Item( Bist_Item i ): Stampa l'oggetto i e va a capo         *
*******************************************************************************/
void printlnBist_Item( Bist_Item i, int N );

/*******************************************************************************
* Bist_Key bist_key(Bist_Item i): Restituisce la chiave dell'oggetto i:        *
*******************************************************************************/
Bist_Key bist_key( Bist_Item i );

/*******************************************************************************
* int bist_cmp(Bist_Key k1, Bist_Key k2): Confronta la prima chiave con la     *
* 					  seconda.			       *
*******************************************************************************/
int bist_cmp( Bist_Key k1, Bist_Key k2, int N );

/*******************************************************************************
* void printBist_Key(Bist_Key k): Stampa la chiave k                           *
*******************************************************************************/
void printBist_Key( Bist_Key k, int N );

/*******************************************************************************
* void printlnBist_Key(Bist_Key k): Stampa la chiave k e va a capo    	       *
*******************************************************************************/
void printlnBist_Key( Bist_Key k, int N );

#endif
