#include <iostream>
#include <random>
#include <cstring>

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

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void fillArr(T* arr, const size_t SIZE, const T leftBorder, const T rightBorder)
{
    for (size_t i = 0; i < SIZE; ++i) arr[i] = makeRandom(leftBorder, rightBorder);
}

template <typename T, const size_t SIZE>
void fillArr(T (&arr)[SIZE], const T leftBorder, const T rightBorder){fillArr(arr, SIZE, leftBorder, rightBorder);}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, const size_t SIZE>
void printArr(T (&arr)[SIZE])
{
    for (size_t i = 0; i < SIZE; i++) std::cout << arr[i] << '\t';
    std::cout << '\n' << std::endl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, const size_t HEIGHT, const size_t WIDTH>
void fillMatrix(T (&matrix)[HEIGHT][WIDTH], const T leftBorder, const T rightBorder)
{
    for (size_t i = 0; i < WIDTH; i++)
        for(size_t j = 0; j < HEIGHT; j++)
            matrix[i][j] = makeRandom(leftBorder, rightBorder);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, const size_t HEIGHT, const size_t WIDTH>
void printMatrix(T (&matrix)[HEIGHT][WIDTH])
{
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            std::cout << matrix[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n' << std::endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, const size_t SIZE>
void quickSort(T (&arr)[SIZE], size_t startIndex, size_t endIndex)
{
    unsigned elemCount = (endIndex - startIndex + 1);

    if (elemCount <= 1) return;
    else if (elemCount == 2) if (arr[startIndex] < arr[endIndex]) std::swap(arr[startIndex], arr[endIndex]);
    
    size_t pivotIndex;
    {
        const size_t midIndex {(startIndex + endIndex) / 2};
        if (arr[startIndex] > arr[midIndex]) std::swap(arr[startIndex], arr[midIndex]);
        if (arr[midIndex] < arr[endIndex]) std::swap(arr[midIndex], arr[endIndex]);

        pivotIndex = endIndex;
    }

    size_t storageIndex = startIndex;
    for (size_t checkIndex = startIndex; checkIndex < endIndex; checkIndex++)
        if (arr[checkIndex] < arr[pivotIndex])
        {
            std::swap(arr[checkIndex], arr[storageIndex]);
            storageIndex++;
        }

    std::swap(arr[pivotIndex], arr[storageIndex]);
    pivotIndex = storageIndex;

    quickSort(arr, startIndex, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, endIndex);
}

template <typename T, const size_t SIZE>
void quickSort(T (&arr)[SIZE]){quickSort(arr, 0, SIZE - 1);}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, const size_t HEIGHT, const size_t WIDTH>
void quickSort(T (&arr)[HEIGHT][WIDTH], size_t startIndex, size_t endIndex)
{
    unsigned elemCount = (endIndex - startIndex + 1);

    if (elemCount <= 1) return;
    else if (elemCount == 2) if (*arr[startIndex] < *arr[endIndex]) std::swap(*arr[startIndex], *arr[endIndex]);
    
    size_t pivotIndex;
    {
        const size_t midIndex {(startIndex + endIndex) / 2};
        if (*arr[startIndex] > *arr[midIndex]) std::swap(*arr[startIndex], *arr[midIndex]);
        if (*arr[midIndex] < *arr[endIndex]) std::swap(*arr[midIndex], *arr[endIndex]);

        pivotIndex = endIndex;
    }

    size_t storageIndex = startIndex;
    for (size_t checkIndex = startIndex; checkIndex < endIndex; checkIndex++)
        if (*arr[checkIndex] < *arr[pivotIndex])
        {
            std::swap(*arr[checkIndex], *arr[storageIndex]);
            storageIndex++;
        }

    std::swap(*arr[pivotIndex], *arr[storageIndex]);
    pivotIndex = storageIndex;

    quickSort(arr, startIndex, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, endIndex);
}

template <typename T, const size_t HEIGHT, const size_t WIDTH>
void quickSort(T (&arr)[HEIGHT][WIDTH]){quickSort(arr, 0, (HEIGHT - 1));}

///////////////////////////////////////////////////////////////////////////////////////////////////

int comp(const void* _a, const void* _b)
{
    const std::string a {std::to_string(*static_cast<const char*>(_a))};
    const std::string b {std::to_string(*static_cast<const char*>(_b))};

    const char c[] {*static_cast<const char*>(_a)};
    const char d[] {*static_cast<const char*>(_b)};
    for (size_t i = 0; i < std::min(a.size(), b.size()); i++)
    {
        if (a[i] == b[i]) continue;
        else return a[i] - b[i];
    }
    return 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

/*  1. Задана последовательность из 1000 целых чисел. Переставить элементы последовательности таким образом, чтобы они располагались в порядке возрастания.
    Написать программу, сортирующую по возрастанию одномерный массив случайных целых чисел, находящихся в интервале {50,100}. Использовать быструю сортировку   */
void task1()
{
    const size_t SIZE {20}; // !!! Взят меньший размер для наглядности
    int myArr[SIZE];
    fillArr(myArr, 50, 100);
    printArr(myArr);
    quickSort(myArr);
    printArr(myArr);

}

void task2()
{
    const size_t HEIGHT {10};
    const size_t WIDTH {HEIGHT};
    int myMatrix[HEIGHT][WIDTH];
    fillMatrix(myMatrix, 5, 61);
    printMatrix(myMatrix);
    quickSort(myMatrix);
    printMatrix(myMatrix);
    
}

void task3()
{
    setlocale(LC_ALL, "Russian");
    char myArr[][100]
    {
        "Jenny Estes",
        "Macie Jarvis",
        "Waylon Sexton",
        "Jordan Ewing",
        "Georgia Wright",
        "Jayce Paul",
        "Jamal Chavez",
        "Madilynn Glover",
        "Asher Kirby",
        "Cael Gomez",
        "Paul George",
        "Jaelyn Stone"
    };
    printArr(myArr);
    std::qsort(myArr, sizeof(myArr)/sizeof(myArr[0]), sizeof(myArr[0]), comp);
    printArr(myArr);
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /*  1. Задана последовательность из 1000 целых чисел. Переставить элементы последовательности таким образом, чтобы они располагались в порядке возрастания.
        Написать программу, сортирующую по возрастанию одномерный массив случайных целых чисел, находящихся в интервале {50,100}. Использовать быструю сортировку   */
    task1();
    
    // 2. Написать программу, сортирующую по возрастанию первый столбец двумерного массива целых чисел. Использовать быструю сортировку Массив создать из случайных чисел, расположенных в интервале {5,61}
    task2();

    // 3. Написать программу, сортирующую список студентов группы по алфавиту и использующую стандартную сортировку qsort
    task3();

}