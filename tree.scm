; vi:ai:lisp:sm

(define (insert tree data)
  (cond
    ((null? tree) (list data '() '()))
    ((< data (car tree)) (list (car tree) (insert (cadr tree) data) (caddr tree)))
    ((> data (car tree)) (list (car tree) (cadr tree) (insert (caddr tree) data)))
    (else tree)))

(define (member? tree data)
  (cond
    ((null? tree) #f)
    ((< data (car tree)) (member? (cadr tree) data))
    ((> data (car tree)) (member? (caddr tree) data))
    (else #t)))
