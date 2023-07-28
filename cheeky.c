#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "algo.h"
#include "sha-256.h"

#define BUFSZ 8

static void hash_to_string(char string[65], const uint8_t hash[32])
{
	size_t i;
	for (i = 0; i < 32; i++) {
		string += sprintf(string, "%02x", hash[i]);
	}
}

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

int hexShiftXor(int i, unsigned char buf[BUFSZ], int flip, int binary, FILE *fo, char *hash){
    static int k;
    if (i%2 == 0) {
        int x = buf[i];
        int y = buf[i+1];
            //and here!
        if (!flip) {

            int tx = x; //weird bug fix
            int ty = y; //weird bug fix
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
            printf(" %02x %02x - %i %c %c |", x, y, k, hash[k], hash[k+1]);
        }
        k = k + 2;
    }
    if (k >= 64 ) {
	return 1;
    }
    return 0;
}

int shuffleInput(FILE *fi, FILE *fo, int flip, int binary){ 
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

int shuffleXorInput(FILE *fi, FILE *fo, int flip, int binary, char *key){
    unsigned char buf[BUFSZ] = {0};
    size_t bytes = 0, i, readsz = sizeof buf;

    __uint8_t hash[32];
    char hash_str[65];
    calc_sha_256(hash, key, strlen(key));
    hash_to_string(hash_str, hash);
	printf("\n%s\n", hash_str);

    /* read/output BUFSZ bytes at a time */
    while ((bytes = fread (buf, sizeof *buf, readsz, fi)) == readsz) {
        for (i = 0; i < readsz; i++) {
            if(hexShiftXor(i, buf, flip, binary, fo, hash_str)) {
		calc_sha_256(hash, hash, 64);
                hash_to_string(hash_str, hash);
		printf("\n%s\n", hash_str);
	    }
        }

        if (fo == stdout && binary == 0) {
            putchar ('\n');
        }
    }

    for (i = 0; i < bytes; i++) /* output final partial buf */
        hexShiftXor(i, buf, flip, binary, fo, hash_str);

    if (fi != stdin)
        fclose (fi);
    if (fo != stdout || binary == 1)
        fclose (fo);
    else 
        putchar('\n');
    return 0;
}

void usage (char* basename) {
    char version[] = "CheekyKitten 0.4 Beta by Josjuar Lister 2021-2023";
    char algo[] = " -- Logical Algorithm\n";
    char usage[] = "%s%s\n\n%s [options] <input file> <output file>\n"
        "CheekyKitten will default to stdout/stdin if i/o files are not provided\n\n"
        "\t-h           Print this help menu\n"
        "\t-k [Key]     Encrypt shuffled output with a key\n"
        "\t-R           Reverse (or Decrypt if used with Key argument)\n"
        "\t-b           Output as binary\n";
        fprintf(stderr, usage, version, algo, basename);
}

int main (int argc, char **argv) {

    int opt, flip = 0, binary = 0, cipher = 0;
    char *key = "";
    
        /* read command line arguments */
    while ((opt = getopt(argc, argv, "hbk:r")) != -1)
        switch((char)opt) {
        case 'h':
            usage(argv[0]);
            exit(0);
        case 'b':
            binary = 1;
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
        printf("error opening output file: %s\n", fo);
        exit(1);
    }
    FILE *fi = argc > 0 ? fopen (argv[0], "rb") : stdin;
    if (fi == NULL) {
        printf("error opening input file: %s\n", fi);
        exit(1);
    }

    if(cipher) {
        shuffleXorInput(fi, fo, flip, binary, key);
    }
    else {
        shuffleInput(fi, fo, flip, binary);
    }

    
}
