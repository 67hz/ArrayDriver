//
//  main.cpp
//  ArrayCPP
//
//  Created by admin on 3/14/19.
//  Copyright © 2019 admin. All rights reserved.
//

#include <iostream>

class Array
{
private:
    int *A;
    int size;
    int length;
    void Swap(int *x, int *y);
    
public:
    Array()
    {
        size = 10;
        length = 0;
        A = new int[size];
    }
    
    Array(int sz)
    {
        size = sz;
        length = 0;
        A = new int[size];
    }
    
    ~Array()
    {
        delete [] A;
    }
    
    void Display();
    void Append(int x);
    void Insert(int idx, int x);
    int LinearSearch(int key);
    int BinarySearch(int key);
    int RBinarySearch(int a[], int l, int h, int key);
    int Get(int idx);
    void Set(int idx, int x);
    int Max();
    int Min();
    int Sum();
    float Avg();
    void Reverse();
    int Delete(int idx);
    void InsertSort(int x);
    int isSorted();
    void Rearrange();
    Array* Merge(Array arr2);
    Array* Union(Array arr2);
    Array* Intersection(Array arr2);
    Array* Difference(Array arr2);
};

void Array::Display()
{
    int i;
    printf("Elements in array are:\n");
    for (i=0; i<length; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// modifying array so call by address on arr
void Array::Append(int x)
{
    if(length < size)
        A[length++] = x;
}

void Array::Insert(int idx, int x)
{
    if(idx >= 0 && idx <= length)
    {
        for(int i = length; i > idx; i--)
            A[i] = A[i-1];
        A[idx] = x;
        length++;
    }
    
}

int Array::Delete(int idx)
{
    int x = 0;
    int i;
    if(idx >=0 && idx < length)
    {
        x=A[idx];
        for (i = idx; i < length - 1; i++) {
            A[i] = A[i+1];
        }
        length--;
        return x; // return deleted value
    }
    
    return 0; // if not found, return 0
}


void Array::Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int Array::LinearSearch(int key)
{
    int i;
    for (i=0; i< length; i++) {
        if(key == A[i])
        {
            Swap(&A[i], &A[0]);
            return i;
        }
    }
    return -1;
}

int Array::BinarySearch(int key)
{
    int l, mid, h;
    l = 0;
    h = length-1;
    while(l <= h)
    {
        mid = (l+h)/2;
        if(key == A[mid])
            return mid;
        else if(key < A[mid])
            h = mid-1;
        else
            l = mid+1;
    }
    
    return -1;
}

int Array::RBinarySearch(int a[], int l, int h, int key)
{
    int mid;
    
    if(l<=h)
    {
        mid = (l + h) / 2;
        if(key==a[mid])
            return mid;
        else if(key < a[mid])
            return RBinarySearch(a, l, mid-1, key);
        else
            return RBinarySearch(a, mid+1, h, key);
    }
    return -1;
}

int Array::Get(int idx)
{
    if (idx >= 0 && idx < length)
        return A[idx];
    
    return -1;
}

void Array::Set(int idx, int x)
{
    if(idx >=0  && idx < length)
        A[idx] = x;
}

int Array::Max()
{
    int max = A[0];
    int i;
    for(i=0; i< length; i++)
    {
        if(max < A[i])
            max = A[i];
    }
    return max;
}

int Array::Min()
{
    int min = A[0];
    int i;
    for(i=0; i< length; i++)
    {
        if(A[i] < min)
            min = A[i];
    }
    return min;
}

int Array::Sum()
{
    int sum = 0;
    int i;
    for(i = 0; i < length; i++)
    {
        sum += A[i];
    }
    return sum;
}

float Array::Avg()
{
    return (float)Sum() / length;
}

void Array::Reverse()
{
    int i, j;
    for(i=0, j = length - 1; i < j; i++, j--)
    {
        Swap(&A[i], &A[j]);
    }
}

void Array::InsertSort(int x)
{
    int i = length - 1;
    
    // no free space if length == size
    if(length == size)
        return;
    
    while(i>=0 && A[i] > x)
    {
        // pull values to right side of array while greater than x
        A[i+1] = A[i];
        i--;
    }
    
    // insert element at i+1 position
    A[i+1] = x;
    length++;
}

int Array::isSorted()
{
    int i;
    for(i=0; i < length - 1; i++)
    {
        if(A[i] > A[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

void Array::Rearrange()
{
    int i = 0;
    int j = length - 1;
    
    while(i < j)
    {
        while(A[i] < 0) {i++;}
        while(A[j] >= 0) {j--;}
        if(i < j)
            Swap(&A[i], &A[j]);
    }
    
}


Array* Array::Merge(Array arr2)
{
    int i,j,k; // indices
    i = j = k = 0;
    
    Array *arr3 = new Array(length + arr2.length);
    
    while (i < length && j < arr2.length)
    {
        if(A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else
            arr3->A[k++] = arr2.A[j++];
    }
    
    for(; i < length; i++)
    {
        arr3->A[k++] = A[i];
    }
    
    for(; j < arr2.length; j++)
    {
        arr3->A[k++] = arr2.A[j];
    }
    
    arr3->length = length + arr2.length;
    arr3->size = 10;
    
    return arr3;
}

Array* Array::Union(Array arr2)
{
    int i, j, k;
    i = j = k = 0;
    Array *arr3 = new Array(length + arr2.length);
    
    while(i < length && j < arr2.length)
    {
        if(A[i] == arr2.A[j])
        {
            arr3->A[k++] = A[i++];
            j++;
        }
        else if(A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else
            arr3->A[k++] = arr2.A[j++];
    }
    
    for(; i < length; i++, k++)
        arr3->A[k] = A[i];
    
    for(; j < arr2.length; j++, k++)
        arr3->A[k] = arr2.A[j];
    
    // k will be length of 3rd array
    arr3->length = k;
    arr3->size = 10;
    
    return arr3;
    
}

Array* Array::Intersection(Array arr2)
{
    int i, j, k;
    i = j = k = 0;
    
    Array *arr3 = new Array(length + arr2.length);
    
    while(i < length && j < arr2.length)
    {
        if(A[i] < arr2.A[j])
            i++;
        else if (arr2.A[j] < A[i])
            j++;
        else if (A[i] == arr2.A[j])
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }
    
    arr3->length = k;
    arr3->size = 10;
    
    return arr3;
}

Array* Array::Difference(Array arr2)
{
    int i, j, k;
    i = j = k = 0;
    Array *arr3 = new Array(length + arr2.length);
    
    while(i < length && j < arr2.length)
    {
        if(A[i] == arr2.A[j])
        {
            i++;
            j++;
        }
        else if(A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else if(arr2.A[j] < A[i])
            j++;
    }
    
    for(; i< length; i++, k++)
        arr3->A[k] = A[i];
    
    arr3->length = k;
    arr3->size = 10;
    
    return arr3;
}

int main()
{
    Array *arr1;
    int ch, sz, x, idx;

    
    printf("Enter size of Array: ");
    scanf("%d", &sz);
    
    
    arr1 = new Array(sz);

    while(ch != 100)
    {
        
        printf("Menu\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Sum\n");
        printf("5. Display\n");
        printf("100. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        
        switch(ch)
        {
            case 1:
                printf("Enter an element and index\n");
                scanf("%d%d", &x, &idx);
                arr1->Insert(idx, x);
                break;
                
            case 2:
                printf("Delete an element at index?\n");
                scanf("%d", &idx);
                x=arr1->Delete(idx);
                printf("Deleted Element is %d\n", x);
                break;
            case 3:
                printf("Enter element to search\n");
                scanf("%d", &x);
                idx = arr1->LinearSearch(x);
                printf("Element found at index: %d\n", idx);
                break;
            case 4:
                printf("Sum is %d\n", arr1->Sum());
                break;
            case 5:
                printf("Displaying array\n");
                arr1->Display();
                break;
        }
    }
    
    
    
    return 0;
}
