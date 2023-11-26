2
(defun contain (X A)
  (if (null X) nil 
      (or (equal (car X) A) (contain (cdr X) A))))

(defun include (Y X) 
  (if (null X) T 
     (and (contain Y (car X)) (include Y (cdr X))))) 
    
(include '(5 3 4 4 8 9) '(5 7 4 9))

6
(defun raz (a b)
  (cond ((null a) nil)
        ((member (car a) b) (raz (cdr a) b))
        ((cons (car a) (raz (cdr a) b)))))
 
(raz '(1 2 3 4 5) '(3 4 5))

9
(defun ins* (func lst) 
	(cond ((null lst) nil)
		((funcall func (car lst)) (cons '* (cons (car lst) (ins* func (cdr lst)))))
        (t (cons (car lst) (ins* func (cdr lst))))))
 
(ins* #'(lambda (x) (>= x 0)) '(1 2 3 0 -1 -2 9 -3 -8))
(ins* #'evenp '(1 2 3 4 5 6))
(ins* #'evenp '(1 2 3 4 5 6 8 10 11))