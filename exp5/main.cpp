#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// 起泡排序
void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 选择排序
void selectionSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 归并排序辅助函数
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

// 归并排序
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 快速排序
void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                swap(arr[++i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[right]);

        quickSort(arr, left, i);
        quickSort(arr, i + 2, right);
    }
}

// 堆排序辅助函数
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 测试函数
void testSortingAlgorithms() {
    vector<int> sizes = {1000, 5000, 10000}; // 数据规模
    for (int size : sizes) {
        vector<int> ascending(size), descending(size), randomVec(size);

        // 生成测试数据
        for (int i = 0; i < size; i++) ascending[i] = i;
        descending = ascending;
        reverse(descending.begin(), descending.end());
        randomVec = ascending;
        random_shuffle(randomVec.begin(), randomVec.end());

        // 算法数组
        vector<void (*)(vector<int>&)> algorithms = {bubbleSort, insertionSort, selectionSort, 
                                                      [](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, 
                                                      [](vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, 
                                                      heapSort};
        vector<string> names = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort", "Heap Sort"};

        for (size_t i = 0; i < algorithms.size(); i++) {
            cout << "Testing " << names[i] << " with size " << size << ":" << endl;

            vector<vector<int>> testCases = {ascending, descending, randomVec};
            vector<string> caseNames = {"Ascending", "Descending", "Random"};

            for (size_t j = 0; j < testCases.size(); j++) {
                vector<int> data = testCases[j];
                auto start = high_resolution_clock::now();
                algorithms[i](data);
                auto end = high_resolution_clock::now();
                duration<double> elapsed = end - start;

                cout << "  " << caseNames[j] << ": " << elapsed.count() << " seconds" << endl;
            }
            cout << endl;
        }
    }
}

int main() {
    testSortingAlgorithms();
    return 0;
}
