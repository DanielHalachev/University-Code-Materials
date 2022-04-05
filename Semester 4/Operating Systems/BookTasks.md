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
