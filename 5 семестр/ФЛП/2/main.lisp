(defun insert_item_in_ordered_list (x L) (
   cond
      ((null L) (list x))
		((> x (car L)) (cons (car L) (insert_item_in_ordered_list x (cdr L))))
		(t (cons x L)) 
))


(defun remove_even (the_list &optional (index 1) ) (
   cond
      ((null the_list) the_list)
      ((evenp index ) (remove_even (cdr the_list) (+ index 1)))
      (t (cons (car the_list) (remove_even (cdr the_list) (+ index 1) )))
))


(defun list_depth(l) (
   cond 
      ((atom l) 0)
      ((null l) 0)
	   (t (max (+ 1 (list_depth(car l))) (list_depth(cdr l)) ) )
))


(print (insert_item_in_ordered_list 7 '(2 3 4 7 )))

(print (remove_even '(1 2 3 4)))

(print (list_depth '( 1 2 (((((*))))) )) )