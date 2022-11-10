# 03. Accumulate и функции от по-висок ред
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

(define (id n)
  n)
(define (++ n)(+ n 1))
```
## Accumulate
Решете следните задачи чрез `accumulate`. За улеснение, може да първо да направите рекурсивно решение.

### Зад 1 `fact` и `fib`
Имплементирайте `fact` и `fib` чрез `accumulate`.
```scheme
;; factorial
(define (fact n)
  (accumulate * 1 1 n id ++))
;; fibonacci
(define (fib n)
  (define end (quotient (- n 1) 2))
  (define (term k)
    (/(fact ( - n k 1)) (* (fact k) (fact (- n (* 2 k) 1)))))
  (if( = n 0) 0 (accumulate + 0 0 end term ++)))
```

> Задачата за `fib` чрез `accumulate` не е особено трудна, стига да знаете формулата,
която се извежда по интересен начин от триъгълника на Паскал.
[Wikipedia](https://en.wikipedia.org/wiki/Fibonacci_number#Mathematics).

### Зад 2 `newton-binomial`
```scheme
(define (newton x y n)
  (define (n-choose-k n k)
    (/ (fact n)
       (* (fact k)
          (fact (- n k)))))
  (define (term k)
    (*(expt x (- n k))(expt y k) (n-choose-k n k)))
  (accumulate + 0 0 n term ++))
```

### Зад 3 `count-palindromes`]
Броят на целите числа палиндроми в интервала [a, b].
```scheme
(define (count-palindromes a b)
  (define (count-digits n)
    (if (< n 10) 1 (+ (count-digits (quotient n 10)) 1)))
  (define (reverse-digits n)
    (if(< n 10)
       n
       (+ (* (remainder n 10) (expt 10 (- (count-digits n) 1))) (reverse-digits (quotient n 10)))))
  (define (palindrome? n)
    (= (reverse-digits n) n))
  (accumulate + 0 a b (lambda (i)(if(palindrome? i) 1 0)) ++))
```

### Зад 4 `prime?-acc`
Имплементирайте `prime?` чрез `accumulate` или `accumulate-i`.
```scheme
(define (prime? n)
  (define end (sqrt n))
  (define (term i)
    (if(= 0 (remainder n i))
       1 0))
  (if(<= n 2) #t (= 0 (accumulate + 0 2 end term ++))))
```
```scheme
(define (prime? n)
  (define end (sqrt n))
  (define (term i)
    (not(= 0 (remainder n i))))
  (if(< n 2) #f (accumulate (lambda (f s)(and f s)) #t 2 end term ++)))
```

### Зад 5 `exists-int?`
Дали **има** цяло число в интервала [a, b], за което предикатът `pred?` е истина?
```scheme
(define (exists-int? pred? a b)
  (accumulate (lambda (f s) (or f s)) #f a b (lambda (i) (pred? i)) ++))
```

### [Зад 6 `all-int?`][all-int?]
Дали **за всяко** цяло число в интервала [a, b] предикатът `pred?` е истина?
```scheme
(define (all-int? pred? a b)
  (accumulate (lambda (f s) (and f s)) #t a b pred? ++))
```

### Зад 7 `count-p`
Броят на числата, удовлетворяващи предиката `pred?` сред числата `a`, `(next a)`, `(next (next a))`, ..., `b`.
```scheme
(define (count-p pred? a b next)
  (accumulate + 0 a b (lambda (i) (if(pred? i) 1 0)) next))
```

### Зад 8 `digit-sum`
Да се напише функция, която намира сбора на цифрите на числото n
```scheme
(define (digit-sum n)
  (define (count-digits n)
    (if (< n 10) 1 (+ (count-digits (quotient n 10)) 1)))
  (accumulate + 0 0 (count-digits n) (lambda (i) (remainder (quotient n (expt 10 i)) 10)) ++))
```

### Зад 9 `maximum-digit-sum`
Най-голямата сума на цифрите на цяло число от интервала [a, b].
```scheme
(define (maximum-digit-sum a b)
  (define (term i)
    (digit-sum i))
  (accumulate (lambda (f s) (if(< f s) s f)) 0 a b term ++))
```

### Зад 10 `count-pairs-gcd`
Броят на наредените двойки цели числа (`x`,`y`) от интервала [a,b], които имат най-голям общ делител равен на `n`.
```scheme
(define (count-pairs-gcd a b n)
  (define (outer i)
    (define (inner j)
      (if(= n (gcd i j)) 1 0))
    (accumulate + 0 a b inner ++))
  (accumulate + 0 a b outer ++))
```

### Зад 11 `twist`
Да се напише функция `(twist k f g)`, която за дадени едноместни функции `f` и `g` и четно число `k` връща функция, еквивалентна на `f(g(f(g(...(x)...))))`, където общият брой извиквания на `f` и `g` е `k`.
```scheme
(define (twist k f g)
  (define (compose f g)
    (lambda(x) (f (g x))))
  (accumulate compose id 1 k (lambda (i)(if(even? i) g f)) ++))
```
```scheme
(define (++ x) (+ x 1))
(define (sq x) (* x x))
(define foo (twist 4 ++ sq))
; това ще смята ((((x^2)+1)^2)+1)
(define bar (twist 2 ++ sq))
; това ще смята ((x^2)+1)
(foo 2) -> 26
(bar 2) -> 5
```

### Зад 12. (задача 1 от контролно 2021/22)
Едно естествено число наричаме **свършено**, ако е с 2 по-малко от сумата на всичките си делители по-малки от него.
- а) (3 т.) Да се реализира функция `done?`, която проверява дали дадено число е свършено.
- б) (7 т.) Да се реализира функция `sum-almost-done`, която по подадени естествени числа a и b намира сумата на всички числа в интервала [a; b], които са по-близко до свършено число, отколкото до краищата на интервала.
```scheme
(done? 20) → #t
(done? 28) → #f
(sum-almost-done 5 24) → 153 ; сумата на числата от 13 до 21
```
```scheme
(define (done? n)
  (define (delimiter-sum n)
    (define (term i)
      (if (= 0 (remainder n i)) i 0))
    (accumulate + 0 1 (- n 1) term ++))
  (= (+ n 2) (delimiter-sum n)))

(define (sum-almost-done a b)
  (define (term i)
    (define(inner-term j) (if (done? j) (abs (- i j)) +inf.0)) 
    (let(
         (distance1 (min (abs (- i a)) (abs (- b i))))
         (distance2 (accumulate (lambda (f s)(min f s)) +inf.0 a b inner-term ++)))
      (if (< distance2 distance1) i 0)))
  (accumulate + 0 a b term ++))
```

### Зад 13. (вариант А, задача 1 от контролно 2019/20)
- а) (3 т.) Да се реализира функция `product-digits`, която намира произведението от цифрите на дадено естествено число.
- б) (7 т.) Нека с **{n}** означим разликата на n и произведението на цифрите на **n**. Да се реализира функция `largest-diff`, която намира най-голямата разлика **{m} – {n}** за **m, n ∈ [a; b]**, където **a** и **b** са параметри на функцията.
Пример:
```scheme
(largest-diff 28 35) → 19  = {30} – {29} = (30 – 0) – (29 – 18)
```
```scheme
(define (number-of-digits n)
      (if (< n 10) 1 (+ 1 (number-of-digits (quotient n 10)))))

(define (product-digits n)  
  (define (term i)    
    (remainder (quotient n (expt 10 i)) 10))
  (accumulate * 1 0 (- (number-of-digits n) 1) term ++))

(define (largest-diff a b)
  (define (diff n)
    (abs (- n (product-digits n))))
  (define (term i)
    (define (inner-term j)
      (abs (- (diff i) (diff j))))
    (accumulate max -inf.0 a b inner-term ++))
  (accumulate max -inf.0 a b term ++))
```
