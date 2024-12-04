#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int left;
    int right;
    int height;
} Building;


typedef struct {
    int x;
    int height;
} KeyPoint;

int compareKeyPoints(const void* a, const void* b) {
    KeyPoint* p1 = (KeyPoint*)a;
    KeyPoint* p2 = (KeyPoint*)b;

    if (p1->x != p2->x)
        return p1->x - p2->x;
    return p2->height - p1->height;
}


KeyPoint* mergeHorizons(KeyPoint* left, int leftSize, KeyPoint* right, int rightSize, int* returnSize) {
    KeyPoint* result = (KeyPoint*)malloc((leftSize + rightSize) * sizeof(KeyPoint));
    int l = 0, r = 0, idx = 0;
    int leftHeight = 0, rightHeight = 0, currentHeight = 0;

    while (l < leftSize && r < rightSize) {
        int x;
        if (left[l].x < right[r].x) {
            x = left[l].x;
            leftHeight = left[l].height;
            l++;
        } else if (left[l].x > right[r].x) {
            x = right[r].x;
            rightHeight = right[r].height;
            r++;
        } else {
            x = left[l].x;
            leftHeight = left[l].height;
            rightHeight = right[r].height;
            l++;
            r++;
        }

        int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
        if (maxHeight != currentHeight) {
            result[idx++] = (KeyPoint){x, maxHeight};
            currentHeight = maxHeight;
        }
    }

    while (l < leftSize) result[idx++] = left[l++];
    while (r < rightSize) result[idx++] = right[r++];

    *returnSize = idx;
    return result;
}

KeyPoint* getSkyline(Building* buildings, int start, int end, int* returnSize) {
    if (start == end) {
        KeyPoint* result = (KeyPoint*)malloc(2 * sizeof(KeyPoint));
        result[0] = (KeyPoint){buildings[start].left, buildings[start].height};
        result[1] = (KeyPoint){buildings[start].right, 0};
        *returnSize = 2;
        return result;
    }

    int mid = (start + end) / 2;
    int leftSize = 0, rightSize = 0;
    KeyPoint* left = getSkyline(buildings, start, mid, &leftSize);
    KeyPoint* right = getSkyline(buildings, mid + 1, end, &rightSize);

    KeyPoint* result = mergeHorizons(left, leftSize, right, rightSize, returnSize);
    free(left);
    free(right);

    return result;
}

bool compareKeyPointArrays(KeyPoint* arr1, int size1, KeyPoint* arr2, int size2) {
    if (size1 != size2) return false;
    for (int i = 0; i < size1; i++) {
        if (arr1[i].x != arr2[i].x || arr1[i].height != arr2[i].height) {
            return false;
        }
    }
    return true;
}

void runTests() {
    bool allTestsPassed = true;

    Building test1Buildings[] = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    KeyPoint expected1[] = {{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}};
    int test1Size = 0;
    KeyPoint* result1 = getSkyline(test1Buildings, 0, 4, &test1Size);
    if (!compareKeyPointArrays(result1, test1Size, expected1, sizeof(expected1) / sizeof(expected1[0]))) {
        printf("Тест 1 не пройден!\n");
        allTestsPassed = false;
    } else {
        printf("Тест 1 пройден.\n");
    }
    free(result1);

    Building test2Buildings[] = {{0, 2, 3}, {2, 5, 3}};
    KeyPoint expected2[] = {{0, 3}, {5, 0}};
    int test2Size = 0;
    KeyPoint* result2 = getSkyline(test2Buildings, 0, 1, &test2Size);
    if (!compareKeyPointArrays(result2, test2Size, expected2, sizeof(expected2) / sizeof(expected2[0]))) {
        printf("Тест 2 не пройден!\n");
        allTestsPassed = false;
    } else {
        printf("Тест 2 пройден.\n");
    }
    free(result2);

    if (allTestsPassed) {
        printf("Все тесты пройдены успешно!\n");
    } else {
        printf("Некоторые тесты не прошли.\n");
    }
}

int main() {
    runTests();
    return 0;
}
