#include <stdio.h>

int find_with_goto(int [], int, int [], int);
int find_without_goto(int [], int, int [], int);

main()
{
	int a[5] = {1, 2, 5, 7, 13};
	int b[4] = {2, 4, 8, 16};
	int c[2] = {0, 1024};

	if (find_with_goto(a, 5, b, 4))
		printf("Arrays a and b have a common element\n");
	else
		printf("No common element found in arrays a and b\n");

	if (find_without_goto(a, 5, b, 4))
		printf("Arrays a and b have a common element\n");
	else
		printf("No common element found in arrays a and b\n");

	printf("\n");
	if (find_with_goto(a, 5, c, 2))
		printf("Arrays a and c have a common element\n");
	else
		printf("No common element found in arrays a and c\n");

	if (find_without_goto(a, 5, c, 2))
		printf("Arrays a and c have a common element\n");
	else
		printf("No common element found in arrays a and c\n");

	return 0;
}

int find_with_goto(int a[], int n, int b[], int m)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (a[i] == b[j])
				goto found;
	/* didn't find any common element */
	printf("No element found!\n");
	return 0;
	found:
		/* got one a[i] == b[j] */
		printf("a[%d] == b[%d] == %d\n", i, j, a[i]);
		return 1;
}

int find_without_goto(int a[], int n, int b[], int m)
{
	int i, j, found;

	found = 0;
	for (i = 0; i < n && !found; i++)
		for (j = 0; j < m && !found; j++)
			if (a[i] == b[j])
				found = 1;
	if (found) {
		/* got one a[i-1] == b[j-1] */
		printf("a[%d] == b[%d] == %d\n", i-1, j-1, a[i-1]);
		return 1;
	} else {
		/* didn't find any common element */
		printf("No element found!\n");
		return 0;
	}
}
