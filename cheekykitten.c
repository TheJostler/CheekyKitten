#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSZ 8

int main (int argc, char **argv) {
    
    char version[] = "CheekyKitten Beta0.1 by Josjuar Lister 2021-2022\n";
    char usage[] = "%s\n\n%s [options] <input file> <output file>]\n"
        "\t-h           Print this help menu\n"
        "\t-k <key>     RESERVED FOR FUTURE IMPLEMENTATION\n"
        "\t-x           Output to file in readable hex (default: binary)\n";

    char S[96][2] = { {'E','F'},{'B','B'},{'B','F'},{'5','2'},{'6','1'},{'7','2'},{'6','5'},{'6','C'},{'7','9'},{'2','0'},{'7','3'},{'6','5'},{'7','4'},{'2','0'},{'6','6'},{'6','F'},{'6','F'},{'7','4'},{'2','0'},{'6','9'},{'6','E'},{'2','0'},{'7','9'},{'6','F'},{'7','5'},{'7','2'},{'2','0'},{'6','E'},{'6','5'},{'6','9'},{'6','7'},{'6','8'},{'6','2'},{'6','F'},{'7','2'},{'E','2'},{'8','0'},{'9','9'},{'7','3'},{'2','0'},{'6','8'},{'6','F'},{'7','5'},{'7','3'},{'6','5'},{'2','C'},{'2','0'},{'5','3'},{'6','F'},{'2','0'},{'7','4'},{'6','8'},{'6','1'},{'7','4'},{'2','0'},{'6','8'},{'6','5'},{'2','0'},{'6','4'},{'6','F'},{'6','5'},{'7','3'},{'2','0'},{'6','E'},{'6','F'},{'7','4'},{'2','0'},{'6','7'},{'6','5'},{'7','4'},{'2','0'},{'7','4'},{'6','9'},{'7','2'},{'6','5'},{'6','4'},{'2','0'},{'6','F'},{'6','6'},{'2','0'},{'7','9'},{'6','F'},{'7','5'},{'2','0'},{'6','1'},{'6','E'},{'6','4'},{'2','0'},{'6','8'},{'6','1'},{'7','4'},{'6','5'},{'2','0'},{'7','9'},{'6','F'},{'7','5'} };
    int opt;
    unsigned char buf[BUFSZ] = {0};
    size_t bytes = 0, i, readsz = sizeof buf;
    
        /* read command line arguments */
    while ((opt = getopt(argc, argv, "hxk:")) != -1)
        switch((char)opt) {
        case 'h':
            fprintf(stderr, usage, version, argv[0]);
            exit(0);
        case 'k':
            printf("Key is: %s\n", optarg);
            break;
            //key
        case 'x':
            printf("Hex output is on!\n");
            break;
            //Output hex
        default :
            printf("Unexpected argument: %s\n", optarg);
            fprintf(stderr, usage, version, argv[0]);
            exit(1);
        }
    argc -= optind;
    argv += optind;

    int streq = strcmp(argv[0], argv[1]);
    if (streq == 0) {
        printf("Warning! setting the same input and output will destroy the data\n");
        exit(1);
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
    /* read/output BUFSZ bytes at a time */
    while ((bytes = fread (buf, sizeof *buf, readsz, fi)) == readsz) {
        for (i = 0; i < readsz; i++)
            if (i%2 == 0){
                int x = buf[i];
                int y = buf[i+1];
                int key[5] = {1, 1, 1, 1};
                    //insert algorithm here!
                int b = x% 0x10;
                int d = y% 0x10;
                int n = i%(sizeof(key));
                //if (key[n]) {
                    x = (y - d) + (x / 0x10);
                    y = (d * 0x10) + b;
                /*}
                else {
                    x = (b * 0x10) + d;
                    y = (x - b) + (y / 0x10);
                }*/
                if (fo != stdout) {
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
        if (fo == stdout) {
            putchar ('\n');
        }
    }

    for (i = 0; i < bytes; i++) /* output final partial buf */
        if (i%2 == 0) {
            int x = buf[i];
            int y = buf[i+1];
            int key[5] = {1, 1, 1, 1};
                //and here!
            int b = x% 0x10;
            int d = y% 0x10;
            int n = i%(sizeof(key));
            //if (key[n]) {
                x = (y - d) + (x / 0x10);
                y = (d * 0x10) + b;
            /*}
            else {
                x = (b * 0x10) + (x / 0x10);
                y = (x - b) + (y / 0x10);
            }*/
            if (fo != stdout) {
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

    if (fi != stdin)
        fclose (fi);
    if (fo != stdout)
        fclose (fo);
    else 
        putchar('\n');
    return 0;
}
