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

    int f1 = open(file1,O_RDONLY,S_IRUSR |S_IWUSR);
    if (f1 == NULL){
        perror("Error in opening file 1");
        return -1;
    }
    int f2 = open (file2, O_RDONLY,S_IRUSR |S_IWUSR);
    if (f2 == NULL){
        perror("Error in opening file 2");
        return -1;
    }

    struct stat sb;
    if (fstat(f1,&sb) == -1){
        perror("Couldn't get file size.\n");
    }
    printf("The file size is %ld\n",sb.st_size);

    struct stat sb2;
    if (fstat(f1,&sb2) == -1){
        perror("Couldn't get file size.\n");
    }
    printf("The file size is %ld\n",sb2.st_size);

    char *file_in_memory = mmap(NULL,sb.st_size ,PROT_READ ,MAP_SHARED,f1,0);
    char *file_in_memory2 = mmap(file_in_memory,sb2.st_size*2,PROT_READ,MAP_SHARED,f2,0);
    char *file_in_memory3 = mmap(file_in_memory2,sb.st_size * 2,PROT_WRITE,MAP_SHARED,STDOUT_FILENO,0);

    for (int i = 0; i < sb.st_size;i++){
        printf("%c",file_in_memory[i]);
    }
    for (int i = 0; i < sb2.st_size;i++){
        printf("%c",file_in_memory2[i]);
    }
    unsigned int row = atoi(&file_in_memory[0]) ;
    unsigned int col = atoi(&file_in_memory[2]) ;
    //file_in_memory3[0] = row + '0'; file_in_memory3[1] = 'x'; file_in_memory3[2] = col + '0';

    pid_t pid_matrix[col];

    for (size_t i = 1; i <= col;i++) {
        pid_matrix[col] = fork();
        if (pid_matrix[col] == -1) {
            //erro
        }
        else if (pid_matrix[col] == 0) {
            //child process

            for (int j = 1; j <= row;j++){
                int new_col = atoi(&file_in_memory[4 + (j-1)*(col*2) + ((i-1)*2)] )+ atoi(&file_in_memory2[4 + (j-1)*(col*2) + ((i-1)*2)]);_
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

    munmap(file_in_memory,sb.st_size);
    munmap(file_in_memory2,sb2.st_size);
    close(f1);
    close(f2);
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