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
#### 19.  2016-SE-04 
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
#### 50
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
