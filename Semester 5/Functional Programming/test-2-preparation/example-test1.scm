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
;; 1
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
  
;; 2
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

;; 3
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

(define (find-longest-major ll)
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
  