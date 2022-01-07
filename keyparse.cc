#include <stdio.h>
#include <stdlib.h>
#include "KP.hh"


int txt2bin(char* key) {
    // A 255 character buffer
    int limit = sizeof(key), i, bin;
    char buff[4096];
    while (*key)
    {
        i += 1;
        bin[i] = itoa(*key, buff, 2);
        ++key;
    }
    return key;
}


int main (int argc, char **argv) {
	int bin = 11010;
	int opt;
	char key[];
	   /* read command line arguments */
    while ((opt = getopt(argc, argv, "k:")) != -1)
	    switch((char)opt) {
	    	case 'k':
		    	key = optarg;
		    	break;
	    	default:
	    		fprintf(stderror, "Unknown command: $s\n", optarg);
	    		exit(1);
    }
    argc -= optind;
    argv += optind;

    printf("key is: %s\n", key);

}