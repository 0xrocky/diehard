/*******************************************************************************
* Implementazione dell'interfaccia itemkey.h, nel caso in cui Item INTERO e la *
* chiave dell'Item è l'intero stesso.					       *
*                                                                              *
* N.B: per semplicità i tipi sono definiti in itmkey.h                         *
*******************************************************************************/

#include <stdio.h>
#include "itemkey.h"


/******************************************************************************/
Item newItem( Key k ){
	return k;
}
/******************************************************************************/
void destroyItem( Item i ){
}
/******************************************************************************/
void printItem( Item i ){
	if( i != NULL_Item )
		printf("%d ",i);
}
/******************************************************************************/
void printlnItem( Item i ){
	printItem( i );
	printf("\n");
}
/******************************************************************************/
Key key( Item i ){
	if( i == NULL_Item ) return NULL_Key;
	else return i;
}
/******************************************************************************/
int cmp( Key k1, Key k2 ){
	return k1 - k2;
}
/******************************************************************************/
void printKey( Key k ){
	printf("%d ",k);
}
/******************************************************************************/
void printlnKey( Key k ){
	printKey( k );
	printf("\n");
}
