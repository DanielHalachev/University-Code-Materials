#### Копирайте съдържанието на файл1 във файл2
```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <errno.h>
int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Invalid number of parameters");
    }
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1){
        printf("Error: %d\n", errno);
    }
    int fd2 = open(argv[2], O_WRONLY);
    if (fd2 == -1){
        printf("Error: %d\n", errno);
    }

    char c;
    while (read(fd1, &c, 1)){
        write(fd2, &c, 1);
    }
    close(fd1);
    close(fd2);
    exit(0);
}
```
