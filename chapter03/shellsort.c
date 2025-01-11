#include <stdio.h>

#define N 12

void shellsort(int [], int);

main()
{
	int data[N] = { 62, 83, 18, 53, 7, 17, 95, 86, 47, 69, 25, 28 };
	int i;

	printf("Before sort:\n");
	for (i = 0; i < N; i++)
		printf("data[%2d] = %2d\n", i, data[i]);

	shellsort(data, N);
	printf("After sort:\n");
	for (i = 0; i < N; i++)
		printf("data[%2d] = %2d\n", i, data[i]);

	return 0;
}

/* shellsort: sort v[0]..v[n-1] into increasing order */
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}
