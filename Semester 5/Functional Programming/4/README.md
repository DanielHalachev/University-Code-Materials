# 04. Списъци

При решаване на сложна задача със списъци (не като тези тук), най-подходящо е тя да се разбие на малки части, а именно на такива прости кратки функции (като тези тук до 17 задача вкл. и задача 20). Това позволява решението на задачата да се проследява последователно, дори да се чете на английски, подобно на математическо доказателство.

От вградените функции, много честно се случва да се ползват `map` и `filter`, малко по-рядко но пак честно `member`, `append`, `reverse`.

### Зад 1 `length`(вградена)
Дължина на списък
```scheme
(define (length l)
  (if(null? l)
     0
     (+ 1 (length (cdr l)))))
```

### Зад 2 `sum`
Сумата на всички числа от списък
```scheme
(define (sum l)
  (if(null? l)
     0
     (+ (car l) (sum(cdr l)))))
```

### Зад 3 `last`
Последния елемент на списък
```scheme
(define (last l)
  (cond
    ((null? l) 'error )
    ((null? (cdr l)) (car l))
    (else (last (cdr l)))))
```

### Зад 4 `append` (вградена)
Слепя два списъка
```scheme
(define (append l1 l2)
  (if(null? l1) l2 (cons (car l1) (append (cdr l1) l2))))
```

### Зад 5 `push-back` (еквивалентна на (flip snoc))
Слага елемент накрая на списък (като създава нов списък)
```scheme
(define (push-back e l)
  (if(null? l) (cons e '())
     (cons (car l) (push-back e (cdr l)))))
```

### Зад 6 `member?`(вградена като `member`)
Дали `x` е елемент на списъка?
```scheme
(define (member? e l)
  (if(null? l) #f (or (equal? e (car l)) (member? e (cdr l)))))
```

### Зад 7 `from-to` (много полезна)
Списък от числата `(a (+ a 1) (+ a 2) (+ a 3) ... b)`, тоест целите числа в интервала [`a`, `b`].
```scheme
(define (from-to a b)
  (if(> a b) '()
     (cons a (from-to (+ a 1) b))))
```

### Зад 8 `reverse`(вградена)
Обратен ред на елементите на списък.
```scheme
(define (reverse l)
  (if(null? l) '()
     (append (reverse (cdr l)) (list (car l)))))
```

### Зад 9 `map` (вградена)
Прилага функция над всеки от елементите на списък.
```scheme
(define (map f l)
  (if (null? l)
     '()
     (cons (f (car l)) (map f (cdr l)))))

```

Спрямо `(a1 a2 a3 a4 ... an)` връща `((f a1) (f a2) (f a3) (f a4) ... (f an))`.

### Зад 10 `filter` (вградена)
Списък от елементите на списък, които изпълняват предикат.
```scheme
(define (filter p? l)
  (cond ((null? l) '())
       ((p? (car l)) (cons (car l) (filter p? (cdr l))))
       (else (filter p? (cdr l)))))
```

### Зад 11 `partition`
Връща списък от два списъка.
```scheme
(define (partition p? l)
  (if (null? l)
     '(() ())
     (let*(
           (rec (partition p? (cdr l)))
           (list-of-true (car rec))
           (list-of-false (cadr rec))
           (x (car l)))
       (if (p? x)
           (list (cons x list-of-true) list-of-false)
           (list list-of-true (cons x list-of-false))))))
```

Първият подсписък съдържа всички елементи които изпълняват предикат, а вторият съдържа всички, които не го.

### Зад 12 `scp`
Сумата на третите степени на всички прости числа в списък
```scheme
;; import prime? from ./../3
(define (scp l)
  (sum
   (map (lambda (i) (* i i i)) (filter prime? l))))
```

### Зад 13 `take` (полезна)
Списък от първите `n` елемента на списък
```scheme
(define (take n l)
  (if (or (= n 0) (null? l))
      '()
      (cons (car l) (take (- n 1) (cdr l)))))
```

### Зад 14 `drop`) (полезна)
Списък от всички елементи на списък без първите `n`.
```scheme
(define (drop n l)
  (cond((null? l) '())
       ((= n 0) l)
       (else (drop (- n 1) (cdr l)))))
```

### Зад 15 `all?` (много полезна)
Дали всички елементи на списък изпълняват предиката `p?`?
```scheme
(define (all? p? l)
  (if(null? l) #t
     (and (p? (car l)) (all? p? (cdr l)))))
```

### Зад 16 `any?` (много полезна)
Дали поне един елемент на списък изпълняват предиката `p?`?
```scheme
(define (any? p? l)
  (if(null? l) #f
     (or (p? (car l)) (any? p? (cdr l)))))
```

### Зад 17 `remove` (донякъде полезна)
Премахва първото срещане на `x` в списък (връщайки нов списък).
```scheme
(define (remove x l)
  (cond
    ((null? l) l)
    ((equal? x (car l)) (cdr l))
    (else (cons (car l) (remove x (cdr l))))))
```

### Зад 18 `sorted?`
Дали списък е сортиран?
```scheme
(define (sorted? l)
  (define (sorted-asc? l)
    (cond
      ((null? l) #t)
      ((null? (cdr l)) #t)
      (else (and (< (car l) (cadr l)) (sorted-asc? (cdr l))))))
  (define (sorted-des? l)
    (cond
      ((null? l) #t)
      ((null? (cdr l)) #t)
      (else (and (> (car l) (cadr l)) (sorted-des? (cdr l))))))
  (or (sorted-asc? l) (sorted-des? l)))
```

### Зад 19 `insertion-sort` (най-лесният алгоритъм за сортиране функционално)
Сортиране на списък по алгоритъма [insertion sort](https://en.wikipedia.org/wiki/Insertion_sort).
```scheme

```

### Зад 20 `explode-digits` (много полезна за задачи с числа)
Списък от цифрите на цяло число.
```scheme
(define (explode-digits n)
  (if (< n 10) (list n)
      (cons (remainder n 10) (explode-digits (quotient n 10)))))
```

### Зад 21 `digit-occurence`
Намира колко пъти цифрата `d` се среща в цялото число `n`.
```scheme
define (digit-occurence d n)
  (sum (map (lambda(i) 1) (filter (lambda(x)(= x d)) (explode-digits n)))))
```

### Зад 22 `remove-repeats`
Премахва последователните повторения на едно и също число от списък.
```scheme
(define (remove-repeats l)
  (cond
    ((null? l) l)
    ((null? (cdr l)) (list (car l)))
    ((eqv? (car l) (cadr l)) (remove-repeats (cdr l)))
    (else (cons (car l) (remove-repeats (cdr l))))))
```

Пример:
```scheme
(remove-repeats '(1 1 4 4 3 3 4 4 4)) -> '(1 4 3 4)
(remove-repeats '(1 2 3 4)) -> '(1 2 3 4)
```

### Зад 23 (задача 3 от контролно 2017/18)
(9 т.) Нека  е даден  списък  l от числа  и двуместна
операция над числа ⊕. Функцията  f наричаме “ендоморфизъм
над l”, ако f трансформира l в себе си, запазвайки операцията ⊕,
т.е. ∀x∈l f(x)∈l и ∀x,y∈l f(x) ⊕ f(y) = f(x ⊕ y). Да се реализира
функция `is-em?`, която проверява дали f е ендоморфизъм.

Пример:
```scheme
(is-em? '(0 1 4 6) + (lambda (x) (remainder x 3))) ; → #t
```
```scheme
(define (accumulate op nv a b term next)
  (if (> a b) nv
      (op (term a) (accumulate op nv (next a) b term next))))
(define (++ n) (+ 1 n))

(define (get i l)
  (cond
    ((null? l) 'error)
    ((= i 1) (car l))
    (else (get (- i 1) (cdr l)))))

(define (all-pairs l)
  (define (term i)
    (define (inner-term j)
      (cons (get i l) (get j l)))
    (accumulate push-back '() (+ i 1) (length l) inner-term ++))
  (accumulate append '() 1 (length l) term ++))

(define (is-em? l op f)
  (let*(
        (pairs (all-pairs l)))
    (define l1 (map (lambda(pair)(f (op (car pair) (cdr pair)))) pairs))
    (define l2 (map (lambda(pair)(op (f (car pair)) (f (cdr pair)))) pairs))
    (equal? l1 l2)))


(define (is-em? l op f)
  (define pairs (all-pairs l))
  (define (term i)
    (define pair (get i pairs))
    (= (f
        (op
         (car pair)
         (cdr pair)))
       (op
        (f (car pair))
        (f (cdr pair)))))
  (accumulate (lambda(f s)(and f s)) #t 1 (length pairs) term ++))
```

### Зад 24 (вариант А, задача 2 от контролно 2019/20)
(10 т.) “Метрика” наричаме функция, която приема като
параметър  списък  от числа  и  връща  число  като  резултат.  Да  се
напише функция `max-metric`, която приема като параметри списък
от метрики `ml` и списък от списъци от числа `ll` и връща метрика `m` от
`ml`, за която сумата от стойностите, които `m` връща над елементите на
`ll`, е максимална в сравнение с останалите метрики от `ml`.

Примери:
```scheme
(define (prod l) (apply * l))
(define (sum l) (apply + l))

(max-metric (list sum prod) '((0 1 2) (3 4 5) (1337 0))) ; → <sum>
(max-metric (list car sum)  '((1000 -1000) (29 1) (42))) ; → <car>
```

```scheme
(define (foldl proc init lst)
  (if (null? lst)
      init
      (foldl proc (proc (car lst) init) (cdr lst))))
(define (max-metric metrics args)
  (define res (map (lambda (m)(cons m (sum (map m args)))) metrics))
  (car (foldl (lambda (p1 p2)(if(< (cdr p1) (cdr p2)) p2 p1)) (car res) (cdr res))))
```
