//
// Created by tommygomez25 on 12-05-2022.
//
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <math.h>


#define BUFFER_SIZE 3

void print_usage(const char *exe) {
    printf("Usage: %s <filename1> <filename2>\n", exe);
}

int addmx(const char *file1, const char *file2){

    FILE *f1 = fopen(file1,"r");

    if (f1 == NULL){
        perror("Error in opening file 1");
        return -1;
    }

    FILE *f2 = fopen (file2, "r");

    if (f2 == NULL){
        perror("Error in opening file 2");
        return -1;
    }


    char ch;
    unsigned row,col;
    size_t len = 0;
    char *line = NULL;
    getline(&line,&len,f1);
    sscanf(line,"%d%c%d",&row,&ch,&col);
    printf("%d\n",row);
    printf("%d\n",col);


    char  *file_in_memory = mmap(NULL,row*col*2, PROT_READ, MAP_SHARED, fileno(f1), 0);
    if (file_in_memory == MAP_FAILED){
        printf("mapeamento failed\n");
        return 1;
    }

    for (int i = 0; i < row*col;i++){
        /*
        if (file_in_memory[i+1] == ' ' || file_in_memory[i+1] == '\n' || file_in_memory[i+1] == 'x'){
            i++;
        }
         */ 
        printf("[%d] : %d\n",i,atoi(&file_in_memory[i]));
    }
    int resultado = atoi(&file_in_memory[4]) + atoi(&file_in_memory[5]);
    printf("%d",resultado);
    /*
    int i = 0;
    do{
        ch = fgetc(f1);
        if (feof(f1)){
            break;
        }

        if ( ch == ' '){
            continue;
        }
        printf("%c",ch);
        i++;
    } while(1);*/


    fclose(f1);
    int err = munmap(file_in_memory,row*col);
    if ( err!=0){
        printf("cenas");
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        return -1;
    }

    if (argc == 3) {
        addmx(argv[1],argv[2]);
    }
}