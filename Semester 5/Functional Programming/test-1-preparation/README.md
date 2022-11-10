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
## Тема 1
### Задача 1
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
### Задача 2 (10 т.) ⚠️
Разглеждаме стекова машина, която представя паметта си като списък от числа и символи и приема списък от инструкции, които интерпретира по следния начин: - ако поредната инструкция е число или символ, то се добавя на върха на стека - ако поредната инструкция е функция, тя се прилага над всички числа в стека (допуска се, че функцията приема само един параметър), променяйки стойностите им в стека - ако поредната инструкция е наредена двойка от операция (двуместна функция) и число n, то горните две числа на стека се изваждат и обратно на върха на стека се записва резултат от прилагането на операцията над тях. Прилагането се повтаря до изчерпване на стека или достигане до символ, но не повече от n пъти. - всички останали инструкции се игнорират.

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
### Задача 3 (10 т.)
Казваме, че един списък е подсписък на друг, ако елементите на първия списък се срещат непосредствено последователно във втория. Например, '(2 4) не е подсписък на '(1 2 3 4 5), но '(2 3 4) е. Казваме, че един списък от числа a се мажорира от списъка b, ако двата списъка са с еднаква дължина n и ai ≤ bi за всяко i ∈ [0; n). Списък от списъци ll наричаме мажорен, ако е вярно, че li се мажорира от подсписък на li+1 за всеки два съседни списъка li и li+1 в ll.

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
### Бонус ⚠️
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
## Тема 2
### Задача 1
а) (3 т.) Да се реализира функция product-digits, която намира произведението от цифрите на дадено естествено число.
б) (7 т.) Нека с {n} означим разликата на n и произведението на цифрите на n. Да се реализира функция largest-diff, която намира най-голямата разлика {m} – {n} за m, n ∈ [a; b], където a и b са параметри на функцията.
Пример: `(largest-diff 28 35) → 19  = {30} – {29} = (30 – 0) – (29 – 18))`
```scheme
(define (number-of-digits n)
  (if(< n 10)
     1
     (+ 1 (number-of-digits (quotient n 10)))))

(define (product-digits n)
  (if(< n 10)
     n
     (accumulate * 1 0 (- (number-of-digits n) 1) (lambda(i)(remainder (quotient n (expt 10 i)) 10)) ++)))

(define (largest-diff a b)
  (define (term i)
    (define (diff n)
      (- n (product-digits n)))
    (define (inner-term j)
      (abs (- (diff i) (diff j))))
    (accumulate (lambda (f s) (max f s)) -inf.0 a b inner-term ++))
  (accumulate (lambda (f s) (max f s)) -inf.0 a b term ++))
```

### Задача 2 (10 т.) 
“Метрика” наричаме функция, която приема като параметър списък от числа и връща число като резултат. Да се напише функция max-metric, която приема като параметри списък от метрики ml и списък от списъци от числа ll и връща метрика m от ml, за която сумата от стойностите, които m връща над елементите на ll, е максимална в сравнение с останалите метрики от ml.
Примери:
```scheme
(define (prod l) (apply * l))        (define (sum l) (apply + l)) 
(max-metric (list sum prod) '((0 1 2) (3 4 5) (1337 0))) → <sum>
(max-metric (list car sum)  '((1000 -1000) (29 1) (42))) → <car>
```
```scheme
(define (prod l) (apply * l))
(define (sum l) (apply + l))

(define (foldl op nv l)
  (if(null? l)
     nv
     (foldl op (op nv (car l)) (cdr l))))

(define (sum l)
  (foldl + 0 l))

(define (max-pair l)
  (foldl (lambda (pair1 pair2)(if (< (cdr pair1) (cdr pair2)) pair2 pair1)) (car l) l))

(define (max-metric ml ll)
  (car (max-pair (map (lambda (metric)(cons metric (sum(map (lambda(l)(metric l)) ll)))) ml))))
```
### Задача 3 (10 т.) 
“Ниво на влагане” на атом в дълбок списък наричаме броя пъти, който трябва да се приложи операцията car за достигане до атома. Да се реализира функция deep-repeat, която в подаден дълбок списък заменя всеки атом на ниво на влагане n с n негови повторения.
Пример:
```scheme
(deep-repeat '(1 (2 3) 4 (5 (6)))) → (1 (2 2 3 3) 4 (5 5 (6 6 6)))
```
```scheme
(define (atom? x)
  (or
   (symbol? x)
   (number? x)
   (procedure? x)))

(define (extend x n)
  (accumulate append '() 1 n (lambda(i)(list x)) ++))

(define (deep-repeat-lvl level dl)
  (cond
    ((null? dl) dl)
    ((null? (car dl)))
    ((atom? (car dl))
     (append (extend (car dl) (+ 1 level)) (deep-repeat-lvl level (cdr dl))))
    (else ;(car dl) is a list
     (cons (deep-repeat-lvl (+ 1 level) (car dl))
           (deep-repeat-lvl level (cdr dl))))))

(define (deep-repeat dl)
  (deep-repeat-lvl 0 dl))
```

## Тема 3
### Задача 1
а) (3 т.) Да се реализира функция sum-digit-divisors, която намира сумата на тези от положителните цифри на дадено естествено число, които са му делители.
б) (7 т.) Да се реализира функция same-sum, която намира броя на двойките числа (m, n), за които  a ≤ m < n ≤ b и функцията sum-digit-divisors от предното подусловие връща един и същ резултат, където a и b са параметри на функцията.
Пример: `same-sum 28 35 → 2       двойките са (28, 32) и (29, 34)`
```scheme
(define (sum-digit-divisors n)
  (define (term i)
    (define digit (remainder (quotient n (expt 10 i)) 10))
    (if (and
         (not (= 0 digit))
         (= 0 (remainder n digit)))
        digit
        0))
  (accumulate + 0 0 (- (number-of-digits n) 1) term ++))

(define (same-sum a b)
  (define (term i)
    (define (inner-term j)
      (if (= (sum-digit-divisors i) (sum-digit-divisors j))
          1
          0))
    (accumulate + 0 (+ i 1) b inner-term ++))
  (accumulate + 0 a b term ++))
```
## Задача 2 ⚠️
(10 т.) “Метрика” наричаме функция, която приема като параметър списък от числа и връща число като резултат. Да се напише функция best-metric?, която приема като параметри списък от метрики ml и списък от списъци от числа ll и проверява дали има метрика в ml, която дава по-големи стойности от всички други метрики от ml над всеки от елементите на ll.
Пример: 
```scheme
(define (prod l) (apply * l))        (define (sum l) (apply + l)) 
(best-metric? (list sum prod) '((0 1 2) (3 -4 5) (1337 0))) → #t
(best-metric? (list car sum)  '((100 -100) (29 1) (42)))    → #f
```
```scheme
(define (more f s)
  (cond
    ((not (= (length f) (length s))) #f)
    ((null? f) #t)
    (else
     (and (> (car f) (car s)) (less (cdr f) (cdr s))))))

(define l1 '(1 2 3))
(define l2 '(3 1 2))

(define (bigger? l1 l2)
  (if (null? (cdr l1))
      (> (car l1) (car l2))
      (cond
        ((> (car l1) (car l2)) #t)
        ((< (car l1) (car l2)) #f)
        (else (bigger? (cdr l1) (cdr l2))))))

(define (insert elem ll)
  (cond
    ((null? ll) (list elem))
    ((bigger? elem (car ll)) (cons (car ll) (insert elem (cdr ll))))
    (else
     (cons elem ll))))

(define (sort ll)
  (if (null? ll)
      ll
      (insert (car ll) (sort (cdr ll)))))

(define (res elem ll)
  (cond
    ((null? ll) #t)
    ((bigger? elem (car ll)) (res (car ll) (cdr ll)))
    (else #f)))

(define (best-metric? ml ll)
  (define my-list (map (lambda (metric) (map (lambda (l)(metric l)) ll)) ml))
  (res (car my-list) (cdr my-list)))
```

## Задача 3 (10 т.)
“Ниво на влагане” на атом в дълбок списък наричаме броя пъти, който трябва да се приложи операцията car за достигане до атома. Да се реализира функция deep-delete, която в даден дълбок списък изтрива всички числови атоми, които са по-малки от нивото им на влагане.
Пример:
```scheme
(deep-delete '(1 (2 (2 4) 1) 0 (3 (1)))) → (1 (2 (4)) (3 ()))
```
```scheme
(define (atom? x)
  (and
   (not (null? x))
   (not (pair? x))))

(define (deep-delete-lvl level dl)
  (cond
    ((null? dl) dl)
    ((null? (car dl)))
    ((atom? (car dl))
     (if (<= (car dl) level)
         (deep-delete-lvl level (cdr l))
         (cons
              (car dl)
              (deep-delete-lvl level (cdr dl)))))
     (else
      (cons
           (deep-delete-lvl (+ 1 level) (car dl))
           (deep-delete-lvl level (cdr dl))))))

(define (deep-delete dl)
  (deep-delete-lvl 0 dl))
```

## Тема 4
### Задача 1. 
а) (3 т.) Да се реализира функция sum-common-divisors, която намира сумата от общите делители на две естествени числа.
б) (7 т.) Да се реализира функция greatest-sum, която намира най-голямата сума на общи делители на две различни числа в интервала [a; b], където a и b са параметри на функцията.
Пример: `greatestSum 21 34 → 15         (за числата 24 и 32)`
```scheme
(define (sum-common-divisors a b)
  (define (term i)
    (if (and (= 0 (remainder a i)) (= 0 (remainder b i)))
        i
        0))
  (accumulate + 0 1 (min a b) term ++))

(define (greatest-sum a b)
  (define (term i)
    (define (inner-term j)
      (sum-common-divisors i j))
    (accumulate (lambda (f s) (max f s)) -inf.0 (+ i 1) b inner-term ++))
  (accumulate (lambda (f s) (max f s)) -inf.0 a b term ++))
```

## Задача 2. (10 т.)
“Метрика” наричаме функция, която приема като параметър списък от числа и връща число като резултат. Да се напише функция count-metrics, която приема като параметри списък от метрики ml и списък от списъци от числа ll и връща броя на метриките от ml, които дават еднакви стойности за всички елементи на ll.
Пример: 
```scheme
(define (prod l) (apply * l))
(define (sum l) (apply + l)) 
(define (count-metrics ml ll)
  (define my-list (map (lambda(metric)(map (lambda(l)(metric l)) ll)) ml))
  (define (term i)
    (define (inner-term j)
      (if (equal?
           (list-ref my-list i)
           (list-ref my-list j))
         1
         0))
    (accumulate + 1 (+ i 1) (- (length my-list) 1) inner-term ++))
  (accumulate (lambda (f s)(max f s)) 0 0 (- (length my-list) 2) term ++))
```
## Задача 3. (10 т.) 
“Ниво на влагане” на атом в дълбок списък наричаме броя пъти, който трябва да се приложи операцията car за достигане до атома. Да се реализира функция level-flatten, която по подаден дълбок списък dl връща плосък списък от всички атоми в dl, като всеки числов атом е увеличен с номера на нивото си на влагане.
Пример:
```scheme
(level-flatten '(1 (2 3) 4 (5 (6)) (7))) → (2 4 5 5 7 9 9)
```
```scheme
(define (level-flatten-lvl level dl)
  (cond
    ((null? dl) dl)
    ((null? (car dl)))
    ((atom? (car dl))
     (append (list (+ (car dl) level)) (level-flatten-lvl level (cdr dl))))
    (else ;; dl is list
     (append
       (level-flatten-lvl (+ 1 level) (car dl))
       (level-flatten-lvl level (cdr dl))))))
  
(define (level-flatten dl)
  (level-flatten-lvl 1 dl))
```

## Тема 5
### Задача 1
Да се напише функция middle-digit, която намира средната цифра от записа на подадено естествено число n. Ако n е с четен брой цифри, функцията връща -1.

Пример: `(middle-digit 452) → 5`

Пример: `(middle-digit 4712) → -1`
```scheme
(define (count-digits n)
  (if(< n 10)
     1
  (+ 1 (count-digits (quotient n 10)))))

(define (middle-digit n)
  (if (= (remainder (count-digits n) 2) 0)
      -1
      (remainder
       (quotient
        n
        (expt
         10
         (quotient (count-digits n) 2)))
       10)))
```

## Задача 2
Нека е даден списък l от числа и двуместна операция над числа ⊕. Функцията f наричаме “ендоморфизъм над l”, ако f трансформира l в себе си, запазвайки операцията ⊕, т.е. ∀x∈l f(x)∈l и ∀x,y∈l f(x) ⊕ f(y) = f(x ⊕ y). Да се реализира функция is-em?, която проверява дали f е ендоморфизъм.

Пример: `(is-em? ‘(0 1 4 6) + (lambda (x) (remainder x 3))) → #t`
```scheme
(define (all-pairs l)
  (define (term i)
    (define (inner-term j)
      (list (cons (list-ref l i) (list-ref l j))))
    (accumulate append '() (+ i 1) (- (length l) 1) inner-term ++))
  (accumulate append '() 0 (- (length l) 2) term ++))

(define (is-em? l op f)
  (define pairs (all-pairs l))
  (equal? (map
           (lambda (pair)(op (f (car pair)) (f (cdr pair))))
           pairs)
          (map
           (lambda (pair)(op (f (car pair)) (f (cdr pair))))
           pairs)))
```

## Задача 3
Да се напише функция (meetTwice? f g a b), която проверява дали в целочисления интервал [a; b] съществуват две различни цели числа x и y такива, че f(x) = g(x) и f(y) = g(y).


Пример:`(meetTwice? (lambda(x)x) (lambda(x) (- x)) -3 1) → #f`

Пример:`(meetTwice? (lambda(x)x) sqrt 0 5) → #t`
```scheme
(define (meetTwice? f g a b)
  (define (term i)
    (define (inner-term j)
      (and
       (= (f i) (g i))
       (= (f j) (g j))))
    (accumulate (lambda (f s)(or f s)) #f (+ i 1) b inner-term ++))
  (accumulate (lambda (f s)(or f s)) #f a b term ++))
```

## Задача 4
Казваме, че списъкът x = (x1 x2 … x2n) от цели числа се получава от прочитането (look-and-say) на списъка y, ако y се състои от последователно срещане на x1 пъти x2, последвано от x3 пъти x4, и така нататък до x2n-1 пъти x2n. Да се дефинира функция next-look-and-say, която по даден списък y намира списъка x, получен от прочитането y.

Пример: `(next-look-and-say ‘(1 1 2 3 3)) → ‘(2 1 1 2 2 3)`
```scheme
(define (next-look-and-say l)
  (define (helper last counter rest result)
    (print 'last:)
    (println last)
    (print 'counter:)
    (println counter)
    (if (null? rest)
      (append result (list counter last))
      (if (eqv? (car rest) last)
          (helper last (+ counter 1) (cdr rest) result)
          (helper (car rest) 1 (cdr rest) (append result (list counter last))))))
   (helper (car l) 1 (cdr l) '()))
```
