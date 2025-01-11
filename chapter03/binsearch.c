#include <stdio.h>

int binsearch(int, int[], int);

main()
{
	/*           0  1  2  3  4  5  6   7   8   9 */
	int v[10] = {2, 4, 5, 6, 6, 7, 8, 20, 40, 100};

	printf("%d -> %d\n", 3, binsearch(3, v, 10));
	printf("%d -> %d\n", 8, binsearch(8, v, 10));
	printf("%d -> %d\n", 6, binsearch(6, v, 10));
	printf("%d -> %d\n", 2, binsearch(2, v, 10));
	printf("%d -> %d\n", 100, binsearch(100, v, 10));
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
		else if (x > v[mid])
			low = mid + 1;
		else    /* found a match */
			return mid;
	}

	return -1;  /* no match */
}
