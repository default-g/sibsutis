
calc(0, []).
calc(N, [N|Xs]) :- 
    N > 0,
    N1 is N - 1,
    calc(N1, Xs).

use(N, X1) :-
    calc(N, X),
    reverse(X, X1).