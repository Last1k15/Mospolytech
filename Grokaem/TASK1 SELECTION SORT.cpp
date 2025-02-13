#include <iostream>
#include <random>

template
<
    typename arithm_t,
    typename = typename std::enable_if<std::is_arithmetic<arithm_t>::value>
>
arithm_t makeRandom(arithm_t start, arithm_t end)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<arithm_t> dist(start, end);
    return dist(gen);
}

/////////////////////////////////////////////////////

template
<
    typename arr_t,
    typename = typename std::enable_if<std::is_array<arr_t>::value>
>
void fillArr(arr_t arr, const size_t SIZE, const size_t leftBorder, const size_t rightBorder)
{
    for (size_t i = 0; i < SIZE; i++) arr[i] = makeRandom(leftBorder, rightBorder);
}

template
<
    typename arithm_t,
    typename = typename std::enable_if<std::is_arithmetic<arithm_t>::value>
>
void printArr (arithm_t* arr, const size_t SIZE) 
{
    for (size_t i = 0; i < SIZE; i++) std::cout << arr[i] << '\t';
    std::cout <<'\n';
}

template<>
void printArr (std::string* arr, const size_t SIZE) 
{
    for (size_t i = 0; i < SIZE; i++) std::cout << arr[i] << '\n';
    std::cout <<'\n';
}

/////////////////////////////////////////////////////

template 
<
    typename arithm_t,
    typename = typename std::enable_if<std::is_arithmetic<arithm_t>::value>
>
void selectionSort(arithm_t* arr, const size_t SIZE, const bool REVERSE = false)
{
    if (SIZE <= 1) return;

    size_t storageIndex = 0;
    size_t nextElemIndex = 0;

    {
        while (storageIndex < (SIZE - 1))
        {
            for (size_t i = storageIndex; i < SIZE; ++i)
            {
                const bool fitCondition
                {
                    REVERSE ?
                    arr[i] > arr[nextElemIndex] :
                    arr[i] < arr[nextElemIndex]
                };
                
                nextElemIndex = (fitCondition) ? i : nextElemIndex;
            }
                
            std::swap(arr[storageIndex], arr[nextElemIndex]);
            storageIndex++;
            nextElemIndex = storageIndex;
        }
    }
}

template <>
void selectionSort(std::string* arr, const size_t SIZE, const bool REVERSE)
{
    if (SIZE <= 1) return;

    size_t storageIndex = 0;
    size_t nextElemIndex = 0;

    while (storageIndex < (SIZE - 1))
    {
        for (size_t searchIndex = storageIndex + 1; searchIndex < SIZE; ++searchIndex)
        {
            const size_t minStrLen {std::min(arr[searchIndex].length(), arr[nextElemIndex].length())};
            bool isNextElem;

            for (size_t charIndex = 0; charIndex < minStrLen; ++charIndex)
            {
                if (arr[searchIndex][charIndex] == arr[nextElemIndex][charIndex]) continue;
                isNextElem = REVERSE ? arr[searchIndex][charIndex] > arr[nextElemIndex][charIndex] : arr[searchIndex][charIndex] < arr[nextElemIndex][charIndex];
                if (isNextElem) nextElemIndex = searchIndex;
                break;
            }
        }
        std::swap(arr[storageIndex], arr[nextElemIndex]);
        storageIndex++;
        nextElemIndex = storageIndex;
    }
}

/////////////////////////////////////////////////////

// 1. Написать программу, сортирующую по возрастанию одномерный массив случайных целых чисел, находящихся в интервале {2,103}. Использовать сортировку выбором. 
void task1()
{
    const size_t SIZE {makeRandom<size_t>(5, 20)};
    int myArr[SIZE];
    fillArr(myArr, SIZE, 2, 103);
    printArr(myArr, SIZE);
    selectionSort(myArr, SIZE, false);
    printArr(myArr, SIZE);
    std::cout << std::endl;
}

// 2. Написать программу, сортирующую по убыванию одномерный массив случайных целых чисел, находящихся в интервале {0,100}. 
void task2()
{
    const size_t SIZE {makeRandom<size_t>(5, 20)};
    int myArr[SIZE];
    fillArr(myArr, SIZE, 0, 100);
    printArr(myArr, SIZE);
    selectionSort(myArr, SIZE, true);
    printArr(myArr, SIZE);
    std::cout << std::endl;
}

// 3. Написать программу, сортирующую список телефонов по возрастанию и использующую  сортировку выбором. Телефон задан в виде строки. Например, 23-45-67.
void task3()
{
    std::string myArr[]
    {
        "+7 9153113923",
        "+7 8125967251",
        "+7 9120219822",
        "+7 8124807724",
        "+7 9126219822",
        "+7 7129206349",
        "+7 9122746214"
    };

    const size_t SIZE = sizeof(myArr) / sizeof(std::string);
    printArr(myArr, SIZE);
    selectionSort(myArr, SIZE, false);
    printArr(myArr, SIZE);
}

/////////////////////////////////////////////////////

int main()
{
    // 1. Написать программу, сортирующую по возрастанию одномерный массив случайных целых чисел, находящихся в интервале {2,103}. Использовать сортировку выбором. 
    task1();
    
    // 2. Написать программу, сортирующую по убыванию одномерный массив случайных целых чисел, находящихся в интервале {0,100}. 
    task2();

    // 3. Написать программу, сортирующую список телефонов по возрастанию и использующую  сортировку выбором. Телефон задан в виде строки. Например, 23-45-67.
    task3();
}