#include "lib/list_functions.h"

int main() {
	Student *list = NULL;
	while (1) {
		printf("\e[1;1H\e[2J");
		print(list);
		int choice = 0;
		printf("Choose option: \n");
		printf("1. Insert \n");
		printf("2. Delete \n");
		printf("3. Serialize \n");
		printf("4. Deserialize \n");
		scanf("%d", &choice);
		switch (choice) {
			case 1: {
				insert_item(create_new_student(), &list);
				break;
			}
			case 2: {
				printf("Input delete position: ");
				int position = 0;
				scanf("%d", &position);
				delete_element(position - 1, &list);
				break;
			}
			case 3: {
				serialize(list);
				break;
			}
			case 4: {
				deserialize(&list);
				break;
			}
			default: {
				printf("There's such option\n");
			}
		}

	}

	return 0;
}