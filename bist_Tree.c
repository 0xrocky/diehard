#include <stdio.h>
#include "bist_itemkey.h"
#include "bist_Tree.h"
#include "my_alloc_IO.h"
#include "arrays.h"

/*******************************************************************************
* "struct bist_node" è un tipo strutturato che rappresenta i nodi dell'albero: *
* contiene l'item, più due puntatori dello stesso tipo, che puntano ai figli   *
* del nodo corrente.							       *
* Bist_Item è l'informazione contenuta nel nodo, che può essere di qualunque   *
* tipo (modificabile in item.c).					       *
* l e r sono due link(puntatori) al figlio sinistro e destro rispettivamente.  *
*******************************************************************************/
struct bist_node{			
   Bist_Item item ;
   struct bist_node *l, *r;
};

/*******************************************************************************
* L'albero è una struttura contenente un puntatore a un primo nodo, un counter *
* aggiornato ai nodi presenti nella struttura, più la quantità di contenitori. *
*******************************************************************************/
struct bist_tree{			
   Bist_node root;
   int length;
   int N_contenitori;
};

/* Procedura ricorsiva che distrugge l'albero */
void intern_destroy( Bist_node root );

/* N.B.: ho scelto di definire sia Bist_node che Bist_Tree nell'header, perchè in questo modo ho potuto dichiarare prototipi che comprendessero entrambi i tipi. Mi è stato comodo per non implementare inutilmente esattamente 8 funzioni in più, che non facessero altro che richiamare la corrispondente procedura ricorsiva. Questo perchè tutte le procedure di stampa sono ricorsive, e quindi, se avessi scelto di tenere nel file.h solo il tipo Bist_Tree(puntatore a struct bist_tree), avrei dovuto dichiarare delle funzioni "d'appoggio" che avessero come parametro formale un tipo Bist_Tree, e dentro queste procedure (nella loro implementazione) avrei semplicemente eseguito una chiamata alle funzioni ricorsive vere e proprie. Questo per non perdere il puntatore alla radice del mio albero, Bist_node root.
Questa tecnica è esattamente quello che ho fatto con bist_destroy( Bist_Tree ) e intern_destroy( Bist_node root ): essendo intern_destroy ricorsiva, se non usassi la funzione d'appoggio bist_destroy( Bist_Tree ) che la richiama, ma gli passassi direttamente il campo root della variabile-parametro Bist_Tree (es.: intern_destroy( tree->root ) dove Bist_Tree tree ), poi il puntatore alla radice andrebbe perso. Ma io ho bisogno di tornare indietro, perchè distruggo prima un sottoalbero e poi devo distruggere il secondo sottoalbero della radice. Ecco che quindi ho bisogno di una funzione d'appoggio, in modo da preservare tree->root.
Con la tecnica della "procedura d'appoggio", però, dovrei creare una procedura per ogni procedura ricorsiva (es.: tutte le stampe!), solo per richiamare effettivamente la corrispondente funzione ricorsiva: avrei dovuto implementare più procedure di quelle di cui ho effettivamente bisogno. 
Per esempio, per la procedura destroy era inevitabile fare una funzione d'appoggio, perchè comunque devo anche deallocare la memoria occupata dalla variabile Bist_Tree, che punta a struct bist_tree. Ma per le stampe sarebbe un surplus di codice inutile.
Ecco che allora ho evitato questo inconveniente, dichiarando sia Bist_Node che Bist_Tree nell'interfaccia.h, e utilizzando prototipi che accettassero parametri formali di tipo Bist_Node se queste erano ricorsive, per preservare il campo radice dell'albero. Infatti in questo modo viene fatta una copia del puntatore che passo come parametro, e non sposto effettivamente tree->root, ma una sua copia. */

/******************************************************************************/
void bist_printnode( Bist_node root, int N ){
/* Procedura che "stampa un nodo"(semplificazione per dire che in realtà stampa l'item contenuto in quel nodo, chiamando printBist_Item di itemkey.h) */
	printlnBist_Item( root->item, N );
}
/******************************************************************************/
void bist_preorder( Bist_node root, int N ){
	/* Procedura ricorsiva di visita che stampa la radice, poi si richiama sul sottoalbero di sinistra, infine sul sottoalbero di destra */
	if( root ){
		bist_printnode( root, N );
		bist_preorder( root->l, N );
		bist_preorder( root->r, N );
	}
}
/******************************************************************************/
void bist_inorder( Bist_node root, int N ){
	/* Procedura ricorsiva di visita che richiama se stessa sul sottoalbero di sx, poi stampa la radice, infine si richiama sul sottoalbero di dx */
	if( root ){
		bist_inorder( root->l, N );
		bist_printnode( root, N );
		bist_inorder( root->r, N );
	}
}
/******************************************************************************/
void bist_postorder( Bist_node root, int N ){
	/* Procedura ricorsiva di visita che richiama se stessa a partire dal sottoalbero di sinistra, poi di destra, infine stampa la radice */
	if( root ){
		bist_postorder( root->l, N );
		bist_postorder( root->r, N );
		bist_printnode( root, N );
	}
}
/******************************************************************************/
void bist_orderPrint( Bist_node root, int N ){
	if( !root ) return;
	bist_inorder( root, N );
}
/******************************************************************************/
void bist_invorderPrint( Bist_node root, int N ){
	/* Procedura ricorsiva di stampa che richiama se stessa sul sottoalbero di dx, poi stampa la radice, infine si richiama sul sottoalbero di sx */
	if( root ){
		bist_invorderPrint( root->r, N );
		printBist_Item( root->item, N );
		bist_invorderPrint( root->l, N );
	}
}
/******************************************************************************/
void bist_printSummary( Bist_node root, int spaces, int N ){
	/* Stampo spaces spazi, e il nodo root. Poi incremento il numero degli spazi e richiamo ricorsivamente la procedura */
	printSpaces( spaces );
	bist_printnode( root, N );
	spaces += 2;
	/* Controllo che il nodo non sia una foglia, per non stampare dopo due righe vuote */
	if( !bist_foglia( root ) ){
		if( root->l ) bist_printSummary ( root->l, spaces, N );
		else { printSpaces(spaces); printf("\n"); }
		if( root->r ) bist_printSummary ( root->r, spaces, N );
		else { printSpaces(spaces); printf("\n"); }
	}
}
/******************************************************************************/
Bist_Tree bist_create( int n ){		/* n è la lunghezza della sequenza inserita dall'utente */
	inizialize_ID();		/* Dichiaro la variabile globale ID = 0 */
	Bist_Tree new = my_malloc( sizeof(struct bist_tree) );
	new->N_contenitori = n;  	/* Ora che so la qtà dei contenitori, inizializzo il campo N_contenitori */
	new->length = 0;
	new->root = NULL;
	return new; 
}
/******************************************************************************/
int bist_foglia( Bist_node root ){
	/* Se root ha contemporaneamente figlio destro e sinistro nulli, è una foglia */
	if( !(root->l) && !(root->r) ) return 1;
	else return 0;
}
/******************************************************************************/
Bist_node bist_new( Bist_Item i ){
	/* Alloco lo spazio per una variabile di tipo struct bist_node */
	Bist_node new = my_malloc( sizeof(struct bist_node) );
	/* Copio i passato come argomento, nel campo item della variabile appena creata*/
	new->item = i;
	/* Specifico che sia una foglia( la collocherò poi nella posizione corretta nella procedura insert ) */
	new->l = NULL; new->r = NULL;
	return new;
}
/******************************************************************************/
Bist_Tree bist_arr2tree( Bist_Item a[], int size, int n ){
	int i;
	Bist_Tree new = bist_create( n );  /* n è la qtà dei miei contenitori */
	new->length = size;
	/* Semplicemente richiamo per size volte la procedura insert, inserendo come item gli elementi di a[] */
	for( i = 0; i < size; i++ )
		bist_insert( new, a[i] );
	return new;
}
/******************************************************************************/
Bist_Item bist_min( Bist_Tree tree ){
	Bist_node root = tree->root;
	if( !root ) return NULL_Bist_Item;
	/* Essendo albero binario di ricerca, il minimo sarà la foglia più a sinistra */
	while( root->l )
		root = root->l;
	return root->item;
}
/******************************************************************************/
Bist_Item bist_max( Bist_Tree tree ){
	Bist_node root = tree->root;
	if( !root ) return NULL_Bist_Item;
	/* Essendo albero binario di ricerca, il massimo sarà la foglia più a destra */
	while( root->r )
		root = root->r;
	return root->item;
}
/******************************************************************************/
Bist_Item bist_search( Bist_Tree tree, Bist_Key k ){
	if( !(tree->root) ) return NULL_Bist_Item;
	int flag;
	Bist_node root = tree->root;
	/* Essendo albero binario di ricerca, eseguo una ricerca binaria: se il confronto tra la chiave cercata e quella del nodo corrente è: ...*/
	while( root && (flag = bist_cmp( k, bist_key(root->item) ,tree->N_contenitori )) != 0 )
		/* ...< 0, allora vado a sinistra perchè la chiave cercata è più piccola rispetto quella dove mi trovo ora */
		if( flag < 0 ) root = root->l;
		/* ...> 0, allora vado a destra perchè la chiave cercata è più grande rispetto quella dove mi trovo ora */
		else root = root->r;
	/* Se sono uscito dall'albero alla fine del ciclo, senza aver trovato una corrispondenza, la chiave cercata non c'è */
	if( !root ) return NULL_Bist_Item;
	/* Altrimenti sono uscito durante il ciclo, e root punta al nodo che contiene l'item con la chiave k cercata*/
	else return root->item;
}
/******************************************************************************/
int bist_father( Bist_Tree tree, Bist_Key k, Bist_node *father, Bist_node *son ){
	/* Se l'albero passato come argomento è vuoto esco subito, restituendo un valore negativo */
	if( !(tree->root) ) return -1;
	/* Altrimenti inizializzo a NULL il puntatore al nodo padre, e al primo nodo dell'albero il puntatore al nodo figlio */
	*father = NULL;
	*son = tree->root;
	int flag;
	/* Finchè sono dentro l'albero( quindi *son non è nullo ) e finchè non ho trovato la chiave cercata */
	while( *son && ( flag = bist_cmp(k,bist_key((*son)->item),tree->N_contenitori) ) != 0 ){
		/* Scorro i nodi dell'albero, facendo puntare il nodo padre al nodo figlio */
		*father = *son;
		/* e poi cambiando la freccia del puntatore nodo figlio, a seconda di dove devo proseguire(ramo sx/dx) */
		if( flag < 0 ) *son = (*son)->l;
		else *son = (*son)->r;
	} /* Se sono uscito dall'albero alla fine del ciclo, senza aver trovato una corrispondenza, la chiave cercata non c'è */
	if( *son == NULL ) return -1;
	return 1;
	
}
/******************************************************************************/
int bist_insert( Bist_Tree tree, Bist_Item i ){
	Bist_Key chiave = bist_key(i);
	if( bist_search( tree, chiave ) != NULL_Bist_Item ) return 0; /* Se la chiave c'è già, non inserisco niente */
	/* Altrimenti creo un nuovo nodo new, contenente i passato come argomento...*/
	Bist_node new = bist_new(i), temp = tree->root;
	if( !temp ){ /* ...se l'albero è vuoto, lo inserisco e lo rendo radice */
		tree->root = new;
	}
	else while( 1 ){ /* ...altrimenti procedo con una ricerca binaria per trovare la sua corretta posizione d'inserimento. */
		/* Se il confronto tra la chiave cercata e quella del nodo corrente è < 0, allora vado a sx perchè la chiave cercata è più piccola */
		if( bist_cmp( chiave, bist_key(temp->item), tree->N_contenitori ) < 0 ) /* rispetto quella dove mi trovo */
			/* se ci sono ancora nodi verso dove devo andare, proseguo la ricerca sul ramo di sinistra */
			if( temp->l ) temp = temp->l;
			else{ /* altrimenti rendo new il figlio sinistro del nodo dove sono ora, ed esco dal ciclo*/
				temp->l = new;
				break;
			}
		else{ 
		/* Altrimenti il confronto tra la chiave cercata e quella del nodo corrente è > 0, quindi vado a dx perchè la chiave cercata è più grande */
			if( temp->r ) temp = temp->r; /* se ci sono ancora nodi verso dove devo andare, proseguo la ricerca sul ramo di destra */
			else{ /* altrimenti rendo new il figlio destro del nodo dove sono ora, ed esco dal ciclo*/
				temp->r = new;
				break;
			}
		}
	}
	tree->length += 1;
	add_ID();	/* Ad ogni nuovo inserimento che ha avuto successo, incremento ID */
	return 1;	
}
/******************************************************************************/
int bist_delete( Bist_Tree tree, Bist_Key k ){
	/* temp è il nodo che devo sostituire a son dopo averlo cancellato */
	Bist_node father, son, temp = NULL;
	if( bist_father( tree, k, &father, &son ) == -1 ) return -1;
	/* Caso in cui il nodo da cancellare non ha figli */
	if( bist_foglia( son ) ) temp = NULL;
	/* Caso in cui il nodo da cancellare abbia un figlio */
	else if( son->l && !(son->r) ) temp = son->l; /* Caso in cui son ha un figlio sinistro */
	else if( !(son->l) && son->r ) temp = son->r; /* Caso in cui son ha un figlio destro */
	/* Caso in cui il nodo da cancellare abbia due figli */
	else{	
		/* Cerco il massimo del sottoalbero di sinistra di son */
		temp = son->l;
		Bist_node padre_temp = son;
		while( temp->r ){
			padre_temp = temp;
			temp = temp->r;
		}
		/* temp per forza non ha figlio destro, altrimenti non era temp e la ricerca continuava perchè c'è un solo massimo */
		temp->r = son->r; /* Collego come sottoalbero destro di temp il sottoalbero destro di son, che dovrò cancellare */
		/* Se temp è figlio destro di padre_temp  */
		if( padre_temp->r == temp ){
			/* Collego il figlio sinistro di temp come figlio destro di padre_temp, posto originario di temp: se temp non ha figlio sinistro 				allora è come se mettessi a NULL il nuovo figlio destro di padre_temp; */
			padre_temp->r = temp->l;
			temp->l = son->l;
		}
	}
	/* Sostituisco son con temp */
	if( son == tree->root ) tree->root = temp; 	/* Se son era la radice, temp diventa la nuova radice */
	else if( father->l == son ) father->l = temp; 	/* Se son era figlio sinistro, temp diventa nuovo figlio sinistro del padre di son */
	else father->r = temp; 				/* Se son era figlio destro, temp diventa nuovo figlio destro del padre di son */
	destroyBist_Item( son->item );
	my_free( son );
	tree->length -= 1;
	return 1;
}
/******************************************************************************/
/* Distruggo i nodi dell'albero: non perdo il campo radice dell'albero, anche se intern_destroy è ricorsiva, perchè viene fatta una copia del puntatore passato come parametro, e non sposto effettivamente tree->root nella procedura ricorsiva, ma una sua copia */

void bist_destroy( Bist_Tree tree ){
	if( tree ){	
		intern_destroy( tree->root );
		my_free( tree );		/* Comunque devo anche deallocare la memoria occupata dalla variabile Bist_Tree */
	}
}
/******************************************************************************/
void intern_destroy( Bist_node root ){ /* Procedura ricorsiva vera e propria, che distrugge i nodi dell'albero a partire dal sottoalbero di sinistra, poi */
	if( root ){		       /* il sottoalbero di destra, infine la radice */
		intern_destroy( root->l );
		intern_destroy( root->r );
		destroyBist_Item( root->item );	/* Giustamente distruggo prima l'item, deallocando la memoria occupata */
		my_free( root );		/* E poi il nodo */
	}
}
/******************************************************************************/
int get_N_contenitori( Bist_Tree tree ){
	return tree->N_contenitori;
}
/******************************************************************************/
Bist_node get_root( Bist_Tree tree ){
	return tree->root;
}
/******************************************************************************/
int get_tree_length( Bist_Tree tree ){
	return tree->length;
}
