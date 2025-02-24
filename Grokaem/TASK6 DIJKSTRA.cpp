<<<<<<< HEAD
#include <iostream>
#include <fstream>
#include <random>
#include <queue>
#include <limits>
#include <unordered_set>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>>
T makeRandom(T start, T end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist{start, end};
    return dist(gen);
}


class task1
{

    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                                    //
    //      Задача №1. Дейкстра                                                                                           \\
    ||                                                                                                                    ||
    \\  Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной вершины до другой.           //
    //                                                                                                                    \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

    mutable int** graphMatrix {nullptr}; // Матрица смежности
    mutable int* minWeight {nullptr}; // Массив минимального веса узлов
    const int inf {std::numeric_limits<int>::max()}; // Определим бесконечность как верхнюю границу int
    
    int answer;
    size_t N, S, F;
    


    void makeData()
    {

        /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
        \\                                                                                                                        //
        //  В первой строке содержатся три числа: N, S и F (1≤ N≤ 100, 1≤ S, F≤ N),                                               \\
        \\  где N – количество вершин графа, S – начальная вершина, а F – конечная.                                               //
        ||  В следующих N строках вводится по N чисел, не превосходящих 100, – матрица смежности графа,                           ||
        //  где -1 означает отсутствие ребра между вершинами, а любое неотрицательное число – присутствие ребра данного веса.     \\
        \\  На главной диагонали матрицы записаны нули.                                                                           //
        //                                                                                                                        \\
        \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

        // Открываем файл на запись
        std::ofstream file {"input.txt"};
        
        // Генерируем константы
        const size_t N = makeRandom<size_t>(1, 100);
        const size_t S = makeRandom<size_t>(0, (N - 1));    
        const size_t F = makeRandom<size_t>(0, (N - 1));
        
        // Записываем константы
        file << N << ' ' << S << ' ' << F << '\n';
        
        size_t zeroIndex {0}; // Отслеживание главной диагонали
        
        // Генерируем и записываем матрицу смежности
        for (size_t col = 0; col < N; col++)
        {
            for (size_t row = 0; row < N; row++)
            {
                if (row == zeroIndex) file << 0 << ' ';
                else file << (makeRandom(0,1) ? -1 : makeRandom(0, 100)) << ' '; // 50% на отсутствие ребра
            }
            zeroIndex++;
            file << '\n';
        }

        // Закрываем файл
        file.close();
    }

    bool readData()
    {
        // Открываем файл на чтение
        std::ifstream file {"input.txt"};
        
        // Буфер ввода
        std::string readValue;
        
        // Считываем константы
        file >> readValue;
        N = static_cast<size_t>(std::stoi(readValue));
        file >> readValue;
        S = static_cast<size_t>(std::stoi(readValue));
        file >> readValue;
        F = static_cast<size_t>(std::stoi(readValue));
        
        
        // Если старт и финишь в одном узле, то смысла читать матрицу нет, возвращаем сигнал same = true
        if (S == F) return true;
        
        // Выделяем память
        graphMatrix = new int*[N];
        minWeight = new int[N];


        
        // Заполняем массивы данных
        for (size_t row = 0; row < N; row++)
        {
            graphMatrix[row] = new int[N];
            minWeight[row] = inf; // Начальный вес каждого непроверенного узла - бесконечность
            for (size_t col = 0; col < N; col++)
            {
                file >> readValue;
                graphMatrix[row][col] = std::stoi(readValue);
            }
        }

        // Закрываем файл
        file.close();

        // Считывание прошло корректно, same = false
        return false;
    }

    int calcAnswer() const
    {
        // Вес начальной позиции должен быть нулем
        minWeight[S] = 0;
        
        // Контейнеры для реализации BFS
        std::queue<size_t> order;
        std::unordered_set<size_t> cache;
        
        // Добавляем первый стартовый узел первым в очередь
        order.push(S);
        

        // Итерируемся пока очередь не опустеет
        while (!order.empty())
        {
            // Текущий узел
            size_t Node {order.front()};
            order.pop();
            
            // Сразу добавляем в кэш
            cache.insert(Node);
            
            // Проходимся по связанным с текущим узлам
            for (size_t linkedNode = 0; linkedNode < N; linkedNode++)
            {
                // Пропускаем несвязанные узлы
                bool noEdge {graphMatrix[Node][linkedNode] == -1};
                if (noEdge) continue;
                
                // Пропускаем проверенные узлы
                bool inCache {cache.find(linkedNode) != cache.end()};
                if (inCache) continue;
                
                // Определяем минимальный вес связанного узла
                minWeight[linkedNode] = std::min(graphMatrix[Node][linkedNode] + minWeight[Node], minWeight[linkedNode]);
                
                // Добавляем связанный узел в очередь 
                if (linkedNode != F) order.push(linkedNode);
            }
        }

        // Если вес остался бесконечным, попасть в финальный узел невозможно
        if (minWeight[F] == inf) return -1;
        else return minWeight[F];
    }
    
    void printAll()
    {
        std::cout << "\n\nNodes:\t" << N << "\nFrom:\t" << S << "\nTo:\t" << F << "\n\n";
  
        // answer == 0 -> readData не считал матрицу 
        if (graphMatrix != nullptr && answer != 0)
        {
            for (size_t row = 0; row < N; row++)
            {
                for (size_t col = 0; col < N; col++)
                    std::cout << graphMatrix[row][col] << ' ';
                std::cout << '\n';
            }
        }

        std::cout << "\nAnswer:\t" << answer;
    }



    public:
    void complete()
    {
        // Заполняем файл случайными значениями
        makeData();
        
        // Сигнал от readData, равен ли стартовый узел конечному
        bool sameNodes;
        sameNodes = readData();

        // Если стартовый и конечный узел равны, то вес равен нулю
        answer = sameNodes ? 0 : calcAnswer();
        
        // Выводим все данные
        printAll();
    }
    
    task1(){}
    
    ~task1()
    {
        if (graphMatrix != nullptr)
            for (size_t row = 0; row < N; row++) delete[] graphMatrix[row];
        delete[] graphMatrix;
        delete[] minWeight;
    }
};



/*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
\\                                                                                                                    //
//      Задача №2. Заправки                                                                                           \\
\\                                                                                                                    //
//    В стране N городов, некоторые из которых соединены между собой дорогами.                                        \\
\\    Для того, чтобы проехать по одной дороге, требуется один бак бензина.                                           //
||    В каждом городе бак бензина имеет разную стоимость.                                                             ||
//    Вам требуется добраться из первого города в N-ый, потратив как можно меньшее денег.                             \\
\\    Покупать бензин впрок нельзя.                                                                                   //
//                                                                                                                    \\
\\    Требуется вывести одно число – суммарную стоимость маршрута или -1, если добраться невозможно.                  //
//                                                                                                                    \\
\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

class task2
{
    size_t N, M;

    mutable int* cost {nullptr};
    mutable int* minCost {nullptr};
    const int inf {std::numeric_limits<int>::max()};

    std::unordered_set<size_t>* townNeighbours {nullptr}; // Корректнее и быстрее использовать вектор, если все данные полезны. set фильтрует бесполезную информацию от makeData
    int answer {-2};
    



void makeData()
{   
    
    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                                    //
    //    В первой строке вводится число N (1≤N≤100), в следующей строке идет N чисел,                                    \\
    \\    i-ое из которых задает стоимость бензина в i-ом городе (всё это целые числа из диапазона от 0 до 100).          //
    //    Затем идет число M – количество дорог в стране, далее идет описание самих дорог.                                \\
    \\    Каждая дорога задается двумя числами – номерами городов, которые она соединяет.                                 //
    //    Все дороги двухсторонние (то есть по ним можно ездить как в одну, так и в другую сторону),                      \\
    \\    между двумя городами всегда существует не более одной дороги, не существует дорог, ведущих из города в себя.    //                                                                 
    //                                                                                                                    \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/
    
    // Открываем файл на запись
    std::ofstream file{"input.txt"};
    
    // Генерируем и записываем N
    const size_t N {makeRandom<size_t>(1, 100)};
    file << N << '\n';
    
    // Генерируем и записываем цены на бензин
    for (size_t i = 0; i < N; i++) file << makeRandom(0, 100) << ' ';
    file << '\n';

    // Генерируем и записываем M
    const size_t M {makeRandom<size_t>(N, 4*N)};
    file << M << '\n';
    
    // Генерируем и записываем пары городов, связанные дорогами
    for (size_t i = 0; i < M * 2; i++) file << makeRandom<size_t>(0, (N-1)) << ' ';
    

    // Закрываем файл
    file.close();
}

    bool readData()
    {
        // Открываем файл на чтение 
        std::ifstream file {"input.txt"};
        
        // Буфер ввода 
        std::string readValue;
        
        // Считываем N
        file >> readValue;
        N = static_cast<size_t>(std::stoi(readValue));

        // Если город один, то возвращаем сигнал onlyOne == true
        if (N <= 1) return true;
        
        // Выделяем память
        cost = new int[N];
        minCost = new int[N];
        townNeighbours = new std::unordered_set<size_t>[N]; 

        
        // Заполняем массивы данными
        for (size_t i = 0; i < N; i++)
        {
            file >> readValue;
            cost[i] = std::stoi(readValue);
            minCost[i] = inf;
        }
        
        // Вынуждены всегда покупать бензин в первом городе
        minCost[0] = cost[0];
        
        // Из последнего города никуда не уезжаем, бензин покупать не нужно
        cost[N-1] = 0;

        
        // Считываем M
        file >> readValue;
        M = static_cast<size_t>(std::stoi(readValue));

        // Проходим по парам соединенных городов и добавляем связь в обе стороны
        for (size_t i = 0; i < M * 2; i++)
        {
            file >> readValue;
            
            size_t town1, town2;
            if (i % 2 == 0) town1 = static_cast<size_t>(std::stoi(readValue));
            else
            {
                town2 = static_cast<size_t>(std::stoi(readValue));
                if (town1 == town2) continue;
                townNeighbours[town1].insert(town2);
                townNeighbours[town2].insert(town1);
            }
        }

        
        // Закрываем файл
        file.close();

        // N > 1, значит возвращаем onlyOne = false
        return false;
    }
    
    int calcAnswer() const
    {
        // Контейнеры для реализации BFS
        std::queue<size_t> order;
        std::unordered_set<size_t> cache;
        
        // Добавляем первый город в очередь
        order.push(0);
        
        // Проходимся по очереди пока не опустеет
        while (!order.empty())
        {

            // Текущий город
            size_t town = order.front();
            order.pop();

            // Сразу добавим текущий город в проверенные
            cache.insert(town);

            // Нет дорог
            if (townNeighbours[town].empty()) continue;

            // Проходимся по соседям
            for (size_t neighbour : townNeighbours[town])
            {
                // Пропускаем проверенных
                if (cache.find(neighbour) != cache.end()) continue;
                
                // Определяем минимальную сумму цен
                minCost[neighbour] = std::min(minCost[town] + cost[neighbour], minCost[neighbour]);
                
                // Добавляем соседа в очередь на проверку
                order.push(neighbour);
            }
        }

        // Возвращаем минимальную цену для последнего города
        return (minCost[N-1] != inf ? minCost[N-1] : -1);
    }

    void printAll() const
    {
        std::cout << "\n\nTowns:\t" << N;
        std::cout << "\nRoads:\t" << M  << "\n\n";
    
        std::cout << "Town\tCost\tNeighbours\n";
        for (size_t i = 0; i < N; i++)
        {
            std::cout << (i + 1);
            if (N <= 1) break;
            std::cout << '\t' << cost[i];
            if (townNeighbours[i].empty()) {std::cout << '\n';continue;}
            else std::cout << '\t';
            for (size_t n : townNeighbours[i])
                std::cout << (n + 1) << ' ';
            std::cout << '\n';
        }
        std::cout << "\nAnswer:\t" << answer << '\n';
    }

    public:
    void complete()
    {
        // Заполняем файл случайными значениями
        makeData();
        
        // сигнал от readData, один ли город в стране
        bool onlyOne {false};
        onlyOne = readData();

        // Если в стране всего один город, значит тратиться на бензин не нужно
        answer = onlyOne ? 0 : calcAnswer();
        
        // Выводим все данные
        printAll();
    }

    task2(){}

    ~task2()
    {
        delete[] cost;
        delete[] minCost;
        delete[] townNeighbours;
    }
};

int main()
{
    while (true)
    {
        task1 graph;
        graph.complete();
        std::cin.get();

        task2 countryTravel;
        countryTravel.complete();
        std::cin.get();
    }
=======
#include <iostream>
#include <fstream>
#include <random>
#include <queue>
#include <limits>
#include <unordered_set>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>>
T makeRandom(T start, T end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist{start, end};
    return dist(gen);
}


class task1
{

    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                                    //
    //      Задача №1. Дейкстра                                                                                           \\
    ||                                                                                                                    ||
    \\  Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной вершины до другой.           //
    //                                                                                                                    \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

    mutable int** graphMatrix {nullptr}; // Матрица смежности
    mutable int* minWeight {nullptr}; // Массив минимального веса узлов
    const int inf {std::numeric_limits<int>::max()}; // Определим бесконечность как верхнюю границу int
    
    int answer;
    size_t N, S, F;
    


    void makeData()
    {

        /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
        \\                                                                                                                        //
        //  В первой строке содержатся три числа: N, S и F (1≤ N≤ 100, 1≤ S, F≤ N),                                               \\
        \\  где N – количество вершин графа, S – начальная вершина, а F – конечная.                                               //
        ||  В следующих N строках вводится по N чисел, не превосходящих 100, – матрица смежности графа,                           ||
        //  где -1 означает отсутствие ребра между вершинами, а любое неотрицательное число – присутствие ребра данного веса.     \\
        \\  На главной диагонали матрицы записаны нули.                                                                           //
        //                                                                                                                        \\
        \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

        // Открываем файл на запись
        std::ofstream file {"input.txt"};
        
        // Генерируем константы
        const size_t N = makeRandom<size_t>(1, 100);
        const size_t S = makeRandom<size_t>(0, (N - 1));    
        const size_t F = makeRandom<size_t>(0, (N - 1));
        
        // Записываем константы
        file << N << ' ' << S << ' ' << F << '\n';
        
        size_t zeroIndex {0}; // Отслеживание главной диагонали
        
        // Генерируем и записываем матрицу смежности
        for (size_t col = 0; col < N; col++)
        {
            for (size_t row = 0; row < N; row++)
            {
                if (row == zeroIndex) file << 0 << ' ';
                else file << (makeRandom(0,1) ? -1 : makeRandom(0, 100)) << ' '; // 50% на отсутствие ребра
            }
            zeroIndex++;
            file << '\n';
        }

        // Закрываем файл
        file.close();
    }

    bool readData()
    {
        // Открываем файл на чтение
        std::ifstream file {"input.txt"};
        
        // Буфер ввода
        std::string readValue;
        
        // Считываем константы
        file >> readValue;
        N = static_cast<size_t>(std::stoi(readValue));
        file >> readValue;
        S = static_cast<size_t>(std::stoi(readValue));
        file >> readValue;
        F = static_cast<size_t>(std::stoi(readValue));
        
        
        // Если старт и финишь в одном узле, то смысла читать матрицу нет, возвращаем сигнал same = true
        if (S == F) return true;
        
        // Выделяем память
        graphMatrix = new int*[N];
        minWeight = new int[N];


        
        // Заполняем массивы данных
        for (size_t row = 0; row < N; row++)
        {
            graphMatrix[row] = new int[N];
            minWeight[row] = inf; // Начальный вес каждого непроверенного узла - бесконечность
            for (size_t col = 0; col < N; col++)
            {
                file >> readValue;
                graphMatrix[row][col] = std::stoi(readValue);
            }
        }

        // Закрываем файл
        file.close();

        // Считывание прошло корректно, same = false
        return false;
    }

    int calcAnswer() const
    {
        // Вес начальной позиции должен быть нулем
        minWeight[S] = 0;
        
        // Контейнеры для реализации BFS
        std::queue<size_t> order;
        std::unordered_set<size_t> cache;
        
        // Добавляем первый стартовый узел первым в очередь
        order.push(S);
        

        // Итерируемся пока очередь не опустеет
        while (!order.empty())
        {
            // Текущий узел
            size_t Node {order.front()};
            order.pop();
            
            // Сразу добавляем в кэш
            cache.insert(Node);
            
            // Проходимся по связанным с текущим узлам
            for (size_t linkedNode = 0; linkedNode < N; linkedNode++)
            {
                // Пропускаем несвязанные узлы
                bool noEdge {graphMatrix[Node][linkedNode] == -1};
                if (noEdge) continue;
                
                // Пропускаем проверенные узлы
                bool inCache {cache.find(linkedNode) != cache.end()};
                if (inCache) continue;
                
                // Определяем минимальный вес связанного узла
                minWeight[linkedNode] = std::min(graphMatrix[Node][linkedNode] + minWeight[Node], minWeight[linkedNode]);
                
                // Добавляем связанный узел в очередь 
                if (linkedNode != F) order.push(linkedNode);
            }
        }

        // Если вес остался бесконечным, попасть в финальный узел невозможно
        if (minWeight[F] == inf) return -1;
        else return minWeight[F];
    }
    
    void printAll()
    {
        std::cout << "\n\nNodes:\t" << N << "\nFrom:\t" << S << "\nTo:\t" << F << "\n\n";
  
        // answer == 0 -> readData не считал матрицу 
        if (graphMatrix != nullptr && answer != 0)
        {
            for (size_t row = 0; row < N; row++)
            {
                for (size_t col = 0; col < N; col++)
                    std::cout << graphMatrix[row][col] << ' ';
                std::cout << '\n';
            }
        }

        std::cout << "\nAnswer:\t" << answer;
    }



    public:
    void complete()
    {
        // Заполняем файл случайными значениями
        makeData();
        
        // Сигнал от readData, равен ли стартовый узел конечному
        bool sameNodes;
        sameNodes = readData();

        // Если стартовый и конечный узел равны, то вес равен нулю
        answer = sameNodes ? 0 : calcAnswer();
        
        // Выводим все данные
        printAll();
    }
    
    task1(){}
    
    ~task1()
    {
        if (graphMatrix != nullptr)
            for (size_t row = 0; row < N; row++) delete[] graphMatrix[row];
        delete[] graphMatrix;
        delete[] minWeight;
    }
};



/*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
\\                                                                                                                    //
//      Задача №2. Заправки                                                                                           \\
\\                                                                                                                    //
//    В стране N городов, некоторые из которых соединены между собой дорогами.                                        \\
\\    Для того, чтобы проехать по одной дороге, требуется один бак бензина.                                           //
||    В каждом городе бак бензина имеет разную стоимость.                                                             ||
//    Вам требуется добраться из первого города в N-ый, потратив как можно меньшее денег.                             \\
\\    Покупать бензин впрок нельзя.                                                                                   //
//                                                                                                                    \\
\\    Требуется вывести одно число – суммарную стоимость маршрута или -1, если добраться невозможно.                  //
//                                                                                                                    \\
\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

class task2
{
    size_t N, M;

    mutable int* cost {nullptr};
    mutable int* minCost {nullptr};
    const int inf {std::numeric_limits<int>::max()};

    std::unordered_set<size_t>* townNeighbours {nullptr}; // Корректнее и быстрее использовать вектор, если все данные полезны. set фильтрует бесполезную информацию от makeData
    int answer {-2};
    



void makeData()
{   
    
    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                                    //
    //    В первой строке вводится число N (1≤N≤100), в следующей строке идет N чисел,                                    \\
    \\    i-ое из которых задает стоимость бензина в i-ом городе (всё это целые числа из диапазона от 0 до 100).          //
    //    Затем идет число M – количество дорог в стране, далее идет описание самих дорог.                                \\
    \\    Каждая дорога задается двумя числами – номерами городов, которые она соединяет.                                 //
    //    Все дороги двухсторонние (то есть по ним можно ездить как в одну, так и в другую сторону),                      \\
    \\    между двумя городами всегда существует не более одной дороги, не существует дорог, ведущих из города в себя.    //                                                                 
    //                                                                                                                    \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/
    
    // Открываем файл на запись
    std::ofstream file{"input.txt"};
    
    // Генерируем и записываем N
    const size_t N {makeRandom<size_t>(1, 100)};
    file << N << '\n';
    
    // Генерируем и записываем цены на бензин
    for (size_t i = 0; i < N; i++) file << makeRandom(0, 100) << ' ';
    file << '\n';

    // Генерируем и записываем M
    const size_t M {makeRandom<size_t>(N, 4*N)};
    file << M << '\n';
    
    // Генерируем и записываем пары городов, связанные дорогами
    for (size_t i = 0; i < M * 2; i++) file << makeRandom<size_t>(0, (N-1)) << ' ';
    

    // Закрываем файл
    file.close();
}

    bool readData()
    {
        // Открываем файл на чтение 
        std::ifstream file {"input.txt"};
        
        // Буфер ввода 
        std::string readValue;
        
        // Считываем N
        file >> readValue;
        N = static_cast<size_t>(std::stoi(readValue));

        // Если город один, то возвращаем сигнал onlyOne == true
        if (N <= 1) return true;
        
        // Выделяем память
        cost = new int[N];
        minCost = new int[N];
        townNeighbours = new std::unordered_set<size_t>[N]; 

        
        // Заполняем массивы данными
        for (size_t i = 0; i < N; i++)
        {
            file >> readValue;
            cost[i] = std::stoi(readValue);
            minCost[i] = inf;
        }
        
        // Вынуждены всегда покупать бензин в первом городе
        minCost[0] = cost[0];
        
        // Из последнего города никуда не уезжаем, бензин покупать не нужно
        cost[N-1] = 0;

        
        // Считываем M
        file >> readValue;
        M = static_cast<size_t>(std::stoi(readValue));

        // Проходим по парам соединенных городов и добавляем связь в обе стороны
        for (size_t i = 0; i < M * 2; i++)
        {
            file >> readValue;
            
            size_t town1, town2;
            if (i % 2 == 0) town1 = static_cast<size_t>(std::stoi(readValue));
            else
            {
                town2 = static_cast<size_t>(std::stoi(readValue));
                if (town1 == town2) continue;
                townNeighbours[town1].insert(town2);
                townNeighbours[town2].insert(town1);
            }
        }

        
        // Закрываем файл
        file.close();

        // N > 1, значит возвращаем onlyOne = false
        return false;
    }
    
    int calcAnswer() const
    {
        // Контейнеры для реализации BFS
        std::queue<size_t> order;
        std::unordered_set<size_t> cache;
        
        // Добавляем первый город в очередь
        order.push(0);
        
        // Проходимся по очереди пока не опустеет
        while (!order.empty())
        {

            // Текущий город
            size_t town = order.front();
            order.pop();

            // Сразу добавим текущий город в проверенные
            cache.insert(town);

            // Нет дорог
            if (townNeighbours[town].empty()) continue;

            // Проходимся по соседям
            for (size_t neighbour : townNeighbours[town])
            {
                // Пропускаем проверенных
                if (cache.find(neighbour) != cache.end()) continue;
                
                // Определяем минимальную сумму цен
                minCost[neighbour] = std::min(minCost[town] + cost[neighbour], minCost[neighbour]);
                
                // Добавляем соседа в очередь на проверку
                order.push(neighbour);
            }
        }

        // Возвращаем минимальную цену для последнего города
        return (minCost[N-1] != inf ? minCost[N-1] : -1);
    }

    void printAll() const
    {
        std::cout << "\n\nTowns:\t" << N;
        std::cout << "\nRoads:\t" << M  << "\n\n";
    
        std::cout << "Town\tCost\tNeighbours\n";
        for (size_t i = 0; i < N; i++)
        {
            std::cout << (i + 1);
            if (N <= 1) break;
            std::cout << '\t' << cost[i];
            if (townNeighbours[i].empty()) {std::cout << '\n';continue;}
            else std::cout << '\t';
            for (size_t n : townNeighbours[i])
                std::cout << (n + 1) << ' ';
            std::cout << '\n';
        }
        std::cout << "\nAnswer:\t" << answer << '\n';
    }

    public:
    void complete()
    {
        // Заполняем файл случайными значениями
        makeData();
        
        // сигнал от readData, один ли город в стране
        bool onlyOne {false};
        onlyOne = readData();

        // Если в стране всего один город, значит тратиться на бензин не нужно
        answer = onlyOne ? 0 : calcAnswer();
        
        // Выводим все данные
        printAll();
    }

    task2(){}

    ~task2()
    {
        delete[] cost;
        delete[] minCost;
        delete[] townNeighbours;
    }
};

int main()
{
    while (true)
    {
        task1 graph;
        graph.complete();
        std::cin.get();

        task2 countryTravel;
        countryTravel.complete();
        std::cin.get();
    }
>>>>>>> 0fd20208acc86b1de3da7bd6f743dd7fd0bb14b0
}