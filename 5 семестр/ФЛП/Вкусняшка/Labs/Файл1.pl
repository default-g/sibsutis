
delete:-
        write("������� ������: "),
        read(List),
        write("������� �����: "),
        read(X),
        p(List, X, K),
        write(K).

p([],_,[]).
p([El|T],El,T1):-
                 !,
                 p(T,El,T1).
                 
p([X|T],El,[X|T1]):-
                 p(T,El,T1).
