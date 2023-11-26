#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define SERIALIZED_FILE_NAME "file.bin"


typedef struct Student {
	char name[50];
	int grades[4];
	struct Student *next;
	struct Student *prev;
} Student;


Student *head = NULL;


Student *create_new_student() {
	Student *new_student = malloc(sizeof(Student));
	printf("Input name >>");
	scanf("%s", new_student->name);
	printf("Input grades >>");
    for (int i = 0; i < 4; i++) {
        scanf( "%d", &new_student->grades[i]);
    }
    new_student->next = NULL;
    new_student->prev = NULL;
    return new_student;
}


int list_length() {
	Student *tmp = head;
	int count = 0;
	while(tmp != NULL) {
		count++;
		tmp = tmp->next;
	}
	return count;
}


void insert_item(Student *student) {
    if (head == NULL) {
        head = student;
    } else {
		Student *tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
        tmp->next = student;
        tmp->next->prev = tmp;
    }
}


void print() {
	Student *tmp = head;
	if (!tmp) {
        printf("List is empty!\n");
		return;
	}
	while (tmp != NULL) {
        printf("%s ", tmp->name);
		for (int i = 0; i < 4; i++) {
            printf("%d ", tmp->grades[i]);
        }
		printf("\n");
		tmp = tmp->next;
	}
}


void delete_element(int position) {
	if (position < 0 || !head) {
		return;
	}
	int current_item_index = 0;
	struct Student *tmp = head;
	for (int i = 0; tmp != NULL && i < position; i++) {
		tmp = tmp->next;
	}
	if (tmp == NULL) {
		return;
	}
    if (head == tmp)
        head = tmp->next;
 
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
   
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    free(tmp);
}


void clear_list() {
	if (!head) {
		return;
	}
	Student *prev = head;

	while(head) {
		head = head->next;
		free(prev);
		prev = head;
	}

}


void serialize() {
	FILE *file = fopen(SERIALIZED_FILE_NAME, "wb");
	Student *tmp = head;
	if (!tmp) {
		return;
	}
	Student *buffer = calloc(list_length(), sizeof(Student));
	int i = 0;
	while(tmp != NULL) {
		Student student_to_copy = *tmp;
		student_to_copy.next = NULL;
		student_to_copy.prev = NULL;
		buffer[i] = student_to_copy;
		tmp = tmp->next;
		i++;
	}
	fwrite(buffer, sizeof(struct Student), list_length(), file);
	fclose(file);
}


Student *clone(Student *student_to_copy) {
	struct Student *new_student = calloc(1, sizeof(struct Student));
	strcpy(new_student->name, student_to_copy->name);
	for(int i = 0; i < 4; i++) {
		new_student->grades[i] = student_to_copy->grades[i];
	}
	return new_student;
}


void deserialize() {
	clear_list();
	FILE *file = fopen(SERIALIZED_FILE_NAME, "rb");
	if (!file) {
		return;
	}

	fseek(file, 0L, SEEK_END);
	unsigned int file_size = ftell(file);
	rewind(file);

	struct Student *students = malloc(file_size);
	fread(&*students, file_size, 1, file);
	
	unsigned int iterations = file_size / sizeof(struct Student);
	for (int i = 0; i < iterations; i++) {
		insert_item(clone(&students[i]));
	}
	
	fclose(file);
}


int main() {
	while (1) {
		printf("\e[1;1H\e[2J");
		print();
		int choice = 0;
		printf("Choose option: \n");
		printf("1. Insert \n");
		printf("2. Delete \n");
		printf("3. Serialize \n");
		printf("4. Deserialize \n");
		scanf("%d", &choice);
		switch (choice) {
			case 1: {
				insert_item(create_new_student());
				break;
			}
			case 2: {
				printf("Input delete position: ");
				int position = 0;
				scanf("%d", &position);
				delete_element(position - 1);
				break;
			}
			case 3: {
				serialize();
				break;
			}
			case 4: {
				deserialize();
				break;
			}
			default: {
				printf("There's such option\n");
			}
		}

	}
	print();
	printf("%d", list_length());
	insert_item(create_new_student());
	print();
	return 0;
}