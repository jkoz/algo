#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ohtbl.h"

/*Reserve a sentinel memory address for vacated elements.*/
static char vacated;

int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key),
		int (*h2)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data)) {
	/* initialize an array of void pointers (according to positions) */
	if ((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL)
		return -1;

	/*Initialize each position.*/
	int i;
	htbl->positions = positions;
	for (i = 0; i < htbl->positions; i++)
		htbl->table[i] = NULL;

	/*Set the vacated member to the sentinel memory address reserved for this.*/
	htbl->vacated = &vacated;

	htbl->h1 = h1;
	htbl->h2 = h2;
	htbl->match = match;
	htbl->destroy = destroy;

	htbl->size = 0;

	return 0;
}

void ohtbl_destroy(OHTbl *htbl) {
	if (htbl->destroy != NULL) {
		int i;
		for (i = 0; i < htbl->positions; i++) {
			if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
				htbl->destroy(htbl->table[i]);
		}
	}
	free(htbl->table);
	memset(htbl, 0, sizeof(OHTbl));
}

int ohtbl_insert(OHTbl *htbl, const void *data) {
	void *temp;
	int position, i;

	/*Do not exceed the number of positions in the table.*/
	if (htbl->size == htbl->positions)
		return -1;

	/* Do nothing if the data is already in the table. */
	temp = (void *)data;
	if (ohtbl_lookup(htbl, &temp) == 0)
		return 1;

	/*Use double hashing to hash the key*/
	for (i = 0; i < htbl->positions; i++) {
		position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
		if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated) {
			htbl->table[position] = (void *)data;
			htbl->size++;
			return 0;
		}
	}

	/*Return that the hash functions were selected incorrectly.*/
	return -1;
}

int ohtbl_remove(OHTbl *htbl, void **data) {
	int position, i;
	for (i = 0; i < htbl->positions; i++) {
		position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
		if (htbl->table[position] == NULL) {
			/*Return that the data was not found*/
			return -1;
		} else if (htbl->table[position] == htbl->vacated) {
			/* search beyond vacated positions */
			continue;
		} else if (htbl->match(htbl->table[position], *data)) {
			*data = htbl->table[position];
			htbl->table[position] = htbl->vacated;
			htbl->size--;
			return 0;
		}
	}

	/*Return that the data was not found*/
	return -1;
}
int ohtbl_lookup(const OHTbl *htbl, void **data) {
	int position, i;
	for (i = 0; i < htbl->positions; i++) {
		position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
		if (htbl->table[position] == NULL) {
			/*Return that the data was not found.*/
			return -1;
		}
		else if (htbl->match(htbl->table[position], *data)) {
			/**  Pass back the data from the table. */
			*data = htbl->table[position];
			return 0;
		}
	}

	/*Return that the data was not found. */
	return -1;
}

void ohtbl_print(OHTbl *htbl, void (*print)(const void *data)) {
	printf("OHTbl: size=%d{ ", htbl->size);
	int i;
	for (i = 0; i < htbl->positions; i++) {
		if (htbl->table[i] == NULL) {
			printf("NULL, ");
		} else if (htbl->table[i] == htbl->vacated) {
			printf("VACATED, ");
		} else {
			print(htbl->table[i]);
			printf(", ");
		}
	}

	printf("}\n");
}
