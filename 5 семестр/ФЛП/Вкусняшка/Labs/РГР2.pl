swap:- writeln('Введите имя файла'), read(Filename),
     check_exist(Filename),
     open(Filename,read,F), set_input(F),
     tell('Finish.txt'),
     write_screen(F),
     told,
     close(F).

check_exist(Filename):- exists_file(Filename),!.

check_exist(_):- writeln('Такого файла нет'), fail.

write_screen(_):-at_end_of_stream,!.

write_screen(F):- read_line_to_codes(F,L), string_to_list(S,L),
     write_screen(F), writeln(S).
