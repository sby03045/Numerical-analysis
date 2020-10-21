// 201811137 lee woo hyun 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main()
{
        int      i, j, k, column, row;
        double   *a;
        double   *c ;
        double   *x, factor, sum;
        double   *tem;               /* temporary adress variable */
        FILE     *fin;

/* File open */

        fin = fopen("r", "finput");

/* Memory Allocation  */
        fscanf(fin,"%d, %d", &column, &row);
        a = (double *)malloc(3 * 3 * sizeof( double));
        c = (double *)malloc(3 * sizeof(double));
        x = (double *)malloc(3 * sizeof(double));

/* initialize */

        tem = a;
        for(i=0; i < 3*3 ; i++) fscanf( fin, "%f", tem++);

        tem = c;
        for(i=0; i < 3 ; i++) fscanf( fin, "%f", tem++);

/* make lower triangular matrix to 0 and a[k][k] = 1 */
        for( k=0; k < 3;k++){
		factor = *(a + 3*k +k);
		for(j=k; j<3; j++) {
			*(a + 3*k +j) /= factor; // make a[k][k] = 1
		}
		*(c + k) /= factor;
                for(i= k+1; i < 3; i++ ){
			factor = *(a + 3*i +k);
                        for(j=0; j<3; j++) *(a + 3*i +j) -= factor * (*(a + 3*k +j));
                        *(c + i) -= factor * (*(c + k));
                }
		
        }

/* make upper triangular matrix to 0 */
	*(x+2) = *(c+2);
        for( i= 3-2; i>=0; i--){
                sum = 0;
                for(j=i+1; j<3; j++ )   sum += (*(a + 3*i +j)) * (*(x+j));
                *(x+i) = *(c+i) - sum ;
        }

/* print results */

        for(i=0; i<3; i++) printf("x[%1d] = %10.4f, ", i, x[i]);
        printf("\n");
}	

