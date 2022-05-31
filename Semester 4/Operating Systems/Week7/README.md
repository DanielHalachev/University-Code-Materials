#### Да се напише програма на С, която получава като параметър команда (без параметри) и при успешното ѝ изпълнение, извежда на стандартния изход името на командата
```c
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(int argc, char* argv[]){
    if (argc !=2){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }
    pid_t p1 = fork();
    if (p1 == -1){
        err(EXIT_FAILURE, "Invalid new thread");
    }
    int status;
    if (p1 > 0){
        wait (&status); 
        if (WIFEXITED(status) == 1){
            printf("The command is: %s\n",argv[1]);
        }
    }
    else if (p1 == 0){
        if(execlp(argv[1], argv[1], (char*)(NULL)) == -1){
            err(EXIT_FAILURE, "Command failed to execute");
        }
    }
    exit(0);
}
```
Да се напише програма на С, която получава като параметри три команди (без параметри), изпълнява ги последователно, като изчаква края на всяка и извежда на стандартния изход номера на завършилия процес, както и неговия код на завършване.
```c
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(int argc, char* argv[]){
    if (argc != 4){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }
    for(int i=1; i<=3; i++){
        pid_t p1 = fork();
        if (p1 == -1){
            err(EXIT_FAILURE, "Invalid new thread");
        }
        int status;
        if (p1 > 0){
            wait (&status); 
            printf("%i, %i\n",p1, status);
        }
        else if (p1 == 0){
            if(execlp(argv[i], argv[i], (char*)(NULL)) == -1){
                err(EXIT_FAILURE, "Command failed to execute");
            }
        }
    }
    exit(0);
}
```
#### Да се напише програма на С, която получава като параметър име на файл. Създава процес син, който записва стринга `foobar` във файла (ако не съществува, го създава, в противен случай го занулява), след което процеса родител прочита записаното във файла съдържание и го извежда на стандартния изход, добавяйки по един интервал между всеки два символа
```c
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define STRING "foobar"

int main(int argc, char* argv[]){
    if (argc != 2){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }
        pid_t p1 = fork();
        if (p1 == -1){
            err(EXIT_FAILURE, "Invalid new thread");
        }
        int p[2];
        if(pipe(p)==-1){
            err(EXIT_FAILURE, "Could not pipe");
        }

        int status;
        if (p1 > 0){
            close(p[1]);
            wait (&status); 
            char c;
            char empty= ' ';
            int i=0;
            while (read(p[0], &c, sizeof(c)) == sizeof(c)){
                if(write(2, &c, sizeof(c)) != sizeof(c)){
                    err(EXIT_FAILURE, "Could not write to stdout");
                }
                i++;
                if(i%2==0){
                    if(write(2, &empty, sizeof(empty)) != sizeof(empty)){
                        err(EXIT_FAILURE, "Could not write to stdout");
                    }  
                }
            }
            close(p[0]);
        }
        else if (p1 == 0){
            close(p[0]);
            int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
            char str[] = {STRING};
            if (write(fd, &str, sizeof(str)) != sizeof(str)){
                err(EXIT_FAILURE, "Invalid write");
            }
            dup2(p[0], fd);
        }
    exit(0);
}
```
#### Да се напише програма на C, която която създава файл в текущата директория и генерира два процесa, които записват низовете foo и bar в създадения файл.
 - Програмата не гарантира последователното записване на низове.
 - Променете програмата така, че да записва низовете последователно, като първия е foo.
```c
#include <sys/types.h>

#define FOO "foo"
#define BAR "bar"

int main(int argc, char* argv[]){
    if (argc != 2){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }
         
        int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
        pid_t p1 = fork();
        if (p1 == -1){
            err(EXIT_FAILURE, "Invalid new thread");
        }        
        if (p1 == 0){
            pid_t p2 = fork();
            if (p2 == 0){
                char str1[] = {FOO};
                if (write(fd, &str1, sizeof(str1)) != sizeof(str1)){
                    close(fd);
                    err(EXIT_FAILURE, "Invalid write");
                }
                exit(0);
            } else if (p2 > 0){
                wait(NULL);
                char str2[] = {BAR};
                if (write(fd, &str2, sizeof(str2)) != sizeof(str2)){
                    close(fd);
                    err(EXIT_FAILURE, "Invalid write");
                }
                exit(0);
            }
            exit(0);
        }
        else if (p1 > 0){
            wait(NULL);
            close(fd);
        }
    exit(0);
```
#### Да се напише програма на C, която получава като параметри от команден ред две команди (без параметри). Изпълнява първата. Ако тя е завършила успешно изпълнява втората. Ако не, завършва с код 42.
```c
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define FOO "foo"
#define BAR "bar"

int main(int argc, char* argv[]){
    if (argc != 3){
    errx(EXIT_FAILURE, "Invalid number of parameters");
    }
     
    pid_t p1 = fork();
    if (p1 == -1){
        err(EXIT_FAILURE, "Invalid new thread");
    }
    if (p1 == 0){
        if(execlp(argv[1], argv[1], (char*)(NULL)) == -1){
        err(EXIT_FAILURE, "Invalid execution");
        }
    }
    else if (p1 > 0){
        int status;
        wait(&status);
        //printf("%d\n", status);
        if (WIFEXITED(status) == 1){
            if(execlp(argv[2], argv[2], (char*)(NULL)) == -1){
                err(EXIT_FAILURE, "Invalid execution");
            }
        }
        else{
            //err(42, "First command failed to execute");
            exit(42);
        }
    }
    exit(0);
}
```
####
Да се напише програма на C, която изпълнява последователно подадените ѝ като параметри команди, като реализира следната функционалност постъпково:
 - main cmd1 ... cmdN Изпълнява всяка от командите в отделен дъщерен процес.
 - ... при което се запазва броя на изпълнените команди, които са дали грешка и броя на завършилите успешно.
```c
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define FOO "foo"
#define BAR "bar"

int main(int argc, char* argv[]){
    if (argc < 2){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }
    int ok = 0;
    int failed = 0;
    for(int i=1; i<=argc; i++){
        pid_t p1 = fork();
        if (p1 == -1){
            err(EXIT_FAILURE, "Invalid new thread");
        }
        if (p1 == 0){
            if(execlp(argv[i], argv[i], (char*)(NULL)) == -1){
                exit(EXIT_FAILURE);
            }
        }
        else if (p1 > 0){
            int status;
            wait(&status);
            if (WIFEXITED(status) == 0){
                failed++;
            }
            else{
                ok++;
            }
        }
    }    
    printf("OK: %d; FAILED: %d\n", ok, failed);
    exit(0);
}
```

