//WILSON GLASS
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[]){
    if(argc != 3){
        printf("Wrong amount of information\n");
        return 1;
    }

    int input = open(argv[1], O_RDONLY);
    int output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR)                                                                                                                                   ;

    if(input == -1){
        perror("The input file cannot be opened\n");
        return 2;
    }

    if(output == -1){
        perror("The output file cannot be opened\n");
        return 3;
    }

    struct stat inputMetric;

    int inputMetricNum = fstat(input, &inputMetric);
    int inputSize = inputMetric.st_size;

    if(inputSize == 0){
        return 0;
    }
    else if(inputSize == -1){
        return 4;
    }

    char * result = mmap(NULL, inputSize, PROT_READ, MAP_SHARED, input, 0);

    if(result == MAP_FAILED){
        perror("mmap failed\n");
        return 5;
    }

    int resultWrite = write(output, &result, inputMetric.st_size);
    if(resultWrite != inputMetric.st_size){
        perror("Size of write is wrong\n");
        return 6;
    }
    return 0;
}
