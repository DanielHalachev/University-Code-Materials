# 05. Fold. Дълбоки списъци
### Задача 1 (много полезна)
Напишете функция `(maximum l)`,
която намира най-големия елемент в l.
```scheme
(define (maximum l)
  (if (null? (cdr l))
      (car l)
      (max (car l) (maximum (cdr l)))))
```

### Задача 1.5 (полезна)
Напишете функция `(argmin f l)`,
която намира елемент `x` на `l`, за който `(f x)` има най-малка стойност, тоест ∀y∈l( f(x) ≤ f(y) ).
```scheme
(define (my-min f a b)
  (if (< (f a) (f b))
      a
      b))
(define (argmin f l)
  (if (null? (cdr l))
      (car l)
      (my-min f (car l) (argmin f (cdr l)))))
```

### Задача 2
Напишете функция `(selection-sort l)`
която сортира списъка l по алгоритъма [selection sort](https://en.wikipedia.org/wiki/Selection_sort).
Пример:
```scheme
(selection-sort '(5 1 2 6 3)) -> '(1 2 3 5 6)
```
> Упътване: използвайте `remove`
```scheme
(define (minimum l)
  (if (null? (cdr l))
      (car l)
      (min (car l) (minimum (cdr l)))))
(define (remove element l)
  (cond ((null? l) l)
        ((equal? element (car l)) (cdr l))
        (else (cons (car l) (remove element (cdr l))))))
(define (selection-sort l)
  (if (null? l)
      l
      (let ((min-el (minimum l)))
        (cons min-el (selection-sort (remove min-el l))))))
```

### Задача 3
Напишете функция `(slice a b l)`,
която връща подсписъкът на l от позиция a до позиция b. Позициите започват от 0.
Пример:
```scheme
(slice 3 7 '(1 2 3 4 5 6 7 8 9)) -> '(4 5 6 7 8)
```
```scheme
(define (slice a b l)
  (cond ((null? l) l)
        ((= 0 b) (list (car l)))
        ((= 0 a) (cons (car l) (slice a (- b 1) (cdr l))))
        (else (slice (- a 1) (- b 1) (cdr l)))))
```

### Задача 4 (полезна, повечко в Хаскел)
Напишете функция `(zip l m)`,
която връща списък от наредени двойки от елементите на l и m.
Пример:
```scheme
(zip '(1 2 3) '(4 5 6)) -> '((1 . 4) (2 . 5) (3 . 6))
```
```scheme
(define (zip l m)
  (cond ((null? l) '())
        ((null? m) '())
        (else (cons (cons (car l) (car m)) (zip (cdr l) (cdr m))))))
```

### Задача 5 (полезна, повечко в Хаскел)
Напишете функция `(zip-with f l m)`,
която връща списък от прилагането на f върху елемент на l и елемент на m.
Пример:
```scheme
(zip-with * '(1 2 3) '(4 5 6)) -> '(4 10 18)
(zip-with cons '(1 2 3) '(4 5 6)) -> '((1 . 4) (2 . 5) (3 . 6))
```
```scheme
(define (zip-with f l m)
  (map (lambda (pair)(f (car pair) (cdr pair))) (zip l m)))
```

### Задача 6
Напишете функция `(unique l)`,
която връща списък от елементите на l без повторения.
Пример:
```scheme
(unique '(1 2 3 3 3 4 3 3 5 5 3)) -> '(1 2 3 4 5)
```
```scheme
(define (filter p? l)
  (cond ((null? l) l)
        ((p? (car l)) (cons (car l) (filter p? (cdr l))))
        (else (filter p? (cdr l)))))
(define (unique l)
  (if (null? l)
      l
      (cons (car l) (unique (filter (lambda (x) (not (equal? x (car l)))) (cdr l))))))
```

### Задача 7
Напишете функция `(intersection l m)`,
която връща списък с елементите, които се срещат едновременно в l и m, без повторения.
Пример:
```scheme
(intersection '(1 2 3 4) '(6 1 4 5)) -> '(1 4)
```
```scheme
(define (intersection l m)
  (filter (lambda (x) (member x m)) l))
```

### Задача 8
Напишете функция `(union l m)`,
която връща списък с елементите на l и m, без повторения.
Пример:
```scheme
(union '(1 2 3 4) '(6 1 4 5)) -> '(1 2 3 4 6 5)
```
```scheme
(define (union l m)
  (unique (append l m)))
```

### Задача 9
Напишете функция `(set-minus l m)`,
която връща списък с елементите на l, които не са елементи на m, без повторения.
Пример:
```scheme
(set-minus '(1 2 3 4 5 6) '(6 1 4)) -> '(2 3 5)
```
```scheme
(define (set-minus l m)
  (filter (lambda (x) (not (member x m))) l))
```

### Задача 10
Напишете функция `(chunk n l)`,
която връща списък от последователните подсписъци на l с дължина n.
Пример:
```scheme
(chunk 3 '(1 2 3 4 5 6 7 8 9 10)) -> '((1 2 3) (4 5 6) (7 8 9) (10))
```
```scheme
(define (take-first n l)
  (cond ((null? l) l)
        ((= 0 n) '())
        (else
         (cons (car l) (take-first (- n 1) (cdr l))))))
(define (drop-first n l)
  (cond ((null? l) l)
        ((= n 0) l)
        (else (drop-first (- n 1) (cdr l)))))
(define (chunk n l)
  (if (null? l)
      l
      (cons (take-first n l) (chunk n (drop-first n l)))))
```

### Задача 11
Напишете функция `(selection-sort less l)`
която сортира списъка l по алгоритъма [selection sort](https://en.wikipedia.org/wiki/Selection_sort), използвайки `less` като функция за сравнение на два елемента.
Пример:
```scheme
(selection-sort > '(5 1 2 6 3)) -> '(6 5 3 2 1)
```
```scheme
(define (remove element l)
  (cond ((null? l) l)
        ((equal? element (car l)) (cdr l))
        (else (cons (car l) (remove element (cdr l))))))
(define (minimum less? l)
  (define (my-min a b)
    (if (less? a b) a b))

  (if (null? (cdr l))
      (car l)
      (my-min (car l) (minimum less? (cdr l)))))

(define (selection-sort less l)
  (if (null? l)
      l
      (let ((min-el (minimum less l)))
        (cons min-el (selection-sort less (remove min-el l))))))
```

### Задача 12
Напишете функция `(count-atoms dl)`,
която намира броя атоми в дълбокия списък dl.
Пример:
```scheme
(count-atoms '((1 2 3) (4) ((5 6) ((7))))) -> 7
```
```scheme
(define (atom? a)
  (and
   (not (null? a))
   (not (pair? a))))
(define (count-atoms dl)
  (cond ((null? l) 0)
        ((atom? l) 1)
        (else (+ (count-atoms (car l)) (count-atoms (cdr l))))))
```

### Задача 13
Напишете функция `(flatten dl)`,
която връща списък от атомите в дълбокия списък dl.
Пример:
```scheme
(flatten '((1 2 3) (4) ((5 6) ((7))))) -> '(1 2 3 4 5 6 7)
```
```scheme
(define (flatten dl)
  (cond ((null? dl) dl)
        ((atom? dl) (list dl))
        (else (append (flatten (car dl)) (flatten(cdr dl))))))
```

### Задача 14
Напишете функция `(deep-reverse dl)`,
която обръща реда на елементите във всеки списък в дълбокия списък dl.
Пример:
```scheme
(deep-reverse '((1 2 3) (4) ((5 6) ((7))))) -> '((((7)) (6 5)) (4) (3 2 1))
```
```scheme
(define (deep-reverse dl)
  (cond ((null? dl) dl)
        ((atom? dl) dl)
        (else (append (deep-reverse (cdr dl)) (list (deep-reverse (car dl)))))))
```

### Задача 15
Напишете функция `(quicksort l)`,
която сортира списъка l по алгоритъма [quicksort](https://en.wikipedia.org/wiki/Quicksort). Като pivot може да ползвате първия елемент на списъка, за най-лесно.
```scheme
(define (quicksort l)
  (cond ((null? l) l)
        ((null? (cdr l)) l)
        (else (let ((pivot (car l)))
          (append
           (quicksort (filter (lambda (x)(<= x pivot)) (cdr l)))
           (list pivot)
           (quicksort (filter (lambda (x)(> x pivot)) l)))))))
```

### Задача 16
Отворен числов интервал `(a;b)` се описва с наредената двойка `(a . b)`. Да се напише функция `longest-interval-subsets`, която по даден списък от интервали `il` връща нов списък, който съдържа всички интервали от `il`, които са подинтервали на най-дългия интервал в списъка.
Бонус: Функцията `longest-interval-subsets` да връща подинтервалите подредени в нарастващ ред по началната си точка.
```
(longest-interval-subsets
  '((24 . 25) (90 . 110) (0 . 100) (10 . 109) (1 . 3) (-4 . 2)))
-> ((0 . 100) (1 . 3) (24 . 25))
```
```scheme
(define (foldl op nv l)
  (if (null? l)
      nv
      (foldl op (op nv (car l)) (cdr l))))

(define (foldl1 op l)
  (foldl op (car l) (cdr l)))

(define (interval-length interval)
  (- (cdr interval) (car interval)))

(define (get-longest il)
  (foldl1
   (lambda(i1 i2) (if (< (interval-length i1) (interval-length i2)) i2 i1))
   il))

(define (is-sub? test interval)
  (and
   (<= (car interval) (car test))
   (>= (cdr interval) (cdr test))))

(define (interval-cmp i1 i2)
  (< (car i1) (car i2)))

(define (longest-interval-subsets il)
  (let ((longest (get-longest il)))
    (selection-sort interval-cmp (filter (lambda (interval) (is-sub? interval longest)) il))))
```

### Задача 17
Да се напише функция `(group-by f lst)`, която групира елементите на списъка `lst` по стойността, която `f` връща за тях. Конкретно, за всяка върната от `f` стойност над някой елемент от `lst` трябва да върнете списък с два елемента - тази стойност и списъкът от елементите на `lst`, за които се получава тя.
```
(group-by even? '(1 2 3 4 5)) -> ((#f (1 3 5))
                                  (#t (2 4))) ; подредбата няма значение
(group-by length '((1 2 3) (4) (5 6 7))) -> '((1 ((4)))
                                              (3 ((1 2 3) (5 6 7))))
```
```scheme
(define (group-by f lst)
  (map
   (lambda (result)
     (cons
      result
      (list (filter
             (lambda (x)
               (equal? result (f x)))
             lst))))
   (unique (map
            (lambda(x)
              (f x))
            lst))))
```
Решение 2 (credits to @stainlesspot & reo101)
```scheme
```scheme
(define compose
  (lambda (f g)
    (lambda (x)
      (f (g x)))))

(define group-by
  (lambda (f l)
    (if (null? l)
      '()
      (let* ((first (car l))
             (is-eq (lambda (x)
                      (equal? (f first)
                              (f x))))
             (is-not-eq (compose not is-eq)))
        (cons (cons (f (car l))
                    (filter is-eq l))
              (group-by f (filter is-not-eq l)))))))
```

### Задача 18 (задача 4 от контролно 2015-16)
(8 т.) Да се напише функция  `(longestAscending l)`,
която намира възходящо сортиран подсписък на списъка от числа l с
максимална дължина. Ако съществуват няколко такива подсписъка,
функцията да върне първия отдясно наляво.
Упътване: Реализирайте  помощна  функция,  която  намира  най-дългия
възходящо сортиран префикс на даден списък.
Пример:
```scheme
(longestAscending ‘(5 3 8 6 4 2 6 7 1)) → (2 6 7)
```
```scheme
(define (foldr op nv l)
  (if (null? l) nv
          (op (car l) (foldr op nv (cdr l)))))

(define (foldr1 op l)
  (if (null? (cdr l)) (car l)
          (op (car l) (foldr1 op (cdr l)))))

(define (longestAscending l)
  (define (helper last rest last-sublist result)
    (cond (
           (null? rest)
           (append result
                   (list(reverse last-sublist))))
          (
           (< last (car rest))
           (helper (car rest)
                   (cdr rest)
                   (cons (car rest)
                         last-sublist)
                   result))
          (else
           (helper (car rest)
                   (cdr rest)
                   (list (car rest))
                   (append result
                           (list (reverse last-sublist)))))))
  (if (null? l)
      l
      (foldr1
       (lambda (l1 l2)
         (if (< (length l1) (length l2))
             l2
             l1))
       (helper (car l) (cdr l) (list (car l)) '()))))
```
