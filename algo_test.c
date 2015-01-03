#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "recursive.h"
#include "sort.h"
#include "string_algo.h"
#include "dlist.h"
#include "list.h"

/* sort */
static int compare_int(const void *x, const void *y) {
	return *((int*)x) - *((int*)y);
}

static void print_int_array(int *a, int size) {
	int i = 0; for (;i < size; i++) printf("%d ", *(a + i));
}

void test_ins_sort() {
	int a[] = {1, 9, 3, 2, 6, 7, 8, 111, 22};
	insert_sort(&a, 9, 4, &compare_int);
	print_int_array(a, 9);
}

/* string_algo */
void test_rev_str() {
	char tmp[] = "  kien  an   ca ";
	char *input = malloc(sizeof(char) * (strlen(tmp)+ 1));
	strcpy(input, tmp);
	printf("Input: '%s'\n", input);


    char *ret = reverse_string1(input);
	printf("Reverse1: '%s'\n", ret);
    ret = reverse_string2(input);
	printf("Reverse2: '%s'\n", ret);
}

/* recursive */
void test_recursive() {
	assert(fact(4) == 24);
	assert(fact2(4, 1) == 24);
}

/* list */
typedef struct inner_ { int a; } inner;
typedef struct my_data_ {
	char *name;
	int age;
	inner *in;
} my_data;

static void my_data_print(void *data) {
	my_data *d = (my_data*) data;
	printf("%s - %d", d->name, d->age);
}

static void my_data_destroy(void *data) {
	my_data *d = (my_data*) data;
	if (data) {
		if (d->in) {
			free(d->in);
		}
		free(d);
	}
}

void test_list() {
	List *list = malloc(sizeof (List));

	list_init(list, my_data_destroy);

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
	list_print(list, my_data_print);

	my_data *rem;
	list_rem_next(list, NULL, (void**)&rem);
	printf("\n>>> Removing %s\nlist remain:\n", rem->name);

	list_print(list, my_data_print);
	free(rem);

	list_destroy(list);
}

/* dlist */
void test_dlist() {
	DList *dlist = (DList*) malloc(sizeof(DList));
	dlist_init(dlist, my_data_destroy);

    // first element
	printf("Add first element\n");
	my_data *first = malloc(sizeof(my_data));
	first->name = "Tai";
	first->age = 28;
	first->in = (inner*) malloc(sizeof(inner));

	assert(dlist_ins_next(dlist, NULL, (void*) first) == 0);
	dlist_print(dlist, my_data_print);

    // second element
	printf("\nAdd second element\n");
	my_data *second = malloc(sizeof(my_data));
	second->name = "Phung";
	second->age = 27;
	second->in = (inner*) malloc(sizeof(inner));

	assert(dlist_ins_prev(dlist, dlist_head(dlist), (void*) second) == 0);
	dlist_print(dlist, my_data_print);


	/*my_data *rem;*/
	/*dlist_remove(dlist, NULL, (void**)&rem);*/
	/*printf("remove %s\nlist remain:\n", rem->name);*/
	/*dlist_print(dlist, my_data_print);*/
	/*free(rem);*/

	dlist_destroy(dlist);
}

int main() {
	/*test_ins_sort();*/
	/*test_rev_str();*/
	/*test_recursive();*/
	test_list();
	test_dlist();

	return 0;
}
