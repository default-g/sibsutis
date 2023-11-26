maxx:-
     open("Start.txt",read,F),
     set_input(F),
     getStrings(F,List),
     close(F),
     getMaxLengthList(List,Size),
     tell('Finish.txt'),
     copyWithSize(List,Size),
     told.

getStrings(_,_):- at_end_of_stream,!.

getStrings(FRead,NewList):-read_line_to_codes(FRead,L),
     string_to_list(S,L),
     atomic_list_concat(L1," ",S),
     getStrings(FRead,List2),
     append([L1,List2],NewList).	

getMaxLengthList([Head|Tail],Length):-string_length(Head,L),
     getMaxLengthList(Tail,L1),
     (L @> L1 -> Length is L; Length is L1).

getMaxLengthList([],0).

copyWithSize([],_).

copyWithSize([Head|Tail],MaxSize):-
     string_length(Head,L),
     (L \=@= MaxSize; writeln(Head)),
     copyWithSize(Tail,MaxSize).
