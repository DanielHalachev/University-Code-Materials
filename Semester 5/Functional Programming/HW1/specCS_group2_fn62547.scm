; common
(define (accumulate op nv a b term next)
  (if (> a b)
      nv
      (op
       (term a)
       (accumulate op nv (next a) b term next))))

(define (accumulate-i op nv a b term next)
  (if (> a b)
      nv
      (accumulate-i op (op nv (term a)) (next a) b term next)))

(define (++ n)
  (+ 1 n))


;; 1
(define (argmin f a b)
  (car (accumulate
        (lambda (first second)
          (if (<
               (cdr first)
               (cdr second))
              first
              second))
        (cons a (f a))
        a
        b
        (lambda (i)(cons i (f i)))
        ++)))


;; 2
(define (count-delims n)
  (accumulate
   + 0
   1 (sqrt n)
   (lambda (i)
     (if (= 0 (remainder n i))
         1
         0))
   ++))

(define (calc pair)
  (count-delims (+
                 (car pair)
                 (cdr pair))))

(define (pair-compare p1 p2)
  (if (>
       (calc p1)
       (calc p2))
      p1
      p2))

(define (best-pair a b)
  (define (term i)
    (define (inner-term j)
      (cons i j))
    (accumulate
     pair-compare
     (cons i (+ i 1))
     (+ i 1)
     b
     inner-term
     ++))
  (accumulate
   pair-compare
   (cons a (+ a 1))
   a
   (- b 1)
   term
   ++))


;; 3
(define (integrate2 f a b c d dx dy)
  (define (term y)
    (define (inner-term x)
      (f x y))
    (* dx (accumulate + 0 a b inner-term (lambda (x)(+ x dx)))))
  (* dy (accumulate + 0 c d term (lambda(y) (+ y dy)))))

;(define pi 3.14159265359)
;(define (f x y) (+ x (sin y) 1))


;; 4.1
(define (n-rooks board n)
  (define (check-rows board n)
    (define (term row)
      (define (inner-term col)
        (if (board row col n)
            1
            0))
      (<
       (accumulate
        + 0
        0 (- n 1)
        inner-term ++)
       2))
    (accumulate
     (lambda (f-row s-row) (and f-row s-row)) #t
     0 (- n 1)
     term ++))
  (define (check-colls board n)
    (define (term col)
      (define (inner-term row)
        (if (board row col n)
            1
            0))
      (<
       (accumulate
        + 0
        0 (- n 1)
        inner-term ++)
       2))
    (accumulate
     (lambda (f-col s-col) (and f-col s-col)) #t
     0 (- n 1)
     term ++))
  (and (check-rows board n) (check-colls board n)))

;(define (board1 x y n)
;  (= (remainder (+ x 2) n) y))
;(define (board2 x y n)
;  (= (min (+ x 2) (- n 1)) y))


;; 4.2
(define (line-compare board i j)
  (not
   (=
    (car (list-ref board i))
    (car (list-ref board j)))))

(define (col-compare board i j)
  (not
   (=
    (cdr (list-ref board i))
    (cdr (list-ref board j)))))

(define (n-rooks board n)
  (define (check-rows board n)
    (define (term i)
      (define (inner-term j)
        (line-compare board i j))
      (accumulate
       (lambda (f s)(and f s)) #t
       (+ i 1) (- (length board) 1)
       inner-term ++))
    (accumulate
     (lambda (f s)(and f s)) #t
     0 (- (length board) 2)
     term ++))
  (define (check-colls board n)
    (define (term i)
      (define (inner-term j)
        (col-compare board i j))
      (accumulate
       (lambda (f s)(and f s)) #t
       (+ i 1)
       (- (length board) 1)
       inner-term ++))
    (accumulate
     (lambda (f s)(and f s))#t 0
     (- (length board) 2)
     term ++))
  (and (check-rows board n) (check-colls board n)))

;(define board1 (list (cons 0 2) (cons 1 3) (cons 2 4) (cons 3 0) (cons 4 1)))
;(define board2 (list (cons 0 2) (cons 1 3) (cons 2 4) (cons 3 2)))