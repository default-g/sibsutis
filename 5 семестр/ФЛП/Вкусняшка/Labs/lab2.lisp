7
(defun task1 (x L)
	(cond ((null L) (cons x nil))
		((> x (car L)) (cons (car L) (task1 x (cdr L))))
		((cons x L))))

(task1 10 '(1 3 4 6 9))


17
(defun task2(x l)
	(cond ((null l) l)
		((equal (rem x 2) 0) (append (cond ((equal (cdr l) nil) (remove nil (list (cdr l)))) (t (task2 (+ x 1) (cdr l))))))
		(t (append (list (car l)) (task2 (+ x 1) (cdr l))))))

(task2 '1 '(-2 6 s -1 4 f 0 z x r))
(task2 ' (1 3 2 3 4 5 6 7 8 9 10 11 12))


27
(defun task3(l)
	(cond ((atom l) 0) ((null l) 0)
	(t (max (+ 1 (task3(car l))) (task3(cdr l))))))

(task3 '((((1))) 2 (3 4)))
(task3 '((1) 2 (3 (((5))) 4)))
(task3 '(1 (2 (3 (4 5 (6))))))

