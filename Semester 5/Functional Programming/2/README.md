# 02. Рекурсия и итерация

### Зад 1 `count-digits`
Брой цифри на цяло число (вкл. и отрицателно).
```scheme
(define (count-digits n)
  (define (cd n result)
    (if(< n 10)
       result
       (cd (quotient n 10) (+ 1 result))))
  (cd (abs n) 1))
```

### Зад 2 `sum-digits`
Сума от цифрите на цяло число.
```scheme
(define (sum-digits n)
  (define (sd n result)
    (if (< n 10)
        (+ n result)
        (sd (quotient n 10) (+ result (remainder n 10)))))
  (sd n 0))
```

### Зад 3 `bin-to-dec`
Преобразуване от двоична в десетична бройна система.
```scheme
(define(bin-to-dec bin)
  (define (helper bin dec i)
    (if(= bin 0)
       dec
       (helper (quotient bin 10) (+ dec (* (remainder bin 10) (pow 2 (+ i 1)))) (+ i 1))))
  (helper bin 0 -1))
```

### Зад 4 `dec-to-bin`
Преобразува число от десетична в двоична бройна система.
```scheme
(define (dec-to-bin dec)
  (define (helper dec bin)
    (if (= dec 0)
        bin
        (helper (quotient dec 2) (+ (remainder dec 2) (* bin 10)))))
  (helper dec 0))
```

### Зад 5 `digit-occurence`
Колко пъти цифрата d се среща в цялото число n?
```scheme
(define (digit-occurence n d)
  (define (helper1 n d)
    (if(= n d)
       1
       0))
  (define (helper2 n d c)
    (if(< n 10)
       (+ c (helper1 n d))
       (helper2 (quotient n 10) d (+ c (helper1 (remainder n 10) d)))))
  (helper2 n d 0))
```

### Зад 6 `reverse-digits`
Обръща реда на цифрите на число.
```scheme
(define (reverse-digits n)
  (define (rev n i result)
    (if(< n 10)
       (+ result n)
       (rev (quotient n 10) (- i 1) (+ result (* (remainder n 10) (pow 10 i))))))
  (rev n (- (count-digits n) 1) 0))
```

### Зад 7 `palindrome?`]
```scheme
(define (plaindrome? n)
  (= n (reverse-digits n)))
```

### Зад 8 `sum-interval`
```scheme
(define (sum-interval a b)
  (define (s a b result)
    (if(= a b)
       a
       (+ a (s (+ a 1) b (+ a result)))))
  (s a b 0))
```

### Зад 9 `monotonous?`
```scheme
(define (monot? n)
  (cond
    ((< n 10) #t)
    ((< n 100) (< (quotient n 10) (remainder n 10)))
    (else (and (< (remainder (quotient n 10) 10) (remainder n 10)) (monot? (quotient n 10))))))
```

### Зад 10 `fast-pow`
Итеративен вариант на Exponentiation by squaring.
```scheme
(define (fast-pow base power)
  (define (square n)
    (* n n))
  (define (helper base power result)
    (cond
      ((= power 0) result)
      ((even? power) (helper base (/ power 2) (result ^ power/2)))
      (else (* (square (helper base (quotient power 2) result)) base))))
  (helper n 0))
```

### Зад 11 `automorphic?`
Дали е автоморфно числото? Едно число е _автоморфно_, ако квадратът му завършва на него.

```scheme
(define (ends-in? n end)
  (cond
    ((< n end) #f)
    (else (= (remainder (- n end) (pow 10 (count-digits end))) 0))))
(define (automorphic? n)
  (ends-in? (* n n) n))
```

### Зад 12 `prime?`
Дали числото е просто?
```scheme
(define (prime? n)
  (define (helper n i)
    (if(> i (sqrt n))
       #t
      (and (not(= (remainder n i) 0)) (helper n (+ i 1)))))
  (helper n 2))
```

### Зад 13 `fibonacci`
```scheme
(define (fibonacci n)
  (define (helper n res1 res2)
    (if(<= n 2)
       res2
       (helper (- n 1) res2 (+ res1 res2))))
  (helper n 1 1))
```
### Зад 14 `factorial`
```scheme
(define (factorial n)
  (define (fact n result)
    (if(<= n 0)
       result
       (fact (- n 1) (* result n))))
  (fact n 1))
```
