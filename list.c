#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

void list_init(List *list, void (*destroy)(void *data)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	return;
}

void list_destroy(List *list) {
	void *data;

	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
	ListElmt *new_element;
	if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return -1;

	new_element->data = (void *)data;

	if (element == NULL) {
		if (list_size(list) == 0)
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	else {
		if (element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;

	return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
	ListElmt *old_element;
	if (list_size(list) == 0)
		return -1;

	if (element == NULL) { /* remove from the head of the list */
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;
		if (list_size(list) == 1)
			list->tail = NULL;
	}
	else { /* remove somewhere else */
		if (element->next == NULL)
			return -1;
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;
		if (element->next == NULL)
			list->tail = element;
	}

	free(old_element);
	list->size--;

	return 0;
}

#if _RUN_TEST
/* run test with gcc -D_RUN_TEST list.h list.c */

typedef struct inner_ { int a; } inner;
typedef struct my_data_ {
	char *name;
	int age;
	inner *in;
} my_data;

static void destroy_data(void *data) {
	my_data *d = (my_data*) data;
	if (data) {
		if (d->in) {
			free(d->in);
		}
		free(d);
	}
}
void print_list(List *list) {
    ListElmt *it = list_head(list);
	while (it != NULL) {
		my_data *d = (my_data*) it->data;
		if (it->data)
			printf("%s - %d\n", d->name, d->age);
		it = it->next;
	}
}

int main() {
	List *list = malloc(sizeof (List));

	list_init(list, destroy_data);

    // freeable struct
	my_data *first = malloc(sizeof(my_data));
	first->name = "Tai";
	first->age = 28;
	first->in = (inner*) malloc(sizeof(inner));

	my_data *second = malloc(sizeof(my_data));
	second->name = "Phung";
	second->age = 27;
	second->in = (inner*) malloc(sizeof(inner));

	list_ins_next(list, NULL, (void*) first);
	list_ins_next(list, NULL, (void*) second);

	/* printf list */
	print_list(list);

	my_data *rem;
	list_rem_next(list, NULL, (void**)&rem);
	printf("remove %s\nlist remain:\n", rem->name);

	print_list(list);
	free(rem);

	list_destroy(list);
}
#endif
