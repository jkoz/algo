#include "chtbl.h"
#include <string.h>
#include <stdio.h>

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data)) {
	if ((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL)
		return -1;

	/*initialize buckets*/
	htbl->buckets = buckets;

	int i;
	for (i = 0; i < htbl->buckets; i++)
		list_init(&htbl->table[i], destroy);

	htbl->h = h;
	htbl->match = match;
	htbl->destroy = destroy;

	htbl->size = 0;
	return 0;
}

void chtbl_destroy(CHTbl *htbl) {
	int i = 0;
	for (i = 0; i < htbl->buckets; i++) {
		list_destroy(&htbl->table[i]);
	}
	free(htbl->table);
	memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl *htbl, const void *data) {
	void *temp;
	int bucket, retval;

	/*Do nothing if the data is already in the table.*/
	temp = (void *)data;
	if (chtbl_lookup(htbl, &temp) == 0)
		return 1;

	/*hash the key*/
	bucket = htbl->h(data) % htbl->buckets;

	/*insert data to buckets*/
	if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
		htbl->size++;

	return retval;
}

int chtbl_remove(CHTbl *htbl, void **data) {
	ListElmt *element, *prev;
	int bucket;

	/*hash the key*/
	bucket = htbl->h(*data) % htbl->buckets;

	/*Search for the data in the bucket.*/
	prev = NULL;
	for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {
		if (htbl->match(*data, list_data(element))) {
			if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
				htbl->size--;
				return 0;
			}
			else {
				return -1;
			}
		}
		prev = element;
	}

	/*data not found*/
	return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data) {
	ListElmt *element;
	int bucket;

	/*hash the key*/
	bucket = htbl->h(*data) % htbl->buckets;

	/*search for data in buckets*/
	for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {
		if (htbl->match(*data, list_data(element))) {
			*data = list_data(element);
			return 0;
		}
	}

	/*data not found*/
	return -1;
}

void chtbl_print(CHTbl *htbl, void (*print)(void *data)) {
	int i;
	for (i = 0; i < htbl->buckets; i++) {
		printf("Bucket %i: ", i);
		list_print(&htbl->table[i], print);
		printf("\n");
	}
}
