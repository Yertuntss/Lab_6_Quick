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
	for (i = lo; i <= hi; i++)
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
static void _single_pivot_qsort(int a[], int lo, int hi)
{
        if(hi - lo <= CUTOFF){
                insertion_sort(a, lo, hi);
                return;
        }
        int key =  a[lo];
        int first = lo+1;
        int last = hi;
        while(1){
                while(first<=hi && a[first]<key){
                        first++;
                }
                while(last>lo && a[last]>key){
                        last--;
                }
                if(first>=last){
                        break;
                }
                swap(&a[first], &a[last]);
                first++;
                last--;
        }
        swap(&a[lo], &a[last]);
        _single_pivot_qsort(a, lo, last-1);
        _single_pivot_qsort(a, last+1, hi);
}

/*
  wrapper function for _single_pivot_qsort
  _single_pivot_qsort-ыг дуудахад ашиглах функц
 */
void single_pivot_qsort(int a[], int lo, int hi)
{

        random_shuffle(a, lo, hi);
        _single_pivot_qsort(a, lo, hi);  

}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi)
{
        if(hi - lo <= CUTOFF){
                insertion_sort(a, lo, hi);
                return;
        }
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

        int mid1 = first;
        int mid2 = last;
        _dual_pivot_qsort(a, lo, mid1-1);
        _dual_pivot_qsort(a, mid1+1, mid2-1);
        _dual_pivot_qsort(a, mid2+1, hi);
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

