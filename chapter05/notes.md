# Pointers

The unary operator `&` gives the address of an object, so the statement

```C
p = &c;
```

assigns the address of c to the variable p, and p is said to "point to" c.  The
`&` operator only applies to objects in memory: variables and array elements.
It cannot be applied to expressions, constants, or `register` variables.

The unary operator `*` is the _indirection_ or _dereferencing_ operator; when
applied to a pointer, it access the object the pointer points to.

```C
int x = 1, y = 2, z[10];
int *ip;          /* ip is a pointer to int */

ip = &x;          /* ip now points to x */
y = *ip;          /* y is now 1 */
*ip = 0;          /* x is now 0 */
ip = &z[0]        /* ip now points at z[0] */
```

The declaration of the pointer ip `int *ip;` is intended as a mnemonic; it says
that the expresion `*ip` is an `int`. The syntax of the declaration for a
variable mimics the syntax of expressions in which the variable might appear.

## Arguments as values

Since C passes arguments to functions by value, the way for a function to
modify the variables passed as arguments is using pointers.

For example, the following function is able to swap two numbers:
```C
void swap(int *px, int *py) /* interchange *px and *py */
{
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}
```

and it must be called with

```C
int a = 1, b = 2;
swap(&a, &b);
```

If you think about the arguments of swap, `&a` gives you a pointer to `a`,
which is what the function expects. `&a` gives you the address of `a` and when
used as `*a` you get what's stored at the address of a (`&a`), which
is exactly the value of the variable `a`.

## Pointer Arithmetic and array notation

if `int a[10];` is an array of ten elements, and `int *pa;` is a pointer to
int, then after the expression

```C
pa = &pa[0];
```

`pa` a and `a` have identical values.

Since the name of an array is a synonym for the location of the initial
element, the assignment `pa=&pa[0]` can also be written as

```C
pa = a;
```

Since `pa+i` points to the i-th element `a[i]`, a reference to `a[i]` can also
be written as `*(pa+i)`. Conversely, if `pa` is a pointer you can also use the
syntax `pa[i]` to mean `*(pa+i)`.

As formal parameters in a function definition,

```C
char s[];
```
and
```C
char *s;
```

are equivalent; the latter is prefered because it says more explicitly that the
parameter is a pointer.

## Multidimensional arrays

```C
daytab[i][j] /* [row][col] */
```

Elements are stored by rows, so the rightmost subscript, or column, varies fastest as elements are accessed in storage order.
