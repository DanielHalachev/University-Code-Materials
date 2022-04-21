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
#### 10. ```
Имате компилируем (a.k.a няма синтактични грешки) source file на езика C. Напишете shell script, който да покaзва колко е дълбоко най-дълбокото nest-ване (влагане).
Примерен .c файл:

#include <stdio.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
		printf("There is only 1 argument");
	} else {
		printf("There are more than 1 arguments");
	}

	return 0;
}
Тук влагането е 2, понеже имаме main блок, а вътре в него if блок.

Примерно извикване на скрипта:

./count_nesting sum_c_code.c

Изход:
The deepest nesting is 2 levels
```
```bash

```
#### 11.
