start :-
     write("¬ведите список: "),
     read(List),
     separate_even_odd(List, X, Y),
     writeln(X),
     writeln(Y).

separate_even_odd([], [], []).

separate_even_odd([X|Xs], [X|Even], Odd) :-
    0 is X mod 2,
    separate_even_odd(Xs, Even, Odd).

separate_even_odd([X|Xs], Even, [X|Odd]) :-
    1 is X mod 2,
    separate_even_odd(Xs, Even, Odd).
