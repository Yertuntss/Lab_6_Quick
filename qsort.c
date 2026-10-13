#include "my_qsort.h"
#include <stdio.h>
/*
  quicksort эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
*/
#ifndef CUTOFF
#define CUTOFF 10
#endif

static int init_seed = 0;  // Random seed 1 удаа эхлүүлнэ

/*
  Оруулан эрэмбэлэх функц.
  [lo, hi] завсрах тоонуудыг оруулан эрэмбэлэх аргаар эрэмбэлнэ.
*/
static void insertion_sort(int a[], int lo, int hi)
{
	int i, j, key;
        int n = hi - lo;
	for (i = lo; i < n; i++)
	{
		key = a[i];
		j = i - 1;
		while (j >= lo && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

/*
  Хоёр утгыг хооронд солих функц
*/
static void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

/*
  [lo, hi] завсрыг санамсаргүйгээр холих функц.
*/
static void random_shuffle(int a[], int lo, int hi)
{
        if (init_seed == 0) {
                srand(time(NULL));
                init_seed = 1;
        }
        int i, j;
        for (i = lo; i <= hi; i++) {
                j = rand() % (hi - lo) + lo;
                swap(&a[i], &a[j]);
        }
}

/*
  1-pivot хурдан эрэмбэлэх функц.
*/
static int _single_pivot_qsort(int a[], int lo, int hi)
{
        int key =  a[lo];
        int first = lo;
        while(lo<hi){
                if(a[lo]>key){
                        if(a[hi]<key){
                                printf("%d, %d", a[lo], a[hi]);
                                swap(&a[lo], &a[hi]);
                        }
                        else{
                                hi--;
                        }
                }
                else{
                        lo++;
                }
        }
        swap(&a[first], &a[lo]);
        return lo;
}

/*
  wrapper function for _single_pivot_qsort
  _single_pivot_qsort-ыг дуудахад ашиглах функц
 */
void single_pivot_qsort(int a[], int lo, int hi)
{
        if(hi - lo == CUTOFF){
                insertion_sort(a, lo, hi);
                return;
        }
        random_shuffle(a, lo, hi);
        int mid = _single_pivot_qsort(a, lo, hi);
        single_pivot_qsort(a, lo, mid);
        single_pivot_qsort(a, mid+1, hi);
}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi)
{
        /*
          Энд dual-pivot quicksort хэрэгжүүл
        */
	
}
/*
  wrapper function for _dual_pivot_qsort
  _dual_pivot_qsort-ыг дуудахад ашиглах функц
*/
void dual_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _dual_pivot_qsort(a, lo, hi);
}

