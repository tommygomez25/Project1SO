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

    struct stat sb;
    if (fstat(fileno(f1),&sb) == -1){
        perror("Couldn't get file size.\n");
    }
    printf("The file size is %ld\n",sb.st_size);

    struct stat sb2;
    if (fstat(fileno(f2),&sb2) == -1){
        perror("Couldn't get file size.\n");
    }
    printf("The file size is %ld\n",sb2.st_size);

    char ch;
    unsigned row,col;
    size_t len = 0;
    char *line = NULL;
    getline(&line,&len,f1);
    sscanf(line,"%d%c%d",&row,&ch,&col); // vai buscar a primeira linha para saber quantas linhas e colunas tem a matriz
    printf("row : %d\n",row);
    printf("col : %d\n",col);

    int * map =(int *) mmap(NULL,row*col,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,-1,0);
    // MAP_ANONYMOUS faz com que o argumento fd seja ignorado, ou seja, ele não vai buscar file nenhum para mapear, simplesmente aloca memória onde os blocos ficam empty
    int * map2 = (int *) mmap(map,row*col,PROT_READ | PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

    int index = 0;
    int num;
    while (fscanf(f1,"%d",&num) != EOF){
        map[index] = num;
        index++;
    }

    for (int i = 0; i < row*col;i++){
        printf("%d\n",map[i]);
    }

    int counter = 0;
    getline(&line,&len,f2); // para ignorar a primeira linha do segundo ficheiro
    index = 0;
    while (fscanf(f2,"%d",&num) != EOF){
        printf("%d",num);
        map2[index] = num;
        index++;
    }
    /*
    for (int i = 0; i < row*col;i++){
        printf("%d\n",map2[i]);
    }
    */
    /*
    pid_t pid_matrix[col];

    for (size_t i = 1; i <= col;i++) {
        pid_matrix[col] = fork();
        if (pid_matrix[col] == -1) {
            //erro
        }
        else if (pid_matrix[col] == 0) {
            //child process

            for (int j = 1; j <= row;j++){
                int new_col = atoi(&file_in_memory[counter + (j-1)*(col*2) + ((i-1)*2)] )+ atoi(&file_in_memory2[counter + (j-1)*(col*2) + ((i-1)*2)]);
                file_in_memory3[counter+ (j-1)*(col*2) + ((i-1)*2)] = new_col + '0';
                printf("%d\n",new_col);
            }

            printf("Child process with pid %d for column %d\n", getpid(),i);
            exit(EXIT_SUCCESS);
        }
        else {
            //parent process
            printf("Created a new process with pid %d\n", pid_matrix[col]);
        }
    }

    for ( int i = 0; i < sb.st_size;i++){
        printf("%c",file_in_memory3[i]);
    }
    munmap(file_in_memory,sb.st_size);
    munmap(file_in_memory2,sb2.st_size);
     */
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