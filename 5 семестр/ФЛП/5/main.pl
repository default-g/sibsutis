
:-use_module(library(prolog_stack)).

one:-
    write("Введите наибольшую границу: "),
    read(L),
    write("Введите наименьшую границу: "),
    read(R),
        format("[~a : ~a]~n",[L, R]),
    recurs(L,R).

recurs(L,R):-
    L >= R,
    L mod 2 =\= 0 -> format("~a ", L),
    L1 is L - 1,
    recurs(L1 ,R);
     L >= R,
    L1 is L - 1,
        recurs(L1 ,R).



two:-
        repeat,
        write("Введите число: "),
        read(X),
        (X < 0, !;
        fib(X, S), write(S), nl, fail).

fib(0, 1):- !.
fib(1, 1):- !.
fib(2, 1):- !.
fib(X, S) :-
    X > 1,
    X1 is X - 1,
    fib(X1, S1),
    X2 is X - 2,
    fib(X2, S2),
    S is S1 + S2.



three:-
        write("Введите список: "),
        read(List),
        write("Введите первое число: "),
        read(B),
        write("Введите второе число: "),
        read(C),
        L1 = [],
        L2 = [],
        L3 = [],
        (B > C, B1 is C, C1 is B; B1 is B, C1 is C),
        first(List, B1, C1, L1, L2, L3).

first(List, B, C, L1, L2, L3):-
        List = [Head|Tail],
        (Head > C, append([Head], L2, L22); L22 = L2),
        (Head < B, append([Head], L1, L11); L11 = L1),
        (Head =< C, Head >= B, append([Head], L3, L33); L33 = L3),
        select(Head, List, List2),
        (List2 \== [], first(List2, B, C, L11, L22, L33),!;

    reverse(L11, L1_REVERSED),
    reverse(L22, L2_REVERSED),
    reverse(L33, L3_REVERSED),

    write(L1_REVERSED),
    write(' '),
    write(L3_REVERSED),
    write(' '),
    write(L2_REVERSED)).


in_sort([ ],[ ]).
in_sort([X|Tail], Sort_list):-
        in_sort(Tail, Sort_tail),
        insert(X, Sort_tail, Sort_list).

insert(X,[Y|Sort_list],[Y|Sort_list1]):-
        X@>Y,!,
        insert(X, Sort_list, Sort_list1).

insert(X, Sort_list, [X|Sort_list]).


f4([],0,[]):-!.
f4([H|T],M,K):-
  length([H|T], N),
  delete(T, H, T2),
  length(T2, N2),
  M1 is N - N2,
  f4(T2, M2, K2),
  chek(H, M1, M2, K2, M, K).
  
chek(H, M1, M2, K2, M, K):-
  M1<M2,!,
  K = K2,
  M = M2.

chek(H, M1, M2, K2, M, K):-
  M1 =:= M2, !,
  K = [H|K2],
  M=M1.

chek(H, M1, M2, K2, M, K):-
 M = M1,
 K = [H].

four :-
  read(S),
  f4(S, M, K),
  subtract(S, K, K2),
  f4(K2, M2, K3),
  append(K, K3, Result),
  write(Result).



