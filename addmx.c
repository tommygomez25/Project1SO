//
// Created by tommygomez25 on 12-05-2022.
//
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>


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
    sscanf(line,"%d%c%d",&row,&ch,&col); // vai buscar a primeira linha para saber quantas linhas e colunas tem a matriz


    // MAP_ANONYMOUS faz com que o argumento fd seja ignorado, ou seja, ele não vai buscar file nenhum para mapear, simplesmente aloca memória onde os blocos ficam empty
    int * map =(int *) mmap(NULL,row*col,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,-1,0);
    int * map2 = (int *) mmap(map,row*col,PROT_READ | PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    int * map3 = (int *) mmap(map2,row*col,PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

    int index = 0;
    int num;
    while (fscanf(f1,"%d",&num) != EOF){
        map[index] = num;
        index++;
    }

    getline(&line,&len,f2); // para ignorar a primeira linha do segundo ficheiro
    index = 0;
    while (fscanf(f2,"%d",&num) != EOF){
        //printf("%d",num);
        map2[index] = num;
        index++;
    }

    pid_t pid_matrix[col];

    for (int i = 0; i <= col;i++) {
        pid_matrix[col] = fork();
        int aux = i;
        if (pid_matrix[col] == -1) {
            //erro
        }
        else if (pid_matrix[col] == 0) {
            //child process

            for (int j = 0; j < row;j++){
                map3[aux] = map[aux] + map2[aux];
                aux+= col;
            }
            //printf("Child process with pid %d for column %d\n", getpid(),i);
            exit(EXIT_SUCCESS);
        }
        else {
            //parent process

            //printf("Created a new process with pid %d\n", pid_matrix[col]);
        }
    }

    printf("%dx%d\n",row,col);

    int i = 0;
    while (1) {
        printf("%d ",map3[i]);
        if ( (i+1) % col == 0){
            printf("\n");
        }
        if ( i+1 == row*col){
            break;
        }
        i++;
    }

    munmap(map,row*col);
    munmap(map2,row*col);
    munmap(map3,row*col);
    close(fileno(f1));
    close(fileno(f2));
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