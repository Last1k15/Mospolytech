#include <iostream>
#include <random>
#include <fstream>
#include <forward_list>
#include <vector>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>>
T makeRandom(T start, T end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(start, end);
    return dist(gen);
}


template <typename T>
void selectionSort(T a, T b, bool reverse = false)
{
    while (a != b)
    {
        T next = a;
        for (T i = a; i != b; i++)
        {
            if (!reverse && *i < *next) next = i;
            else if (reverse && ((*i < *next) == false)) next = i;
        }
        std::swap(*a, *next);
        a++;
    }
}


class task1
{
    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                                                    //
    //        Задача 1                                                                                                                    \\
    \\                                                                                                                                    //
    //    Дана лекционная аудитория, в которой несколько профессоров хотят прочесть свои лекции.                                          \\
    \\    Для составления расписания профессора подали заявки, вида [si,fi) – время начала и конца лекции.                                //
    //    Лекция считается открытым полуинтервалом, то есть какая-то лекция может начаться в момент окончания другой, без перерыва.       \\
    \\    Составьте расписание занятий так, чтобы выполнить максимальное количество заявок.                                               //
    //                                                                                                                                    \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/
    
    struct lecture
    {
        int start {0};
        int end {0};
        int interval {0};
        
        lecture() = default;
        lecture(int _start, int _end)
            :   start{_start}, 
                end{_end},
                interval{end - start}{}
        
        bool operator<(lecture& other)
        {
            return start < other.start;
        }

        std::string makeTime(int val)
        {
            if (val == 1440) return "00:00";
            std::string Hours {std::to_string(val / 60)};
            std::string Minutes {std::to_string(val % 60)};
            if (val % 60 < 10 != 0) Minutes.insert(Minutes.end() - 1, '0');
            return Hours + ':' + Minutes;
        }
    };

    lecture* lectureArray;

    size_t N;
    unsigned int answer {0};

    void makeData() const
    {
        /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
        \\                                                                                                                                                                            //
        //    В первой строке вводится натуральное число N, не более 1000 – общее количество заявок. Затем вводится N строк с описаниями заявок - по два числа в каждом si и fi.      \\
        \\    Гарантируется, что si<fi<. Время начала и окончания лекции – натуральное число, не превышает 1440 (в минутах с начала суток :) )                                        //
        //                                                                                                                                                                            \\
        \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/
        
        // Открываем файл на запись
        std::ofstream file {"input.txt"};
        
        // Генерируем и записываем константу
        const size_t N {makeRandom<size_t>(1, 1000)};
        file << N << '\n';

        // Генерируем и записываем N временных отрезков
        for (size_t i = 0; i < N; i++)
        {
            const int minInterval = 10;
            const int maxInterval = 120;
            int startTime {makeRandom(420, 1440 - minInterval)};
            int endTime {makeRandom(startTime + minInterval, startTime + maxInterval)}; // Лекции длятся от 10 минут до 2 часов
            endTime = std::min(1440, endTime);

            file << startTime << ' ' << endTime << '\n';
        }


        // Закрываем файл
        file.close();
    }

    void readData()
    {
        // Открываем файл на чтение
        std::ifstream file {"input.txt"};
        
        // Буфер ввода
        std::string readValue;

        // Читаем N
        file >> readValue;
        N = static_cast<size_t>(std::stoi(readValue));

        // Выделяем память
        lectureArray = new lecture[N];
        
        // Читаем временные отрезки лекций
        for (size_t i = 0; i < N * 2; i++)
        {
            int startTime;
            int endTime;
            file >> readValue;
            if (i % 2 == 0) startTime = std::stoi(readValue);
            else
            {
                endTime = std::stoi(readValue);
                lectureArray[i / 2] = lecture{startTime, endTime};
            }
        }
    }
    
    unsigned int calcAnswer()
    {
        selectionSort(lectureArray, lectureArray + N);
        
        unsigned int lectCount {1}; 
        size_t currentLecture {0};
        while (lectureArray[currentLecture].end < lectureArray[N-1].start)
        {
            for (size_t nextLecture = currentLecture + 1; nextLecture < N; nextLecture++)
            {
                if (lectureArray[nextLecture].start >= lectureArray[currentLecture].end)
                {
                    currentLecture = nextLecture;
                    lectCount++;
                    break;
                }
            }
        }

        return lectCount;
    }
    
    void printAll()
    {
        std::cout << "\n\nN:\t" << N;
        
        std::cout << "\n\nstart\t" << "end\t" << "interval\n";
        for (size_t i = 0; i < N; i++)
        {
            lecture& current = lectureArray[i];
            std::cout << current.makeTime(current.start) << '\t' << current.makeTime(current.end) << '\t' << current.makeTime(current.interval) << '\n';
        }


        std::cout << "\n\nAnswer:\t" << answer;
    }
    


    public:

    void complete()
    {
        makeData();
        readData();
        answer = calcAnswer();
        printAll();
    }

    task1() = default;
    ~task1()
    {
        delete[] lectureArray;
    }
};

class task2
{
    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                                                                                            //
    //      Задача 2. Коробки                                                                                                                                                     \\
    \\                                                                                                                                                                            //
    //  У Васи в комнате очень много коробок, которые валяются в разных местах. Васина мама хочет, чтобы он прибрался.                                                            \\
    \\  Свободного места в комнате мало и поэтому Вася решил собрать все коробки и составить их одну на другую.К сожалению, это может быть невозможно.                            //
    //  Например, если на картонную коробку с елочными украшениями положить что-то железное и тяжелое, то вероятно следующий Новый год придется встречать с новыми игрушками.     \\
    \\  Вася взвесил каждую коробку и оценил максимальный вес который она может выдержать.                                                                                        //
    //  Помогите ему определить какое наибольшее количество коробок m он сможет составить одну на другую так,                                                                     \\
    \\  чтобы для каждой коробки было верно, что суммарный вес коробок сверху не превышает максимальный вес, который она может выдержать.                                         //
    //                                                                                                                                                                            \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/


    unsigned int N;
    struct box
    {
        unsigned int boxWeight;
        unsigned int limitWeight;
        
        box() = default;
        box(unsigned int wi, unsigned int ci)
            :   boxWeight{wi}, limitWeight{ci}{}

        bool operator<(box& other)
        {
            return boxWeight < other.boxWeight;
        }
        int getEfficiency()
        {
            return (limitWeight - boxWeight);
        }
    };

    box* boxArray;
    unsigned int answer;
    
    bool myComp1(box a, box b)
    {
        return a.boxWeight < b.boxWeight;
    }

    bool myComp2(box a, box b)
    {
        return a.limitWeight > b.limitWeight;
    }

    void makeData()
    {

    /*\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
    \\                                                                                                            //
    //    Первая строка входного файла содержит целое число n (1≤n≤105) - количество коробок в комнате.           \\
    ||    Каждая следующая из n строк содержит два целых числа wi и ci (1≤wi≤105,1≤ci≤109),                       ||
    \\    где wi −− это вес коробки с номером i, а ci −− это вес который она может выдержать.                     //
    //                                                                                                            \\
    \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\*/

        std::ofstream file {"input.txt"};
        const unsigned int N {makeRandom<unsigned int>(1, 105)};
        file << N << '\n';
        for (size_t i = 0; i < N; i++)
        {
            unsigned int boxWeight {makeRandom<unsigned int>(1,105)};
            unsigned int limitWeight {makeRandom<unsigned int>(1, 109)};
            file << boxWeight << ' ' << limitWeight << '\n';
        }
        file.close();
    }

    void readData()
    {
        std::ifstream file {"input.txt"};
        std::string readValue;
        file >> readValue;
        N = std::stoi(readValue);

        boxArray = new box[N];

        for (size_t i = 0; i < N * 2; i++)
        {
            unsigned int boxWeight;
            unsigned int limitWeight;
            file >> readValue;
            if (i % 2 == 0) boxWeight = std::stoi(readValue); 
            else
            {
                limitWeight = std::stoi(readValue);
                boxArray[i / 2] = box{boxWeight, limitWeight};
            }
        }
        file.close();
    }

    unsigned int calcAnswer()
    {
        selectionSort(boxArray, boxArray + N);

        
        std::vector<box*> boxTower;
        bool willCollapse = false;
        box* bestLimitBox {&boxArray[0]};
        for (size_t i = 0; i < N; i++)
            bestLimitBox = (boxArray[i].limitWeight > bestLimitBox->limitWeight) ? &boxArray[i] : bestLimitBox;
        boxTower.push_back(bestLimitBox);
        unsigned int totalWeight {bestLimitBox->boxWeight};

        for (size_t i = 0; i < N; i++)
        {
            unsigned int locatedWeight = totalWeight;
            unsigned int newBoxWeight = boxArray[i].boxWeight;
            for (box* boxPtr : boxTower)
            {
                locatedWeight -= boxPtr->boxWeight;
                if (locatedWeight + newBoxWeight > boxPtr->limitWeight) 
                {
                    willCollapse = true;
                    break;
                }
            }
            if (!willCollapse)
            {
                totalWeight += newBoxWeight;
                boxTower.push_back(&boxArray[i]);
            }
        }
        
        return boxTower.size();
    }

    void printAll()
    {
        std::cout << "\n\nN:\t" << N;
        std::cout << "\n\nlimitWeight\tboxWeight\n";
        for (size_t i = 0; i < N; i++)
            std::cout << boxArray[i].limitWeight << "\t\t" << boxArray[i].boxWeight << '\n';
        std::cout << "\n\nAnswer:\t" << answer;
    }

    public:
    void complete()
    {
        makeData();
        readData();
        answer = calcAnswer();
        printAll();
    }

    task2() = default;
    ~task2()
    {
        delete[] boxArray;
    }
};

int main()
{
    while (true)
    {
        task1 auditoryProblem;
        auditoryProblem.complete();
        std::cin.get();

        task2 boxProblem;
        boxProblem.complete();
        std::cin.get();
    }
}