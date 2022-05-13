#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print_usage(const char *exe) {
    printf("Usage: %s [-l] <filename>\n", exe);
}

int phrases(const char*fname, bool mode){

    unsigned int count = 0;
    unsigned int index = 1;
    char c;
    char last = ' ';

    FILE *f = fopen(fname,"r");
    if ( f == NULL){
        perror("Error in opening file");
        return -1;
    }
    if (mode && (c = fgetc(f)) != EOF){
        printf("[%d] %c",index,c);
    }

    do {
        c = fgetc(f);
        if (feof(f)){
            break;
        }
        if ( c == '.' || c == '?' || c == '!'){
            index++;
            if (mode){
                printf("\n[%d]",index);
            }
            count++;
            last = ' ';
        }

        else {
            if (mode){
                printf("%c",c);
            }
            last = c;
        }
    } while (1);

    if (mode){
        printf("\n");
    }

    fclose(f);
    return count + (last != ' ');
}



int main(int argc, char const *argv[]) {

    if (argc < 2 ) {
        print_usage(argv[0]);
        return -1;
    }

    else if (argc == 2) {
        printf("%d\n",phrases(argv[1],false));
        return 0;
    }

    // handle third optional argument
    if (argc == 3) {
        if (strcmp("-l", argv[1]) != 0) {
            print_usage(argv[0]);
            return -1;
        }
        else {
            phrases(argv[2],true);
            return 0;
        }
    }

}
