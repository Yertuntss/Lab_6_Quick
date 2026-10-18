#include "my_qsort.h"
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
	for (i = lo; i < hi; i++)
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
        int first = lo+1;
        int last = hi-1;
        while(1){
                while(a[lo]<=key && lo<=last){
                        lo++;
                }
                while(a[hi]>= key && hi>first){
                        hi--;
                }
                if(lo>=hi){
                        break;
                }
                swap(&a[lo], &a[hi]);
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
        if(hi - lo <= CUTOFF){
                insertion_sort(a, lo, hi);
                return;
        }
        random_shuffle(a, lo, hi);
        int mid = _single_pivot_qsort(a, lo, hi);       
        single_pivot_qsort(a, lo, mid-1);
        single_pivot_qsort(a, mid+1, hi);
}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi, int *mid1, int *mid2)
{
        if(a[lo] > a[hi]){
                swap(&a[hi], &a[lo]);
        }
        int key1 =  a[lo];
        int key2 =  a[hi];
        int first = lo+1;
        int last = hi-1;
        int var = first;
        while(var <= last){
                if(a[var] < key1){
                        swap(&a[var], &a[first]);
                        first++;
                        var++;
                }
                else if(a[var] > key2){
                        while(a[last]>key2 && var<last){
                                last--;
                        }
                        swap(&a[var], &a[last]);
                        last--;

                        if(a[var] < key1){
                                swap(&a[var], &a[first]);
                                first++;
                        }
                        var++;
                }
                else{
                        var++;
                }
        }
        first--;
        last++;
        swap(&a[first], &a[lo]);
        swap(&a[last], &a[hi]);

        *mid1 = first;
        *mid2 = last;
}
/*
  wrapper function for _dual_pivot_qsort
  _dual_pivot_qsort-ыг дуудахад ашиглах функц
*/
void dual_pivot_qsort(int a[], int lo, int hi)
{
        if(hi - lo <= CUTOFF){
                insertion_sort(a, lo, hi);
                return;
        }
        random_shuffle(a, lo, hi);
        
        int mid1, mid2;
        _dual_pivot_qsort(a, lo, hi, &mid1, &mid2);

        dual_pivot_qsort(a, lo, mid1-1);
        dual_pivot_qsort(a, mid1+1, mid2-1);
        dual_pivot_qsort(a, mid2+1, hi);
}

