/*******************************************************************************
* Interfaccia per l'oggetto Contenitore              			       *
* N.B.: CONTIENE LE FUNZIONI RICHIESTE NEL PROGETTO ! ! !		       *
*******************************************************************************/

#ifndef CONTENITORE_H
#define CONTENITORE_H

#include "bist_itemkey.h"
#include "bist_Tree.h"
#include "hashTable.h"
#include "graph.h"

/* Definisco un nuovo tipo strutturato con i seguenti campi: Capacita c è la sequenza introdotta dall'utente, e rappresenta appunto le singole capacità dei contenitori. Config a è la configurazione "attuale", quella a cui l'utente è arrivato tramite operazioni di riempimento, svuotamento, travaso (all'inizio, subito dopo crea_contenitori, sarà 0...0). Entrambi i campi sono definiti come array di interi: Caapcita e Config sono lo stesso, tipo, int* . Per distinguere mentalmente una configurazione dall'array delle capacità, che non cambia mai, ho definito questi due tipi, che sono lo stesso anche se si chiamano diversamente. Max è una variabile, inizializzata in crea_contenitori, che contiene la massima capacità inserita dall'utente. Utilizzo questa variabile esclusivamente per la funzione esiste. */

struct contenitore{
	Capacita c;
	Config a;
	int max;
};

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct contenitore" nel tipo "*Contenitore".*
*******************************************************************************/
typedef struct contenitore *Contenitore;

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   FUNZIONI RICHIESTE NEL PROGETTO   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*******************************************************************************
* Contenitore crea_contenitori( int n, int *C ):			       *
* Dato un vettore C = (c1, c2,..., cn ) di interi positivi, inizializza una    *
* sequenza di n contenitori inizialmente vuoti aventi capacità c1, c2,..., cn. *
* Ad esempio, crea contenitori(2, 3, 6) inizializzerà la configurazione        *
* (0[2],0[3],0[6]). Se esiste già una sequenza di contenitori, la cancella e   *
* ne crea una nuova.							       *
*******************************************************************************/
Contenitore crea_contenitori( int n, int *C );

/*******************************************************************************
* int riempi( Contenitore cont, int i ):				       *
* Il contenitore i viene riempito fino all’orlo: il suo livello diventa ci. Ad *
* esempio, riempi(2) sulla configurazione (0[2],2[3],0[6]) porta alla          *
* configurazione (0[2],3[3],0[6]). L’operazione non è valida se il contenitore *
* i è già pieno. In tal caso stampa OPERAZIONE NON VALIDA.		       *
* N.B.: modifico direttamente la configurazione cont->a, presente nell'oggetto *
* puntato dal tipo Contenitore 						       *
*******************************************************************************/
int riempi( Contenitore cont, int i );

/*******************************************************************************
* int svuota( Contenitore cont, int i ):				       *
* Il contenitore i viene svuotato completamente: il suo livello diventa 0. Ad  *
* esempio, svuota(2) sulla configurazione (0[2],2[3],0[6]) porta alla          *
* configurazione (0[2],0[3],0[6]). L’operazione non è valida se il contenitore *
* i è già vuoto. In tal caso stampa OPERAZIONE NON VALIDA.		       *
* N.B.: modifico direttamente la configurazione cont->a, presente nell'oggetto *
* puntato dal tipo Contenitore.					               *
*******************************************************************************/
int svuota( Contenitore cont, int i );

/*******************************************************************************
* int travasa( Contenitore cont, int i, int j ):	                       *
* L’acqua del contenitore i viene versata nel contenitore j fino al completo   *
* riempimento di j o al completo svuotamento di i. Ad esempio, data la 	       *
* configurazione (0[2],3[3],2[6]), travasa(2,1) porta alla configurazione      *
* (2[2],1[3],2[6]) mentre travasa(2,3) porta alla configurazione 	       *
* (0[2],0[3],5[6]) L’operazione non è valida se i è già vuoto o se j è già     *
* pieno. In tal caso stampa OPERAZIONE NON VALIDA.			       *
* N.B.: modifico direttamente la configurazione cont->a, presente nell'oggetto *
* puntato dal tipo Contenitore.						       *
*******************************************************************************/
int travasa( Contenitore cont, int i, int j );

/*******************************************************************************
* void visualizza( Contenitore cont ): Visualizza la configurazione attuale.   *
*******************************************************************************/
void visualizza( Capacita c, Config a, int N );

/*******************************************************************************
* void esiste( int k ): 						       *
* Stampa SI’ oppure NO a seconda che dalla configurazione attuale sia possibile* 
* o no raggiungere una configurazione in cui almeno un contenitore ha livello k*
*******************************************************************************/
void esiste( int *esist, int k );

/*******************************************************************************
* void raggiungibile( Config a ):   					       *
* Dato un vettore a = (a1, a2, ..., an) di interi positivi, stampa SI’ oppure  *
* NO a seconda che dalla configurazione attuale sia possibile raggiungere una  *
* configurazione in cui, per ogni i ∈ {1, 2, ..., n}, il contenitore i ha      *
* livello ai.								       *
*******************************************************************************/
void raggiungibile( Bist_Tree tree, Config a );

/*******************************************************************************
* void configurazioni( int d ): 					       *	
* Stampa tutte le configurazioni raggiungibili dalla configurazione attuale    *
* eseguendo esattamente d operazioni elementari. Ad esempio, dalla             *
* configurazione (2[3],0[5]) con una mossa si possono raggiungere le           *
* configurazioni (3[3],0[5]) con riempi(1), (2[3],5[5]) con riempi(2),         *
* (0[3],0[5]) con svuota(1) e (0[3],2[5]) con travasa(1, 2).		       *
*******************************************************************************/
void configurazioni( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int d );

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   Funzioni di supporto   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*******************************************************************************
* void destroy_contenitori(Contenitore cont): distrugge un oggetto contetitore *
*******************************************************************************/
void destroy_contenitori( Contenitore cont );

/*******************************************************************************
* void ripristina( Contenitore, Config ): copia la configurazione passata come *
* parametro, nel campo a, configurazione della variabile contenitore.	       *  
*******************************************************************************/
void ripristina( Contenitore cont, Config originaria, int N );

/*******************************************************************************
* void print_all( Contenitore, Bist_Tree, HashTable, Graph ): stampa tutte le  *
* 							      mie strutture.   *
*******************************************************************************/
void print_all( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int *esistenze );

/*******************************************************************************
* void set_all( Contenitore, Bist_Tree, HashTable, Graph, int *):	       *
* procedura che prende come parametri un array di contenitori (con capacità e  *
* configurazione), un albero binario, una hashTable, un grafo, un array VUOTI  *
* e riempie con tutte le possibili configurazioni l'albero, con puntatori a    *
* alle configurazioni la hashTable, con gli id associati alle configurazioni   *
* il grafo, e in presenza di ogni livello possibile per i contenitori, setta a *
* 1 l'array, in posizione array[ livello_contenitore ].			       *
*******************************************************************************/
void set_all( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int *esistenze );

/*******************************************************************************
* void free_all( Contenitore, Bist_Tree, HashTable, Graph ):	               *
* procedura che prende come parametri un array di contenitori (con capacità e  *
* configurazione), un albero binario, una hashTable, un grafo e un array pieni * 
* li svuota e li dealloca.		       				       *
*******************************************************************************/
void free_all( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int *esistenze );

/*******************************************************************************
* int get_max_capacita( Contenitore cont ): restituisce la capacità massima    *
* trovata tra la sequenza di contenitori che ha inserito l'utente.	       *
*******************************************************************************/
int get_max_capacita( Contenitore cont );

#endif
