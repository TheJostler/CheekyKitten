#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "algo.h"
#include "keyparse.h"

#define BUFSZ 8

void usage (char* basename) {
    char version[] = "CheekyKitten 0.3 Beta by Josjuar Lister 2021-2022";
    char algo[] = " -- Logical Algorithm\n";
    char usage[] = "%s%s\n\n%s [options] <input file> <output file>\n"
        "CheekyKitten will default to stdout/stdin if i/o files are not provided\n\n"
        "\t-h           Print this help menu\n"
        "\t-k <key>     Encrypt with a key\n"
        "\t-R           Reverse\n"
        "\t-b           Output as binary\n";
        fprintf(stderr, usage, version, algo, basename);
}

int main (int argc, char **argv) {

    int opt, flip, binary = 0, n = 0;
    char *txtkey = NULL;
    
    unsigned char buf[BUFSZ] = {0};
    size_t bytes = 0, i, readsz = sizeof buf;
    
        /* read command line arguments */
    while ((opt = getopt(argc, argv, "hbk:r")) != -1)
        switch((char)opt) {
        case 'h':
            usage(argv[0]);
            exit(0);
        case 'b':
            binary = 1;
            break;
            //Output
        case 'k':
            txtkey = optarg;
            break;
            //key
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
            exit(5318008);
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

    if(txtkey != NULL){
        int *key;
            int keylen = 12;
            /* read/output BUFSZ bytes at a time */
            while ((bytes = fread (buf, sizeof *buf, readsz, fi)) == readsz) {
                for (i = 0; i < readsz; i++)
                    if (i%2 == 0) {
                        int x = buf[i];
                        int y = buf[i+1];
                            //insert algorithm here!
                        key = txt2bin(txtkey);
                        n ++;
                        n = n % keylen;
                        if (*(key + n) ^ flip) {
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
                        printf (" %02x %02x ", x, y);
                        }
                    }
                if (fo == stdout && binary == 0) {
                    putchar ('\n');
                }
            }

            for (i = 0; i < bytes; i++) /* output final partial buf */
                if (i%2 == 0) {
                    int x = buf[i];
                    int y = buf[i+1];
                        //and here!
                    key = txt2bin(txtkey);
                    n ++;
                    n = n % keylen;
                    if (*(key + n) ^ flip){
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
    }
    else {
        int key = 1;
        int keylen = 1;
            /* read/output BUFSZ bytes at a time */
            while ((bytes = fread (buf, sizeof *buf, readsz, fi)) == readsz) {
                for (i = 0; i < readsz; i++)
                    if (i%2 == 0) {
                        int x = buf[i];
                        int y = buf[i+1];
                            //insert algorithm here!
                        if (key ^ flip) {
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
                        printf (" %02x %02x ", x, y);
                        n += 1;
                        n = n % keylen;
                        }
                    }
                if (fo == stdout && binary == 0) {
                    putchar ('\n');
                }
            }

            for (i = 0; i < bytes; i++) /* output final partial buf */
                if (i%2 == 0) {
                    int x = buf[i];
                    int y = buf[i+1];
                        //and here!
                    if (key ^ flip) {
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
                    n += 1;
                    n = n % keylen;
                    }
                }
    }

    if (fi != stdin)
        fclose (fi);
    if (fo != stdout || binary == 1)
        fclose (fo);
    else 
        putchar('\n');
    return 0;
}
