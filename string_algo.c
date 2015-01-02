#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_algo.h"

/** Use buffer memory */
char *reverse_string1(char *str) {

	/* return length of str (excluding \0) */
	int len = strlen(str);

	/* return reverse string */
	char *ret = malloc(sizeof(char) * (len + 1));

	/* point to head of returned string*/
	char *dst = ret;

	/* point to begin and ended of a particular word (use for copy word) */
	char *begin, *end;

	/* point to last char of input */
	char *src = &str[len - 1];

	while (src >= &str[0]) {
		if (*src == ' ') {
			*dst = *src;
			dst++; src--;
		} else {
			/* identify the last character of a word */
			end = src;

			/* finding begining of the word */
			while(*src != ' ' && src >= &str[0]) {
				src--;
			}

			/* identify begin of the word */
			begin = src + 1;

			/* copy word from begin to end (including ' ')*/
			while (begin <= end) {
				*dst = *begin;
				begin++; dst++;
			}
		}
	}

	/* terminate string with NULL character */
	*dst = '\0';

	return ret;
}

/** Not use buffer memory */
char *reverse_string2(char *str) {
	/* return length of str (excluding \0) */
	int len = strlen(str);

	/* swap var */
	char tmp;

	char *begin = str;
	char *end = &str[len - 1];

	/* swap begin and end characters */
	while (begin <= end) {
		tmp = *end;
		*end = *begin;
		*begin = tmp;
		begin++; end--;
	}

	/* reinitialize begin and end */
	begin = str; end = &str[len - 1];

	char *bw, *ew;
    while (begin <= end) {
		if (*begin == ' ') {
			begin++;
		} else {
			/* itentify begin word */
			bw = begin;

			/* find end word */
			while (*begin != ' ' && begin <= end) begin++;

			/* identify end word */
			ew = begin - 1;

			/* swap bw and ew characters */
			while (bw <= ew) {
				tmp = *ew;
				*ew = *bw;
				*bw = tmp;
				bw++; ew--;
			}
		}
	}

	return str;
}

int main() {
	char tmp[] = "  kien  an   ca ";
	char *input = malloc(sizeof(char) * (strlen(tmp)+ 1));
	strcpy(input, tmp);
	printf("Input: '%s'\n", input);


    char *ret = reverse_string1(input);
	printf("Reverse1: '%s'\n", ret);
    ret = reverse_string2(input);
	printf("Reverse2: '%s'\n", ret);

	return 0;
}
