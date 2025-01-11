/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with
 * only one test inside the loop and measure the difference in run-time. □
 */

#include <stdio.h>

int binsearch(int, int[], int);
int binsearch_high(int, int[], int);

main()
{
	/*           0  1  2  3  4  5  6   7   8   9 */
	int v[10] = {2, 4, 5, 6, 6, 7, 8, 20, 40, 100};

	printf("%d -> %d\n", 3, binsearch(3, v, 10));
	printf("%d -> %d\n", 8, binsearch(8, v, 10));
	printf("%d -> %d\n", 6, binsearch(6, v, 10));
	printf("%d -> %d\n", 2, binsearch(2, v, 10));
	printf("%d -> %d\n", 100, binsearch(100, v, 10));
	printf("%d -> %d\n", 3, binsearch_high(3, v, 10));
	printf("%d -> %d\n", 8, binsearch_high(8, v, 10));
	printf("%d -> %d\n", 6, binsearch_high(6, v, 10));
	printf("%d -> %d\n", 2, binsearch_high(2, v, 10));
	printf("%d -> %d\n", 100, binsearch_high(100, v, 10));
	return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else /* if (x >= v[mid]) */
			low = mid + 1;
	}
	if (v[mid] == x)
		return mid;
	else if (v[mid-1] == x)
		return mid-1;
	return -1;  /* no match */
}

/* alternatively put the equal in the high branch */
int binsearch_high(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x <= v[mid])
			high = mid - 1;
		else /* if (x > v[mid]) */
			low = mid + 1;
	}
	if (v[mid] == x)
		return mid;
	else if (v[mid+1] == x)
		return mid+1;
	return -1;  /* no match */
}
