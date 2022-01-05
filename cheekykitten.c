#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 8

int main (int argc, char **argv) {
    
    char S[96][2] = { {'E','F'},{'B','B'},{'B','F'},{'5','2'},{'6','1'},{'7','2'},{'6','5'},{'6','C'},{'7','9'},{'2','0'},{'7','3'},{'6','5'},{'7','4'},{'2','0'},{'6','6'},{'6','F'},{'6','F'},{'7','4'},{'2','0'},{'6','9'},{'6','E'},{'2','0'},{'7','9'},{'6','F'},{'7','5'},{'7','2'},{'2','0'},{'6','E'},{'6','5'},{'6','9'},{'6','7'},{'6','8'},{'6','2'},{'6','F'},{'7','2'},{'E','2'},{'8','0'},{'9','9'},{'7','3'},{'2','0'},{'6','8'},{'6','F'},{'7','5'},{'7','3'},{'6','5'},{'2','C'},{'2','0'},{'5','3'},{'6','F'},{'2','0'},{'7','4'},{'6','8'},{'6','1'},{'7','4'},{'2','0'},{'6','8'},{'6','5'},{'2','0'},{'6','4'},{'6','F'},{'6','5'},{'7','3'},{'2','0'},{'6','E'},{'6','F'},{'7','4'},{'2','0'},{'6','7'},{'6','5'},{'7','4'},{'2','0'},{'7','4'},{'6','9'},{'7','2'},{'6','5'},{'6','4'},{'2','0'},{'6','F'},{'6','6'},{'2','0'},{'7','9'},{'6','F'},{'7','5'},{'2','0'},{'6','1'},{'6','E'},{'6','4'},{'2','0'},{'6','8'},{'6','1'},{'7','4'},{'6','5'},{'2','0'},{'7','9'},{'6','F'},{'7','5'} };
    unsigned char buf[BUFSZ] = {0};
    size_t bytes = 0, i, readsz = sizeof buf;
    
    FILE *fo = argc > 2 ? fopen (argv[2], "wb") : stdout;
    if (fo == NULL) {
        printf("error opening output file");
        exit(1);
    }
    FILE *fi = argc > 1 ? fopen (argv[1], "rb") : stdin;
    if (fi == NULL) {
        printf("error opening input file");
        perror("fopen");
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
        putchar ('\n');
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
    putchar ('\n');

    if (fi != stdin)
        fclose (fi);
    if (fo != stdout)
        fclose (fo);
    return 0;
}
