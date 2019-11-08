/* Albero binario di ricerca( alberi con radice ordinati dove ogni nodo ha al più 2 figli (destro/sinistro), tale che l < root < r ) */

#ifndef BIST_TREE
#define BIST_TREE

#include "bist_itemkey.h"

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct bist_node" nel tipo "*Bist_node"     *
* Nell'interfaccia utilizzo SOLO il tipo Bist_node, e non struct bist_node,    *
* che invece definisco nell'implementazione( perchè appunto lo uso lì ).       *
* Bist_node è un puntatore al tipo strutturato struct bist_node		       *
*******************************************************************************/
typedef struct bist_node *Bist_node;

/*******************************************************************************
* Ridefinisco il tipo strutturato "struct bist_tree" nel tipo "*Bist_Tree"     *
* Nell'interfaccia utilizzo SOLO il tipo Bist_Tree, e non lo struct bist_      *
* che invece definisco nell'implementazione( perchè appunto lo uso lì ).       *
* Bist_Tree è un puntatore al tipo strutturato struct bist_tree		       *
*******************************************************************************/
typedef struct bist_tree *Bist_Tree;


/*******************************************************************************
* void bist_printnode( Bist_node root ): stampa un singolo nodo (stampa il     *
*					 campo item, richiamando               *
*					 printBist_Item(root->item) )          *
*******************************************************************************/
void bist_printnode( Bist_node root, int N );

/*******************************************************************************
* void bist_preorder( Bist_node root ): visita in ordine antcipato( root,l,r ) *
*******************************************************************************/
void bist_preorder( Bist_node root, int N );

/*******************************************************************************
* void bist_inorder( Bist_node root ): visita in ordine simmetrico( l,root,r ) *
*******************************************************************************/
void bist_inorder( Bist_node root, int N );

/*******************************************************************************
* void bist_postorder(Bist_node root): visita in ordine posticipato (l,r,root) *
*******************************************************************************/
void bist_postorder( Bist_node root, int N );

/*******************************************************************************
* void bist_orderPrint( Bist_node root ): stampa in ordine crescente di chiave *
*******************************************************************************/
void bist_orderPrint( Bist_node root, int N );

/*******************************************************************************
* void bist_invorderPrint( Bist_node root ): stampa l'albero ordinato in       *
*					     ordine decrescente di chiave      *
*******************************************************************************/
void bist_invorderPrint( Bist_node root, int N );

/*******************************************************************************
* void bist_printSummary( Bist_node root, int spaces ):                        *
visitando in preorder l'albero, stampa il contenuto dei nodi, indentando       *
correttamente. Nel caso in cui un  nodo abbia un solo figlio, per poter        *
distinguere tra figlio destro e sinistro, stampa con una riga vuota l’assenza  *
del figlio mancante. N.B.: ausilio di printSpaces(int) in definita in arrays.  *
*******************************************************************************/
void bist_printSummary( Bist_node root, int spaces, int N ); 

/*******************************************************************************
* Bist_Tree bist_create(int n ): funzione che inizializza un albero binario di *
* ricerca, ovvero restituisce un puntatore ad un albero vuoto. 		       *
*******************************************************************************/
Bist_Tree bist_create( int n );

/*******************************************************************************
* int bist_foglia( Bist_node root ): torna 1 se root punta a una foglia, o 0   * 
*******************************************************************************/
int bist_foglia( Bist_node root );

/*******************************************************************************
* Bist_node bist_new(Bist_Item i):					       *
* crea un nuovo nodo, copiando i nel suo campo item e inizializzando figlio    *
* sinistro e destro a NULL, e restituisce il suo indirizzo.		       *
*******************************************************************************/
Bist_node bist_new( Bist_Item i );

/*******************************************************************************
* Bist_Tree bist_arr2tree(Bist_Item a[], int size):			       *
* costruisce l’albero binario completo con radice a[0]			       *
*******************************************************************************/
Bist_Tree bist_arr2tree( Bist_Item a[], int size, int n );

/*******************************************************************************
* Bist_Item bist_min( Bist_Tree tree ): restituisce l'item con chiave minima   *
*******************************************************************************/
Bist_Item bist_min( Bist_Tree tree );

/*******************************************************************************
* Bist_Item bist_max( Bist_Tree tree ): restituisce l'item con chiave massima  *
*******************************************************************************/
Bist_Item bist_max( Bist_Tree tree );

/*******************************************************************************
* Bist_Item bist_search(Bist_Tree tree,Bist_Key k): 			       *
* ritorna l'item con chiave k, o NULL_Item se questo non esiste.	       *
*******************************************************************************/
Bist_Item bist_search( Bist_Tree tree, Bist_Key k );

/*******************************************************************************
* int bist_father(Bist_Tree tree,Bist_Key k,Bist_node *father,Bist_node *son)  *
* cerca il nodo con chiave k nel sottoalbero di radice root, ne memorizza      *
* l'indirizzo in son, e l'indirizzo del padre in father. Nel caso in cui non   *
* esistano nodi con chiave k, restituisce -1, son = NULL e father punta alla   *
* foglia alla quale attaccare eventualmente k                                  *
*******************************************************************************/
int bist_father( Bist_Tree tree, Bist_Key k, Bist_node *father, Bist_node *son );

/*******************************************************************************
* int bist_insert( Bist_Tree tree, Bist_Item i ):			       *	
* inserisce un oggetto i di tipo Bist_Item nell'albero di ricerca: se esiste   *
* un nodo con la stessa chiave, non inserisce niente e torna 0, altrimenti 1.  *
*******************************************************************************/
int bist_insert( Bist_Tree tree, Bist_Item i );

/*******************************************************************************
* int bist_delete( Bist_Tree tree, Bist_Key k ):                               *
* Procedura che cancella il nodo con chiave k di tipo Bist_Key nell'albero di  *
* ricerca passato per indirizzo tramite *root. Se non esiste tale nodo con     *
* chiave k, restituisce -1 . 						       *
*******************************************************************************/
int bist_delete( Bist_Tree tree, Bist_Key k );

/*******************************************************************************
* void bist_destroy( Bist_Tree tree ): ricorsivamente distrugge tutto l'albero *
*******************************************************************************/
void bist_destroy( Bist_Tree tree );

/*******************************************************************************
* int get_N_contenitori( Bist_Tree ): restituisce quanti contenitori ci sono.  *
*******************************************************************************/
int get_N_contenitori( Bist_Tree tree );

/*******************************************************************************
* Bist_node get_root(Bist_Tree tree): restituisce la radice dell'albero        *
* N.B.: molto utile in quanto non ho accesso diretto ai campi dell'albero in   *
* files esterni alla sua implementazione (es.: nel main), ma ne ho bisogno in  *
* quanto ho molte procedure ricorsive (es.: tutte quelle di stampa) a cui devo *
* passare come parametro la radice dell'albero.				       *
*******************************************************************************/
Bist_node get_root( Bist_Tree tree );

/*******************************************************************************
* int get_tree_length( Bist_Tree ): restituisce quanti nodi ci sono.  	       *
*******************************************************************************/
int get_tree_length( Bist_Tree tree );

#endif
