
(define (++ n) (+ n 1))
(define (id n) (n))

(define (accumulate op nv a b term next)
  (if (> a b)
      nv
      (op (term a) (accumulate op nv (next a) b term next))))

;; 1
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

;; 2
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

;; 3
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



;; 1
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

;; 2
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

;; 3
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


;; 1
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

;; 2
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

;; 3
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

;; 1
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

;; 2
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

;; 3
(define (meetTwice? f g a b)
  (define (term i)
    (define (inner-term j)
      (and
       (= (f i) (g i))
       (= (f j) (g j))))
    (accumulate (lambda (f s)(or f s)) #f (+ i 1) b inner-term ++))
  (accumulate (lambda (f s)(or f s)) #f a b term ++))

;; 4
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
