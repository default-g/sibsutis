#include "stdio.h"
#include "list_functions.h"
int main() {
    Student *students = calloc(1, sizeof(Student));
    while(1) {
       clear_list(&students);
    }
    return 0;
}
