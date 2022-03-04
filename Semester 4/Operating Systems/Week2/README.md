# Добре дошли в ада
## Linux Mint FTW

#### 1. Направете копие на файла /etc/passwd във вашата home директория под името my_passwd.
```bash
cp /etc/passwd my_passwd
```
#### 2. Направете директория practice-test в home директорията ви. Вътре направете директория test1. След това създайте празен файл вътре, който да се казва test.txt, преместете го в practice-test чрез релативни пътища.
```bash
mkdir -p practice-test/test1
cd practice-test/test1
touch test.txt
mv test.txt ../test.txt
```
#### 3. Създайте директорията practice/01 във вашата home директория. Създайте 3 файла в нея - f1, f2, f3. Копирайте файловете f1, f2, f3 от директорията practice/01/ в директория dir1, намираща се във вашата home директория. Ако нямате такава, създайте я.
```bash
mkdir -p practice/01
mkdir dir1
cd practice/01/
touch f1 f2 f3
cp f1 f2 f3 -t ../../dir1
```
#### 4. Нека файлът f2 бъде преместен в директория dir2, намираща се във вашата home директория и бъде преименуван на numbers.
```bash
cd
mkdir dir2
cd dir1
mv f2 ../dir2/numbers
```
#### 5. Отпечатайте имената на всички директории в директорията /home.
```bash
cd
ls -d */      # only visible
```
```bash
ls -d .*/     # only hidden
```
```bash
ls -d .*/ */  # all
```
#### 6. Създайте файл permissions.txt в home директорията си. За него дайте единствено - read права на потребителя създал файла, write and exec на групата, read and exec на всички останали. Направете го и с битове, и чрез "буквички".
``` bash
cd
touch permissions.txt
chmod 435 permissions.txt
```
```bash
chmod u=r,g=wx,o=rx permissions.txt # no intervals between permissions, only comma
```
#### 7. За да намерите какво сте правили днес: намерете всички файлове в home директорията ви, които са променени в последния 1 час.
```bash
find -maxdepth 1 -amin -60 -type f
```
#### 8. Копирайте /etc/services в home директорията си. Прочетете го с командата cat. (Ако този файл го няма, прочетете с cat произволен текстов файл напр. /etc/passwd)
```bash
cd
cp /etc/services .
cat services
```
#### 9. Създайте symlink на файла /etc/passwd в home директорията ви (да се казва например passwd_symlink).
```bash
ln -s /etc/passwd passwd_symlink
```
#### 10. Изведете всички обикновени ("regular") файлове, които /etc и нейните преки поддиректории съдържат
```bash
find /etc -maxdepth 2 -type f 
```
#### 11. Изведете само първите 5 реда от /etc/services
```bash
head -n 5 /etc/services
```
#### 12. Изведете всички обикновени ("regular") файлове, които само преките поддиректории на /etc съдържат
```bash
find /etc/*/ -maxdepth 1 -type f
```
```bash
find /etc -mindepth 1 -maxdepth 2 -type f
```
#### 13. Изведете всички преки поддиректории на /etc
```bash
ls -d /etc/*/
```
#### 14. Създайте файл, който да съдържа само последните 10 реда от изхода на 13.
```bash
ls -d /etc/*/ | head -n 10 > bullshit.txt
```
#### 15. Изведете обикновените файлове по-големи от 42 байта в home директорията ви
```bash
cd
find . -maxdepth 1 -type f -size +42c
```
#### 16. Изведете всички обикновени файлове в директорията /tmp които са от вашата група, които имат write права за достъп за група или за останалите(o=w)
```bash
find /tmp -type f - group "students" -perm g=w,o=w
```bash
find /tmp -type f - group "students" -perm /0022
```
#### 17. Изведете всички файлове, които са по-нови от practice/01/f1 ( би трябвало да е създаден като част от по-ранна задача ).
???? Какво означава "по-нови"?! С по-късна дата на създаване или по-късна дата на последна промяна?
```bash
find . -type f -newerBB ~/dir1/f1 #not supported ???
```bash
find . -type f -newermm ~/dir1/f1 #this works but newermm means "edited after, not created after"
```
#### 18. Изтрийте файловете в home директорията си по-нови от practice/01/f3 (подайте на rm опция -i за да може да изберете само тези които искате да изтриете).
```bash
find . -type f -maxdepth 1- newermm ~/practice/01/f3 | xargs -I {} rm -i {}
```
#### 19. Намерете файловете в /bin, които могат да се четат, пишат и изпълняват от всички.
```bash
find /bin -maxdepth 1 -type f -perm 777
```
#### 20. Копирайте всички файлове от /etc, които могат да се четат от всички, в
директория myetc в home директорията ви. Направете такава, ако нямате.
```bash
find /etc -maxdepth 1 -type f -perm /0004 -exec cp {} ~/myetc \; # /; shows that the subcommand end there
```bash
find /etc -maxdepth 1 -type f -perm /0004 -exec cp -n {} ~/myetc \; so that already existing files with the same name won't be replaced by the new ones
```
```bash
find /etc -maxdepth 1 -type f -perm /0004 | xargs -I {} cp {} ~/myetc # -I and the placeholder {} allow the same thing
```
#### 21. от предната задача: когато вече сте получили myetc с файлове, архивирайте всички от тях, които започват с 'c' в архив, който се казва c_start.tar. Изтрийте директорията myetc и цялото ѝ съдържание. Изтрийте архива c_start.tar
```bash
find ~/myetc -name "c*" -type f | xargs -I {} tar cfv "c_start.tar" {}
rm -rf myetc
rm "c_start.tar"
```
#### 22. Използвайки едно извикване на командата find, отпечатайте броя на редовете във всеки обикновен файл в /etc директорията.
```bash
find /etc -maxdepth 1 -type f | xargs -I {} wc -l {}
```
```bash
find /etc -maxdepth 1 -type f | xargs -I {} grep -c ^ {} # POSIX-compliant solution
```
#### 23. Копирайте най-малкия файл от тези, намиращи се в /etc, в home директорията си.
```bash
ls -Sr /etc | head -n 1 | xargs -I {} cp /etc/{} ~/{}
```
