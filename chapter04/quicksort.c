#include <stdio.h>

int numbers[] = { 9, 5, 2, 8, 3, 0, 4, 1, 7, 6 };
int len = sizeof(numbers)/sizeof(numbers[0]);

void qsort(int [], int, int);
void print_array(int [], int);

main()
{


	printf("Unsorted original array\n");
	printf("=======================\n");
	print_array(numbers, len);
	qsort(numbers, 0, len-1);
	printf("Sorted array\n");
	printf("============\n");
	print_array(numbers, len);

	return 0;
}

/* qsort: sort v[left]...v[right] into increaseing order */
void qsort(int v[], int left, int right)
{
	int i, last;
	void swap(int v[], int i, int j);
	static int step = 0;

	printf(
		"step %2d: left = %d, pivot = %d, right = %d\n",
		step++, left, (left+right)/2, right
	);

	if (left >= right)     /* do nothing if array contains */
		return;            /* fewer than two elements */
	print_array(v, len);
	printf("-> Swaping %d and %d\n", v[left], v[(left+right)/2]);
	swap(v, left, (left+right)/2); /* move partition elem */
	print_array(v, len);
	last = left;                   /* to v[0] */
	for (i = left+1; i <= right; i++)  /* partition */
		if (v[i] < v[left]) {
			print_array(v, len);
			printf("Swaping %d and %d\n", v[last+1], v[i]);
			swap(v, ++last, i);
			print_array(v, len);
			printf("\n");
		}
	print_array(v, len);
	printf("Swaping %d and %d\n", v[left], v[last]);
	swap(v, left, last);         /* restore partition element */
	print_array(v, len);
	printf("Calling qsort(v, %d, %d)\n", left, last-1);
	qsort(v, left, last-1);
	printf("Calling qsort(v, %d, %d)\n", last+1, right);
	qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* print_array: prints the array of the given size */
void print_array(int v[], int size)
{
	int i;
	for (i = 0; i < size; i ++)
		printf("%d ", v[i]);
	printf("\n");
}
