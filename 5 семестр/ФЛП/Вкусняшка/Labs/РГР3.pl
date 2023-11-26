toy("Кукла","50").
toy("Собака","180").
toy("Мишка","10").
toy("Робот","220").
toy("Автостоянка","150").
toy("Самосвал","120").
toy("Расскраска","60").
toy("Диванчик","110").
toy("Чаепитие","25").
toy("Одежда для кукол","40").

itog:- toy(Name,Cost), findmin(Cost,).

min_list([H|T], Min) :-
    min_list(T, H, Min).

min_list([], Min, Min).
min_list([H|T], Min0, Min) :-
    Min1 is min(H, Min0),
    min_list(T, Min1, Min).
