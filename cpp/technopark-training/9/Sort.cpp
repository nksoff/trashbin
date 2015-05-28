namespace sort{
    void quickSort(int *arr, int first, int last) {
        int i = first, j = last, middle = arr[(first+last)/2];
        do {
            while(arr[i] < middle) i++;
            while(arr[j] > middle) j--;

            if(i <= j) {
                if(arr[i] > arr[j]) {
                    int tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                }
                i++;
                j--;
            }
        } while(i <= j);

        if(i < last) {
            quickSort(arr, i, last);
        }
        if(first < j) {
            quickSort(arr, first, j);
        }
    }
}
