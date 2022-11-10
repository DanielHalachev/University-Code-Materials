# Подготовка за тест 1
## Готови функции
```scheme
(define (accumulate op nv a b term next)
  (if (> a b) nv
          (op (term a) (accumulate op nv (next a) b term next))))

(define (accumulate-i op nv a b term next)
  (if (> a b) nv
          (accumulate-i op (op nv (term a)) (next a) b term next)))

(define (filter p l)
  (cond ((null? l) l)
               ((p (car l)) (cons (car l) (filter p (cdr l))))
               (else (filter p (cdr l)))))

(define (foldr op nv l)
  (if (null? l) nv
          (op (car l) (foldr op nv (cdr l)))))

(define (foldl op nv l)
  (if (null? l) nv
          (foldl op (op nv (car l)) (cdr l))))

(define (foldr1 op l)
  (if (null? (cdr l)) (car l)
          (op (car l) (foldr1 op (cdr l)))))

(define (foldl1 op l)
  (foldl op (car l) (cdr l)))

(define (++ n) (+ n 1))
(define (id n) (n))
```
## Зад 1. 
Едно естествено число наричаме свършено, ако е с 2 по-малко от сумата на всичките си делители по-малки от него.

а) (3 т.) Да се реализира функция done?, която проверява дали дадено число е свършено.

б) (7 т.) Да се реализира функция sum-almost-done, която по подадени естествени числа a и b намира сумата на всички числа в интервала [a; b], които са по-близко до свършено число, отколкото до краищата на интервала.

Примери:
```scheme
(done? 20) → #t
(done? 28) → #f

(sum-almost-done 5 24) → 153 ; сумата на числата от 13 до 21
```
```scheme
(define (sum-delims n)
  (accumulate
    + 0
    1 (- n 1)
    (lambda (i)
     (if (= 0 (remainder n i))
        i
        0))
    ++))

(define (done? n)
  (=
   (+ n 2)
   (sum-delims n)))

(define (sum-almost-done a b)
  (define (dist-to-ends n)
    (min (- n a)(- b n)))
  (define (term i)
    (define (dist-to-done i)
      (accumulate
       (lambda (f s)(min f s))
       (- b a)
       a b
       (lambda(j)(if (done? j)
                    (abs (- j i))
                    (- b a)))
       ++))
    (if (> (dist-to-ends i) (dist-to-done i))
        i
        0))
   (accumulate + 0 a b term ++))
```
Задача 2. (10 т.) Разглеждаме стекова машина, която представя паметта си като списък от числа и символи и приема списък от инструкции, които интерпретира по следния начин: - ако поредната инструкция е число или символ, то се добавя на върха на стека - ако поредната инструкция е функция, тя се прилага над всички числа в стека (допуска се, че функцията приема само един параметър), променяйки стойностите им в стека - ако поредната инструкция е наредена двойка от операция (двуместна функция) и число n, то горните две числа на стека се изваждат и обратно на върха на стека се записва резултат от прилагането на операцията над тях. Прилагането се повтаря до изчерпване на стека или достигане до символ, но не повече от n пъти. - всички останали инструкции се игнорират.

Да се реализира функция run-machine, която връща като резултат списък, представящ паметта на машината след последователно обработване на всички инструкции. Първоначално машината се инициализира с празен стек.

Пример:
```scheme
(run-machine (list 1 'x 4 'a 9 16 25 sqrt 6))                       → (6 5 4 3 a 2 x 1)
(run-machine (list 1 'x 4 'a 9 16 25 sqrt 6 (cons + 2) (cons * 5))) → (45 a 2 x 1)
```
```scheme
(define (run-machine l)
  (define process 
    (lambda (ops stack)
      (if (null? l)
          stack
          (let(
               (current (car l))
               (rest (cdr l)))
            (cond
              (
               (or (number? current) (symbol? current))
               (process rest (cons current stack)))
              (
               (procedure? current)
               (process rest (map (lambda(i)(if (number? i) (current i) i)) stack)))
              (
               (and (pair? current) (procedure? (car current)) (number? (cdr current)))
               (let(
                    (current (car current))
                    (n-repeat (cdr current)))
                 (if(
                     or
                     (< (length stack) 2)
                     (= 0 (n-repeat))
                     (or
                      (not (number? (car stack)))
                      (not (number? (cadr stack)))))
                    (process rest stack)
                    (let(
                         (f (car stack))
                         (s (cadr stack))
                         (r (cddr stack)))
                      (process (cons (cons current (- n-repeat 1)) rest) (cons (current f s) r))))))
              (else
               (process rest stack)))))))
  (process l '()))
```
Задача 3. (10 т.) Казваме, че един списък е подсписък на друг, ако елементите на първия списък се срещат непосредствено последователно във втория. Например, '(2 4) не е подсписък на '(1 2 3 4 5), но '(2 3 4) е. Казваме, че един списък от числа a се мажорира от списъка b, ако двата списъка са с еднаква дължина n и ai ≤ bi за всяко i ∈ [0; n). Списък от списъци ll наричаме мажорен, ако е вярно, че li се мажорира от подсписък на li+1 за всеки два съседни списъка li и li+1 в ll.

Да се реализира функция is-major?, която проверява дали даден списък от списъци от числа е мажорен.

Примери:
```scheme
(is-major? '((1 3) (4 2 7) (2 5 4 3 9 12))) → #t
(is-major? '((1 3) (4 2 7) (2 5 3 3 9 12))) → #f
```
```scheme
(define (helper l1 l2)
  (cond ((null? l1) #t)
        (< (length l1) (length l2) #f)
        (else
         (and (<= (car l1) (car l2)) (helper (cdr l1) (cdr l2))))))

(define (is-majored? l1 l2)
  (cond ((null? l1) #t)
        ((> (length l1) (length l2)) #f)
        (else
         (or (helper l1 l2) (is-majored? l1 (cdr l2))))))

(define (is-major? ll)
  (if (< (length ll) 2)
      #t
      (and (is-majored? (car ll) (cadr ll)) (is-major? (cdr ll)))))

```
## Бонус: 
(5 т.) Да се реализира функция find-longest-major, която намира най-дългия мажорен подсписък на даден списък от списъци от числа.
```scheme
define (find-longest-major ll)
  (define (helper ll res last)
    (define current (car ll))
      (if (< (length ll) 2)
          (if (is-majored? last current)
              (cons current res)
              res)
          (if (is-majored? last current)
              (helper (cdr ll) (cons current res) current)
              res)))
  (reverse (helper ll '() '())))
```
