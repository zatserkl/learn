#include <stdio.h>

int main()
{
    const char *fname = "fscanf_xy.dat";
    FILE *file = fopen(fname, "r");
    if (!file) {
        printf("Could not find file %s\n",fname);
        printf("Example of the file %s:\n", fname);
        for (int i=0; i<5; ++i) printf("%d\t%d\n", (i+1), 10*(i+1));
        return 0;
    }

    double x[20000];
    double y[20000];
    int np = 0;

    //
    //  Comment to fscanf
    //  -----------------
    //
    //  The fscanf needs to be checked that the number of items read > 0.
    //      The best is to compare with the expected number of items.
    //      In case of bad formatted field that variable and next in the line will be undefined.
    //      NB: the EOF returns -1.
    //      NB: while(fscanf(..)) will miss the EOF and continue reading until Segmentation fault.
    //
    //  The fscanf will stop before bad formatted piece of data:
/*
1       10
2       20
3       30
this line will terminate processing
4       40
5       50
*/
//      NB: in this example of bad format fscanf will read the first number (100) correctly 
//      leaving the second undefined. The np will be increamented.
/*
1       10
2       20
3       30
100 this line will terminate processing
4       40
5       50
*/

    //
    //  read as a double
    //

    printf("\nwhile loop\n");

    while (fscanf(file,"%lg%lg",&x[np],&y[np]) == 2)    // the best is to compare with expected number of items
    // while (fscanf(file,"%lg%lg",&x[np],&y[np]) > 0)  // the variables after bad formatted field will be undefined
    // while (fscanf(file,"%lg%lg",&x[np],&y[np]))      // will miss the EOF (return value is -1)
    {
        printf("%d\t %f %f\n",np,x[np],y[np]);

        ++np;
    }
    if (!feof(file)) printf("***Warning: read error occured!\n");
    fclose(file);

    printf("np = %d\n",np);

    printf("\nfor loop\n");

    FILE *file_for = fopen(fname, "r");

    for (np = 0; fscanf(file_for,"%lg%lg",&x[np],&y[np]) == 2; ++np)    // init and increament of np
    {
        printf("%d\t %f %f\n",np,x[np],y[np]);
    }
    if (!feof(file_for)) printf("***Warning: read error occured!\n");
    fclose(file_for);

    printf("np = %d\n",np);

    //
    //  read as integer data
    //

    printf("\nread the file as containing integer data\n");

    FILE *file_int = fopen(fname, "r");

    int ix, iy;
    np = 0;

    while (fscanf(file_int,"%d%d",&ix,&iy) == 2)    // the best is compare with expected number
    // while (fscanf(file_int,"%d%d",&ix,&iy) > 0)  // hope and pray
    // while (fscanf(file_int,"%d%d",&ix,&iy))      // will miss the EOF (return value is -1)
    {
        printf("%d\t %d %d\n",np,ix,iy);

        ++np;
    }
    if (!feof(file_int)) printf("***Warning: read error occured!\n");
    fclose(file_int);

    printf("np = %d\n",np);

    return 0;
}
