(defun contains_item (item the_list) (
    cond
        ((null the_list) nil)
        ((equal item (car the_list)) t)
        ((contains_item item (cdr the_list)))
))


; Является ли одно множество подмножеством другого.
(defun is_sublist_of (needle haystack) (
    cond
        ((null haystack) nil)
        ((null needle) t)
        ((contains_item (car needle) haystack)
            (is_sublist_of (cdr needle) haystack))
        (nil)
))

; Возвращающую разность двух множеств, т.е. множество из элементов первого множества, не входящих во второе.
(defun list_diff (A B) (
    cond
        ((null A) A)
        ((contains_item (car A) B) (list_diff (cdr A) B))
        ((cons (car A) (list_diff (cdr A) B)))
))

; Вставляющий перед каждым элементом списка, обладающим определенным свойством, символ *. 
; Проверьте работу функционала для предикатов:
; - неотрицательное число (функциональный аргумент – лямбда выражение);
; - четное число (функциональный аргумент – имя встроенного предиката evenp).
(defun add_* (the_list function) (
    cond
        ((null the_list) nil)
        ((funcall function (car the_list)) 
            (cons '* ( cons (car the_list) (add_* (cdr the_list) function)))
        )
        ((cons (car the_list) (add_* (cdr the_list) function)))
))

(print 'is_sublist_of )


(print (is_sublist_of '(1 2 (3) ) '(1 2 (3) (2) 4) ))
(print (is_sublist_of '() '(1 2 (3) (2) 4) ))
(print (is_sublist_of '(4) '() ))

(print 'list_diff )

(print (list_diff '(1 2 3 4) '() ))

(print 'add_* )

(print (add_* '(1 2 -3 4 -5) #'(lambda (x) (>= x 0)) ))
(print (add_* '(1 2 3 4 5) 'evenp))


