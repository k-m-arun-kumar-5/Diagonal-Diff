/* ********************************************************************
FILE                   : square_dia.c

PROGRAM DESCRIPTION    : Diagonal Difference - Given a square matrix of size , calculate the absolute difference between the sums of its diagonals.

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            :    

NOTE                  :  Compiled and Tested in Dev-C++ on Windows 7 (32 bit) Desktop OS.

Input Format          : The first line contains a single integer, . The next  lines denote the matrix's rows, with each line containing  space-separated integers describing the columns.



Output Format        ; Print the absolute difference between the two sums of the matrix's diagonals as a single integer.

Sample Input         : 

3
11 2 4
4 5 6
10 8 -12


Sample Output         :

15

Explanation           :

The primary diagonal is:

11
   5
     -12
     
Sum across the primary diagonal: 11 + 5 - 12 = 4

The secondary diagonal is:

     4
   5
10

Sum across the secondary diagonal: 4 + 5 + 10 = 19 

Difference: |4 - 19| = 15 
                                    
CHANGE LOGS           : 

*****************************************************************************/


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int diagonalDifference(int a_size_rows, int a_size_cols, int** a) {
     // Complete this function
    int pri_dia_sum = 0, sec_dia_sum = 0, i = 0,j,k;    
     for(i =0; i < a_size_rows; ++i)
     {
         j = i;
         pri_dia_sum += a[i][j];
         k = a_size_cols - 1 - i;
         sec_dia_sum += a[i][k];
     }
     return (abs(pri_dia_sum - sec_dia_sum));
}

int main() {
    int n, **a, i; 
    scanf("%i", &n);
    a = (int **)malloc(sizeof(int *) *n );
    for(i = 0; i < n; ++i)
    {
        a[i] = (int *)malloc(sizeof(int) * n);
    }
    for (int a_i = 0; a_i < n; a_i++) {
       for (int a_j = 0; a_j < n; a_j++) {
      
          scanf("%i",&a[a_i][a_j]);
       }
    }
    int result = diagonalDifference(n, n, a);
    printf("%d\n", result);
    for(i = 0; i < n; ++i)
    {
        free(a[i]);
    } 
    free(a);
    return 0;
}
