toy("�����","50").
toy("������","180").
toy("�����","10").
toy("�����","220").
toy("�����������","150").
toy("��������","120").
toy("����������","60").
toy("��������","110").
toy("��������","25").
toy("������ ��� �����","40").

itog:- toy(Name,Cost), findmin(Cost,).

min_list([H|T], Min) :-
    min_list(T, H, Min).

min_list([], Min, Min).
min_list([H|T], Min0, Min) :-
    Min1 is min(H, Min0),
    min_list(T, Min1, Min).
