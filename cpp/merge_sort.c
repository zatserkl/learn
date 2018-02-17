/*
Compile with debug information:
clang -g -Wall merge_sort.c

Some LLDB commands
------------------
lldb a.out
n                           <-- next (step in function)
s                           <-- step (step over function)
b merge_sort.c:60           <-- set breakpoint at the line 60
b Merge                     <-- set breakpoint at function Merge
frame var                   <-- show local vars
p na                        <-- show value of the variable na
p *(data_type(*) [3])b      <-- show 3 elements of the array b
q                           <-- quit
<CR>                        <-- repeat the last command
help
command history             <-- command history of the current session
                                actual file is $HOME/.lldb/lldb-history
 */

#include <stdio.h>
#include <stdlib.h>


typedef int data_type;


void Merge(data_type *b, int nb, data_type *c, int nc, data_type *a, int na)
{
    int ia = 0;
    int ib = 0;
    int ic = 0;
    while (ib < nb && ic < nc) {
        if (b[ib] < c[ic]) {
            a[ia++] = b[ib++];
        }
        else {
            a[ia++] = c[ic++];
        }
    }

    while (ib < nb) a[ia++] = b[ib++];
    while (ic < nc) a[ia++] = c[ic++];

    free(b);
    free(c);
}


void SplitMerge(data_type *a, int na)
{
    if (na > 1)
    {
        int nb = na/2;
        int nc = na - nb;
        data_type *b = malloc(nb*sizeof(data_type));
        data_type *c = malloc(nc*sizeof(data_type));

        for (int i=0; i<nb; ++i) b[i] = a[i];
        for (int i=0; i<nc; ++i) c[i] = a[nb+i];

        SplitMerge(b, nb);
        SplitMerge(c, nc);
        Merge(b, nb, c, nc, a, na);
    }
}


int main()
{
    data_type a[] = {6, 2, 5, 3, 4, 1};
    int na = sizeof(a) / sizeof(data_type);

    for (int i=0; i<na; ++i) printf("%d ", a[i]);
    printf("\n");

    SplitMerge(a, na);

    for (int i=0; i<na; ++i) printf("%d ", a[i]);
    printf("\n");
}
