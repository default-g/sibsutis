

f(L,R):-
        L > R, !.
f(_,R):-
     Chek is R mod 2, Chek == 1, writeln(R), fail.
f(L,R):-
        Next is R - 1, f(L,Next).
        
func1:-
 read(L), read(R), f(L,R).

%2

f2(0,1):-!.
f2(1,1):-!.

f2(X,Y):-
         X1 is X - 1, X2 is X - 2,
         f2(X2,Y2), f2(X1,Y1),
         Y is Y1 + Y2.

func2:-
       repeat,
       writeln('Enter Index'), read(X),
       (X < 0,!;
       f2(X, Y), writeln(Y), fail).

%3
f3(_,_,[],[],[],[]):-!.

f3(L,R,[H|T],[H|T1],S2,S3):-
  H<L,!,
  f3(L,R,T,T1,S2,S3).
  
f3(L,R,[H|T],S1,[H|T2],S3):-
  H=<R,!,
  f3(L,R,T,S1,T2,S3).
f3(L,R,[H|T],S1,S2,[H|T3]):-
  f3(L,R,T,S1,S2,T3).

func3:-
  writeln('Print date'),
  read(S), read(L), read(R),
  checkf3(L,R,S,S1,S2,S3),
  writeln(S1), writeln(S2), writeln(S3).

checkf3(L,R,S,S1,S2,S3):-
  L=<R,!,
  f3(L,R,S,S1,S2,S3).
  
checkf3(L,R,S,S1,S2,S3):-
  f3(R,L,S,S1,S2,S3).
  
%4
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

func4:-
  read(S),
  f4(S, M, K),
  writeln(K).
