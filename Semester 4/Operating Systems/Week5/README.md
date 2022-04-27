#### 1. Сменете вашия prompt с нещо по желание. После върнете оригиналния обратно.
```bash
foo=$PS1
export $PS1=\[\e]0;\u@\h: \w\a\]$
PS1=$foo
```
#### 2. Редактирайте вашия .bash_profile файл, за да ви поздравява (или да изпълнява някаква команда по ваш избор) всеки път, когато влезете в системата.
```bash

```
#### 3. Направете си ваш псевдоним (alias) на полезна команда.
```bash
vim .bashrc
alias ll='ls -l'
```
#### 4. Да се напише shell скрипт, който приканва потребителя да въведе низ (име) и изпечатва "Hello, низ".
```bash
#! /usr/bin/bash
read -p "Enter name: " name
echo "Hello, " $name
exit 0
```
#### 5. Да се напише shell скрипт, който приема точно един параметър и проверява дали подаденият му параметър се състои само от букви и цифри.
```bash
#! /usr/bin/bash
if [ $# -eq 1 ]
then
  echo $1 | awk '$0~/[a-zA-Z0-9]*/ {print "Yes"} {print No}';
  exit 0;
else
  echo "Number of arguments must be exactly one";
  exit 1
fi
exit 0
```
#### 6. Да се напише shell скрипт, който приканва потребителя да въведе низ - потребителско име на потребител от системата - след което извежда на стандартния изход колко активни сесии има потребителят в момента.
```bash
#!/usr/bin/bash
read -p "Enter username: " userName
echo "User $userName has" $(who | grep "$userName" | wc -l) "active sessions"
exit 0
```
#### 7. Да се напише shell скрипт, който приканва потребителя да въведе пълното име на директория и извежда на стандартния изход подходящо съобщение за броя на всички файлове и всички директории в нея.
```bash
#!/usr/bin/bash
read -p "Enter directory: " dir
echo "Directory $dir has" $(find $dir -maxdepth 1 2>/dev/null | wc -l) "elements"
exit 0
```
#### 8. Да се напише shell скрипт, който чете от стандартния вход имената на 3 файла, обединява редовете на първите два (man paste), подрежда ги по азбучен ред и резултата записва в третия файл.
```bash
#!/usr/bin/bash
paste -d'\n' $1 $2 | sort > $3
exit 0
```
#### 9. Да се напише shell скрипт, който чете от стандартния вход име на файл и символен низ, проверява дали низа се съдържа във файла и извежда на стандартния изход кода на завършване на командата с която сте проверили наличието на низа.*NB! Символният низ може да съдържа интервал (' ') в себе си.*
```bash
#!/usr/bin/bash
cat "$1" | grep "$2" >/dev/null 2>&1 
echo $?
exit 0
```
#### 10. Имате компилируем (a.k.a няма синтактични грешки) source file на езика C. Напишете shell script, който да покaзва колко е дълбоко най-дълбокото nest-ване (влагане).
Примерен .c файл:
```
#include <stdio.h>
int main(int argc, char *argv[]) {
  if (argc == 1) {
		printf("There is only 1 argument");
	} else {
		printf("There are more than 1 arguments");
	}
	return 0;
}
```
Тук влагането е 2, понеже имаме main блок, а вътре в него if блок.
Примерно извикване на скрипта:
```
./count_nesting sum_c_code.c
```
Изход:
```The deepest nesting is 2 levels
```
```bash

```
#### 11. Напишете shell script, който автоматично да попълва файл указател по подадени аргументи: име на файла указател, пълно име на човека (това, което очакваме да е в /etc/passwd) и избран за него nickname.
Файлът указател нека да е във формат:
<nickname, който лесно да запомните> <username в Astero>
Може да сложите и друг delimiter вместо интервал
Примерно извикване:
`./pupulate_address_book myAddressBook "Даниел Халачев" Kotaka`
Добавя към myAddressBook entry-то:
`Kotaka s62547`
***Бонус: Ако има няколко съвпадения за въведеното име (напр. има 10 човека Ivan Petrov в /etc/passwd), всички те да се показват на потребителя, заедно с пореден номер >=1,
след което той да може да въведе някой от номерата (или 0 ако не си хареса никого), и само избраният да бъде добавен към указателя.***
```bash
#!/usr/bin/bash
result=$(cat /etc/passwd | grep "$2")
if [ ! -f "$1" ]
then
    touch "$1"
fi

if [ $(echo "$result" | wc -l) -eq 1 ]
then
    echo $3 "$result" | awk -F ':' '{print $1}' >> "$1"
else
    echo "Chose one: "
    multipleResult=$(echo "$result" | awk -v counter='1' '{printf "%s) %s\n",counter,$1; counter++}')
    echo "$multipleResult"
    read selection
    echo $3 $(echo "$multipleResult" | grep "^$selection) " | cut -d' ' -f 2 | cut -d':' -f 1) >> "$1"
        #awk -F '\) ' '$1~/$selection/ {print $2}' >> $1
fi
exit 0
```
#### 12. Напишете shell script, който да приема параметър име на директория, от която взимаме файлове, и опционално експлицитно име на директория, в която ще копираме файлове. Скриптът да копира файловете със съдържание, променено преди по-малко от 45 мин, от първата директория във втората директория. Ако втората директория не е подадена по име, нека да получи такова от днешната дата във формат, който ви е удобен. При желание новосъздадената директория да се архивира.
```bash
#!/usr/bin/bash
if [ $# -eq 0 ] 
then
    echo "Invalid number of arguments"
    exit 1
elif [ $# -eq 1 ]
then 
    fromDir=$1
    toDir="$(date +%d.%m.%Y-%H:%M)"
elif [ $# -eq 2 ]
then
    fromDir=$1
    toDir=$2
fi

if [ ! -d $fromDir ]
then
    echo "Starting directory is non-existent"
    exit 2
fi
if [ ! -d $toDir ]
then
    mkdir -p "$toDir"
fi

find $fromDir -maxdepth 1 -type f -mmin -45 -exec mv -t $toDir {} +
exit 0
```
#### 13. Да се напише shell скрипт, който получава при стартиране като параметър в командния ред идентификатор на потребител. Скриптът периодично (sleep(1)) да проверява дали потребителят е log-нат, и ако да - да прекратява изпълнението си, извеждайки на стандартния изход подходящо съобщение.
```bash
#!/usr/bin/bash
if [ $# -eq 0 ] 
then
    echo "Invalid number of arguments"
    exit 1
fi
while [ true ]
do
    sleep 1
    if [ ! $(who | grep "$1" | wc -l) -eq 0 ]
    then 
        echo "User logged in"
        break
    else
        echo "Checking... "
    fi
done
exit 0
```
#### 14. Да се напише shell скрипт, който валидира дали дадено цяло число попада в целочислен интервал. Скриптът приема 3 аргумента: числото, което трябва да се провери; лява граница на интервала; дясна граница на интервала.
Скриптът да връща exit status:
- 3, когато поне един от трите аргумента не е цяло число
- 2, когато границите на интервала са обърнати
- 1, когато числото не попада в интервала
- 0, когато числото попада в интервала

Примери:

`$ ./validint.sh -42 0 102; echo $?`
`1`
`$ ./validint.sh 88 94 280; echo $?`
`1`
`$ ./validint.sh 32 42 0; echo $?`
`2`
`$ ./validint.sh asdf - 280; echo $?`
`3`
```bash
if [ ! $# = 3 ]
then
    echo "Incorrect number of arguments"
    exit 1
fi

regex="^-{0,1}[0-9]+$"
if [[ $1 =~ $regex ]] && [[ $2 =~ $regex ]] && [[ $3 =~ $regex ]]
then
    if [ $2 -ge $3 ]
    then
        echo "Reversed interval"
        exit 2
    elif [ $1 -le $2 ] || [ $1 -ge $3 ]
    then
        echo "Not in interval"
        exit 1
    else 
        echo "In interval"
        exit 0
    fi
else
    echo "Not integers"
    exit 3
fi
exit 0
```
#### 15. Да се напише shell скрипт, който форматира големи числа, за да са по-лесни за четене. Като пръв аргумент на скрипта се подава цяло число. Като втори незадължителен аргумент се подава разделител. По подразбиране цифрите се разделят с празен интервал.

Примери:
`$ ./nicenumber.sh 1889734853`
`1 889 734 853`

`$ ./nicenumber.sh 7632223 ,` 
`7,632,223`
```bash
regex="^[0-9]+$"
if [ $# -lt 1 ] || [ ! $1=~regex ]
then
    echo "Incorrect number of arguments"
    exit 1
elif [ $# -eq 1 ]
then
    NUM="$(echo "$1" | rev | tr -d ' ')"
    DELIM=" "
else
    NUM="$(echo "$1" | rev | tr -d ' ')"
    DELIM="$2"
fi
counter=1
result=""
for ((i=0; i<${#NUM}; i++))
do
    char="${NUM: $i: 1}"
    result="$result$char"
    if [ $(($counter%3)) -eq 0 ]
    then
        result="$result$DELIM"
    fi
    counter=$(($counter+1))
done
result="$(echo "$result" | rev)"
if [ $(($counter%3)) -eq 1 ]
then
    echo "$(echo "$result" | cut -c 2-)"
else
    echo "$result"
fi
exit 0
```
#### 16. Да се напише shell скрипт, който приема файл и директория. Скриптът проверява в подадената директория и нейните под-директории дали съществува копие на подадения файл и отпечатва имената на намерените копия, ако съществуват такива.
```bash
if [ $# -lt 2 ]
then
    echo "Incorrect number of arguments"
    exit 1
else
    FILE=$1
    DIR="$2"
fi

if [ ! -f "$FILE" ]
then
    echo "Provided file does not exist"
    exit 1
fi
if [ ! -d "$DIR" ]
then
    echo "Provided directory does not exist"
    exit 1
fi
result=""
find "$DIR" -type f -exec cmp -s "$FILE" {} \; -and -print
# when you have to perform two actions and perform the second only when the first was successful, use -and 
exit 0
```
#### 17. Да се напише shell script, който генерира HTML таблица съдържаща описание на потребителите във виртуалката ви. Таблицата трябва да има:
- заглавен ред с имената нa колоните
- колони за username, group, login shell, GECOS field (man 5 passwd)

Пример:
```$ ./passwd-to-html.sh > table.html```
```$ cat table.html```
```html
<table>
  <tr>
    <th>Username</th>
    <th>group</th>
    <th>login shell</th>
    <th>GECOS</th>
  </tr>
  <tr>
    <td>root</td>
    <td>root</td>
    <td>/bin/bash</td>
    <td>Нещо1,,,,</td>
  </tr>
  <tr>
    <td>ubuntu</td>
    <td>ubuntu</td>
    <td>/bin/dash</td>
    <td>Нещо2,,,,</td>
  </tr>
</table>```
```
```bash
echo "<table>"
echo Username \n Group \n "Login Shell" \n GECOS \n "$(cat /etc/passwd)" | awk -F ':' '{printf "\t<tr>\n\t\t<th>%s</th>\n\t\t<th>%s</th>\n\t\t<th>%s</th>\n\t\t<th>%s</th>\n\t</tr>\n",$1,$4,$NF,$5}'
echo "</table>"
```
#### 17. Да се напише shell скрипт, който получава единствен аргумент директория и изтрива всички повтарящи се (по съдържание) файлове в дадената директория. Когато има няколко еднакви файла, да се остави само този, чието име е лексикографски преди имената на останалите дублирани файлове.

Примери:
```$ ls .```
f1 f2 f3 asdf asdf2
- asdf и asdf2 са еднакви по съдържание, но f1, f2, f3 са уникални

```$ ./rmdup .```
```$ ls .```
f1 f2 f3 asdf
- asdf2 е изтрит

```bash
WTF?
```
#### 18. ???Да се напише shell скрипт, който получава единствен аргумент директория и отпечатва списък с всички файлове и директории в нея (без скритите). До името на всеки файл да седи размера му в байтове, а до името на всяка директория да седи броят на елементите в нея (общ брой на файловете и директориите, без скритите). Добавете параметър -a, който указва на скрипта да проверява и скритите файлове и директории.

Пример:
```$ ./list.sh .```
*asdf.txt (250 bytes)
Documents (15 entries)
empty (0 entries)
junk (1 entry)
karh-pishtov.txt (8995979 bytes)
scripts (10 entries)*
```bash
#!/usr/bin/env bash
while getopts 'a' OPTION
do
    case "$OPTION" in
        a)
            echo "Hello there"
            find $2 -maxdepth 1 -type d | xargs -I {} echo "{} (" "$(find {} -maxdepth 1 | wc -l)" "entries)"
            exit 0
            ;;
        ?)
            echo "You can use no option or [-a] to show the hidden files"
            exit 0
            ;;
    esac
done
echo "Bruh"
```
#### 19. Да се напише shell скрипт, който приема произволен брой аргументи - имена на файлове. Скриптът да прочита от стандартния вход символен низ и за всеки от зададените файлове извежда по подходящ начин на стандартния изход броя на редовете, които съдържат низа.
NB! Низът може да съдържа интервал.
```bash
#!/usr/bin/env bash
read -p "Enter string: " STRING
for var in "$@"
do
    printf "%s\t%s lines\n" "$var" "$(cat "$var" | grep "$STRING" | wc -l)"
done
exit 0
```
#### 20. Да се напише shell скрипт, който приема два параметъра - име на директория и число. Скриптът да извежда на стандартния изход имената на всички обикновени файлове във директорията, които имат размер, по-голям от подаденото число.
```bash
#!/usr/bin/env bash
if [ ! $# -eq 2 ]
then
    echo "Invalid number of parameters"
    exit 1
fi
if [ ! -d $1 ]
then
    echo "Directory does not exist"
    exit 2
fi
regex="^[0-9]+$"
if [ ! $2=~regex ]
then
    echo "Second argument is not integer"
    exit 2
fi
find $1 -maxdepth 1 -type f -size +$2b 2>/dev/null
exit 0
```
#### 21. Да се напише shell скрипт, който приема произволен брой аргументи - имена на файлове или директории. Скриптът да извежда за всеки аргумент подходящо съобщение:
	- дали е файл, който може да прочетем
	- ако е catдиректория - имената на файловете в нея, които имат размер, по-малък от броя на файловете в директорията.
```bash
#!/usr/bin/env bash
for object in "$@"
do
    if [ -r $object ] && [ ! -d $object ]
    then
        echo "$object" "is a readable file"
    elif [ -d $object ]
    then
        num="$(find $object -maxdepth 1 -type f | wc -l)"
        find $object -maxdepth 1 -type f -size -${num}b
    fi
done
exit 0 
```
#### 22. Напишете shell script guess, която си намисля число, което вие трябва да познате. В зависимост от вашия отговор, програмата трябва да ви казва "надолу" или "нагоре", докато не познате числото. Когато го познаете, програмата да ви казва с колко опита сте успели.

./guess (програмата си намисля 5)

Guess? 22
...smaller!
Guess? 1
...bigger!
Guess? 4
...bigger!
Guess? 6
...smaller!
Guess? 5
RIGHT! Guessed 5 in 5 tries!

Hint: Един начин да направите рандъм число е с $(( (RANDOM % b) + a  )), което ще генерира число в интервала [a, b]. Може да вземете a и b като параметри, но не забравяйте да направите проверката.
```bash
#!/usr/bin/env bash
RAND=$(( (RANDOM % 3) + 1 ))
GUESS=-1
COUNTER=0
while [ $GUESS -ne $RAND ]
do
    read -p "Your guess: " GUESS
    if [ $GUESS -gt $RAND ]
    then
        echo "It is smaller..."
    elif [ $GUESS -lt $RAND ]
    then
        echo "It is bigger..."
    fi
    COUNTER=$(( $COUNTER + 1))
done
echo "You guessed it in" "$COUNTER" "tries!"
exit 0
```
#### 23. Да се напише shell скрипт, който приема параметър - име на потребител. Скриптът да прекратява изпълненито на всички текущо работещи процеси на дадения потребител, и да извежда колко са били те.
```bash
#!/usr/bin/env bash
for process in $(ps -u $1 -o pid=)
do
    kill -9 $process
done
exit 0
```
#### 24. Да се напише shell скрипт, който приема два параметъра - име на директория и число. Скриптът да извежда сумата от размерите на файловете в директорията, които имат размер, по-голям от подаденото число.
```bash
#!/usr/bin/env bash
#Do some validation here cuz I don't care anymore
find $1 -maxdepth 1 -type f -size +$2b -printf "%s\n" | awk -v sum=0 '{sum+=$1} END{print sum}'
exit 0
```
https://github.com/avelin/fmi-os/blob/master/exercises/05.scripts/05-b-7800.txt
