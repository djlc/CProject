#include <stdio.h>

int main() {
	int *b = new int[100000];
	for (int i = 0; i < 100000; i++) {
		*(b+i) = i;
		printf("b[%d] = %d,\t *(b+%d) = %d\n", i, b[i], i, *(b+i));
	}
	return 0;
}
