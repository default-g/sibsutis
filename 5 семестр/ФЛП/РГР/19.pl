
repeated_elements(List, Repeated) :-
 repeated_elements(List, [], Repeated).
    
repeated_elements([], Repeated, Repeated) :- !.
repeated_elements([Head|Tail], Buf, Repeated):-
    member(Head, Tail),
    not(member(Head, Buf)), !,
    repeated_elements(Tail, [Head|Buf], Repeated);
    repeated_elements(Tail, Buf, Repeated).

task1:-
    read(X),
    repeated_elements(X, RESULT),
    write(RESULT).

task2:- open('input.txt', read, F),
    set_input(F),
    write_screen(F, Res1),
    delete(Res1, "", Res),
    writeln(Res),
    countWords(Res, R1),
    writeln(R1),
    close(F),
    writeInFile(R1).

writeLines([]).
writeLines([H|T]) :- writeln(H),
                     writeLines(T).

writeInFile(L) :- tell('output.txt'),
  writeLines(L),
  told.

countWords([], _).
countWords([H|T], Result):-
  delete([H|T], H, T1),
  writeln(T1),
  length(T, Len1),
  length(T1, Len2),
  Countt is Len1 - Len2 + 1,
  string_concat(H, " - ", Curr1),
  string_concat(Curr1, Countt, Curr2),
  string_concat(Curr2, " повторов", Curr3),
  countWords(T1, Res),
  append(Res, [Curr3], Result).




write_screen(_,_):- at_end_of_stream.
write_screen(F, Result):- read_line_to_codes(F, L),
  string_to_list(S, L),
  write_screen(F, Res),
  split_string(S,' ','',L1),
  append(Res, L1, Result).

