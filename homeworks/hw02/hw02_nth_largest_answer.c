#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "test.dat"
#define uint32_t u_int32_t

int  arg_test(int argc, char **argv);
void conversion_test();
void load_data(int **int_array, uint32_t *array_size);
int  find_nth(int *int_array, uint32_t array_size, int n);
void print_array(uint32_t size, int *arr);

int main(int argc, char **argv)
{
    int valid = arg_test(argc, argv);
    // Test function for atoi
    //conversion_test();
 
    if(valid) {
        int *int_array = NULL;
        uint32_t array_size = 0;
        load_data(&int_array, &array_size);

        // This function prints the content of the array - debugging tool
        // Insert your code here (1)
        int n = atoi(argv[1]);
        //if n is less than or equal to 0, input error
        if(n <= 0)
        {
            //which with n = -1, then nth will be -2 (below)
            //will end up printing Some error! after finding the nth value
            n = -1;
        }
        int nth = find_nth(int_array, array_size, n);
        // ------------------------
        if(nth >= 0) {
            printf("---- Answer ----\n");
            printf("The nth value is %d\n", int_array[nth]);
            printf("--------\n");
        } else if(nth == -1) {
            printf("---- Answer ----\n");
            printf("n is too large!\n");
            printf("--------\n");
        } else if(nth == -2) {
            printf("---- Answer ----\n");
            printf("Some error!\n");
            printf("--------\n");
        } else {
            // Do nothing
        }
    } else {
        // Do nothing
    }
    
    return 0;
}

int arg_test(int argc, char **argv)
{
    int return_val = 0;
    if(argc < 2) {
        fprintf(stderr, "Error: no input entered\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else if(argc > 2) {
        fprintf(stderr, "Error: too many inputs\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else {
        return_val = 1;
    }
    return return_val;
}

void conversion_test()
{
    printf("---- ATOI Sample Usage ----\n");
    char *num_str = "101";
    int num = atoi(num_str);
    printf("The number is %d\n", num);
    printf("--------\n\n");
}

void load_data(int **int_array, uint32_t *array_size)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    int tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        cnt++;
    }
    fclose(fp);

    int *tmp_array = (int*) malloc(sizeof(int) * cnt);
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }
    cnt = 0;
    tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        tmp_array[cnt] = tmp;
        cnt++;
    }
    fclose(fp);
    
    *int_array = tmp_array;
    *array_size = cnt;
}

// Given n as input, find the nth largest value
// in the list of integers loaded from the file.
// If n is larger than the number of integers,
// return -1.
// Return -2 for any other errors.
// NOTE 1:
// The file used for grading will be different from
// the file given with the homework - it will have
// different number of integers and different integer
// values
int cmpfunc (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}
int find_nth(int *int_array, uint32_t array_size, int n)
{
    // Insert your code here (2)
    if(n < 0)
    {
        return -2;
    }
    //variable to keep track of the size of the array
    int size = array_size;
    int index = 0;
    //creates a temporary array that will be sorted
    int *temp_array = malloc(sizeof(int) * array_size);
    memcpy(temp_array, int_array, sizeof(int) * array_size);
    //sort the given array (using quick sort)
    qsort(temp_array, array_size, sizeof(int), cmpfunc);
    for(int i = 0; i < size; i++)
    {
        //loop throuh looking at the next element
        for(int j = i + 1; j < size; j++)
        {
            //If any duplicate found 
            if(temp_array[i] == temp_array[j])
            {
                //update the array so the duplicate is dealt with
                for(int z = j; z < size; z++)
                {
                    temp_array[z] = temp_array[z + 1];
                }
                //decrement the size of the list when 
                size--;
                //if element swap occurs then dont increment j
                j--;
            }
        }
    }
    //if n is greater than all the different elements in the array
    if(size < n)
    {
        return -1;
    }
    //find the first occurence in the array
    for(int i = 0; i < array_size; i++)
    {
        if(temp_array[size-n] == int_array[i])
        {
            index = i;
            break;
        }
    }
    //returns the final index
    return index;
    // ------------------------
}

void print_array(uint32_t size, int *arr)
{
   printf("---- Print Array ----\n");
    printf("This file has %d elements\n", size);
    printf("#\tValue\n");
    for(int i = 0; i < size; i++) {
        printf("%d\t%d\n", i, arr[i]);
    }
   printf("--------\n\n");
}

