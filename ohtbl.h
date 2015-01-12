#ifndef OHTBL_H
#define OHTBL_H

typedef struct OHTbl_ {
	int positions;
	void *vacated; /* stored in tablle serve as a indication that a new element may be inserted at that position */
	int size;
	void **table;

	int (*h1)(const void *key);
	int (*h2)(const void *key);
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);

} OHTbl;

int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int (*h2)(const void *key), int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));
void ohtbl_destroy(OHTbl *htbl);
int ohtbl_insert(OHTbl *htbl, const void *data);
int ohtbl_remove(OHTbl *htbl, void **data);
int ohtbl_lookup(const OHTbl *htbl, void **data);
#define ohtbl_size(htbl) ((htbl)->size)
void ohtbl_print(OHTbl *htbl, void (*print)(const void *data));

#endif
