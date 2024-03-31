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
find . -type f -printf "%p|%s\\n" | sort -t "|" -nr -k 2 | head -n 5| awk -F "|" '{print $1} | 'xargs -I {} rm {}
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
#### 10. 2019-SE-02
```bash
cat /etc/passwd | grep -E "$(find /home -maxdepth 1 -mindepth 1 -type d -printf "%p\\t%C@\\n" | awk -F "\t" '$2 > 1700000000 && $2 < 1720000000 {print $1}')" | cut -d ":" -f 1,5 | cut -d "," -f 1
```
#### 11. 2019-SE-03
```bash
find /home/velin -type f -inum $(find /home/velin -type f -printf "%T@ %p %i\n" | sort -k 1 | head -n 1 | cut -d ' ' -f 3) | grep -o / | wc -l
```
```bash
find /home/velin -samefile $(find /home/velin -type f -printf "%p|%T@\\n" | sort -t "|" -nr -k2 | head -n 1 | cut -d "|" -f 1)
```
```bash
find /home/velin -type f | sort -k 1 | head -n 1 | cut -d ' ' -f 3 | grep -o / | wc -l
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
if [ ! $(id --user) -eq 0 ]
then
  echo "Not running as root"
  exit 1
fi
while IFS=: read -r user _ _ _ _ homeDir _ 
do
  if [[ ! ${homeDir} =~ "/home" ]]
  then
    echo ${user}
  elif [[ ! -d ${homeDir} ]]
  then
    echo ${user}
  else
    permission=$(ls -ld ${homeDir} | cut -c 3)
    if [[ ${permission} != "w" ]]
    then 
      echo ${user}
    fi
  fi
done < /etc/passwd

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
или
```bash
#!/usr/bin/env bash

if [ $# != 1 ]
then
  echo "Please supply exactly one parameter" >&2
  exit 1
fi

inputUserProcesses=$(ps -u $1 -o pid=)
minCount=$(echo ${inputUserProcesses} | wc -l)
allProcesses=$(ps -e -o user=,pid=,time=)

declare -A userProcessCount
declare -A userProcessTime
hours=0
munites=0
seconds=0

while read -r user pid time
do
  hh=$(echo ${time} | cut -d ":" -f 1 | sed -E "s/^0{1}//g")
  mm=$(echo ${time} | cut -d ":" -f 2 | sed -E "s/^0{1}//g")
  ss=$(echo ${time} | cut -d ":" -f 3 | sed -E "s/^0{1}//g")
  hours=$((${hours} + ${hh}))
  minutes=$((${munites} + ${mm}))
  seconds=$((${seconds} + ${ss}))
  userProcessCount[${user}]=$(( userProcessCount[${user}] + 1 ))
  userProcessTime[${pid}]=$(( userProcessTime[${pid}] + $((${hh} * 360 + ${mm} * 60 + ${ss}))))
done < <(ps -e -o user=,pid=,time=)

totalTime=$((${hours} * 360 + ${munites}*60 + ${seconds}))
averageTime=$((${totalTime} / $(echo ${allProcesses} | wc -l)))
for user in ${!userProcessCount[@]}
do
  if [ ${userProcessCount[${user}]} -gt ${minCount} ]
  then
    echo ${user}
  fi
done

printf "%02d:%02d:%02d" $((${averageTime} / 3600)) $(((${averageTime} % 3600) / 60)) $((${averageTime} % 60))

for pid in ${!userProcessTime[@]}
do
  if [ ${userProcessTime[${pid}]} -gt $((${averageTime} * 2)) ]
  then
    echo ${pid}
  fi
done
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
    # find "$1" -type f -printf "%p %n" | awk -v limit=${2} '$2>=limit {print $1}'
    find $1 -type f -links +$2
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
или
```bash
#!/usr/bin/env bash

if [ $# -lt 3 ]
then
  echo "Please provide at least three parameters" >&2
  exit 1
fi

if [ $(id --user) -ne 0 ]
then
  echo "Please run as root" >&2
  exit 1
fi

if [ ! -d $1 ]
then
  echo "Source must be a directory" >&2
  exit 1
fi

if [ ! -d $2 ]
then
  echo "Destination must be a directory" >&2
  exit 1
fi

SRC=$1
DST=$2
STR=$3

for file in $(find ${SRC} -type f -name "*${STR}*" -printf "%p|%h\n")
do
  fullPath=$(echo ${file} | cut -d "|" -f 1)
  directories=$(echo ${file} | cut -d "|" -f 2 | sed -E "s/${SRC}[\/]?//g")
  if [ ! -d ${DST}/${directories} ]
  then
    mkdir -p "${DST}/${directories}"
  fi
  mv "${fullPath}" "${DST}/${directories}"
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
```bash
#!/usr/bin/env bash
FILE="$(mktemp)"
while read line
do
  echo "$line" | tr -c '[0-9.\-]'  ' ' | tr -s ' ' | tr ' ' '\n' | grep "[0-9]" >> $FILE
done < ${1:-/dev/stdin}
STRING="$(cat $FILE | sort -n)"
NUM1="$(echo "$STRING" | head -n 1)"
NUM2="$(echo "$STRING" | tail -n 1)"

if [ ${NUM1#-} -gt ${NUM2#-} ]
then
  echo $NUM1
elif [ ${NUM1#-} -lt ${NUM2#-} ]
then
  echo $NUM2
else
  echo $NUM1
  echo $NUM2
fi
exit 0
```
```bash
#!/usr/bin/env bash
FILE1="$(mktemp)"
FILE2="$(mktemp)"
while read line
do
  echo "$line" | tr -c '[0-9.\-]'  ' ' | tr -s ' ' | tr ' ' '\n' | grep "[0-9]" >> $FILE1
done < ${1:-/dev/stdin}
cat $FILE1 | awk -F '' '{sum=0;for(i=1; i<=NF; i++)sum+=$i;print $0, sum}' | sort -k2,2nr -k1,1n | head -n 1 | cut -d ' ' -f 1
exit 0
```
#### 34. 2019-SE-02
```bash
#!/usr/bin/env bash
if [ $# -lt 1 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
FILE=$(mktemp)
if [ $1 == "-n" ]
then
  START=3
  REGEX="^[0-9]+$"
  if [[ $2 =~ "$REGEX" ]]
  then
    NUM=$2
  else
    echo "Invalid format"
    exit 1
  fi
else
  START=1
  NUM=10
fi
for ((i=$START; i<=$#; i++))
do
  NAME="$(echo "${!i}" | sed -s 's/.log//g')"
  cat "${!i}" | tail -n $NUM | awk -v name=$NAME '{$2=$2" "name; print $0}' >> $FILE
done
cat $FILE | sort -nr
```
####  35. 2019-SE-03
```bash

```
#### 36. 2020-SE-01
```bash
#!/usr/bin/env bash
if [ $# -lt 2 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
FILE="$1"
DIR="$2"
echo "hostname,phy,vlans,hosts,failover,VPN-3DES-AES,peers,VLAN Trunk Ports,license,SN,key" > $FILE
if [ ! -f "$FILE" ]
then
  echo "File does not exist"
fi
if [ ! -d "$DIR" ]
then
  echo "Directory does not exist"
fi
for file in $(find "$DIR" -type f -name "*.log")
do
  NAME="$(basename "$file" | sed -s "s/.log//g")"
  printf "$NAME" >> $FILE 
  cat "$file" | tr -s ' ' | grep -v "Licensed features for this platform:" | sed -s "s/ license.//g" | sed -E -s "s/This platform has an{0,1}/ license :/g" | sed -s "s/ : /:/g" | sed -s "s/: /:/g" | sed -E -s "s/Serial//g" | sed -E -s "s/Running//g" | grep -E -v "^+$"| cut -c 2- | awk -F ':' '{printf ",%s",$2}' >>$FILE
  echo >> $FILE
done
```
####  37. 2020-SE-02
```bash
#!/usr/bin/env bash
if [ $# -lt 1 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
TOP="$(cat $1 | cut -d ' ' -f 2 | sort | uniq -c | sort -nr -k1,1 | head -n 3 | tr -s ' ' | cut -c 2- | cut -d ' ' -f 2)"
for website in $TOP
do
  LOGS="$(cat $1 | grep "$website")"
  printf "%s HTTP/2.0:  %d non-HTTP/2.0:  %d\n" "$website" "$(echo "$LOGS" | cut -d ' ' -f8 | grep "HTTP/2.0" | wc -l)" "$(echo "$LOGS" | cut -d ' ' -f8 | grep -v "HTTP/2.0" | wc -l)"
  echo "$LOGS" | awk '$9>302{print $1}' | sort | uniq -c
done
```
#### 38. 2020-SE-03
```bash
#!/usr/bin/env bash

if [ $# -lt 2 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
REPO_PATH="$(realpath $1)"
PACKAGE_PATH="$(realpath $2)"
if [ ! $(find $REPO_PATH -mindepth 1 -type f -name "db" | wc -l) -eq 1 ]
then
  echo "Invalid repo"
fi
if [ ! $(find $REPO_PATH -mindepth 1 -type d -name "packages" | wc -l) -eq 1 ]
then
  echo "Invalid repo"
fi
if [ ! $(find $PACKAGE_PATH -mindepth 1 -type f -name "version" | wc -l) -eq 1 ]
then
  echo "Invalid package"
fi
if [ ! $(find $PACKAGE_PATH -mindepth 1 -type d -name "tree" | wc -l) -eq 1 ]
then
  echo "Invalid package"
fi
BASE="$(basename $PACKAGE_PATH)"
VERSION="$BASE-$(cat "$PACKAGE_PATH/version" | head -n 1 | egrep "[0-9]+.[0-9]+.[0-9]+-[0-9]+" | tr -d ' ')"
tar cf "$BASE.tar" "$PACKAGE_PATH/tree"
xz -z "$BASE.tar"
HASH="$(sha256sum "$BASE.tar.xz" | cut -d ' ' -f 1 | tr -d ' ')"
mv "$BASE.tar.xz" "$REPO_PATH/packages/$HASH.tar.xz"
SAME_VERSIONS=$(cat "$REPO_PATH/db" | egrep "$VERSION" | wc -l)
if [ $SAME_VERSIONS -eq 0 ]
then
    echo "$VERSION" "$HASH" >> "$REPO_PATH/db"
    mv "$REPO_PATH/db" "$REPO_PATH/tmp"
    cat "$REPO_PATH/tmp" | sort -k1,1 > "$REPO_PATH/db"
    rm "$REPO_PATH/tmp"
elif [ $NAME_VERSIONS -eq 1 ]
then
  cat "$REPO_PATH/db" | egrep -v "$VERSION" > "$REPO_PATH/tmp"
  echo "$VERSION" "$HASH" >> "$REPO_PATH/tmp"
  rm "$REPO_PATH/db" 
  mv "$REPO_PATH/tmp" "$REPO_PATH/db"
fi
```
#### 39. 2020-SE-04
```bash
#!/usr/bin/env bash

if [ $# -lt 2 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
SRC="$(realpath $1)"
DST="$(realpath $2)"

if [ ! -d "$SRC" ]
then
  echo "Non-existent source"
  exit 1
fi

if [ -d "$DST" ]
then
  echo "Existent destination"
  exit 1
fi

mkdir -p "$DST/images"
mkdir "$DST/by-date"
mkdir "$DST/by-album"
mkdir "$DST/by-title"

find "$SRC" -type f -name "*.jpg" -print0 | 
  while IFS= read -r -d '' file
  do
    TITLE="$(echo " " "$(basename "$file")" | tr -s ' ' | cut -c 2- | sed -E -s "s/[\ ]*.[\ ]*jpg[\ ]*//g" | sed -E -s "s/\([^\(\)]*\)//g" | tr -s ' ')"
    ALBUM="$(echo "$(basename "$file")" | egrep "^[a-zA-Z\(\) ]+\(([^\(\)]+)\)[^\(\)]*$" | sed -E -s "s/^[a-zA-Z\(\)\ ]+\(([^\(\)]+)\)[^\(\)]*$/\1/g")"
    if [ "$ALBUM" = "" ]
    then
      ALBUM='misc'
    fi
    DATE="$(stat -c "%y" "$file" | cut -d ' ' -f 1)"
    HASH="$(sha256sum "$file" | cut -c 1-16)"
    NEW_NAME="$DST/images/$HASH.jpg"
    cp "$file" "$NEW_NAME"
    mkdir -p "$DST/by-date/$DATE/by-album/$ALBUM/by-title"
    ln -rs "$NEW_NAME" "$DST/by-date/$DATE/by-album/$ALBUM/by-title/$TITLE.jpg"
    mkdir -p "$DST/by-date/$DATE/by-title"
    ln -rs "$NEW_NAME" "$DST/by-date/$DATE/by-title/$TITLE.jpg"
    mkdir -p "$DST/by-album/$ALBUM/by-date/$DATE/by-title" 
    ln -rs "$NEW_NAME" "$DST/by-album/$ALBUM/by-date/$DATE/by-title/$TITLE.jpg"
    mkdir -p "$DST/by-album/$ALBUM/by-title"
    ln -rs "$NEW_NAME" "$DST/by-album/$ALBUM/by-title/$TITLE.jpg"
    mkdir -p "$DST/by-title"
    ln -rs "$NEW_NAME" "$DST/by-title/$TITLE.jpg"
  done
```
#### 40. 2020-SE-05
```bash
#!/usr/bin/env bash

if [ $# -lt 3 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
USERS="$1"
CONFIG_FILE="$2"
DIR="$3"

if [ ! -f "$USERS" ]
then
  echo "Non-existent users file"
  exit 1
fi

if [ -f "$CONFIG_FILE" ]
then
  echo "Existent config file"
  exit 1
fi

if [ ! -d "$DIR" ]
then
  echo "Non-existent directory"
  exit 1
fi

STR1="{ no-production };"
STR2="{ volatile };"
STR3="{ run-all; };"

GROUP="($STR1)|($STR2)|($STR3)"
touch "$CONFIG_FILE"

find "${DIR}" -type f -name "*.cfg" -print0 |
  while IFS= read -r -d '' file
  do
    if [ ! $(cat "$file" | egrep -v "$GROUP" | wc -l) -eq 0 ]
    then
      echo Error in "$(basename "$file")" : 
      cat "$file" | awk  -v regex="$GROUP" '$0 !~ /regex/ {printf "Line %d: %s\n",NR,$0}'
      continue;
    fi
    NAME="$(basename "$file" | sed -s "s/.cfg//g")"
    cat "$file" >> "$CONFIG_FILE"
    if [ $(cat "$USERS" | egrep "$NAME" | wc -l) -eq 0 ]
    then
      PWD="somepassword" # "$(pwgen 16 1)"
      printf "%s:%s\n" "$NAME" "$PWD" >> "$USERS"
      echo "$NAME" "$PWD" 
    fi
  done
```
#### 41. 2020-SE-06
```bash
#!/usr/bin/env bash
# breaks if there is a case # to...  \nto ...
if [ $# -lt 3 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
FILE="$1"
KEY="$2"
VALUE="$3"

if [ ! -f "$FILE" ]
then
  echo "Non-existent users file"
  exit 1
fi

DATE="$(date)"
USER="$(whoami)"
if [ $(cat "$FILE" | cut -d '=' -f 1 | egrep "$KEY" | wc -l) -eq 0 ]
then
  echo "Hello"
  printf "%s = %s # added at %s by %s\n" "$KEY" "$VALUE" "$DATE" "$USER" >> "$FILE"
else
  echo "Bye"
  sed -E -s "s/^([\ ]*$KEY[\ ]*=[^\n]+)$/\# \1 \# edited at $DATE by $USER \\n$KEY=$VALUE \# added at $DATE by $USER/g" "$FILE"
fi
```
#### 42. 2021-SE-01
```bash

```
#### 44. 2021-SE-03 
```
#!/usr/bin/env bash
if [ $# -lt 2 ]
then
  echo "Invalid number of parameters"
  exit 1
fi
INPUT="$1"
OUTPUT="$2"
STRING="$(xxd $INPUT | cut -d ' ' -f2-9 | sed -E -s "s/([0-9a-z]{4})/\t\t0x\1,\\n/g" | egrep ",")"
echo "$STRING"
COUNT=$(echo "$STRING" | wc -l)
echo "#include <stdint.h>" > $OUTPUT
echo "int main (int argc, char* argv[]){" >> $OUTPUT
echo -e "\tuint32_t arrN=$COUNT;" >> $OUTPUT
echo -e "\tuint16_t arr[]={" >> $OUTPUT
echo "$STRING" >> $OUTPUT
echo -e "\t};\n}" >> $OUTPUT
```
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

#include <err.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define A 0x41
#define Z 0x5A
#define NUM_PARAMETERS 5

int main(int argc, char* argv[]) {
  // argv[1]   f1data
  // argv[2]   f1index
  // argv[3]   f2data
  // argv[4]   f2index
  if (argc != NUM_PARAMETERS) {
    errx(EXIT_FAILURE, "Please provide 4 parameters.");
  }
  int f1data = open(argv[1], O_RDONLY);
  if (f1data < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s", argv[1]);
  }
  int f1index = open(argv[2], O_RDONLY);
  if (f1index < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s", argv[2]);
  }

  int f2data =
      open(argv[3], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRGRP | S_IROTH);
  if (f2data < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s", argv[3]);
  }
  int f2index =
      open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRGRP | S_IROTH);
  if (f2index < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s", argv[4]);
  }
  struct triple {
    uint16_t offset;
    uint8_t length;
    uint8_t reserved;
  };
  struct triple triple;
  while (read(f1index, &triple, sizeof(triple)) == sizeof(triple)) {
    if (lseek(f1data, triple.offset, SEEK_SET) == -1) {
      err(EXIT_FAILURE, "Couldn't move cursor in file %s", argv[1]);
    }
    uint8_t* string = calloc(triple.length, sizeof(uint8_t));
    if (string == NULL) {
      err(EXIT_FAILURE, "Couldn't allocate memory");
    }
    if (read(f1data, string, triple.length * sizeof(uint8_t)) <
        triple.length * sizeof(uint8_t)) {
      errx(EXIT_FAILURE, "Couldn't read string from %s", argv[1]);
    }
    if (string[0] >= A && string[0] <= Z) {
      if (write(f2data, string, triple.length * sizeof(uint8_t)) !=
          triple.length * sizeof(uint8_t)) {
        errx(EXIT_FAILURE, "Couldn't write in file %s", argv[3]);
      }
      off_t position = lseek(f2index, 0, SEEK_CUR);
      if (position == -1) {
        err(EXIT_FAILURE, "Couldn't find cursor in file %s", argv[3]);
      }
      triple.offset = position;
      if (write(f2index, &triple, sizeof(triple)) < sizeof(triple)) {
        errx(EXIT_FAILURE, "Couldn't write in file %s", argv[4]);
      }
    }
    free(string);
  }
  if (write(f2data, "\0", sizeof("\0")) != sizeof("\0")) {
    errx(EXIT_FAILURE, "Couldn't write in file %s", argv[3]);
  }
  close(f1data);
  close(f1index);
  close(f2data);
  close(f2index);
  exit(EXIT_SUCCESS);
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
#### 54. 2017-SE-02
```c

#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/bitypes.h>
#include <unistd.h>

#define NUM_LENGTH 10

int writeToStdOut(int input, bool lines, int lineCount) {
  char previous = '\n';
  char symbol = '\n';
  if (lines) {
    while (read(input, &symbol, sizeof(symbol)) == sizeof(symbol)) {
      if (previous == '\n') {
        char str[NUM_LENGTH];
        sprintf(str, "%d\t", lineCount);
        if (write(1, str, sizeof(char) * strlen(str)) !=
            sizeof(char) * strlen(str)) {
          errx(EXIT_FAILURE, "Couldn't write to stadard output");
        }
        lineCount++;
      }
      if (write(1, &symbol, sizeof(symbol)) != sizeof(symbol)) {
        errx(EXIT_FAILURE, "Couldn't write to stadard output");
      }
      previous = symbol;
    }
  } else {
    while (read(input, &symbol, sizeof(symbol)) == sizeof(symbol)) {
      if (write(1, &symbol, sizeof(symbol)) != sizeof(symbol)) {
        errx(EXIT_FAILURE, "Couldn't write to stadard output");
      }
    }
  }
  return lineCount;
}

int main(int argc, char* argv[]) {
  bool lines = false;
  int numFiles = argc;
  int i = 1;
  if (argc == 2) {
    numFiles--;
    if (strcmp(argv[i], "-n") == 0) {
      i++;
      lines = true;
    }
  } else if (argc > 2) {
    numFiles--;
    if (strcmp(argv[i], "-n") == 0) {
      numFiles--;
      i++;
      lines = true;
    }
  }
  int* inputs = calloc(numFiles, sizeof(int));
  int j = 0;
  for (; i < argc; i++) {
    if (strcmp(argv[i], "-") != 0) {
      inputs[j] = open(argv[i], O_RDONLY);
      if (inputs[j] < 0) {
        err(EXIT_FAILURE, "Couldn't read from file %s", argv[1]);
      }
    }
    j++;
  }
  int lineCount = 0;
  for (int j = 0; j < numFiles; j++) {
    lineCount = writeToStdOut(inputs[j], lines, lineCount);
    char newLine = '\n';
    if (write(1, &newLine, sizeof(char)) != sizeof(char)) {
      err(EXIT_FAILURE, "Couldn't write to stdout");
    }
    if (inputs[j] != 0) {
      close(inputs[j]);
    }
  }
  free(inputs);
  exit(EXIT_SUCCESS);
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
или
```c

#include <err.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc != 4) {
    errx(EXIT_FAILURE, "Please provide 3 parameters");
  }

  int patchFile = open(argv[1], O_RDONLY);
  if (patchFile < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s.", argv[1]);
  }
  int file1 = open(argv[2], O_RDONLY);
  if (file1 < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s.", argv[2]);
  }
  int file2 =
      open(argv[3], O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
  if (file2 < 0) {
    err(EXIT_FAILURE, "Couldn't open file %s.", argv[3]);
  }
  struct triple {
    uint16_t offset;
    uint8_t original;
    uint8_t new;
  } triple;
  uint8_t symbol;
  while (read(file1, &symbol, sizeof(symbol)) == sizeof(symbol)) {
    if (write(file2, &symbol, sizeof(symbol)) != sizeof(symbol)) {
      err(EXIT_FAILURE, "Couldn't write to file %s", argv[3]);
    }
  }

  while (read(patchFile, &triple, sizeof(triple)) == sizeof(triple)) {
    if (lseek(file1, triple.offset, SEEK_SET) == -1) {
      err(EXIT_FAILURE, "Couldn't move in file %s", argv[2]);
    }
    if (read(file1, &symbol, sizeof(symbol)) != sizeof(symbol)) {
      err(EXIT_FAILURE, "Couldn't read from file %s", argv[2]);
    }
    if (symbol != triple.original) {
      errx(EXIT_FAILURE, "Patch file and original not matching");
    }
    symbol = triple.new;
    if (lseek(file2, triple.offset, SEEK_SET) == -1) {
      err(EXIT_FAILURE, "Couldn't move in file %s", argv[2]);
    }
    if (write(file2, &symbol, sizeof(symbol)) != sizeof(symbol)) {
      err(EXIT_FAILURE, "Couldn't write to file %s", argv[3]);
    }
  }
  close(patchFile);
  close(file1);
  close(file2);
  exit(EXIT_SUCCESS);
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
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHAR_MAX_VALUE 256

int in(char* str, char symbol);
int in(char* str, char symbol) {
  for (size_t i = 0; i < strlen(str); i++) {
    if (symbol == str[i]) {
      return 1;
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  char char1;
  char char2;
  struct pair {
    char first;
    char second;
  };

  if (argc != 3) {
    errx(EXIT_FAILURE, "Invalid number of parameters");
  }

  if (strcmp(argv[1], "-s") == 0) {
    char set1[strlen(argv[2]) + 1];
    strcpy(set1, argv[2]);

    if (read(STDIN_FILENO, &char1, sizeof(char1)) != sizeof(char1)) {
      err(EXIT_FAILURE, "Could not write to STDOUT");
    }
    if (write(STDOUT_FILENO, &char1, sizeof(char1)) != sizeof(char1)) {
      err(EXIT_FAILURE, "Could not write to STDOUT");
    }

    while (read(STDIN_FILENO, &char2, sizeof(char2)) == sizeof(char2)) {
      if (char1 != char2 || in(set1, char1) == 0) {
        char1 = char2;
        if (write(STDOUT_FILENO, &char2, sizeof(char2)) != sizeof(char2)) {
          err(EXIT_FAILURE, "Could not write to STDOUT");
        }
      }
    }
    exit(EXIT_SUCCESS);
  }
  if (strcmp(argv[1], "-d") == 0) {
    char set1[strlen(argv[2]) + 1];
    strcpy(set1, argv[2]);

    if (read(STDIN_FILENO, &char1, sizeof(char1)) != sizeof(char1)) {
      err(EXIT_FAILURE, "Could not write to STDOUT");
    }

    while (read(STDIN_FILENO, &char1, sizeof(char1)) == sizeof(char1)) {
      if (in(set1, char1) == 0) {
        if (write(STDOUT_FILENO, &char1, sizeof(char1)) != sizeof(char1)) {
          err(EXIT_FAILURE, "Could not write to STDOUT");
        }
      }
    }
    exit(EXIT_SUCCESS);
  }
  char set1[strlen(argv[1]) + 1];
  strcpy(set1, argv[1]);
  char set2[strlen(argv[2]) + 1];
  strcpy(set2, argv[2]);
  if (strlen(set1) != strlen(set2)) {
    err(EXIT_FAILURE, "Set 1 and Set2 are not of equal length");
  }
  char map[CHAR_MAX_VALUE];
  for (int i = 0; i < CHAR_MAX_VALUE; i++) {
    map[i] = i;
  }
  for (size_t i = 0; i < strlen(set1); i++) {
    map[set1[i]] = set2[i];
  }
  while (read(STDIN_FILENO, &char1, sizeof(char1)) == sizeof(char1)) {
    char2 = map[char1];
    if (write(STDOUT_FILENO, &char2, sizeof(char2)) != sizeof(char2)) {
      err(EXIT_FAILURE, "Could not write to STDOUT");
    }
  }

  exit(EXIT_SUCCESS);
}
```
#### 59. 2021-SE-03
```c
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_FIELD_SIZE 10

void parseFields(const char* string, int* start, int* end) {
  if (strlen(string) == 1) {
    *start = *end = string[0] - '0';
  } else if (strlen(string) == 3) {
    *start = string[0] - '0';
    *end = string[2] - '0';
  } else {
    errx(EXIT_FAILURE, "Field should be [0-9] or [0-9]-[0-9]");
  }
}
int main(int argc, char* argv[]) {
  // ./main -c [0-9]
  // ./main -c [0-9]-[0-9]
  // ./main -d CHAR -f [0-9][-[0-9]]
  if (argc < 3) {
    errx(EXIT_FAILURE, "Usage: ./main.c -c NUM[-NUM] or ./main.c -d SYMBOL");
  }

  int start;
  int end;
  char symbol;
  int position = 0;

  if (strcmp(argv[1], "-c") == 0) {
    parseFields(argv[2], &start, &end);
    while (read(STDIN_FILENO, &symbol, sizeof(symbol)) == sizeof(symbol)) {
      position++;
      if (position < start || position > end) {
        continue;
      }
      if (write(STDOUT_FILENO, &symbol, sizeof(symbol)) != sizeof(symbol)) {
        err(EXIT_FAILURE, "Couldn't write to STDOUT");
      }
    }
    // symbol = '\0';
    // if (write(STDOUT_FILENO, &symbol, sizeof(symbol)) != sizeof(symbol)) {
    //   err(EXIT_FAILURE, "Couldn't write to STDOUT");
    // }
    exit(EXIT_SUCCESS);
  }

  if (strcmp(argv[1], "-d") == 0) {
    if (argc != 5 || strcmp(argv[3], "-f") != 0) {
      errx(EXIT_FAILURE, "Usage: ./main.c -d CHAR -f [0-9][-[0-9]]");
    }
    const char SEPARATOR = argv[2][0];
    parseFields(argv[4], &start, &end);
    char* field = calloc(DEFAULT_FIELD_SIZE, sizeof(char));
    if (field == NULL) {
      err(EXIT_FAILURE, "Couldn't allocate memory");
    }
    size_t currentSize = 0;
    size_t maxSize = DEFAULT_FIELD_SIZE;
    while (read(STDIN_FILENO, &symbol, sizeof(symbol)) == sizeof(symbol)) {
      if (currentSize == maxSize) {
        field = reallocarray(field, currentSize * 2, sizeof(char));
        maxSize = maxSize * 2;
      }
      field[currentSize] = symbol;
      currentSize++;
      if (symbol == SEPARATOR) {
        position++;
        if (position < start || position > end) {
          currentSize = 0;
          continue;
        }
        // remove field separator if final field
        if (position == end) {
          currentSize--;
        }
        if (write(STDOUT_FILENO, field, sizeof(char) * currentSize) !=
            sizeof(char) * currentSize) {
          err(EXIT_FAILURE, "Couldn't write to STDOUT");
        }
        currentSize = 0;
      }
    }
    // handle case, where we want last field,
    // but there is no separator to increment the count
    if (position == end - 1) {
      if (write(STDOUT_FILENO, field, sizeof(char) * currentSize) !=
          sizeof(char) * currentSize) {
        err(EXIT_FAILURE, "Couldn't write to STDOUT");
      }
    }
    // symbol = '\0';
    // if (write(STDOUT_FILENO, &symbol, sizeof(symbol)) != sizeof(symbol)) {
    //   err(EXIT_FAILURE, "Couldn't write to STDOUT");
    // }
    free(field);
    exit(EXIT_SUCCESS);
  }
  exit(EXIT_FAILURE);
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
#### 72. 2016-SE-01
```c
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
int main(int argc, char* argv[]) {
  if (argc != 2) {
    errx(EXIT_FAILURE, "Please provide file to read from");
  }
  int fileDescriptors[2];
  if (pipe(fileDescriptors) == -1) {
    err(EXIT_FAILURE, "Couldn't create pipe");
  }
  pid_t process = fork();
  // instead of synchronizing processes manually using wait, we rely on the
  // pipes
  if (process < 0) {
    err(EXIT_FAILURE, "Couldn't create child process");
  }
  if (process > 0) {  // parent
    close(fileDescriptors[READ_END]);
    dup2(fileDescriptors[WRITE_END], STDOUT_FILENO);
    close(fileDescriptors[WRITE_END]);
    execlp("cat", "cat", argv[1], NULL);
    // execlp replaces process with command process and only return if failed
    exit(EXIT_SUCCESS);

  } else {
    close(fileDescriptors[WRITE_END]);
    dup2(fileDescriptors[READ_END], STDIN_FILENO);
    close(fileDescriptors[READ_END]);
    execlp("sort", "sort", (char*)NULL);
    // execlp replaces process with command process and only return if failed
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
```
#### 73. 2016-SE-03
```c
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
  const char* prompt = "Enter command: ";
  while (1) {
    if (write(STDOUT_FILENO, prompt, strlen(prompt)) != strlen(prompt)) {
      err(EXIT_FAILURE, "Couldn't write to STDOUT");
    }
    char cmd[50];
    ssize_t bytesRead = read(STDIN_FILENO, cmd, 50);
    if (bytesRead < 0) {
      err(EXIT_FAILURE, "Couldn't read from STDIN");
    }
    // read doesn't put a terminating null at the end
    cmd[bytesRead] = '\0';
    if (strcmp(cmd, "exit\n") == 0) {
      break;
    }
    pid_t pid = fork();
    if (pid < 0) {
      err(EXIT_FAILURE, "Couldn't create a child");
    }
    if (pid > 0) {
      wait(NULL);
    } else {
      // find the position of the newline character and set it it \0
      // otherwise execlp doesn't work
      cmd[strcspn(cmd, "\n")] = '\0';
      execlp(cmd, cmd, (char*)NULL);
    }
  }
  exit(EXIT_SUCCESS);
}
```
#### 76. 2018-SE-01
```c
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
int main(int argc, char* argv[]) {
  if (argc != 2) {
    err(EXIT_FAILURE, "Please provide name of directory");
  }
  int findSortPipe[2];
  if (pipe(findSortPipe)) {
    err(EXIT_FAILURE, "Couldn't pipe");
  }
  pid_t findSortPid = fork();
  if (findSortPid < 0) {
    err(EXIT_FAILURE, "Couldn't fork");
  }
  // parent
  if (findSortPid > 0) {
    close(findSortPipe[READ_END]);
    dup2(findSortPipe[WRITE_END], STDOUT_FILENO);
    close(findSortPipe[WRITE_END]);
    execlp("find", "find", argv[1], "-type", "f", "-printf", "\%p|%T@\n", NULL);
  } else {
    close(findSortPipe[WRITE_END]);
    dup2(findSortPipe[READ_END], STDIN_FILENO);
    close(findSortPipe[READ_END]);
    int sortHeadPipe[2];
    if (pipe(sortHeadPipe) < 0) {
      err(EXIT_FAILURE, "Couldn't pipe");
    }
    pid_t sortHeadPid = fork();
    if (sortHeadPid < 0) {
      err(EXIT_FAILURE, "Couldn't fork");
    }
    if (sortHeadPid > 0) {
      close(sortHeadPipe[READ_END]);
      dup2(sortHeadPipe[WRITE_END], STDOUT_FILENO);
      close(sortHeadPipe[WRITE_END]);
      execlp("sort", "sort", "-t", "|", "-nr", "-k2", NULL);
    } else {
      close(sortHeadPipe[WRITE_END]);
      dup2(sortHeadPipe[READ_END], STDIN_FILENO);
      close(sortHeadPipe[READ_END]);
      int headCutPipe[2];
      if (pipe(headCutPipe) < 0) {
        err(EXIT_FAILURE, "Couldn't pipe");
      }
      pid_t headCutPid = fork();
      if (headCutPid < 0) {
        err(EXIT_FAILURE, "Couldn't fork");
      }
      if (headCutPid > 0) {
        close(headCutPipe[READ_END]);
        dup2(headCutPipe[WRITE_END], STDOUT_FILENO);
        close(headCutPipe[WRITE_END]);
        execlp("head", "head", "-n", "1", NULL);
      } else {
        close(headCutPipe[WRITE_END]);
        dup2(headCutPipe[READ_END], STDIN_FILENO);
        close(headCutPipe[READ_END]);
        execlp("cut", "cut", "-d", "|", "-f", "1", NULL);
      }
    }
  }
  exit(EXIT_SUCCESS);
}
```
