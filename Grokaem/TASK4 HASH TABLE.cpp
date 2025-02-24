#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <set>
#include <algorithm>

int makeRandom(int startValue, int endValue)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(startValue, endValue);

    return static_cast<int>(dist(gen));
}

////////////////////////////////////////////////////////////////////////////////////////////////

template <typename arithm_t, typename = typename std::enable_if<std::is_arithmetic<arithm_t>::value>>
void printArr(arithm_t* arr, const size_t SIZE)
{
    for (size_t i = 0; i < SIZE; i++) std::cout << arr[i] << '\t';
    std::cout << '\n';
}

////////////////////////////////////////////////////////////////////////////////////////////////

template <typename arithm_t, typename = typename std::enable_if<std::is_arithmetic<arithm_t>::value>>
void fill_inputfile(const size_t _INPUTCOUNT, const arithm_t _LEFTBORDER, const arithm_t _RIGHTBORDER)
{
    const size_t zeroIndex {static_cast<size_t>(makeRandom(0, _INPUTCOUNT / 2))};
    std::ofstream file ("input.txt");
    for (size_t i = 0; i < _INPUTCOUNT; i++)
    {
        if (i == zeroIndex) file << 0 << ' ';
        else file << makeRandom(_LEFTBORDER, _RIGHTBORDER) << ' ';
    }
        
    file.close();
}

void read_inputfile(std::set<int>& set)
{
    std::ifstream file ("input.txt");
    std::string temp;
    while (!file.eof())
    {
        file >> temp;
        if (temp == "0") return;
        if (temp.at(0) == '-') set.erase(std::stoi(temp.substr(1)));
        else set.insert(std::stoi(temp));
    }
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /*  Условие
        Дана последовательность целых чисел. Каждое прочитанное число обрабатывается следующим образом:
        если число больше нуля, оно добавляется к текущему множеству чисел;
        если число меньше нуля, противоположное ему число удаляется из текущего множества чисел;
        если число равно нулю, множество чисел выводится в порядке возрастания и программа завершает работу.
        Формат входного файла
        Входной файл содержит последовательность чисел.
        Формат выходного файла
        Выходной файл должен содержать последовательность чисел, отсортированных по возрастанию.
        Ограничения
        Количество чисел находится в диапазоне от 0 до 10^6, сами числа — в диапазоне от  − 2^31 до 2^31 − 1.

        Примечание: предлагается решать задачу с использованием хэш-таблиц.
        Примеры теста:
        Входной файл (input.txt) 3 2 1 3 0

        Выходной файл (output.txt) 1 2 3                                                                        */

    const size_t INPUT_COUNT {static_cast<size_t>(makeRandom(0, 1e6 - 1))};
    std::set<int> inputSet;

    const int minValue {static_cast<int>(-1*std::pow(2, 31))};
    const int maxValue {static_cast<int>(std::pow(2, 31) - 1)};

    fill_inputfile(INPUT_COUNT, minValue, maxValue);
    read_inputfile(inputSet);
    for (int n : inputSet) std::cout << n << '\n';
    
}