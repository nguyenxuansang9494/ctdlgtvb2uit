#include <iostream>

int input(int *&arr)
{
    int n;
    std::cout << "Nhap so phan tu: ";
    std::cin >> n;
    arr = new int[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    return n;
}

void output(int *arr, int count)
{
    std::cout << "Mang: " << std::endl;
    for (size_t i = 0; i < count; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int linearSearch(int *arr, int count, int target)
{
    for (size_t i = 0; i < count; i++)
    {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int binarySearch(int *arr, int count, int target)
{
    if (count == 0)
        return -1;
    if (count == 1 && arr[count / 2] != target)
        return -1;
    if (arr[count / 2] == target)
        return count / 2;
    if (arr[count / 2] > target)
        return binarySearch(arr, count / 2, target);
    if (arr[count / 2] < target)
    {
        int index = binarySearch(arr + count / 2 + 1, count - count / 2 - 1, target);
        return index == -1 ? -1 : count / 2 + 1 + index;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int *arr;
    int n = input(arr);
    output(arr, n);
    std::cout << "Nhap so can tim: ";
    int target;
    std::cin >> target;
    int index = binarySearch(arr, n, target);
    // index = -1 <=> khong chua phan tu can tim
    std::cout << index << std::endl;
    return 0;
}
