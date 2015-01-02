#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "recursive.h"
#include "sort.h"
#include "string_algo.h"

/* sort */
int compare_int(const void *x, const void *y) {
	return *((int*)x) - *((int*)y);
}

void print_int_array(int *a, int size) {
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


int main() {
	/*test_ins_sort();*/
	/*test_rev_str();*/

	return 0;
}
