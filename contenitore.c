/*******************************************************************************
* Implementazione dell'interfaccia contenitore.h                               *
*******************************************************************************/

#include <stdio.h>
#include "my_alloc_IO.h"
#include "arrays.h"
#include "bist_itemkey.h"
#include "bist_Tree.h"
#include "hashTable.h"
#include "graph.h"
#include "contenitore.h"

/* crea_contenitori inizializza una variabile contenitore: l'idea implementativa è che l'utente, quando effettua una qualsiasi operazione elementare, in realtà cambia il campo a, che rappresenta la configurazione attuale, mentre c (la sequenza di capacità) e max (la massima capacità tra tutte) restano invariate. Precedentemente però (esattamente nel main, subito dopo aver letto la sequenza e creato una variabile contenitore) io genero tutte le configurazioni raggiungibili dalle capacità che l'utente ha inserito, e inizializzo delle "strutture di supporto" per le varie operazioni che l'utente può compiere.  */

Contenitore crea_contenitori( int n, int *C ){
	Contenitore new = my_malloc( sizeof(struct contenitore) );
	new->c = my_malloc( n*sizeof(int) );
	new->a = my_calloc( n,sizeof(int) );
	new->max = max_capacita( n, C );
	int i;
	for( i = 0; i < n; i++ ) new->c[i] = C[i];
	return new;
}
/******************************************************************************/
/* Le seguenti operazioni elementari non generano effettivamente una nuova configurazione, ma modificano quella della variabile contenitore (a). Decremento in ogni operazione elementare la variabile i perchè l'utente inserisce numeri da 1 a N. Ma io sto lavorando su array, quindi su indici da 0 a N-1. */

int riempi( Contenitore cont, int i ){
	--i;
	if( cont->a[i] < cont->c[i] ){
		cont->a[i] = cont->c[i];
		return 1;
	}
	return 0;
}
/******************************************************************************/
int svuota( Contenitore cont, int i ){
	--i;
	if( cont->a[i] != 0 ){
		cont->a[i] = 0;
		return 1;
	}
	return 0;
}
/******************************************************************************/
int travasa( Contenitore cont, int i, int j ){
	if( i == j ) return 0;	/* Esco subito se il contenitore da svuotare è identico a quello da travasare */
	--i; --j;
	if( cont->a[i] == 0 || cont->a[j] == cont->c[j] ) return 0;
	else while( cont->a[i] != 0 && cont->a[j] < cont->c[j] ){
		cont->a[i]--;
		cont->a[j]++;
	}
	return 1;
}
/******************************************************************************/
void visualizza( Capacita c, Config a, int N ){
	int i;
	printf("(");
	for( i = 0; i < N; i++ ){
		printf("%d[%d]", a[i], c[i] );
		if( i == N-1 ) break;
		printf(", ");
	}
	printf(")\n");
}
/******************************************************************************/
/* Per l'implementazione di esiste( k ) sfrutto il fatto che non può esistere un livello k di un qualsiasi contenitore maggiore della massima capacità introdotta dall'utente. Quindi creo un vettore esistenze, lungo quanto la massima capacità inserita dall'utente +1. Questo perchè esistenze dev'essere un array che ha come indici da 0 alla capacità massima (es.: N 3 5 -->> esistenze[0]...esistenze[5]), e contiene 1 o 0:
- 1 se l'indice dell'array è un livello che è stato raggiunto da almeno un contenitore; 
- 0 altrimenti. 
Il vettore esistenze poi rimane allocato nel main (insieme a tutte le mie altre strutture "di supporto"), sino a che l'utente non inserisce una nuova sequenza. E' un'ottima soluzione, in quanto il costo di un inserimento in un array è praticamente nullo, perchè avviene tramite accesso diretto (e gli inserimenti in esistenze[] avvengono in set_all(), quando popolo tutte le mie strutture).
Successivamente, verificare lo stato di una posizione del'array conoscendone l'indice, è ancora nullo! Questo è quello che fa esiste: in pratica, il costo di esiste( k ) è O(1); lo spazio che richiede esistenze sarà O(contenitore->max+1). */

void esiste( int *esist, int k ){
	if( esist[k] == 1 ) printf("\nSI'\n");
	else printf("\nNO\n");
}
/******************************************************************************/
/* Io riempio un albero binario di ricerca con tutte le configurazioni possibili che sono riuscito a generare. Quindi per eseguire raggiungibile( a[] ) semplicemente ricerco nel mio albero, già implementato in case N: se a è una chiave già presente nell'albero, stamperò SI', oppure NO.
La ricerca costerà O(log ID): ID perchè, una volta terminati tutti gli inserimenti nell'albero, ID è aggiornata al numero successivo l'ultimo id che ho assegnato per l'ultima configurazione. Lo spazio richiesto dall'albero sarà O( ID*N_contenitori ), perchè ogni array è composto da N_contenitori interi. */

void raggiungibile( Bist_Tree tree, Config a ){
	if( bist_search( tree, a ) != NULL_Bist_Item ) printf("\nSI'\n");
	else printf("\nNO\n");
}
/******************************************************************************/
/* Per configurazioni utilizzo una tabella HashTable, che sarebbe un array di ID puntatori a configurazioni inserite nell'albero; e un grafo di ID interi, che sarebbero gli id associati alle configurazioni (generati dopo l'albero in case N). Se l'utente vuole vedere che configurazioni può raggiungere dalla configurazione attuale, prima recupero l'id della configurazione a cui l'utente è arrivato nell'albero. Poi chiamo una procedura ricorsiva che si basa su una visita in profondità del grafo, e che stampa appunto le configurazioni (recuperandole dai puntatori nella hashtable) grazie agli id visitati nel grafo. 
N.B.: se l'utente digita 0, non eseguo nemmeno la funzione ricorsiva: l'unica posizione raggiungibile con 0 mosse è quella dove sono!
Il costo di configurazioni è dato da: la ricerca dell'albero + l'allocazione di n_V interi, a 0, dove n_V sono i nodi del grafo (=ID) + il costo di graph_config. Quindi O(log n_V) + O(n_V) + O(m_E) = O( n_V+m_E );

N.B.: il costo di recupero di una configurazione, dato un id è O(1), perchè la tabella hash è un vettore.
Lo spazio occupato dalla mia hashtable sarà O( ID puntatori ), mentre lo spazio occupato dal grafo sarà O( n+m ). Lo spazio che richiederà configurazioni, quindi, sarà nel caso peggiore quello richiesto dallo stack per la ricorsione, più ovviamente l'array delle marche: O(n) + O(n) = O(n). */

void configurazioni( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int d ){
	if( d <= 0 ){ 
		visualizza( cont->c, cont->a, get_N_contenitori(tree) );
		return;
	}
	else{
		Bist_Item item = bist_search( tree, cont->a );
		int *marche = my_calloc( ID,sizeof(int) );
		int flag = graph_config( cont->c, hash, graph, item->id, d, marche, get_N_contenitori(tree) );
		my_free( marche );
	}
	
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   Funzioni di supporto   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/******************************************************************************/
void destroy_contenitori( Contenitore cont ){
	if( cont ){
		my_free( cont->c );
		my_free( cont->a );
		my_free( cont );
	}
}
/******************************************************************************/
/* Data una variabile di tipo contenitore e una configurazione, copia i valori della configurazione passata nel campo a, configurazione di contenitore. Questa procedura è particolarmente utile perchè in set_all io genero tutte le mie possibili configurazioni, partendo dalla prima configurazione che ho creato (0...0) ed eseguendo a cascata tutte le operazioni elementari (riempi/svuota/travasa), modificando il campo cont->a della variabile contenitore: quindi io non creo spazio, ma modifico una configurazione già allocata, verifico se questa è presente, se no la inserisco in albero, creando un nuovo item(e allocando qui effettivamente spazio per questa), e in tabella un puntatore a questa, e nel grafo il suo id. Se sì inserisco solo nel grafo.
Il problema sta nel fatto che già dopo riempi(1), la mia configurazione iniziale da 0...0 diventerà 1...0; poi però io devo ritornare alla configurazione "originaria" (i-esima) per eseguire le restanti operazioni: riempi(2), riempi(3)...riempi(n)...svuota(n)...travasa(n,k).
Questa procedura mi permette di fare ciò, prelevando prima dalla mia hashtable la configurazione originaria, su cui sto facendo tutte le mie possibili modifiche, e passandola come parametro assieme alla variabile contenitore. */

void ripristina( Contenitore cont, Config originaria, int N ){
	int i;
	for( i = 0; i < N; i++ )
		cont->a[i] = originaria[i];
}
/******************************************************************************/
void print_all( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int *esistenze ){
	int i;
	visualizza( cont->c, cont->a, get_N_contenitori(tree) );
	bist_printSummary( get_root(tree), 0, get_N_contenitori(tree) );
	hashtable_print( hash, get_N_contenitori(tree) );
	graph_print( graph );
	for( i = 0; i <= get_max_capacita(cont); i++ ) printf("%d: %d ",i,esistenze[ i ]);
	printf("\n\n");
}
/******************************************************************************/
/* Questa procedura prende come parametri una sequenza di contenitori (con capacità c e configurazione a iniziale 0...0), un albero binario di ricerca, una tabella hashTable, un grafo e un array di interi vuoti, e li riempie.
Genera tutte le configurazioni possibili ottenibili  dalle n capacità di c, e popola l'albero di queste, la tabella di puntatori a queste, il grafo di id associati alle configurazioni, e l'array di esistenze dei possibili livelli che si vengono a creare man mano.
Per prima cosa viene inserita la configurazione iniziale 0...0, già presente in cont, nell'albero. Ogni volta che un inserimento nell'albero ha successo, allora inserisco anche nella hashtable un puntatore alla configurazione appena generata, in posizione hashtable[ID-1], perchè incremento automaticamente ID con bist_insert.
Successivamente, nel ciclo for più esterno, prelevo la prima configurazione presente in tabella (so che c'è: è quella che ho appena inserito! 0...0. ID sarà sicuramente a 1 ora), e salvo il suo indirizzo in attuale. I cicli for più interni eseguono a cascata tutte le possibili operazioni di riempimento, svuotamento e travasamento della configurazione attuale, modificando però la configurazione di cont, così da non allocare spazio in memoria inutilmente:

 - riempio esistenze[] di 1 dove si verifica uno stadio possibile, usando proprio come indici per accedere all'array i diversi livelli;

 - faccio una ricerca nell'albero: se la ricerca della configurazione nell'albero appena generata dalla modifica dell'operazione elementare ha esito negativo, allora creo un nuovo item per l'albero con la suddetta chiave (allocando ora spazio in memoria), e inserisco nella tabella un puntatore alla chiave (chiamo una funzione insert per hashTable che fa puntare hashTable->configurazioni[id configurazione inserita nell'albero] alla configurazione appena inserita nell'albero. Questo perchè appunto gli elementi della table sono puntatori a configurazioni, a cui accedo con gli id delle corrispondenti configurazioni).
 
 - altrimenti by-passo l'inserimento, e inserisco direttamente un arco dall'item della configurazione attuale a quella dove sono arrivato. N.B.: per il grafo, devo sempre e comunque inserire un lato, sia che creo una nuova configurazione o meno. */


void set_all( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int *esistenze ){
	Bist_Item item = NULL; 
	Config attuale = NULL;
	int i, j, k;
	/* Inserisco la configurazione iniziale 0...0 nell'albero e nella tabella */
	item = newBist_Item( cont->a, get_N_contenitori(tree) );
	if( bist_insert( tree, item ) ) hashtable_insert( hash, bist_key(item) );
	
	/* Genero tutte le possibili configurazioni, e man mano creandole le inserisco anche nelle mie strutture se è il caso */
	for( i = 0; i < ID; i++ ){
		/* Prendo una configurazione dalla mia tabella hash: ID verrà incrementato ad ogni inserimento nell'albero */
		attuale = hashtable_get_config( hash, i );
		/* Eseguo tanti riempimenti, svuotamenti, travasi quanti contenitori ho */
		for( j = 1; j <= get_N_contenitori(tree); j++ ){
			/* Ogni volta riprisitino il contenitore alla configurazione i-esima perchè viene continuamente modificato ad ogni iterazione */
			ripristina( cont, attuale, get_N_contenitori(tree) ); 							/* dei for più interni */
			/* Pongo a 1 gli stadi che si presentano: alla fine del for più esterno, in esistenze[] saranno settati a 1 gli stadi possibili */
			esistenze[ attuale[j-1] ] = 1;
			/* CASO DI RIEMPI */
			if( riempi( cont, j ) ){
				item = bist_search( tree, cont->a );	 /* cerco la configurazione appena creata, per vedere se c'è già */
				if( item == NULL_Bist_Item ){    	 /* se non presente, la inserisco nell'albero */
					item = newBist_Item(cont->a,get_N_contenitori(tree)); /* creando un nuovo item con la configurazione come chiave */
					if( bist_insert( tree, item ) )	
						hashtable_insert( hash, bist_key(item) ); /* e inserisco un puntatore alla configurazione nella tabella */
				}			  /* altrimenti, se la ricerca non ha esito negativo, vuol dire che nell'albero era già presente */
				graph_edgeinsert( graph, i, item->id );	/* in ogni caso, che sia appena stata creata o era già presente, recupero il suo */
			}						/* id, e inserisco un arco tra l'id della configurazione attuale e questo */
		}
		for(j = 1; j <= get_N_contenitori(tree); j++){
			ripristina( cont, attuale, get_N_contenitori(tree) );
			/* CASO DI SVUOTA */
			if( svuota( cont, j ) ){
				item = bist_search( tree, cont->a );
				if( item == NULL_Bist_Item ){
					item = newBist_Item(cont->a,get_N_contenitori(tree));
					if( bist_insert( tree, item ) )
						hashtable_insert( hash, bist_key(item) );
				}
				graph_edgeinsert( graph, i, item->id );
			}
		}
		for(j = 1; j <= get_N_contenitori(tree); j++){
			for (k = 1; k <= get_N_contenitori(tree); k++){
				ripristina( cont, attuale, get_N_contenitori(tree) );
				/* CASO DI TRAVASA */
				if( travasa( cont, j, k ) ){			
					item = bist_search( tree, cont->a );
					if( item == NULL_Bist_Item ){
						item = newBist_Item(cont->a,get_N_contenitori(tree));
						if( bist_insert( tree, item ) )
							hashtable_insert( hash, bist_key(item) );
					}
					graph_edgeinsert( graph, i, item->id );
				}
					
			}
		}
	}
	ripristina( cont, hashtable_get_config( hash, 0 ), get_N_contenitori(tree) ); 	/* Rimetto cont->a a 0...0 */
	hashtable_sistema( hash );							/* Libero lo spazio in eccesso per la tabella, e per il grafo */
	graph_sistema( graph );
}
/******************************************************************************/
/* Questa procedura dealloca lo spazio per tutte le mie strutture di supporto, più la sequenza di contenitori */

void free_all( Contenitore cont, Bist_Tree tree, HashTable hash, Graph graph, int *esistenze ){
	destroy_contenitori( cont );
	bist_destroy( tree );
	hashtable_destroy( hash );
	graph_destroy( graph );
	my_free( esistenze );
}
/******************************************************************************/
/* Funzione particolarmente utile per il caso di esiste: restituisce il campo max, che indica la massima capacità tra tutte quelle nella sequenza */

int get_max_capacita( Contenitore cont ){
	return cont->max;
}
