;; Brigade 7


(defun solve_1() (
    print (car (
        cdaadr '((1) ((2 *)) (3 (4)))
    ))
))

(defun solve_2() (
    print (
        list '(+ 1 2) '() '(+ 1)
)))


(defun solve_3_1() ( 
    print (
        cons (cons 1 (cons 2 (cons (cons (cons 3 nil) nil) nil))) nil
)))

(defun solve_3_2() (
    print (
        list (
            list '1 '2 (list (list 3))
    )
)))

(defun solve_4(the_list) (
     print (
         append (append(list (car my_list ) (car (last the_list))) (butlast (cddr the_list))) (list (cadr (butlast the_list)))
     )
 ))

(defvar my_list '(1 2) )


(solve_1)

(solve_2)

(solve_3_1)

(solve_3_2)

(solve_4 my_list)

(solve_4_2 my_list)
