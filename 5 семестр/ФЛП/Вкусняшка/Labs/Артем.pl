tesst:-
open("Start.txt",read,F),
set_input(F),
getStrings(F,List),!,
close(F),
getMaxLengthList(List,Size),
copyWithSize(List,Size,NewList),
tell('Finish.txt'),
writeString(NewList),
told
.

getStrings(_,_):-at_end_of_stream,!.
getStrings(FRead,NewList):-read_line_to_codes(FRead,L),
string_to_list(S,L),
split_string(S," "," ",L1),
getStrings(FRead,List2),
append([L1,List2],NewList)
.

getMaxLengthList([Head|Tail],Length):-string_length(Head,L),getMaxLengthList(Tail,L1),(L @> L1 -> Length is L;Length is L1).
getMaxLengthList([],0).

copyWithSize([],_,[]).
copyWithSize([Head|Tail],MaxSize,NewList):-
string_length(Head,L),
(L =@= MaxSize -> append([[]],List);append([[Head]],List)),
copyWithSize(Tail,MaxSize,List1),
append([List,List1],NewList).

writeString([]).
writeString([Head|Tail]):- write(Head),write(" "),writeString(Tail).
