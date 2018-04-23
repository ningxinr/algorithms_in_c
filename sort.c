#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define PIVOT_SZ                                                               \
    1 /* pivot size for partitioning, must be smaller than insertion max*/
#define INSERTION_MAX 10        /* max size for using insertion sort*/
#define TEST_ARR_SZ_S 3         /* size of small test array*/
#define TEST_ARR_SZ_M 11        /* size of medium test array*/
#define TEST_ARR_SZ_L 100000000 /* size of large test array*/

/* Sorting functions */
void insertion_sort(int *arr_ptr, int arr_sz);

/* Helper functions */
int partition(int *arr_ptr, int arr_sz);
void exchange(int *arr_ptr, int i, int j);
void print_arr(int *arr_ptr, int arr_sz);
void test_arr(int *arr_ptr, int arr_sz);
int is_not_sorted(int *arr_ptr, int arr_sz);

/* Main sorting routine */
void sort(int *arr_ptr, int arr_sz);

void print_arr(int *arr_ptr, int arr_sz) {
    int i;

    for (i = 0; i < arr_sz; i++) {
        printf("%d\n", arr_ptr[i]);
    }
}

void insertion_sort(int *arr_ptr, int arr_sz) {
    int i, j;
    for (j = 1; j < arr_sz; j++) {
        int temp = arr_ptr[j];
        i = j;
        while (arr_ptr[i - 1] > temp && i > 0) {
            arr_ptr[i] = arr_ptr[i - 1];
            i--;
        }
        arr_ptr[i] = temp;
    }
}

void exchange(int *arr_ptr, int i, int j) {
    if (i != j) {
        int temp = arr_ptr[i];
        arr_ptr[i] = arr_ptr[j];
        arr_ptr[j] = temp;
    }
}

int partition(int *arr_ptr, int arr_sz) {
    if (arr_sz > PIVOT_SZ) {
        int i, j, pivot_idx;
        pivot_idx = PIVOT_SZ / 2;
        int pivot[PIVOT_SZ];

        for (i = 0; i < PIVOT_SZ; i++) {
            pivot[i] = arr_ptr[i];
        }
        sort(pivot, PIVOT_SZ);

        if (PIVOT_SZ > 1) {
            i = -1;
            while (i < PIVOT_SZ && arr_ptr[++i] != pivot[0])
                ;
            exchange(arr_ptr, i, 0);

            j = PIVOT_SZ;
            while ((j > 0) && arr_ptr[--j] != pivot[PIVOT_SZ - 1])
                ;
            exchange(arr_ptr, j, arr_sz - 2);
        }

        i = -1;
        while (i < PIVOT_SZ && arr_ptr[++i] != pivot[pivot_idx])
            ;
        exchange(arr_ptr, i, arr_sz - 1);

        i = -1;
        j = arr_sz - 1;
        while (1) {
            while (i < (arr_sz - 1) && arr_ptr[++i] < pivot[pivot_idx])
                ;

            while ((j > 0) && arr_ptr[--j] > pivot[pivot_idx])
                ;

            if (i >= j) {
                break;
            }

            exchange(arr_ptr, i, j);
        }
        arr_ptr[arr_sz - 1] = arr_ptr[i];
        arr_ptr[i] = pivot[pivot_idx];
        return i;
    }

    return -1;
}

void sort(int *arr_ptr, int arr_sz) {
    if (arr_sz <= INSERTION_MAX) {
        insertion_sort(arr_ptr, arr_sz);
    } else {
        int i;
        i = partition(arr_ptr, arr_sz);
        if (i != -1) {
            sort(arr_ptr, i);
            sort(arr_ptr + (i + 1), arr_sz - i - 1);
        }
    }
}

int is_not_sorted(int *arr_ptr, int arr_sz) {
    int i;
    for (i = 0; i < arr_sz - 1; i++) {
        if (arr_ptr[i] > arr_ptr[i + 1]) {
            return 1;
        }
    }

    return 0;
}

void test_arr(int *arr_ptr, int arr_sz) {
    printf("Sorting Array...\n");
    sort(arr_ptr, arr_sz);

    if (is_not_sorted(arr_ptr, arr_sz)) {
        printf("Failed to sort array!\n");
        print_arr(arr_ptr, arr_sz);
    } else {
        printf("Array has been sorted!\n");
    }

    printf("\n");
}

int main(int argc, char **argv) {

    int test_arr_s[TEST_ARR_SZ_S] = {3, 2, 1};

    test_arr(test_arr_s, TEST_ARR_SZ_S);

    int test_arr_m1[TEST_ARR_SZ_M] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    test_arr(test_arr_m1, TEST_ARR_SZ_M);

    int test_arr_m2[TEST_ARR_SZ_M] = {-1, 0, 1, 2, 6, 4, 5, 3, 7, 8, 9};

    test_arr(test_arr_m2, TEST_ARR_SZ_M);

    int test_arr_m3[TEST_ARR_SZ_M] = {0, 1, 2, 6, 4, 5, 3, 7, 8, 9, 10};

    test_arr(test_arr_m3, TEST_ARR_SZ_M);

    int test_arr_m4[TEST_ARR_SZ_M] = {1, 1, 2, 6, 5, 5, 3, 7, 8, 9, 9};

    test_arr(test_arr_m4, TEST_ARR_SZ_M);

    int *test_arr_l = (int *)malloc(TEST_ARR_SZ_L * sizeof(int));
    if (!test_arr_l) {
        perror("Malloc for large array failed");
        exit(1);
    } else {
        int i;
        for (i = 0; i < TEST_ARR_SZ_L; i++) {
            test_arr_l[i] = rand();
        }
        test_arr(test_arr_l, TEST_ARR_SZ_L);
        free(test_arr_l);
    }

    return 0;
}
