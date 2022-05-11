#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 5
void print_usage(const char *exe) {
    printf("Usage: %s [-l] <filename>\n", exe);
}

int phrases_count(const char *fname){
    unsigned int count = 0;

    char buf[BUF_SIZE];

    FILE *f = fopen(fname,"r");
    if ( f == NULL){
        return -1;
    }

    char last = ' ';
    while (!feof(f)) {
        size_t c = fread(buf, sizeof(char), BUF_SIZE - 1, f);
        buf[c] = '\0';
        int i = 0;
        for (i = 0; buf[i]; ++i) {
            if (buf[i] == '.' || buf[i] == '?' || buf[i] == '!') {
                count++;
                last = ' ';
            } else if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n') {
                continue; //white-space doesn't include to sentence of top.
            } else {
                last = buf[i]; //check for Not terminated with ".?!"
            }
        }
    }
    fclose(f);
    return count += (last != ' '); // +1 if Not terminated with ".?!"
}

int phrases(const char*fname){

    unsigned int count = 1;
    char buf[BUF_SIZE];

    FILE *f = fopen(fname,"r");
    if ( f == NULL){
        return -1;
    }

    unsigned z = 1;
    while (!feof(f)) {
        size_t c = fread(buf, sizeof(char), BUF_SIZE - 1, f);
        /*
        if ( z == 1){
            printf("[1]");
        }
        z++;
         */
        buf[c] = '\0';
        for (int i = 0; buf[i];i++){
            printf("%c",buf[i]);

        }
        printf("\n");
        /*
        buf[c] = '\0';
        int i = 0;
        for (i = 0; buf[i]; ++i) {
            if (buf[i] == '.' || buf[i] == '?' || buf[i] == '!') {
                count++;
            } else if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n') {
                continue; //white-space doesn't include to sentence of top.
            } else {
                if (buf[i-1] == '.' || buf[i-1] == '?' || buf[i-1] == '!') {
                    printf("\n[%d]",count);
                }
                printf("%c", buf[i]);
            }
        }
         */
    }
         
    printf("\n");
    fclose(f);
    return 0;
}



int main(int argc, char const *argv[]) {

    if (argc < 2 ) {
        print_usage(argv[0]);
        return -1;
    }

    // default operating mode is not changing the string
    //output_mode_t m = ORIGINAL;

    // handle third optional argument
    if (argc == 3) {
        if (strcmp("-l", argv[1]) != 0) {
            print_usage(argv[0]);
            return -1;
        }
        else {
            phrases(argv[2]);
            return 0;
        }
    }

    else if (argc == 2) {
        printf("%d\n",phrases_count(argv[1]));
        return 0;
    }

}
