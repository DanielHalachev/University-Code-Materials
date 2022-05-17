#### 1. 2016-SE-01. 
```bash
echo Броят на тъпите задачи в този сборник е: $(egrep '[2,4,6,8]+' philip-j-fry.txt | egrep -v '[a-w]'|wc -l)
```
#### 2. 2017-IN-01.
```bash
find / -uid $(id -u) 2>/dev/null 
```
#### 3. 2017-IN-02
```bash
find . -type f -size 0 | xargs -I {} rm {}
```
```bash
find . -type f -printf "%p %s\n" | sort -nr -k 2 | head -n 5| xargs -I {} rm {}
```
#### 4. 2017-IN-03
```bash
cat /etc/passwd | awk -F ':' '$4==502' | cut -d ',' -f1 | egrep '^*а$' | cut -c 3,4 | sort | uniq -c | sort -nr -k 1 | head -1
```
#### 5. 2017-SE-01
```bash
find . -type f -printf "%f %n" | sort -nr -k 2 | head -5 | cut -d ' ' -f 1
```
#### 6. 2018-SE-01
```bash
find ~/ -maxdepth 1 -type f -exec chmod 644 {};/
```
#### 7. 2018-SE-02
```bash
stat -c "%i" $(find -maxdepth 1 -type f -printf "%p %T@\n" | sort -nr -k 2 | head -n 1 | cut -d ' ' -f 1)
```
#### 8. 2018-SE-03
```bash
cat /etc/passwd | sort -n -t':' -k 3 | head -n 201 | tail -n 1 | cut -d':' -f 4 | xargs -I {} awk -F ':' '$4=={}' /etc/passwd
```
#### 9. 2019-SE-01
```bash
egrep "^[^;]+;$(cat planets.txt | tail -n +2 | sort -n -t';' -k 3,3 | tail -n 1 | cut -d';' -f2)" planets.txt | sort -n -t ';' -k 3,3 | head -n 1 | awk -OF '\t' '{print $1, $4}'
```
#### 10. 

#### 11. 2019-SE-03
```bash
find /home/velin -type f -inum $(find /home/velin -type f -printf "%T@ %p %i\n" | sort -k 1 | head -n 1 | cut -d ' ' -f 3) | grep -o / | wc -l
```
```bash
find /home/velin -maxdepth 1 -type f | sort -k 1 | head -n 1 | cut -d ' ' -f 3 | grep -o / | wc -l
```
#### 12. 2020-SE-01
```bash
find ~ -type f -perm 644 -exec chmod g+w {}
```
#### 13. 2020-SE-02
```bash
cat space.txt | tail -n +2 | grep $(cat space.txt | tail -n +2 | awk -F '|' '$3=="Failure"{print $2}' | sort | uniq -c | sort -k 1| awk '{print $2}') | sort -nr -t '|' -k 1 | head -n 1 | awk -F '|' '{printf "%s:%s\n",$3,$4}'
```
#### 14. 2022-CE-01
```bash
find ~ -maxdepth 1 -type f -user $(whoami) -exec chmod 644 {}
```
#### 15. 2016-SE-01
```bash
#!/usr/bin/bash
if [ $# -lt 1 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
if [ -d $1 ]
then
    find -L $1 -type l  # -l gets symlinks, -L does not follow symlinks. 
    #If the symlinks worked, they wouldn't be displayed. 
    #But if they are broken, they wouldn't be followed, i.e, 
    #they would fit the -L criteria
fi
exit 0
```
#### 16.  2016-SE-0
```bash
#!/usr/bin/bash
if [ $# -lt 1 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
regex="^[0-9]+$"
if [[ ! $1 =~ $regex ]]
then
    echo "Your parameter is not a number."
    exit 1
fi
if [ "$UEID"=0 ]
then
    for user in $(cat /etc/passwd | awk -F ':' '{print $1}')
    do
        total=$(ps -u $user -o rss= | awk -v sum=0 '{sum+=$1}END {print sum}')
        echo $total
        if [ $total -ge $1 ] 
        then
            kill -9 $(ps k-rss -u $user -o pid= | head -n 1 )
            # k is the same as -sort
            # +- specifies whether to sort by increasing or decreasing order
            # then follows the name of th column
        fi       
    done
fi
exit 0
```
#### 17.  2016-SE-0
```bash
#!/usr/bin/bash
if [ "$UEID"=0 ]
then
    cat /etc/passwd | awk -F ':' '$6!~/home/{print $0}'
fi
exit 0
```
#### 18.  2016-SE-0
```bash
#!/usr/bin/bash
if [ $# -lt 2 ]
then
    echo "Invalid number of parameteres"
    exit 1
fi
regex="^[0-9]+$"
if [[ ! $1 =~ $regex ]] || [[ ! $2 =~ $regex ]]
then
    echo "Not all provided parameters are numbers"
fi
if [ $1 -gt $2 ]
then
    temp=$1
    $1=$2
    $2=$temp
fi
mkdir {a,b,c}
for file in $(pwd)/*
do
    if [ -f $file ]
    then
        lines=$(cat $file | wc -l)
        if [ $lines -lt $1 ]
        then
            mv -t "a" $file
        elif [ $lines -ge $1 ] && [ $lines -lt $2 ]
        then
            mv -t "b" $file
        else
            mv -t "c" $file
        fi
    fi
done
```
#### 19. 2016-SE-04 
```bash
#!/usr/bin/bash
if [ $# -lt 2 ]
then
    echo "Invalid number of parameteres"
    exit 1
fi
if [ ! -f $1 ] || [ ! -f $2 ]
then
    echo "Not all provided parameters are files"
fi
lines1=$(cat $1 | grep $1 | wc -l)
lines2=$(cat $2 | grep $2 | wc -l)
if [ $lines1 -lt $lines2 ]
then
    winner="$2"
else
    winner="$1"
fi
cat "$winner" | awk '{$1="";$2="";$3="";print $0}' | cut -c 4-| sort > "$winner.songs"
```
#### 20. 2016-SE-02
```bash
#!/usr/bin/env bash
if [ $# != 1 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
if [ ! -f $1 ]
then
    echo "The provided file does not exist"
    exit 2
fi
cat "$1" | cut -c 10- | awk -v i=1 '{print i "." $0; i++}' | sort -k2
exit 0
```
#### 21. 2017-IN-01
```bash
#!/usr/bin/env bash
if [ $# != 3 ]
then
    echo "Invalid number of parameters"
    exit 1
fi

if [ ! -f $1 ]
then
    echo "The provided file does not exist"
    exit 2
fi
TERMS1="$(cat $1 | grep "$2=" | cut -d "=" -f 2)"   # $2= is very important, as otherwise grep catches the line with key2 as well
RESULT="$3="
for term in $(cat $1 | grep "$3" | cut -d "=" -f 2)
do
    if [ ! $(echo "${TERMS1}" | grep "${term}" | wc -l) -eq 0 ]
    then
        continue
    fi
    RESULT=${RESULT}" "${term}
done
cat $1 | sed -s "s/$(cat $1 | grep "$3")/${RESULT}/g" > bruh.txt    # without the grep here only $3 is replaced
#echo "${RESULT}"
exit 0
```
#### 22. 2017-IN-02
```bash
#!/usr/bin/env bash
if [ $# != 1 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
COUNT=$(ps -a -u "$1" -o pid= | wc -l)
for user in $(who | cut -d ' ' -f 1)
do
    if [ $(ps -a -u "${user}" -o pid= | wc -l) -gt ${COUNT} ]
    then
        echo "${user}"
    fi
done
```
```bash
#!/usr/bin/env bash
if [ $# != 1 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
COUNT=$(ps -a -u "$1" -o pid= | wc -l)
    ps -e -o time= | awk -F ':' -v sum=0 '{nr=NR;sum=sum+$1*3600+$2*360+$3;}END{sum=sum/nr; printf("%02d:%02d:%02d\n", sum/3600, sum/60%60, sum%60)}'
exit 0
```
```bash
#!/usr/bin/env bash
if [ $# != 1 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
AVERAGE=$(ps -e -o times= | awk -v sum=0 '{nr=NR;sum=sum+$1;}END{print sum=sum/nr;}')
ps -e -o pid= -o times= | awk -v avg=${AVERAGE} '$2>2*avg{print $1;}' | xargs -I {} kill 9 {}
exit 0
```
#### 23. 2017-IN-03 
```bash
#!/usr/bin/env bash
find /home -type f -printf "%p; %p %T@\n" | sort -n -k 3 | head -n 1 | sed -s "s/\/home\///" | sed -s "s/\/[^;]*;//" | cut -d ' ' -f 1,2    # folder names may contain space
# that's why I delimit it with ;, which cannot be inside a name
```
#### 24. 2017-SE-01
```bash
#!/usr/bin/env bash
if [ "$EUID" -ne 0 ]
then 
  echo "Please run as root"
  exit
fi
if [ $# -le 1 ]
then
    echo "Invalid number of parameters"
fi
if [ $# -eq 1 ]
then
    find -L "$1" -type l
elif [ $# -eq 2 ]
then
    find "$1" -type f -printf "%p %n" | awk -v limit=${2} '$2>=limit {print $1}'
fi
exit 0
```
#### 25. 2017-SE-02
```bash
#!/usr/bin/env bash
if [ "$EUID" -ne 0 ]
then 
  echo "Please run as root"
  exit
fi
if [ ! $# -eq 3 ]
then
    echo "Invalid number of parameteres"
    exit 0
fi
SRC="$1"
DST="$2"
ABC="$3"

if [ ! $(find "${DST}" -mindepth 2 -maxdepth 2 | wc -l) -eq 0 ]
then
    echo "Directory" "${DST}" "is not empty"
fi

cp -r --no-preserve=all "${SRC}"/* "${DST}"
find "${DST}" -type f ! -name "*${ABC}*" -exec rm {} \;
find "${SRC}" -type f -name "*${ABC}*" -exec rm {} \;
for dr in $(find ${DST} -type d)
do
    if [ ! -d $dr ]
    then
        continue
    fi
    echo $dr
    if [ $(find ${dr} -type f | wc -l) -eq 0 ]
    then
        rmdir $dr
    fi
done
for dr in $(find ${SRC} -type d)
do
    if [ ! -d $dr ]
    then
        continue
    fi
    echo $dr
    if [ $(find ${dr} -type f | wc -l) -eq 0 ]
    then
        rmdir $dr
    fi
done
exit 0
```
#### 26. 2017-SE-03
```bash
#!/usr/bin/env bash
if [ ! $(echo $EUID) -eq 0 ]
then
    echo "Please run as root"
fi
for user in $(ps -e -o user= | cut -d ' ' -f 1 | sort | uniq)
do
    echo $user - $(ps -a -o rss= -u $user | awk -v sum=0 '{sum+=$1;}END{print sum;}')
done
exit 0
```
#### 27. 2017-SE-04
```bash
#!/usr/bin/env bash
if [ $# -lt 1 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
RESULT="$(echo "$(find $1 -maxdepth 1 -type l -printf "%f -> %l\n")" "Broken links:\n" "$(find -L $1 -type l | wc -l)")" 
if [ $# -eq 1 ]
then
  echo "${RESULT}"
else
  echo "${RESULT}" > "$2"
fi
exit 0
```
#### 28. 2017-SE-05
```bash
#!/usr/bin/env bash
if [ $# -lt 2 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
DIR="$1"
STR="$2"
find $DIR -maxdepth 1 -type f -printf "%f\n" | egrep "^vmlinuz-[0-9]+.[0-9]+.[0-9]+-${STR}$" | awk -F '-' '{printf "%s.%s\n",$2,$0}' | tail -n 1 | cut -d '.' -f 4-
exit 0
```
#### 29. 2017-SE-06 
```bash
#!/usr/bin/env bash

STRING=""
cat /etc/passwd | while read -r line    # very important, /etc/passwd has spaces in it which break the for cycle
do
  DIR=$(echo "${line}" | cut -d ':' -f 7)
  USR=$(echo "${line}" | cut -d ':' -f 1)
  if [ ! -d "${DIR}" ] || [ ! "$(stat -c "%U" $DIR)" = "${USR}" ] || [ "$(stat -c "%A" ${DIR} | cut -c 3)" = "-"] 
  then
    STRING="$(echo ${STRING}"\n"${USR})"
  fi
done
LIMIT=$(ps -a -u 0 -o rss= | awk -v sum=0 '{sum+=$1}END{print sum}')
for usr in ${STRING}
do
  if [ $(ps -a -u "$usr" | awk -v sum=0 '{sum+=$1}END{print sum}') -ge $LIMIT ]
  then 
    ps -a -u "$usr" -o pid= | xargs -I {} kill 9 {}
  fi
done
exit 0
```
#### 30. 2018-SE-01
```bash
#!/usr/bin/env bash
if [ ! $# -eq 1 ]
then
  echo "invalid number of parameters"
  exit 1
fi
LOGDIR="$1"
FILE="$(mktemp)"
for friend in $(find ${LOGDIR} -mindepth 3 -maxdepth 3 -printf "%f\n" | sort | uniq)
do
  echo $friend $(find $LOGDIR -mindepth 4 -maxdepth 4 -path "$LOGDIR/*/*/$friend/*"| egrep "[0-9]{4}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}.txt$" | xargs wc -l | tail -n 1 | cut -d ' ' -f 2) >> $FILE 
done
cat $FILE | sort -nr -k 2 | head -n 10
exit 0
```
#### 31. 2018-SE-02
```bash
#!/usr/bin/env bash
if [ ! $# -eq 2 ]
then
  echo "invalid number of parameters"
  exit 1
fi
FILE="$1"
DIR="$2"
if [ ! -d "$DIR" ]
then
  echo "Directory does not exist"
  exit 2
fi
if [ ! -f "$FILE" ]
then
  echo "File does not exist"
  exit 3
fi
if [ ! $(find "$DIR" -mindepth 1 | wc -l) -eq 0 ]
then
  echo "Directory is not empty"
  exit 4
fi
STRING="$(cat "${FILE}" | tr -s ' ' | sed -E -s "s/([a-zA-Z^ ]+ [a-zA-Z^ ]+)?\([a-zA-Z ]+\)?/\1/g" | sed -s "s/\s*:\s*/:/g")"
touch dict.txt
COUNTER=0
echo "$STRING" | cut -d ':' -f 1 | sort | uniq | while read -r person
do
  COUNTER=$(( $COUNTER + 1 ))
  echo "$person;$COUNTER" >> dict.txt
  touch "${DIR}/${COUNTER}.txt"
  echo "$STRING" | awk -F ':' -v p="${person}" '$1==p{print $2}' >> "${DIR}/${COUNTER}.txt" 
done
exit 0
```
#### 32. 2018-SE-03
```bash
#!/usr/bin/env bash
if [ ! $# -eq 2 ]
then
  echo "invalid number of parameters"
  exit 1
fi
if [ ! -f $1 ]
then
  echo "File does not exist"
  exit 2
fi
FILE1="$1"
FILE2="$2"
NF=$(cat "${FILE1}" | head -n 1 | awk -F ',' 'END{print NF}')
cat "${FILE1}" | sort -t ',' -k 1,1 | sort -s -t ',' -k2,$NF -u > "${FILE2}"
exit 0

#Explanation
# sorting by first key will make lines be ordered by their ID
# sorting stabily with -s then sorts by all other fields, thus making identical lines (except the id) be next to each other but in the same time be ordered by their ID
# -u removes the duplicates specified by the sorting key, which is k2,$NF
# sort -t ',' -k2,$NF -u -k1,1 doesn't work for some reason. It seems that there must be exactly one -k for -u to work
```
#### 33. 2019-SE-01



#### 50. 2016-SE-02
```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>
#include <err.h>
#include <sys/stat.h>
#include <stdint.h>
int main(int argc, char* argv[]){
    if (argc != 4){
        errx(1, "Invalid number of parameters");
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1){
        err(2, "Could not open file");
    }
    struct stat st1;
    stat(argv[1], &st1);
    uint32_t size1 = st1.st_size;

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1){
        err(3,"Could not open file");
    }
    struct stat st2;
    stat(argv[2], &st2);
    uint32_t size2 = st2.st_size;

    if (size1%8 !=0 || size2%4 != 0){
        err(3, "Invalid file contents");
    }

    int fd3 = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU|S_IROTH);
    if (fd3 == -1){
        err(4, "Could not open file");
    }

    struct pair {
        uint32_t start;
        uint32_t length;
    } pair;

    while(read(fd1, &pair, sizeof(pair) == sizeof(pair))){
        lseek(fd2, pair.start*sizeof(uint32_t), SEEK_SET);
        for(uint32_t i=0; i<pair.length; i++){
            if(read(fd2, &pair, sizeof(pair)) != sizeof(pair)){
                err(5, "Invalid read");
            }
            if(write(fd3, &pair, sizeof(pair))!=sizeof(pair)){
                err(6, "Invalid read");
            }
        }
    } 

    close(fd1);
    close(fd2);
    close(fd3);
    exit(0);
}
```
#### 52. 2017-IN-01
```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char* argv[]){
    struct tuple{
        uint16_t shift;
        uint8_t length;
        uint8_t reserved;
    }__attribute__((packed)) tuple;
    
    if (argc != 5){
        errx(1, "Invalid number of parameters");
    }
    
    int fd_dat1 = open(argv[1], O_RDONLY);
    if (fd_dat1 == -1){
        err(2, "%s", argv[1]);
    }
    int fd_idx1 = open(argv[2], O_RDONLY);
    if (fd_idx1 == -1){
        err(2, "%s", argv[2]);
    }
    int fd_dat2 = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
    if (fd_dat1 == -1){
        err(2, "%s", argv[3]);
    }
    int fd_idx2 = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    if (fd_idx2 == -1){
        err(2, "%s", argv[4]);
    }
    while(read(fd_idx1,&tuple, sizeof(tuple))==sizeof(tuple)){
        if(lseek(fd_dat1, tuple.shift, SEEK_SET) == -1){
            err(3, "Could not move in file");
        }
        char str[tuple.length];
        if (str == NULL){
            err(4, "Could not allocate memory");
        }
        if(read(fd_dat1, &str, tuple.length) != tuple.length){
            err(4, "Could not read from file %s", argv[1]);
        }
        if (str[0] >= 0x41 && str[0] <= 0x5A){
            if(write(fd_dat2, &str, tuple.length) != tuple.length){
                err(5, "Could not write in file %s", argv[3]);
            }
            if(write(fd_idx2, &tuple, sizeof(tuple)) != sizeof(tuple)){
                err(5, "Could not write in file %s", argv[4]);
            }
        }
    }

    if(close(fd_dat1) != 0){
        err(3, "%s", argv[1]);
    }
    if(close(fd_idx1) != 0){
        err(3, "%s", argv[1]);
    }
    if(close(fd_dat2) != 0){
        err(3, "%s", argv[1]);
    }
    if(close(fd_idx2) != 0){
        err(3, "%s", argv[1]);
    }
}
```
#### 53. 2017-SE-01
```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
int main(int argc, char* argv[]){
    struct tuple{
        uint16_t shift;
        uint8_t original;
        uint8_t replacement;
    }__attribute__((packed)) tuple;    
    if (argc != 4){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }    
    int fd1bin = open(argv[1], O_RDONLY);
    if (fd1bin == -1){
        err(EXIT_FAILURE, "%s", argv[1]);
    }
    int fd2bin = open(argv[2], O_RDONLY);
    if (fd2bin == -1){
        err(EXIT_FAILURE, "%s", argv[2]);
    }
    int fd_patch = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    if (fd_patch == -1){
        err(EXIT_FAILURE, "%s", argv[3]);
    }
    uint8_t c1;
    uint8_t c2;
    uint16_t position=-1;
    while (read(fd1bin, &c1, sizeof(c1)) == sizeof(c1)){
        position++;
        if (read(fd2bin, &c2, sizeof(c2)) != sizeof(c2)){
            err(EXIT_FAILURE, "Could not read from file %s", argv[2]);
        }
        if (c1 != c2){
            tuple.shift = position;
            tuple.original = c1;
            tuple.replacement = c2;
            if(write(fd_patch, &tuple, sizeof(tuple)) != sizeof(tuple)){
                err(EXIT_FAILURE, "Could not write in file %s", argv[3]);
            }
        }
    }
    if(close(fd1bin) != 0){
        err(EXIT_FAILURE, "%s", argv[1]);
    }
    if(close(fd2bin) != 0){
        err(EXIT_FAILURE, "%s", argv[2]);
    }
    if(close(fd_patch) != 0){
        err(EXIT_FAILURE, "%s", argv[3]);
    }
}
```
#### 54. 2017-SE-02 ⚠️
```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char* argv[]){
    bool enumerating = false;
    char c;
    int line=1;
    if (argc == 1){
            if(read(0, &c, sizeof(c)) != sizeof(c)){
                err(EXIT_FAILURE, "Could not read from stdin");
            }
            if (write(1, &c, sizeof(c)) != sizeof(c)){
                err(EXIT_FAILURE, "Could not write to stdout"); 
            }
    }
    int i=1;
    if (strcmp(argv[1], "-n")==0){
        enumerating = true;
    }
    for (;i <= argc; i++){
        if (enumerating == true){
            char str[2];
            str[0]=line;
            str[1]=(char)" ";
            if(write(1, &str, sizeof(str)) != sizeof(str)){
                err(EXIT_FAILURE, "Could not write to stdout");
            } 
            if(strcmp(argv[i], "-")==0){

            }else{
                int fd=open(argv[i], O_RDONLY);
                while(read(fd, &c, sizeof(c)) == sizeof(c)){
                    if(write(1, &c, sizeof(c)) != sizeof(c)){
                            err(EXIT_FAILURE, "Could not write to stdout");
                    } 
                    if(c=="\n"){
                        line++;
                        str[0]=line;
                        if(write(1, &str, sizeof(str)) != sizeof(str)){
                            err(EXIT_FAILURE, "Could not write to stdout");
                        }           
                    }
                }
                close(fd);
            }
        }
        else{
            if(strcmp(argv[i], "-")==0){

            }
            else{
                int fd=open(argv[i], O_RDONLY);
                while(read(fd, &c, sizeof(c)) == sizeof(c)){
                    if(write(1, &c, sizeof(c)) != sizeof(c)){
                            err(EXIT_FAILURE, "Could not write to stdout");
                    } 
                }
                close(fd);
            }
        }
    }
}
```
####  55. 2017-SE-03
```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/stat.h>
int main(int argc, char* argv[]){
    struct tuple{
        uint16_t shift;
        uint8_t original;
        uint8_t replacement;
    }__attribute__((packed)) tuple;    
    int fd_patch = open(argv[1], O_RDONLY);
    if (fd_patch == -1){
        err(EXIT_FAILURE, "%s", argv[1]);
    }
    if (argc != 4){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }    
    int fd1bin = open(argv[2], O_RDONLY);
    if (fd1bin == -1){
        err(EXIT_FAILURE, "%s", argv[2]);
    }
    int fd2bin = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    if (fd2bin == -1){
        err(EXIT_FAILURE, "%s", argv[3]);
    }
    uint8_t c;
    uint16_t position=-1;
    struct stat st;
    stat(argv[0], &st);
    if (st.st_size != 0){
        int result = read(fd_patch, &tuple, sizeof(tuple));
        if (result == -1){
            err(EXIT_FAILURE, "Could not read from %s", argv[1]);
        }
    }
    else{
        tuple.shift=0;
    }
    while (read(fd1bin, &c, sizeof(c)) == sizeof(c))
    {
        position++;
        if(position == tuple.shift && c == tuple.original){
            c = tuple.replacement;
            int result = read(fd_patch, &tuple, sizeof(tuple));
            if(result == -1){
                err(EXIT_FAILURE, "Could not read from file %s", argv[1]);
            }
            if(result < sizeof(tuple)){
                tuple.shift = position;
                // never will patch be read again
            }
        }
        if (write(fd2bin, &c, sizeof(c)) != sizeof(c)){
            err(EXIT_FAILURE, "Could not read from file %s", argv[3]);
        }
    }
    if(close(fd1bin) != 0){
        err(EXIT_FAILURE, "%s", argv[1]);
    }
    if(close(fd2bin) != 0){
        err(EXIT_FAILURE, "%s", argv[2]);
    }
    if(close(fd_patch) != 0){
        err(EXIT_FAILURE, "%s", argv[3]);
    }
}
```
#### 56. 2017-SE-04
```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
int main (int argc, char* argv[]){
    char c;
    if (argc == 1){
    while(read(STDIN_FILENO, &c, sizeof(c))==sizeof(c)){
            if(write(STDOUT_FILENO, &c, sizeof(c))!=sizeof(c)){
                err(EXIT_FAILURE, "Could not write to STDOUT");
            }
        }
    }
    else{
        for (int i=1; i<argc; i++){
            if(strcmp(argv[i], "-") == 0){
                while(read(STDIN_FILENO, &c, sizeof(c))==sizeof(c)){
                    if(write(STDOUT_FILENO, &c, sizeof(c))!=sizeof(c)){
                        err(EXIT_FAILURE, "Could not write to STDOUT");
                    }
                }
            }
            else{
                int fd = open(argv[i], O_RDONLY);
                while(read(fd, &c, sizeof(c))==sizeof(c)){
                    if(write(STDOUT_FILENO, &c, sizeof(c))!=sizeof(c)){
                        err(EXIT_FAILURE, "Could not write to stdout");
                    }
                }
                close(fd);
            }
        }
    }
    exit(0);
}
```
#### 57. 2018-SE-01
```c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

int in(char* str, char c);
int in(char* str, char c){
    for(size_t i=0; i<strlen(str); i++){
        if (c==str[i]){
            return 1;
        }
    }
    return 0;
}

int main (int argc, char* argv[]){
    char c1;
    char c2;
    struct pair{
        char first;
        char second;
    };

    if (argc != 3){
        errx(EXIT_FAILURE, "Invalid number of parameters");
    }
       
    if (strcmp(argv[1], "-s") == 0){
        char set1[strlen(argv[2])+1]; 
        strcpy(set1,argv[2]);

        if(read(STDIN_FILENO, &c1, sizeof(c1))!=sizeof(c1)){
                err(EXIT_FAILURE, "Could not write to STDOUT");
        }
        if(write(STDOUT_FILENO, &c1, sizeof(c1))!=sizeof(c1)){
                err(EXIT_FAILURE, "Could not write to STDOUT");
        }

        while(read(STDIN_FILENO, &c2, sizeof(c2))==sizeof(c2)){
            if(c1 != c2 || in(set1, c1)==0){
                c1=c2;
                if (write(STDOUT_FILENO, &c2, sizeof(c2))!= sizeof(c2)){
                    err(EXIT_FAILURE, "Could not write to STDOUT");
                }
            }
        }
    }
    else if(strcmp(argv[1], "-d") == 0){
        char set1[strlen(argv[2])+1]; 
        strcpy(set1,argv[2]);

        if(read(STDIN_FILENO, &c1, sizeof(c1))!=sizeof(c1)){
                err(EXIT_FAILURE, "Could not write to STDOUT");
        }
        if(write(STDOUT_FILENO, &c1, sizeof(c1))!=sizeof(c1)){
                err(EXIT_FAILURE, "Could not write to STDOUT");
        }

        while(read(STDIN_FILENO, &c1, sizeof(c1))==sizeof(c1)){
            if(in(set1, c1)==0){
                if (write(STDOUT_FILENO, &c1, sizeof(c1))!= sizeof(c1)){
                    err(EXIT_FAILURE, "Could not write to STDOUT");
                }
            }
        }
    }
    else{
        char set1[strlen(argv[1])+1]; 
        strcpy(set1,argv[1]);
        char set2[strlen(argv[2])+1]; 
        strcpy(set2,argv[2]);
        if (strlen(set1)!=strlen(set2)){
            err(EXIT_FAILURE, "Set 1 and Set2 are not of equal length");
        }
        struct pair map[256];
        for (int i=0; i<256; i++){
            map[i].first=i;
            map[i].second=i;
        }
        for(size_t i=0; i<strlen(set1); i++){
            map[(int)set1[i]].second=set2[i]; 
        } 
        while(read(STDIN_FILENO, &c1, sizeof(c1))==sizeof(c1)){
            c2 = map[(int)c1].second;
            if (write(STDOUT_FILENO, &c2, sizeof(c2))!= sizeof(c2)){
                err(EXIT_FAILURE, "Could not write to STDOUT");
            }
        }
    }
    exit(0);
}
```
#### 65. 2021-SE-01
```c
#include <err.h>     // for err and errx
#include <fcntl.h>   // for open
#include <stdint.h>  // for ints
#include <stdio.h>   // for IO
#include <stdlib.h>  // for exit
#include <unistd.h>  // for close

uint8_t arr1[]  = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080};
uint16_t arr2[] = {0x0002, 0x0008, 0x0020, 0x0080, 0x0200, 0x0800, 0x2000, 0x8000};
uint16_t arr3[] = {0x0001, 0x0004, 0x0010, 0x0040, 0x0100, 0x0400, 0x1000, 0x4000};

uint16_t encode(const uint8_t number);
uint16_t encode(const uint8_t number) {
    uint16_t result = 0;
    for (int i = 0; i < 8; i++) {
        if ((number & arr1[i]) > 0) {
            result = result | arr2[i];
        }
    }

    for (int i = 0; i < 8; i++) {
        if ((number & arr1[i]) == 0) {
            result = result | arr3[i];
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(EXIT_FAILURE, "Invalid number of parameteres");
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        err(EXIT_FAILURE, "Could not open first file");
    }

    int fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd2 == -1) {
        err(EXIT_FAILURE, "Could not open second file for writing");
    }

    uint16_t map[256];
    for (int i = 0; i < 256; i++) {
        map[i] = encode(i);
    }

    uint8_t number;
    uint16_t encodedNumber;
    while (read(fd1, &number, sizeof(number)) == sizeof(number)) {
        encodedNumber = map[number];
        if (write(fd2, &encodedNumber, sizeof(encodedNumber)) !=
            sizeof(encodedNumber)) {
            err(EXIT_FAILURE, "Could not write to output file");
        }
    }
    if (close(fd1)) {
        err(EXIT_FAILURE, "Could not close input file");
    }
    if (close(fd2)) {
        err(EXIT_FAILURE, "Could not close output file");
    }
    exit(0);
}
```
