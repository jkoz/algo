#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "recursive.h"
#include "sort.h"
#include "string_algo.h"
#include "dlist.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
#include "chtbl.h"

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
			free(d->name);
		}
		free(d);
	}
}

my_data *my_data_init(my_data *d, char *name, int age) {
	d->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
	strcpy(d->name, name);
	d->age = age;
	d->in = (inner*) malloc(sizeof(inner));
	return d;
}

void test_list() {
	List *list = malloc(sizeof (List));

	list_init(list, my_data_destroy);

	/*initialize 2 elements*/
	my_data *first = malloc(sizeof(my_data));
	list_ins_next(list, NULL, (void*) my_data_init(first, "Tai", 27));
	my_data *second = malloc(sizeof(my_data));
	list_ins_next(list, NULL, (void*) my_data_init(second, "Phung", 27));

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

	my_data *rem;
	dlist_remove(dlist, dlist_tail(dlist), (void**)&rem);
	printf("remove %s\nlist remain:\n", rem->name);
	dlist_print(dlist, my_data_print);
	free(rem);

	dlist_destroy(dlist);
}

/* stack */
void test_stack() {
	Stack *stack= (Stack*) malloc(sizeof(Stack));

	// first element
	printf("\nAdd first element\n");
	my_data *d1 = malloc(sizeof(my_data));
	assert(stack_push(stack, (void*) my_data_init(d1, "Tai", 28)) == 0);
	stack_print(stack, my_data_print);

	// second element
	printf("\nAdd second element\n");
	my_data *d2 = malloc(sizeof(my_data));
	assert(stack_push(stack, (void*) my_data_init(d2, "Phung", 27)) == 0);
	stack_print(stack, my_data_print);
	stack_destroy(stack);
}

void test_queue() {
	Queue *queue = (Queue*) malloc(sizeof(Queue));

	// first element
	printf("\nAdd first element\n");
	my_data *d1= malloc(sizeof(my_data));
	assert(queue_enqueue(queue, (void*) my_data_init(d1, "Tai", 28)) == 0);
	stack_print(queue, my_data_print);

	// second element
	printf("\nAdd second element\n");
	my_data *d2= malloc(sizeof(my_data));
	assert(queue_enqueue(queue, (void*) my_data_init(d2, "Phung", 27)) == 0);
	stack_print(queue, my_data_print);

	stack_destroy(queue);
}

/* set */
int my_data_match(const void *d1, const void *d2) {
	my_data *o1 = (my_data *) d1;
	my_data *o2 = (my_data *) d2;
	int ret = strcmp(o1->name, o2->name);
	return ret == 0;
}

void test_set() {
	Set *set1 = (Set *)malloc(sizeof(Set));

	set_init(set1, my_data_match, my_data_destroy);

	my_data *d1 = malloc(sizeof(my_data));
	set_insert(set1, (void*) my_data_init(d1, "Tai", 28));
	set_print(set1, my_data_print);
	assert(set_size(set1) == 1);

	/*insert same object*/
	set_insert(set1, (void*) d1);
	set_print(set1, my_data_print);
	assert(set_size(set1) == 1);

	my_data *d2 = malloc(sizeof(my_data));
	set_insert(set1, (void*) my_data_init(d2, "Phung", 28));
	assert(set_size(set1) == 2);
	set_print(set1, my_data_print);
}

int hash_string(const void *key) {
	const char *ptr;
	int val;

	val = 0;
	ptr = key;

	/*Hash the key by performing a number of bit operations on it.*/
	while (*ptr != '\0') {
		int tmp;
		val = (val << 4) + (*ptr);
		if ((tmp = (val & 0xf0000000))) {
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		ptr++;
	}

	printf("hash(%s)=%d\n", (char*) key, val);
	return val;
}

/* chain hash table */
int my_data_hash(const void *data) {
	my_data *d = (my_data *) data;
	return hash_string((void*)d->name);
}

void test_chbtl() {
	CHTbl *chtbl = malloc(sizeof(CHTbl));
	chtbl_init(chtbl, 7, my_data_hash, my_data_match, my_data_destroy);

	my_data *d1 = malloc(sizeof(my_data));
	chtbl_insert(chtbl, (void*) my_data_init(d1, "Tai", 27));

	my_data *d2 = malloc(sizeof(my_data));
	chtbl_insert(chtbl, (void*) my_data_init(d2, "Phung", 27));

	my_data *d3 = malloc(sizeof(my_data));
	my_data_init(d3, "Taylorxsdfas", 27);
	chtbl_insert(chtbl, (void*) d3);

	assert(chtbl_size(chtbl) == 3);

	chtbl_print(chtbl, my_data_print);

	printf("remove Taylor...\n");
	chtbl_remove(chtbl, (void **) &d3);
	chtbl_print(chtbl, my_data_print);
	assert(chtbl_size(chtbl) == 2);

	printf("remove Tai...\n");
	chtbl_remove(chtbl, (void **) &d1);
	chtbl_print(chtbl, my_data_print);
	assert(chtbl_size(chtbl) == 1);

	chtbl_destroy(chtbl);
}

int main() {
	/*test_ins_sort();*/
	/*test_rev_str();*/
	/*test_recursive();*/
	/*test_list();*/
	/*test_dlist();*/
	/*test_stack();*/
	/*test_queue();*/
	/*test_set();*/
	test_chbtl();

	return 0;
}
