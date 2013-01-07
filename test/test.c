#include <stdio.h>

void swap(int * i, int * j) {
	int temp;
	temp = *i;
	*i = *j;
	*j = temp;
}

int test1() {
	int i, j;
	i = 4;
	j = 5;
	printf("\nTest1\n\n");
	printf("i is set to %d\n", i);
	printf("j is set to %d\n", j);
	swap(&i, &j);
	if (i == 5 && j == 4) {
		printf("SUCCESS\n");
		return 0;
	}
	else {
		return 1;
	}
}

int main(void) {
	int result = 0;
	 test1();
	return result;
}