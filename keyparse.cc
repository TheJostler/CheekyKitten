#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "KP.hh"

int *txt2bin(char *txt) {
    static int bin[10];
    int i;

    for(; *txt != 0; ++txt) {
        for( i = 7; i >= 0; --i)
            (*txt & 1 << i) ? bin[i] = 1 : bin[i] = 0;
    }
        return bin;
}


/*
 * Temporary main function with args parsing while testing the new feature
 * This script will contain the functions to cast the key string character array to binary
 * and assign each binary bit to a possition within an array...
 * this will define how the algo switches between ixi and xx output.
 */

int main (int argc, char *argv[]) {
	int opt, i, s, *key;
    char *txtkey;
	   /* read command line arguments */
    while ((opt = getopt(argc, argv, "k:")) != -1)
	    switch((char)opt) {
	    	case 'k':
		    	txtkey = optarg;
		    	break;
    }

    argc -= optind;
    argv += optind;

    printf("key is: %i\n", txtkey);

    int size = 255;
    key=txt2bin(txtkey);
    for (i=0; i < size; i++) {
        s = i % 8;
        printf( "*(key + %d) : %d\n", s, *(key + s));
    }

   return 0;
}