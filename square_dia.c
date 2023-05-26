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
#include <ctype.h>

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int64_t;
typedef enum { SUCCESS, FAILURE, FSM_INPUT_MATRIX_SIZE, FSM_MATRIX_VAL, FSM_CALC_RESULT, FSM_DEALLOC, FSM_TO_CONTINUE, FSM_EXIT} sys_status_t;

#define NULL_DATA_PTR                            ((void *)0)
#define NULL_CHAR                               ('\0')

#define STR_MAX_CHARS                            (7)
#define MATRIX_MIN_SIZE                          (1)
#define MATRIX_MAX_SIZE                          (10)

#define MATRIX_MIN_VAL                          (-1000)
#define MATRIX_MAX_VAL                          (1000)

uint16_t Get_Validate_Input_Number(void *const int32_input_num_ptr, char *const input_str_ptr, const unsigned int input_str_max_chars, const int32_t valid_min_value, const int32_t valid_max_value);
uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars);
uint16_t Str_to_Num_Conv(void *const num_conv_from_str, const char *const num_in_str);
uint32_t Power_Of(const uint8_t base, const uint8_t power);

char input_str[STR_MAX_CHARS];
uint16_t system_fsm;

int diagonalDifference(int a_size_rows, int a_size_cols, int** a)
{
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

int main()
{
    int n, **a, i, result;
	char to_continue[2]  = "Y";
	bool is_error = false;

	system_fsm = FSM_INPUT_MATRIX_SIZE;
	while(1)
	{
		switch(system_fsm)
		{
			case FSM_INPUT_MATRIX_SIZE:
		       printf("\n Enter square matrix size: ");
		      // scanf("%i", &n);
		      if((Get_Validate_Input_Number(&n, input_str, STR_MAX_CHARS, MATRIX_MIN_SIZE, MATRIX_MAX_SIZE)) != SUCCESS)
		      {
		        	printf("\n ERR: Invalid square matrix size ");
		      }
              else
              {
                 system_fsm = FSM_MATRIX_VAL;
			  }
            break;
            case FSM_MATRIX_VAL:
               a = (int **)malloc(sizeof(int *) *n );
               for(i = 0; i < n; ++i)
               {
                 a[i] = (int *)malloc(sizeof(int) * n);
               }
               for (int a_i = 0; a_i < n; a_i++)
	           {
                  for (int a_j = 0; a_j < n; a_j++)
	              {
					  if(is_error == true)
						  break;
					  printf("row : %i, column : %i - Enter val : ", a_i + 1, a_j + 1);
                      //scanf("%i ",&a[a_i][a_j]);
			          if((Get_Validate_Input_Number(&a[a_i][a_j], input_str, STR_MAX_CHARS, MATRIX_MIN_VAL, MATRIX_MAX_VAL)) != SUCCESS)
		              {
		            	printf("\n ERR: Invalid square matrix size");
						is_error = true;
			            system_fsm = FSM_DEALLOC;
						break;
					  }
				  }
                  if(is_error == true)
                     break;
			      printf("\n");
		       }
			   if(is_error == true)
				  break;
               system_fsm = FSM_CALC_RESULT;
            break;
			case FSM_CALC_RESULT:
			   result = diagonalDifference(n, n, a);
               printf("diagonal diff = %d\n", result);
			   system_fsm = FSM_DEALLOC;
			break;
			case FSM_DEALLOC:
	            for(i = 0; i < n; ++i)
                {
                    free(a[i]);
                }
                free(a);
				system_fsm = FSM_TO_CONTINUE;
		    break;
			case FSM_TO_CONTINUE:
			   printf("\n Do you want to continue Y or y to continue, any other char(s) to exit. \n Enter : ");
			   if((Get_Input_Str(to_continue, 2)) != SUCCESS)
			   {
				   to_continue[0] = 'N';
				   system_fsm = FSM_EXIT;
			   }
			   else
               {
               	   to_continue[0] = toupper(to_continue[0]);
			       if(to_continue[0] == 'Y')
			 		  system_fsm = FSM_INPUT_MATRIX_SIZE;
			       else
			       	 system_fsm = FSM_EXIT;
			   }
			break;
			case FSM_EXIT:
                return SUCCESS;
            break;
		}
    }
    return 0;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Str_to_Num_Conv

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           : digits are extracted from left to right format from digit in num_in_str

Func ID        : 02.04

BUGS           :
-*------------------------------------------------------------*/
uint16_t Str_to_Num_Conv( void *const num_conv_from_str_ptr, const char *const num_in_str)
{
	 int32_t num = 0, *num_conv_from_str;
	 uint32_t place;
	 int16_t cur_unit;
	 uint8_t num_chars = 0, base = 10, pos = 0, start_num_pos = 0 ;

	 if(num_conv_from_str_ptr == NULL_DATA_PTR || num_in_str == NULL_DATA_PTR )
	 {
		 #ifdef TRACE_ERROR
		   printf("ERR: data are null ptr \n");
		#endif
		return FAILURE;
	 }
	 num_conv_from_str = (int32_t *)num_conv_from_str_ptr;
	 *num_conv_from_str = 0;
	 if(num_in_str[0] >= '0' && num_in_str[0] <= '9')
	 {
		  start_num_pos = 0;
	 }
	 else if(num_in_str[0] == '-')
	 {
		 start_num_pos = 1;
	 }
	 else
	 {
    	 #ifdef TRACE_ERROR
		    printf("ERR: invalid char: %c \n", num_in_str[0]);
		 #endif
         return FAILURE;
	 }
	 num_chars = strlen(num_in_str + start_num_pos);
	 if(num_chars == 0)
	 {
		 #ifdef TRACE_ERROR
		    printf("ERR: data empty \n");
		 #endif
         return FAILURE;
	 }
	 pos = start_num_pos;
     for( place = Power_Of(base, num_chars - 1); place >= 1; place /= base, ++pos )
     {
     	 cur_unit = num_in_str[pos] - '0';
    	 if(cur_unit < 0 ||  cur_unit > 9 )
    	 {
	    	 #ifdef TRACE_ERROR
		       printf("ERR: invalid char at data[%d] = %c \n", pos, num_in_str[pos]);
		     #endif
             return FAILURE;
	     }
         num += (cur_unit * place);
     }
	 if(num_in_str[0] == '-')
	 {
		 *num_conv_from_str = -num;
	 }
	 else
	 {
	     *num_conv_from_str = num;
	 }
	 return SUCCESS;
}
/*------------------------------------------------------------*
FUNCTION NAME  : Power_Of

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 02.10

Bugs           :
-*------------------------------------------------------------*/
uint32_t Power_Of(const uint8_t base, const uint8_t power )
{
    uint32_t power_val = 1;
    uint8_t i = 0;

    if(power == 0)
    {
       return power_val;
    }
    for(i = 1; i <= power; ++i)
    {
      power_val *= base;
    }
    return power_val;
}
/*------------------------------------------------------------*
FUNCTION NAME  : Validate_Number_Input

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 01.02

BUGS           :
-*------------------------------------------------------------*/
uint16_t Get_Validate_Input_Number(void *const input_num_ptr, char *const input_str_ptr, const unsigned int input_str_max_chars, const int32_t valid_min_value, const int32_t valid_max_value)
{
	int32_t temp_int, *int32_input_num_ptr;

	if(int32_input_num_ptr == NULL_DATA_PTR)
	{
		return FAILURE;
	}
	if(valid_min_value > valid_max_value)
	{
	   return FAILURE;
	}
	int32_input_num_ptr = (int32_t *)input_num_ptr;
	*int32_input_num_ptr = 0;
	if((Get_Input_Str(input_str_ptr, input_str_max_chars)) != SUCCESS)
		return FAILURE;
	if((Str_to_Num_Conv(&temp_int, input_str_ptr)) != SUCCESS)
	{
		memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
		return FAILURE;
	}
	memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
	if(temp_int < valid_min_value || temp_int > valid_max_value)
	{
		 #ifdef TRACE_ERROR
		      printf("ERR: input data - %d, out of range [%d,%d] \n", temp_int, valid_min_value, valid_max_value);
		 #endif
		 return FAILURE;
	}
	*int32_input_num_ptr = temp_int;
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Get_Input_Str

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 01.02

BUGS           :
-*------------------------------------------------------------*/
uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars)
{
    unsigned int input_str_num_chars = 0;
	char rcvd_char;

    if(input_str_ptr == NULL_DATA_PTR || input_str_max_chars <= 1)
	{
		return FAILURE;
	}
    memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
	while (1)
	{
		rcvd_char = (char) getchar();
		//scanf("%c", &rcvd_char);
		switch(rcvd_char)
        {
			case '\b':
              if(input_str_num_chars > 0)
			  {
			      input_str_ptr[input_str_num_chars] = NULL_CHAR;
				  --input_str_num_chars;
			  }
			break;
            case '\n':
			   if(input_str_num_chars != 0)
			   {
			      input_str_ptr[input_str_num_chars] = NULL_CHAR;
			      return SUCCESS;
			   }
            break;
            default:
     			if(input_str_num_chars + 1 < input_str_max_chars )
    		    {
		    	   input_str_ptr[input_str_num_chars] = rcvd_char;
                   ++input_str_num_chars;
	    		}
		    	else
			    {
			       printf("ERR: Input data num chars exceeds max chars : %u \n", input_str_max_chars - 1);
			       memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
				   fflush(stdin);
				   return FAILURE;
			    }
		}
	}
	return SUCCESS;
}
