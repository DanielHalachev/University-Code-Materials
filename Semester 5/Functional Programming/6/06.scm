(define m '((1 2 3 4) (5 6 7 8) (9 10 11 12)))

;; matrix-ref
(define (matrix-ref m i j)
  (list-ref (list-ref m i) j))

;; (mat? m)
(define (all? pred? l)
  (if (null? l)
      #t
      (and (pred? (car l)) (all? pred? (cdr l)))))

(define (mat? m)
  (and (not (null? m))
       (not (null? (car m)))
       (> (length m) 2)
       (let ((width (length (car m))))
         (all? (lambda (row)(= width (length row))) (cdr m)))))

;; delete row/column
(define (delete-from-list l i)
  (cond ((null? l) l)
        ((= 0 i) (cdr l))
        (else (cons (car l) (delete-from-list (cdr l) (- i 1))))))

(define (delete-column i m)
  (map (lambda (row) (delete-from-list row i)) m))

(define (delete-row i m)
  (delete-from-list m i))

;; get row/column
(define (get-row i m)
  (cond ((null? m) m)
        ((= 0 i) (car m))
        (get-row (-i 1) (cdr m))))

(define (get-col i m)
  (cond ((null? m) m)
        (else (map (lambda (row) (list-ref row i)) m))))

;; get element
(define (get-element i j m)
  (list-ref (get-row i m) j))


;; transpose
(define (transpose m)
  (if (null? (get-row 0 m))
      '()
      (cons (get-col 0 m) (transpose (delete-column 0 m)))))

;; map-matrix
(define (map-matrix f m)
  (map (lambda (row) (map (lambda (i)(f i)) row)) m))

;; width, height, dimensions
(define (width m)
  (if (null? m)
      0
      (length (car m))))

(define height length)

(define (dimensions m)
  (cons (width m) (height m)))

;; main-diagonal
(define (main-diagonal m)
  (if (null? m)
      m
      (cons (car (car m)) (main-diagonal (delete-column 0 (delete-row 0 m))))))

;; reverse-columns
(define (reverse-columns m)
  (map (lambda (row) (reverse row)) m))

;; all columns
(define (all-columns? p? m)
  (if (or (null? m) (null? (car m)))
      #t
      (and (p? (get-col 0 m)) (all-columns? p? (delete-column 0 m)))))

;; prime-in-each-columns
(define (any? p? l)
  (if (null? l)
      #f
      (or (p? (car l)) (any? p? (cdr l)))))

(define (accumulate op nv a b term next)
  (if (> a b) nv
          (op (term a) (accumulate op nv (next a) b term next))))

(define (prime? n)
  (if (< n 4)
      #t
      (accumulate (lambda(f s)(and f s))
              #t
              2 (sqrt n)
              (lambda(i)(not (= 0 (remainder n i))))
              (lambda(i)(+ i 1)))))

(define (prime-in-each-column? m)
  (all-columns? (lambda(col)(any? prime? col)) m))


;; multiply
(define (multiply-lists l1 l2)
  (apply + (map * l1 l2)))

(define (multiply m1 m2)
  (let ((m2new (transpose m2)))
    (map (lambda (row) (map (lambda (column)(multiply-lists row column)) m2new)) m1)))
 
;; find-columns - wrong
(define (find-columns m)
  (define (pred? col)
    (all? (lambda (c)(any? (lambda (row)(member c row)) m)) col))
  (apply +
         (map (lambda (col)
                (if (pred? col)
                    1
                    0))
              (transpose m))))