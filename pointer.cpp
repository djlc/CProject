#include <stdio.h>

int main() {
	int a = 10;
	int* b;
	printf("aのアドレスは%p\n", &a);
	printf("bのアドレスは%p\n", &b);
	*b = 20;
	*(b+sizeof(int)) = 30;
	printf("b = %d\n", *b);
	printf("b[0] = %d, b[1] = %d\n", *b, *(b+sizeof(int)));
	return 0;
}
