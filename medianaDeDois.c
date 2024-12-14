#include <stdio.h>
#include <stdlib.h>

// Função para comparar dois elementos (usada no qsort)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Particiona o array em três partes: menor, igual e maior que o pivo
void partition(int* arr, int size, int pivot, int** less, int* lessSize, int** equal, int* equalSize, int** greater, int* greaterSize) {
    *less = (int*)malloc(size * sizeof(int));
    *equal = (int*)malloc(size * sizeof(int));
    *greater = (int*)malloc(size * sizeof(int));

    *lessSize = *equalSize = *greaterSize = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < pivot) {
            (*less)[(*lessSize)++] = arr[i];
        } else if (arr[i] == pivot) {
            (*equal)[(*equalSize)++] = arr[i];
        } else {
            (*greater)[(*greaterSize)++] = arr[i];
        }
    }
}

// Seleciona o k-ésimo menor elemento do array
int select(int* arr, int size, int k) {
    if (size <= 5) {
        qsort(arr, size, sizeof(int), compare);
        return arr[k];
    }

    // Encontrar as medianas dos grupos de 5
    int numGroups = (size + 4) / 5;
    int* medians = (int*)malloc(numGroups * sizeof(int));

    for (int i = 0; i < numGroups; i++) {
        int groupSize = (i * 5 + 5 <= size) ? 5 : size - i * 5;
        qsort(arr + i * 5, groupSize, sizeof(int), compare);
        medians[i] = arr[i * 5 + groupSize / 2];
    }

    // Mediana das medianas
    int pivot = select(medians, numGroups, numGroups / 2);
    free(medians);

    int *less, *equal, *greater;
    int lessSize, equalSize, greaterSize;
    partition(arr, size, pivot, &less, &lessSize, &equal, &equalSize, &greater, &greaterSize);

    int result;
    if (k < lessSize) {
        result = select(less, lessSize, k);
    } else if (k < lessSize + equalSize) {
        result = pivot;
    } else {
        result = select(greater, greaterSize, k - lessSize - equalSize);
    }

    free(less);
    free(equal);
    free(greater);
    return result;
}

// Encontra o k-ésimo elemento de duas listas combinadas
int findKthElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    int* combined = (int*)malloc((nums1Size + nums2Size) * sizeof(int));
    for (int i = 0; i < nums1Size; i++) {
        combined[i] = nums1[i];
    }
    for (int i = 0; i < nums2Size; i++) {
        combined[nums1Size + i] = nums2[i];
    }

    int result = select(combined, nums1Size + nums2Size, k);
    free(combined);
    return result;
}

// Função principal para encontrar a mediana de dois arrays ordenados
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int totalLen = nums1Size + nums2Size;
    if (totalLen % 2 == 1) {
        return findKthElement(nums1, nums1Size, nums2, nums2Size, totalLen / 2);
    } else {
        int left = findKthElement(nums1, nums1Size, nums2, nums2Size, totalLen / 2 - 1);
        int right = findKthElement(nums1, nums1Size, nums2, nums2Size, totalLen / 2);
        return (left + right) / 2.0;
    }
}