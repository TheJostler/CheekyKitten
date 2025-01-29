#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "algo.h"
#include "sha-256.h"

#define BUFSZ 8

int xor(int data, int key){
    // XOR the data to encrypt.
    return data ^ key;
}

int hexShift(int i, unsigned char buf[BUFSZ], int flip, int binary, FILE *fo){
    if (i%2 == 0) {
        int x = buf[i];
        int y = buf[i+1];
            //and here!
        if (!flip) {
            int tx = x; //weird bug fix
            int ty = y; //weird bug fix
            x = x_ixi(tx, ty);
            y = y_ixi(tx, ty);
        }
        else {
            int tx = x; //weird bug fix
            int ty = y; //weird bug fix
            x = x_xx(tx, ty);
            y = y_xx(tx, ty);
        }
        if (fo != stdout || binary == 1) {
            size_t ewx = fwrite(&x, 1, 1, fo);
            size_t ewy = fwrite(&y, 1, 1, fo);
            if (ewx == 0 || ewy == 0) {
                return 2;
            }
        }
        else {
            printf(" %02x %02x ", x, y);
        }
    }
    return 0;
}

int hexShiftXor(int i, unsigned char buf[BUFSZ], int flip, int binary, FILE *fo, uint8_t hash[32]){
    static int k;
    if (i%2 == 0) {
        int x = buf[i];
        int y = buf[i+1];
            //and here!
        if (!flip) {
            int tx = x; //weird bug fix
            int ty = y; //weird bug fix
	    //printf("[%c^%x, %c^%x]%i", x, hash[k], y, hash[k+1], k);
            x = xor(x_ixi(tx, ty), hash[k]);
            y = xor(y_ixi(tx, ty), hash[k+1]);
		
        }
        else {
            int ex = xor(x, hash[k]);
            int ey = xor(y, hash[k+1]);
	    x = x_xx(ex, ey);
            y = y_xx(ex, ey);
        }
        if (fo != stdout || binary == 1) {
            size_t ewx = fwrite(&x, 1, 1, fo);
            size_t ewy = fwrite(&y, 1, 1, fo);
            if (ewx == 0 || ewy == 0) {
                return 2;
            }
        }
        else {
            printf(" %02x %02x ", x, y);
        }
        k = k + 2;
    }
    if (k >= 32 ) {
	k = 0;
	return 1;
    }
    return 0;
}

int shuffleInputFromFile(FILE *fi, FILE *fo, int flip, int binary){ 
    unsigned char buf[BUFSZ] = {0};
    size_t bytes = 0, i, readsz = sizeof buf;

    /* read/output BUFSZ bytes at a time */
    while ((bytes = fread (buf, sizeof *buf, readsz, fi)) == readsz) {
        for (i = 0; i < readsz; i++)
            hexShift(i, buf, flip, binary, fo);

        if (fo == stdout && binary == 0) {
            putchar ('\n');
        }
    }

    for (i = 0; i < bytes; i++) /* output final partial buf */
        hexShift(i, buf, flip, binary, fo);

    if (fi != stdin)
        fclose (fi);
    if (fo != stdout || binary == 1)
        fclose (fo);
    else 
        putchar('\n');
    return 0;
}

int shuffleXorInputFromFile(FILE *fi, FILE *fo, int flip, int binary, char *key){
    unsigned char buf[BUFSZ] = {0};
    size_t bytes = 0, i, readsz = sizeof buf;

    uint8_t hash[32];
    calc_sha_256(hash, key, strlen(key));

    /* read/output BUFSZ bytes at a time */
    while ((bytes = fread (buf, sizeof *buf, readsz, fi)) == readsz) {
        for (i = 0; i < readsz; i++) {
       	    if(hexShiftXor(i, buf, flip, binary, fo, hash) == 1) {
		calc_sha_256(hash, hash, 32);
	    }
        }

        if (fo == stdout && binary == 0) {
            putchar ('\n');
        }
    }

    for (i = 0; i < bytes; i++) /* output final partial buf */
        hexShiftXor(i, buf, flip, binary, fo, hash);

    if (fi != stdin)
        fclose (fi);
    if (fo != stdout || binary == 1)
        fclose (fo);
    else 
        putchar('\n');
    return 0;
}

void usage (char* basename) {
    char version[] = "CheekyKitten 0.9 Beta by Josjuar Lister 2021-2025\n";
    char usage[] = "%sA cipher and binary obfuscation tool.\n\n"
	    "Usage: %s [options] <input file> <output file>\n"
	"CheekyKitten will default to stdin/stdout if i/o files are not provided.\n\n"
        "\t-h           Print this help menu\n"
        "\t-k [Key]     Encrypt shuffled output with a key\n"
        "\t-r           Reverse (or Decrypt if used with Key argument)\n"
        "\t-x           Output as hex\n";
        fprintf(stderr, usage, version, basename);
}

int main (int argc, char **argv) {

    int opt, flip = 0, binary = 1, cipher = 0;
    char *key = "";
    
        /* read command line arguments */
    while ((opt = getopt(argc, argv, "hxk:r")) != -1)
        switch((char)opt) {
        case 'h':
            usage(argv[0]);
            exit(0);
        case 'x':
            binary = 0;
            break;
        case 'k':
            key = optarg;
            cipher = 1;
            break;
        case 'r':
            flip = 1;
            break;
        default :
            printf("Unexpected argument\n");
            usage(argv[0]);
            exit(1);
    }
    argc -= optind;
    argv += optind;

    if (argv[0] != NULL && argv[1] != NULL) {
        int streq = strcmp(argv[0], argv[1]);
        if (streq == 0) {
            printf("Warning! setting the same input and output will destroy the data\n");
            exit(1);
        }
    }
    FILE *fo = argc > 1 ? fopen (argv[1], "wb") : stdout;
    if (fo == NULL) {
        printf("error opening output file: %s\n", argv[1]);
        exit(1);
    }
    FILE *fi = argc > 0 ? fopen (argv[0], "rb") : stdin;
    if (fi == NULL) {
        printf("error opening input file: %s\n", argv[2]);
        exit(1);
    }

    if(cipher) {
        shuffleXorInputFromFile(fi, fo, flip, binary, key);
    }
    else {
        shuffleInputFromFile(fi, fo, flip, binary);
    }

    
}
