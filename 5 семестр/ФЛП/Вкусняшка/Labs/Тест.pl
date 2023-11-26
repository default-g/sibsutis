readFromFile(File):-
    open(File,read,Stream),
    read_line_to_codes(Stream,L),
    string_to_list(S,L),
    writeln(S)
    process_the_stream(Char1,Stream),
    close(Stream).

% Exit condition
process_the_stream(end_of_file,_):-
    !.

process_the_stream(Char,Stream):-
    print(Char),
    writeln(Char),
    get_char(Stream,Char2),
    process_the_stream(Char2,Stream).


main:-
    FilePath = 'toys.txt',
    readFromFile(FilePath).
