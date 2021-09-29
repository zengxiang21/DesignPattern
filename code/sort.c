

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_ARRAY_LENGTH		12


int shell_sort(int *data, int length) {

	int gap = 0;
	int i = 0, j = 0;
	int temp;

	for (gap = length / 2;gap >= 1; gap /= 2) {

		for (i = gap;i < length;i ++) {

			temp = data[i];
			for (j = i-gap;j >= 0 && temp < data[j];j = j - gap) {

				data[j+gap] = data[j];
				
			}
			data[j+gap] = temp;
		}

	}

	return 0;
}



void merge(int *data, int *temp, int start, int middle, int end) {

	int i = start, j = middle+1, k = start;

	while (i <= middle && j <= end) {
		if (data[i] > data[j]) {
			temp[k++] = data[j++];
		} else {
			temp[k++] = data[i++];
		}
	}

	while (i <= middle) {
		temp[k++] = data[i++];
	}

	while (j <= end) {
		temp[k++] = data[j++];
	}

	for (i = start;i <= end;i ++) {
		data[i] = temp[i];
	}
}


int merge_sort(int *data, int *temp, int start, int end) {

	int middle;
	
	if (start < end) {
		middle = start + (end - start) / 2;

		merge_sort(data, temp, start, middle);
		merge_sort(data, temp, middle+1, end);

		merge(data, temp, start, middle, end);
	}

} 


void sort(int *data, int left, int right) {

	if (left >= right) return ;

	int i = left;
	int j = right;
	int key = data[left];

	while (i < j) {

		while (i < j && key <= data[j]) {
			j --;
		}
		data[i] = data[j];

		while (i < j && key >= data[i]) {
			i ++;
		}
		data[j] = data[i];
	}

	data[i] = key;

	sort(data, left, i - 1);
	sort(data, i + 1, right);

}

int quick_sort(int *data, int length) {

	sort(data, 0, length-1);

}

int main() {

	int data[DATA_ARRAY_LENGTH] = {23, 64, 24, 12, 9, 16, 53, 57, 71, 79, 87, 97};
	int i = 0;
	
#if 0
	shell_sort(data, DATA_ARRAY_LENGTH);

#elif 0

	int temp[DATA_ARRAY_LENGTH] = {0};

	merge_sort(data, temp, 0, DATA_ARRAY_LENGTH-1);

#else

	quick_sort(data, DATA_ARRAY_LENGTH);

#endif

	for (i = 0;i < DATA_ARRAY_LENGTH;i ++) {
		printf("%4d", data[i]);
	}
	printf("\n");

}


