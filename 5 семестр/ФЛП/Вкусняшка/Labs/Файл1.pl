
delete:-
        write("¬ведите список: "),
        read(List),
        write("¬ведите число: "),
        read(X),
        p(List, X, K),
        write(K).

p([],_,[]).
p([El|T],El,T1):-
                 !,
                 p(T,El,T1).
                 
p([X|T],El,[X|T1]):-
                 p(T,El,T1).
