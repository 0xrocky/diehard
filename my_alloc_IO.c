#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_alloc_IO.h"
#define INIT_SIZE 5

/******************************************************************************/
void *my_malloc( size_t size ){
	void *p;
	p = malloc( size );
	if( !p ){
		printf("malloc_failure\n");
		exit( EXIT_FAILURE );
	}
	else return p;
}
/******************************************************************************/
void *my_realloc( void *p, size_t size ){
	void *temp;
	temp = realloc( p, size );
	if( !temp ){
		printf("realloc_failure\n");
		exit( EXIT_FAILURE );
	}
	else return temp;
}
/******************************************************************************/
void *my_calloc( size_t nmemb, size_t size ){
	void *p;
	p = calloc( nmemb,size );
	if( !p ){
		printf("calloc_failure\n");
		exit( EXIT_FAILURE );
	}
	else return p;
}
/******************************************************************************/
void my_free( void *p ){
	free( p );
}
/******************************************************************************/
char *read_word(void){
	int count = 0, size = INIT_SIZE;
	char ch, *p = my_malloc( size*sizeof(char) );
	while( (ch = getchar()) != EOF ){
		if( count == size ){
			size *= 2;
			p = my_realloc( p, size );
		}
		if( !isalnum(ch) ){
			p[count] = '\0';
			break;
		}
		p[count++] = ch;
	}
	return p;
}
/******************************************************************************/
char *read_line(void){
	int count = 0, size = INIT_SIZE;
	char ch, *p = my_malloc( size*sizeof(char) );
	while( (ch = getchar()) != EOF ){
		if( count == size ){
			size += 10;
			p = my_realloc( p, size );
		}
		if( ch == '\n' ){
			p[count] = '\0';
			break;
		}
		p[count++] = ch;
	}
	return p;
}
