#include <stdio.h>
#include <stdlib.h>



void baseline ( unsigned n , float a [ n ] , float b [ n ] , float c [ n ]) {
	unsigned i ;
	for ( i =0; i < n ; i ++) {
		if ( i < n /3)
			c [ i ] = a [ i ] * b [ i ];
		else
			c [ i ] = a [ i ] - b [ i ];
	}
	
	
	for ( i =1; i < n ; i ++)
		c [ i ] *= 2;
}
