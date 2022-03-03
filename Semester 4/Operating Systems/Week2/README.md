##### 1. Направете копие на файла /etc/passwd във вашата home директория под името my_passwd.
```cp /etc/passwd my_passwd```
##### 2. Направете директория practice-test в home директорията ви. Вътре направете директория test1. След това създайте празен файл вътре, който да се казва test.txt, преместете го в practice-test чрез релативни пътища.
```
mkdir -p practice-test/test1
cd practice-test/test1
touch test.txt
mv test.txt ../test.txt
```
##### 3. Създайте директорията practice/01 във вашата home директория. Създайте 3 файла в нея - f1, f2, f3. Копирайте файловете f1, f2, f3 от директорията practice/01/ в директория dir1, намираща се във вашата home директория. Ако нямате такава, създайте я.
```
mkdir -p practice/01
mkdir dir1
cd practice/01/
touch f1
touch f2
touch f3
cp f1 f2 f3 -t ../../dir1
```
##### 4. Нека файлът f2 бъде преместен в директория dir2, намираща се във вашата home директория и бъде преименуван на numbers.
```
cd
mkdir dir2
cd dir1
mv f2 ../dir2/numbers
```
#### 5. Отпечатайте имената на всички директории в директорията /home.
```
cd
ls -d */      # only visible
ls -d .*/     # only hidden
ls -d .*/ */  # all
```
#### 6. Създайте файл permissions.txt в home директорията си. За него дайте единствено - read права на потребителя създал файла, write and exec на групата, read and exec на всички останали. Направете го и с битове, и чрез "буквички".
```
cd
touch permissions.txt
chmod 435 permissions.txt
chmod chmod u=r,g=wx,o=rx permissions.txt # no intervals between permissions, only comma
```
