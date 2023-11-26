#ifndef LIST_FUNCTIONS
#define LIST_FUNCTIONS

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef struct Student {
	char name[50];
	int grades[4];
	struct Student *next;
	struct Student *prev;
} Student;

#define SERIALIZED_FILE_NAME "file.bin"

Student *create_new_student();
int list_length(Student*);
void insert_item(Student*, Student**);
void print(Student*);
void delete_element(int position, Student **);
void clear_list(Student**);
void serialize(Student*);
Student *clone(Student*);
void deserialize(Student**);


#endif