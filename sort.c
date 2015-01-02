#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/* Insert sort O(n^2) */
int insert_sort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2)) {
	char *a = data;
	void *key;
	int i, j;

	/*Allocate storage for the key element.*/
	if ((key = malloc(esize)) == NULL) return -1;

	for (j = 1; j < size; j++) {
		memcpy(key, &a[j * esize], esize);

		/*Determine the position at which to insert the key element.*/
		for (i = j - 1; i >= 0 && compare(&a[i * esize], key) > 0; i--) {
			memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
		}

		memcpy(&a[(i + 1) * esize], key, esize);
	}
	/*Free the storage allocated for sorting.*/
	free(key);
	return 0;
}

