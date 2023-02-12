//modify qsort.c in section 9.6 so that low, high, and middle are pointers to array elements rather than integers. The split function willneed to return a pointer not an integer 


#include <stdio.h>

#define N 10

void quicksort(int *a, int *low, int *high);
int *split(int *a, int *low, int *high);


int main(void) {

	int a[N], i;

	printf("Enter %d numbers to be sorted: ", N);

	for(i = 0; i < N; i++)
		scanf("%d", (a + i));

	int lowVal = 0;
	int *low = &lowVal;

	int highVal = N-1;
	int *high = &highVal;

	//i know I can pass a instead of &a[0] but I think this approach is easier to read
	quicksort(&a[0], low, high);

	printf("In sorted order: ");
	for(i = 0; i < N; i++)
		printf("%d ", *(a + i) );

	printf("\n");

	return 0;
}

void quicksort(int *a, int *low, int *high) {

	int middleVal;

	if(*(low) >= *(high))
		return;


	int lowCopy = *(low);
        int *lowPointer = &lowCopy;

	int highCopy = *(high);
	int *highPointer = &highCopy;
	//split returns a pointer to an integer to we dereference it's return
	middleVal = *( split(a, lowPointer, highPointer) );

	int middle1 = middleVal - 1;
	int *middle1Pointer = &middle1;


	int lowCopy2 = *(low);
	int *lowPointer2 = &lowCopy2;

	quicksort(a, lowPointer2, middle1Pointer);

	//since middle was changed to middle - 1 just before this to get to middle + 1 we need
	//to write middle + 1 + 1 or middle + 2
	int middle2  = middleVal + 1;
	int *middle2Pointer = &middle2;

	int highCopy2 = *(high);
	int *highPointer2 = &highCopy2;
	quicksort(a, middle2Pointer, highPointer2);

}

int *split(int *a, int *low, int *high) {

	//use a[low] as the pivot and treat a[low] as an empty element
	int part_element = *(a + *(low));

	for(;;) {

		//find the first element from right to left that is less than the pivot
		while(*(low) < *(high) && part_element <=  *(a + *(high)) )
			*(high) = *(high) - 1;

		if(*(low) >= *(high))
			break;

		//Swap the element that high points to [which we found to be less than the pivot]
		//with a[low] (the element that is being treated as empty) and then increment low
		//the empty element is now at a[high]
		*(a + *(low) ) = *(a + *(high));
		*(low) = *(low) + 1;

		//find the first element left to right that is greater than the pivot
		while(*(low) < *(high) && *(a + *(low)) <= part_element)
			*(low) = *(low) + 1;

		if(*(low) >= *(high))
			break;

		//Swap the element that low points to [which we found to be greater than the
		//pivot] with a[high] and then decrement high. The empty element is now at low
		*(a + *(high) ) = *(a + *(low));
		*(high) = *(high) - 1;
	}

	//when the loop terminates high and low will point to the same location, the empty element
	//which marks the position where the paritioning element should be place [that is, the
	//position in which everything to the left of the partitioning elemtent is less than it
	//and everything to the right is greater than it


	//now place the partitioning element in it's final resting location
	*(a + *(high)) = part_element;
	return high;
}
