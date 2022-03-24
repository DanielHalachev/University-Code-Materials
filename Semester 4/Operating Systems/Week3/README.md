#### 1. Сортирайте /etc/passwd лексикографски по поле UserID.
- ```-t``` for delimiter
- ```-k``` for key
```bash
sort -t: -k 3 /etc/passwd
```
```bash
cat /etc/passwd | sort -t: -k 3
```
#### 2. Сортирайте /etc/passwd числово по поле UserID. (Открийте разликите с лексикографската сортировка)
```bash
sort -n -t: -k 3 /etc/passwd
```
```bash
cat /etc/passwd | sort -n -t: -k 3
```
#### 3. Изведете само 1-ва и 5-та колона на файла /etc/passwd спрямо разделител ":".
```bash
cut -d: -f1,5 /etc/passwd
```
```bash
cut -d : -f 1,5 /etc/passwd
```
#### 4. Изведете съдържанието на файла /etc/passwd от 2-ри до 6-ти символ.
```bash
head -1 /etc/passwd | cut -c 2-7 # includes 6-th symbol
```
#### 5. Отпечатайте потребителските имена и техните home директории от /etc/passwd.
```bash
cut -d: -f1,6 /etc/passwd
```
#### 6. Отпечатайте втората колона на /etc/passwd, разделена спрямо символ '/'.
```bash
cut -d/ -f2 /etc/passwd
```
#### 7. Изведете броя на байтовете в /etc/passwd. Изведете броя на символите в /etc/passwd. Изведете броя на редовете в /etc/passwd.
```bash
cat /etc/passwd | wc -c # байтове
```
```bash
cat /etc/passwd | wc -m # символи
```
```bash
cat /etc/passwd | wc -l # редове
```
#### 8. С отделни команди, извадете от файл /etc/passwd:
- първите 12 реда
- първите 26 символа
- всички редове, освен последните 4
- последните 17 реда
- 151-я ред (или друг произволен, ако нямате достатъчно редове)
- последните 4 символа от 13-ти ред (символът за нов ред не е част от реда)
```bash
head -12 /etc/passwd
```
```bash
word=$(cat /etc/passwd)
echo ${word:0:26}
```
или ```cut -z -c 0-26 /etc/passwd  #-z за да разделя на \0, -c символи до 26ти``` 

```bash
head -n -4 /etc/passwd
```
```bash
tail -n 17 /etc/passwd
```
```bash
head -n 151 /etc/passwd | tail -n 1
```
```bash
head -13 /etc/passwd | tail -n 1 | rev | cut -c 1-4 | rev
```
#### 9. Запаметете във файл в своята home директория резултатът от командата `df -P`. Напишете команда, която извежда на екрана съдържанието на този файл, без първия ред (хедъра), сортирано по второ поле (numeric).
```bash
sudo df -P > output.txt
cat output.txt | tail -n + 2 | sort -nrk2
```
#### 10. Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.
```bash
cat /etc/passwd | cut -d: -f1 > users
```
#### 11. Изпишете всички usernames от /etc/passwd с главни букви.
```bash
cat /etc/passwd | cut -d : -f 1 | tr a-z A-Z
```
#### 12. 
- Изведете реда от /etc/passwd, на който има информация за вашия потребител.
- Изведедете този ред и двата реда преди него.
- Изведете този ред, двата преди него, и трите след него.
- Изведете *само* реда, който се намира 2 реда преди реда, съдържащ информация за вашия потребител.
```bash
cat /etc/passwd | grep daniel
```
```bash
cat /etc/passwd | grep -B 2 daniel
```
```bash
cat /etc/passwd | grep -B 2 -A 3 daniel
```
```bash
cat /etc/passwd | grep -B 2 daniel | head -1
```
#### 13. Изведете колко потребители не изпозват /bin/bash за login shell според /etc/passwd
```bash
cat /etc/passwd | grep -v bash | wc -l
```
#### 14. Изведете само имената на хората с второ име по-дълго от 6 (>6) символа според /etc/passwd
???
```bash
cat /etc/passwd | cut -d : -f 5 | cut -d , -f 1 | awk 'length($2) > 6 {print $2}'
```
#### 15. Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?
```bash
cat /etc/passwd | cut -d : -f 5 | cut -d , -f 1 | awk 'length($2) < 8 {print $2}'
```
#### 16. Изведете целите редове от /etc/passwd за хората от 15.
```bash
WHY ARE YOU GAE
```
#### 17. Копирайте <РЕПО>/exercises/data/emp.data във вашата home директория.
##### Посредством awk, използвайки копирания файл за входнни данни, изведете:
- общия брой редове
- третия ред
- последното поле от всеки ред
- последното поле на последния ред
- всеки ред, който има повече от 4 полета
- всеки ред, чието последно поле е по-голямо от 4
- общия брой полета във всички редове
- броя редове, в които се среща низът Beth
- най-голямото трето поле и редът, който го съдържа
- всеки ред, който има поне едно поле
- всеки ред, който има повече от 17 знака
- броя на полетата във всеки ред и самият ред
- първите две полета от всеки ред, с разменени места
- всеки ред така, че първите две полета да са с разменени места
- всеки ред така, че на мястото на първото поле да има номер на реда
- всеки ред без второто поле
- за всеки ред, сумата от второ и трето поле
- сумата на второ и трето поле от всеки ред
```bash
awk 'END {print NR}' emp.data
```
```bash
awk 'NR == 3 {print $0}' emp.data
```
```bash
awk '{print $NF}' emp.data
```
```bash
awk 'END {print $NF}' emp.data
# OR awk '{last = $0} END { print $3 }' emp.data
```
```bash
awk 'NF > 4' emp.data 
```
```bash
awk '$NF > 4' emp.data
```
```bash
awk -v SUM=0 '{SUM += NF} END{print SUM}' emp.data
```
```bash
awk '/Beth/ {print}' emp.data
```
```bash
awk -v MAX=0 -v LINE='' '$NF > MAX{MAX=$NF; LINE=$R} END{print MAX," - ",LINE}' emp.data
```
```bash
awk 'NR >= 1' emp.data
```
```bash
awk 'length($R)>17' emp.data
```
```bash
awk '{print NF, $0}' emp.data
```
```bash
awk -v OFS='\t' '{print $2,$1}' emp.data
```
```bash
awk -v OFS='\t' '{print $2,$1,$3}' emp.data
```
```bash
awk -v OFS='\t' '{print NR,$2,$3}' emp.data
```
```bash
awk -v OFS='\t' '{$2=""; print $0 }' emp.data #lazy
#OR
awk -v OFS='\t' '{printf "%s%s",$1,OFS}; {for(i=3; i<=NF; i++){printf "%i",$i}}; {print ""}' emp.data
```
```bash
awk '{print $2 + $3}' emp.data
```
```bash
awk -v SUM=0 '{SUM += ($2 + $3)} END {print SUM}' emp.data
```
#### 18. Намерете само Group ID-то си от файлa /etc/passwd.
```bash
cat /etc/passwd | grep daniel | cut -d : -f 4
```
#### 19. Колко коментара има във файла /etc/services ? Коментарите се маркират със символа #, след който всеки символ на реда се счита за коментар.
```bash
cat /etc/services | grep \# | wc -l
```
#### 20. Колко файлове в /bin са 'shell script'-oве? (Колко файлове в дадена директория са ASCII text?)
```bash
find /bin/ -maxdepth 1 -type f | xargs -I {} file {} | grep 'shell script' | wc -l
```
#### 21. Направете списък с директориите на вашата файлова система, до които нямате достъп. Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина.
```bash
find / -maxdepth 3 -type d -readable 
```
#### 22. Създайте следната файлова йерархия в home директорията ви:
dir5/file1
dir5/file2
dir5/file3
##### Посредством vi въведете следното съдържание:
file1:
```
1
2
3
```
file2:
```
s
a
d
f
```
file3:
```
3
2
1
45
42
14
1
52
```
Изведете на екрана:
- статистика за броя редове, думи и символи за всеки един файл
- статистика за броя редове и символи за всички файлове
- общия брой редове на трите файла
```bash
wc -l -w -c file{1,2,3}
```
```bash
cat file{1,2,3} | wc -l -w -c
```
```bash
cat file{1,2,3} | wc -l
```
#### 23. Във file2 (inplace) подменете всички малки букви с главни.
```bash

```
#### 24. Във file3 (inplace) изтрийте всички "1"-ци.
```bash

```
#### 25. Изведете статистика за най-често срещаните символи в трите файла.
```bash

```
#### 26. Направете нов файл с име по ваш избор, чието съдържание е конкатенирани съдържанията на file{1,2,3}.
```bash
cat file{1,2,3} > concat.txt
```
#### 27. Прочетете текстов файл file1 и направете всички главни букви малки като запишете резултата във file2.
```bash
awk '{print toupper($0)}' file1 > file2
```
или
```bash
cat file1 | tr [:lower:] [:upper:] > file2
```
#### 28. Намерете броя на символите, различни от буквата 'а' във файла /etc/passwd
```bash

```
#### 29. Намерете броя на уникалните символи, използвани в имената на потребителите от /etc/passwd.
```bash

```
#### 30. Отпечатайте всички редове на файла /etc/passwd, които не съдържат символния низ 'ов'.
```bash
cat /etc/passwd | grep -v 'ов'
```
#### 31. Отпечатайте последната цифра на UID на всички редове между 28-ми и 46-ред в /etc/passwd.
```bash
cat /etc/passwd | head -46 | tail -n 19 | cut -d : -f 3 | rev | cut -c 1 | rev
```
#### 32. Отпечатайте правата (permissions) и имената на всички файлове, до които имате read достъп, намиращи се в директорията /tmp. (hint: 'man find', вижте -readable)
```bash
find /tmp -type f -readable -printf "%M\t%p"
```
#### 33. Намерете имената на 10-те файла във вашата home директория, чието съдържание е редактирано най-скоро. На първо място трябва да бъде най-скоро редактираният файл. Намерете 10-те най-скоро достъпени файлове. (hint: Unix time)
```bash
find . -maxdepth 1 -type f -printf '%T@ %p\n' | sort -n | tail -10
```
#### 34. Да приемем, че файловете, които съдържат C код, завършват на `.c` или `.h`. Колко на брой са те в директорията `/usr/include`? Колко реда C код има в тези файлове?
```bash
find /usr/include/*.c /usr/include/*.h -type f # not working
find /usr/include/ -type f -name '*.[c\|h]'
find /usr/include/ -type f -name '*.[c\|h]' | wc -l
```
#### 35. Даден ви е ASCII текстов файл - /etc/services. Отпечатайте хистограма на 10-те най-често срещани думи. Дума наричаме непразна последователност от букви. Не правим разлика между главни и малки букви. Хистограма наричаме поредица от редове, всеки от които има вида: <брой срещания> <какво се среща толкова пъти>
```bash
cat /etc/services | tr -c '[:alnum:]' '[\n*]' | sort | uniq -c | sort -nr | head -10
```
#### 36. Вземете факултетните номера на студентите (описани във файла <РЕПО>/exercises/data/mypasswd.txt) от СИ и ги запишете във файл si.txt сортирани.
- Студент е част от СИ, ако home директорията на този потребител (според <РЕПО>/exercises/data/mypasswd.txt) се намира в /home/SI директорията.
```bash
cat mypasswd | grep '/home/SI' | cut -d : -f 1| tr -d 's' > si.txt
```
#### 37. За всяка група от /etc/group изпишете "Hello, <група>", като ако това е вашата група, напишете "Hello, <група> - I am here!".
```bash
awk -F : '{print "Hello,", $1}' /etc/group
```
#### 38. Shell Script-овете са файлове, които по конвенция имат разширение .sh. Всеки такъв файл започва с `"#!<interpreter>"` , където `<interpreter>` указва на операционната система какъв интерпретатор да пусне (пр: "#!/bin/bash", "#!/usr/bin/python3 -u"). Намерете всички .sh файлове в директорията `/usr` и нейните поддиректории, и проверете кой е най-често използваният интерпретатор.
```bash
find /usr -type f -name "*.sh" | xargs -I {} head -1 {} | grep '#!' | tr -d ' ' | awk -F '\/' '{print $(NF)}' 2>/dev/null | sort | uniq -c | sort -nr -k 1 | head -1 | awk '{print $2}'
```
#### 39. 
#### A). Изведете GID-овете на 5-те най-големи групи спрямо броя потребители, за които съответната група е основна (primary).
#### Б). (*) Изведете имената на съответните групи.
```bash
awk -F: '{print $4}' /etc/passwd | sort | uniq -c | sort -nr -k 1 | head -5 | awk '{print $2}'
```
```bash

```
#### 40. Направете файл eternity. Намерете всички файлове, намиращи се във вашата home директория и нейните поддиректории, които са били модифицирани в последните 15мин (по възможност изключете .).  Запишете във eternity името (път) на файла и времето (unix time) на последната промяна.
```bash
find . -mindepth 2 -type f -mmin 15 -printf '%p %T@\n' > eternity
```
#### 41. Копирайте файл <РЕПО>/exercises/data/population.csv във вашата home директория.
#### 42. Използвайки файл population.csv, намерете колко е общото население на света през 2008 година. А през 2016?
```bash
cat population.csv | tail -n +2 | awk -F , '$3==1980 {pop+=$NF} END {print pop}'
```
#### 43. Използвайки файл population.csv, намерете през коя година в България има най-много население.
```bash
cat population.csv | tail -n +2 | awk -F , '$1=="Bulgaria"' | sort -nr -t, -k 4 | head -1 | cut -d , -f 3
```
#### 44. Използвайки файл population.csv, намерете коя държава има най-много население през 2016. А коя е с най-малко население? (Hint: Погледнете имената на държавите)
```bash
cat population.csv | tail -n +2 | awk -F , '$3==2016' | sort -nr -t, -k 4 | head -1 | cut -d, -f 1
```
#### 45. Използвайки файл population.csv, намерете коя държава е на 42-ро място по население през 1969. Колко е населението й през тази година?
```bash
cat population.csv | awk -F , '$3==1969' | sort -nr -t, -k 4 | cat population.csv | awk -F , '$3==1969' | sort -nr -t, -k 4 | head -42 | tail -1 | cut -d, -f 1,4
```
#### 46. В home директорията си изпълнете командата `curl -o songs.tar.gz "http://fangorn.uni-sofia.bg/misc/songs.tar.gz"`
#### 47. Да се разархивира архивът songs.tar.gz в директория songs във вашата home директория.
```bash
mkdir songs
tar -xvf songs.tar.gz --directory=songs
```
#### 48. Да се изведат само имената на песните.
```bash
find songs -type f -name *.ogg | awk -F/ '{print $2}' | awk -F ' \\(' '{print $1}'
```
#### 49. Имената на песните да се направят с малки букви, да се заменят спейсовете с долни черти и да се сортират.
```bash
find songs -type f -name *.ogg | awk -F/ '{print $2}' | awk -F ' \\(' '{print $1}' | awk '{print tolower($0)}' | tr ' ' '_'
```
#### 50. Да се изведат всички албуми, сортирани по година.
```bash
find songs -type f -name *.ogg | awk -F '(' '{print $2}' | awk -F ')' '{print $1}' | sort -n -t',' -k 2 | cut -d, -f 1
```
#### 51. Да се преброят/изведат само песните на Beatles и Pink.
```bash
find songs -type f -name *.ogg | grep 'Beatles\|Pink' | awk -F '/' '{print $2}' | awk -F ' \\(' '{print $1}'
```
#### 52. Да се направят директории с имената на уникалните групи. За улеснение, имената от две думи да се напишат слято: Beatles, PinkFloyd, Madness
```bash
find songs -type f -name *.ogg | awk -F '/' '{print $2}' | awk -F ' -' '{print $1}' | sort | uniq | tr -d ' ' | xargs mkdir 
```
#### 53. Напишете серия от команди, които извеждат детайли за файловете и директориите в текущата директория, които имат същите права за достъп както най-големият файл в /etc директорията.
```bash

```
#### 54. Дадени са ви 2 списъка с email адреси - първият има 12 валидни адреса, а вторията има само невалидни. Филтрирайте всички адреси, така че да останат само валидните. Колко кратък регулярен израз можете да направите за целта?
```
Валидни email адреси (12 на брой):
email@example.com
firstname.lastname@example.com
email@subdomain.example.com
email@123.123.123.123
1234567890@example.com
email@example-one.com
_______@example.com
email@example.name
email@example.museum
email@example.co.jp
firstname-lastname@example.com
unusually.long.long.name@example.com

Невалидни email адреси:
#@%^%#$@#$@#.com
@example.com
myemail
Joe Smith <email@example.com>
email.example.com
email@example@example.com
.email@example.com
email.@example.com
email..email@example.com
email@-example.com
email@example..com
Abc..123@example.com
(),:;<>[\]@example.com
just"not"right@example.com
this\ is"really"not\allowed@example.com
```
```bash

```
#### 55. Посредством awk, използвайки emp.data (от 03-a-6000.txt) за входнни данни, изведете:
- всеки ред, като полетата са в обратен ред (Разгледайте for цикли в awk)
```bash

```
