#pragma once
#include <iostream>
#include <bits/stdc++.h>
#include "Sequence.h"
#include "ArraySequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "LinkedListSequence.h"
#include "Complex.h"

template <typename T>
void PrintVec(Sequence<T>* s) {
    s->PrintArray();
}

template <typename T>
void BubbleSort(Sequence<T>* sec,  int (*cmp)(T,T))
{
    int i, j;
    for (i = 0; i < sec->GetLength() - 1; i++)

        for (j = 0; j < sec->GetLength() - i - 1; j++)
            if (cmp(sec->Get(j), sec->Get(j + 1)))
                swap(sec->Get(j), sec->Get(j + 1));
}

template <typename T>
void CocktailSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    bool swapped = true;
    int start = 0;
    int end = sec->GetLength() - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (cmp(sec->Get(i), sec->Get(i + 1))) {
                swap(sec->Get(i), sec->Get(i + 1));
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (cmp(sec->Get(i), sec->Get(i + 1))) {
                swap(sec->Get(i), sec->Get(i + 1));
                swapped = true;
            }
        }
        start++;
    }
}

template <typename T>
void InsertionSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    int i, j;
    T key;
    for (i = 1; i < sec->GetLength(); i++)
    {
        key = sec->Get(i);
        j = i - 1;
        while (j >= 0 && cmp(sec->Get(j), key))
        {
            sec->Get(j + 1) = sec->Get(j);
            j = j - 1;
        }
        sec->Get(j + 1) = key;
    }
}

template <typename T>
void SelectionSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    int i, j, min_idx;
    for (i = 0; i < sec->GetLength() - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < sec->GetLength(); j++)
            if (!cmp(sec->Get(j), sec->Get(min_idx)))
                min_idx = j;
        swap(sec->Get(min_idx), sec->Get(i));
    }
}

//Разобраться с + 1
template <typename T>
int BinarySearch(Sequence<T>* sec, T item,
                 T low, T high, int (*cmp)(T,T))
{
    if (high <= low)
        if (cmp(item, sec->Get(low))) {
            return low + 1;
        }
        else {
            return low;
        }


    T mid = (low + high) / 2;

    if (item == sec->Get(mid))
        return mid + 1;

    if (cmp(item, sec->Get(mid)))
        return BinarySearch(sec, item,
                            mid + 1, high, cmp);
    return BinarySearch(sec, item, low,
                        mid - 1, cmp);
}

template <typename T>
void InsertionSortBinary(Sequence<T>* sec, int (*cmp)(T,T))
{
    int loc, j;
    T selected;

    for (int i = 1; i < sec->GetLength(); ++i)
    {
        j = i - 1;
        selected = sec->Get(i);

        // find location where selected should be inseretd
        loc = BinarySearch(sec, selected, 0, j, cmp);

        // Move all elements after location to create space
        while (j >= loc)
        {
            sec->Get(j + 1) = sec->Get(j);
            j--;
        }
        sec->Get(j + 1) = selected;
    }
}

template <typename T>
void CountSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    int max = sec->Get(0);
    for (int i = 0; i < sec->GetLength(); i++) {
        if (cmp(sec->Get(i), max)) {
            max = sec->Get(i);
        }
    }
    // создаем целочисленный массив размера `n` для хранения отсортированного массива
    int output[sec->GetLength()];

    // создать целочисленный массив размером `k + 1`, инициализированный всеми нулями
    int freq[max + 1];
    memset(freq, 0, sizeof(freq));

    // 1. Используя значение каждого элемента входного массива в качестве индекса,
    // сохраняем счетчик каждого целого числа в `freq[]`
    for (int i = 0; i < sec->GetLength(); i++) {
        freq[sec->Get(i)]++;
    }

    // 2. Вычислить начальный индекс для каждого целого числа
    int total = 0;
    for (int i = 0; i < max + 1; i++)
    {
        int oldCount = freq[i];
        freq[i] = total;
        total += oldCount;
    }

    // 3. Копируем в выходной массив, сохраняя порядок входов с одинаковыми ключами
    for (int i = 0; i < sec->GetLength(); i++)
    {
        output[freq[sec->Get(i)]] = sec->Get(i);
        freq[sec->Get(i)]++;
    }

    // копируем выходной массив обратно во входной массив
    for (int i = 0; i < sec->GetLength(); i++) {
        sec->Get(i) = output[i];
    }
}



template <typename T>
void Merge(Sequence<T>* sec, int const left, int const mid,
           int const right, int (*cmp)(T,T))
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto* leftArray = new ArraySequence<T>;
    auto* rightArray = new ArraySequence<T>;

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray->Append(sec->Get(left + i));
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray->Append(sec->Get(mid + 1 + j));


    auto indexOfSubArrayOne = 0;
    auto indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (!cmp(leftArray->Get(indexOfSubArrayOne), rightArray->Get(indexOfSubArrayTwo))) {
            sec->Get(indexOfMergedArray) = leftArray->Get(indexOfSubArrayOne);
            indexOfSubArrayOne++;
        }
        else {
            sec->Get(indexOfMergedArray) = rightArray->Get(indexOfSubArrayTwo);
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        sec->Get(indexOfMergedArray) = leftArray->Get(indexOfSubArrayOne);
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        sec->Get(indexOfMergedArray) = rightArray->Get(indexOfSubArrayTwo);
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
//    ~leftArray;
//    ~rightArray;
}
template <typename T>
void MergeSort(Sequence<T>* sec, int (*cmp)(T,T)) {
    MergeSortLocal(sec, 0, sec->GetLength() - 1, cmp);
}

template <typename T>
void MergeSortLocal(Sequence<T>* sec, int const begin, int const end, int (*cmp)(T,T))
{
    if (begin >= end)
        return; // Returns recursively
    auto mid = begin + (end - begin) / 2;
    MergeSortLocal(sec, begin, mid, cmp);
    MergeSortLocal(sec, mid + 1, end, cmp);
    Merge(sec, begin, mid, end, cmp);
}

template <typename T>
void Heapify(Sequence<T>* sec, int n, int i, int (*cmp)(T,T))
{

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && cmp(sec->Get(l), sec->Get(largest)))
        largest = l;

    if (r < n && cmp(sec->Get(r), sec->Get(largest)))
        largest = r;

    if (largest != i) {
        swap(sec->Get(i), sec->Get(largest));
        Heapify(sec, n,largest, cmp);
    }
}

template <typename T>
void HeapSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    for (int i = sec->GetLength() / 2 - 1; i >= 0; i--)
        Heapify(sec, sec->GetLength(), i, cmp);

    for (int i = sec->GetLength() - 1; i > 0; i--) {
        swap(sec->Get(0), sec->Get(i));
        Heapify(sec, i, 0, cmp);
    }
}

template <typename T>
int Partition(Sequence<T>* sec, int start, int end, int (*cmp)(T,T))
{

    T pivot = sec->Get(start);

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (!cmp(sec->Get(i), pivot))
            count++;
    }

    int pivotIndex = start + count;
    swap(sec->Get(pivotIndex), sec->Get(start));
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex) {

        while (!cmp(sec->Get(i), pivot)) {
            i++;
        }

        while (cmp(sec->Get(j), pivot)) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(sec->Get(i++), sec->Get(j--));
        }
    }

    return pivotIndex;
}


template <typename T>
void QuickSort(Sequence<T>* sec, int (*cmp)(T,T)) {
    QuickSortLocal(sec, 0, sec->GetLength() - 1, cmp);
}


template <typename T>
void QuickSortLocal(Sequence<T>* sec, int start, int end, int (*cmp)(T,T))
{

    if (start >= end)
        return;

    int p = Partition(sec, start, end, cmp);

    // Sorting the left part
    QuickSortLocal(sec, start, p - 1, cmp);

    // Sorting the right part
    QuickSortLocal(sec, p + 1, end, cmp);
}

template <typename T>
void ShellSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    for (int gap = sec->GetLength() / 2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < sec->GetLength(); i += 1)
        {

            T temp = sec->Get(i);

            int j;
            for (j = i; j >= gap && cmp(sec->Get(j - gap), temp); j -= gap) {
                sec->Get(j) = sec->Get(j - gap);
            }

            sec->Get(j) = temp;
        }
    }
}



template <typename T>
void CompAndSwap(Sequence<T>* sec, int i, int j, int dir, int (*cmp)(T,T))
{
    if (dir == (cmp(sec->Get(i), sec->Get(j)))) {
        swap(sec->Get(i), sec->Get(j));
    }
}

template <typename T>
void BitonicMerge(Sequence<T>* sec, int low, int cnt, int dir, int (*cmp)(T,T))
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            CompAndSwap(sec, i, i + k, dir, cmp);
        }
        BitonicMerge(sec, low, k, dir, cmp);
        BitonicMerge(sec, low + k, k, dir, cmp);
    }
}

template <typename T>
void BitonicSortL(Sequence<T>* sec, int low, int cnt, int dir, int (*cmp)(T,T))
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        BitonicSortL(sec, low, k, 1, cmp);

        BitonicSortL(sec, low + k, k, 0, cmp);

        BitonicMerge(sec, low, cnt, dir, cmp);
    }
}

template <typename T>
void BitonicSort(Sequence<T>* sec, int (*cmp)(T,T))
{
    BitonicSortL(sec ,0, sec->GetLength(), 1, cmp);
}


#ifndef SEM2LAB1_ALGORITHMS_H
#define SEM2LAB1_ALGORITHMS_H

#endif //SEM2LAB1_ALGORITHMS_H
