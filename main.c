#include <stdio.h>
#include "my_alloc_IO.h"
#include "arrays.h"
#include "bist_itemkey.h"
#include "bist_Tree.h"
#include "itemkey.h"
#include "hashTable.h"
#include "graph.h"
#include "contenitore.h"

/* PROGRAMMA PRINCIPALE - MICHELE CORRIAS MAT.741863 */

int main(void){
	Contenitore cont = NULL;
	Bist_Tree tree = NULL;
	HashTable hash = NULL;
	Graph graph = NULL;
	int *temp = NULL, letti, i, j, *esistenze = NULL;
	char ch;

	while( ( ch = getchar() ) != 'f' ){ 	/* Il ciclo termina quando c e’ ’f’ */
		switch( ch ){
			case 'N':
				/* Memorizzo in temp i numeri letti da input dinamicamente: in "letti" ho la qtà corretta di interi letti effettivamente */
				temp = leggiArray( &letti );
				/* Se l'utente ha già inserito una sequenza di contenitori e vuole inserirne una nuova, cancello e dealloco tutte le */
				if( cont != NULL ) free_all( cont, tree, hash, graph, esistenze ); /* strutture precedentemente create */
				/* Creo una nuova sequenza di contenitori, copiando da temp le capacità singole */
				cont = crea_contenitori( letti, temp );
				/* Dealloco il vettore di int letto, per evitare memory-leak: ora ho tutto ciò che mi serve in cont */
				my_free( temp );
				/* Creo il mio albero di configurazioni, inizializzando N_Contenitori con letti */
				tree = bist_create( letti );
				/* Creo la mia tabella (di massima capacità) di puntatori a configurazioni presenti nell'albero */
				hash = hashtable_create( cont->c, letti );
				/* Creo un grafo (di massima capacità) di id delle configurazioni presenti nell'albero */
				graph = graph_create( hash_get_size( hash ) );
				/* Creo un vettore lungo quanto la massima capacità inserita dall'utente */
				esistenze = my_calloc( (get_max_capacita(cont)+1),sizeof(int) );
				/* Riempio le mie strutture */
				set_all( cont, tree, hash, graph, esistenze );
				break;
			case 'R':
				scanf("%d",&i);
				/* Se il contenitore letto sfora dalla sequenza, o il contenitore i è già pieno, stampo un messaggio */
				if( i > letti || !riempi(cont,i) ) printf("\nOPERAZIONE NON VALIDA\n");
				break;
			case 'S':
				scanf("%d",&i);
				/* Se il contenitore letto sfora dalla sequenza, o il contenitore i è già vuoto, stampo un messaggio */
				if( i > letti || !svuota(cont,i) ) printf("\nOPERAZIONE NON VALIDA\n");
				break;
			case 'T':
				scanf("%d %d",&i,&j);
				/* Se i contenitori letti sforano dalla sequenza, o il contenitore i è già vuoto o quello j già pieno stampo un messaggio */
				if( i > letti || j > letti || !travasa(cont,i,j) ) printf("\nOPERAZIONE NON VALIDA\n");
				break;
			case 'v':
				visualizza( cont->c, cont->a, letti );
				printf("\n");
				break;
			case 'e':
				scanf("%d",&i);
				/* Se si richiede un livello maggiore del massimo livello raggiungibile nella sequenza, non eseguo neanche esiste() */
				if( i > (get_max_capacita(cont)) ){ printf("\nNO\n"); break;}
				else esiste( esistenze, i );
				break;
			case 'r':
				/* Leggo una sequenza di interi, presupponendo già di conoscerne la lunghezza (scoperta in case N) */
				temp = read_arr_knowing_length( letti );
				raggiungibile( tree, temp );
				my_free( temp ); /* Dealloco il vettore di int letto, per evitare memory-leak. */
				break;	
			case 'c':
				scanf("%d",&i);
				configurazioni( cont, tree, hash, graph, i );
				break;
		}
	}
	/* Prima di uscire definitivamente dal programma, dealloco definitivamente tutte le strutture che ho creato */
	free_all( cont, tree, hash, graph, esistenze );
	return 0;
}
