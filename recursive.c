#include <assert.h>
#include <stdio.h>
#include "recursive.h"

/** recursive 
 * winding phase : do nothing
 * unwinding phase: calculate value */
int fact(int n) {
	if (n < 0) {
		return 0;
	} else if (n == 0) {
		return 1;
	} else {
		return n*fact(n - 1); /* final return is here */
	}
}

/** tail recursive - i.e. fact2(4, 1)
 * winding phase : calculate
 * unwinding phase: do nothing */
int fact2(int n, int a) {
	if (n < 0) {
		return 0;
	} else if (n == 0) {
		return 1;
	} else if (n == 1) {
		return a; /* final return is here */
	} else {
		return fact2(n - 1, a*n);
	}
}
