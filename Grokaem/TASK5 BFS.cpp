#include <iostream>
#include <queue>
#include <unordered_set>
#include <limits>

struct Room
{
    static inline char idMaker {'A'};
    unsigned connectedCount {5};
    const char ID;
    Room** connectedPtr;

    /////////////////////////////////////////////////////////////////
    // LIFETIME

    Room(std::initializer_list<Room*>&& initList) :   ID{idMaker++}
    {
        connectedCount = initList.size();
        connectedPtr = new Room*[connectedCount];
        std::copy(initList.begin(), initList.end(), connectedPtr);

    }
    Room(char _ID)
        :   ID{_ID}
        {
            connectedPtr = new Room*[5];
            for (size_t i = 0; i < 5; i++) connectedPtr[i] = nullptr; 
        }
    Room()
        :   ID{idMaker++}
        {
            connectedPtr = new Room*[5];
            for (size_t i = 0; i < 5; i++) connectedPtr[i] = nullptr;
        };

    ~Room()
    {
        delete[] connectedPtr;
    }

    /////////////////////////////////////////////////////////////////
    // FUNC

    template <const bool inOther = false>
    void connectWith(Room& other)
    {
        if (connectedPtr[connectedCount - 1] != nullptr) reallocate(connectedCount * 2);

        for (size_t i = 0; i < connectedCount; i++)
        {
            if (connectedPtr[i] == nullptr)
            {
                connectedPtr[i] = &other;
                break;
            }
        }
        
        if (!inOther) other.connectWith<true>(*this);
    }

    std::pair<int, std::string> findShortestPath(Room& goal)
    {
        using pair = std::pair<Room*, int>;
        using RoomInfo = std::tuple<Room*, int, std::string>;
        
        std::unordered_set<Room*> checked;
        std::queue<RoomInfo> checkList;
        int minCount {std::numeric_limits<int>::max()};
        std::string minPath;
        

        checkList.push(RoomInfo{this,1, std::string{ID}});
        
        while (!checkList.empty())
        {
            Room* currentRoom {std::get<0>(checkList.front())};
            int currentCount {std::get<1>(checkList.front())};
            std::string currentPath {std::get<2>(checkList.front())};
            checkList.pop();
            checked.insert(currentRoom);
            
            if (currentRoom == &goal) 
            {
                if (currentCount < minCount)
                {
                    minCount = currentCount;
                    minPath = currentPath;
                }
                continue;
            }

            for (size_t i = 0; i < connectedCount; i++)
            {
                Room* currentConnectedRoom = currentRoom->connectedPtr[i];
                if (!currentConnectedRoom) break;

                bool isChecked {find(checked.begin(), checked.end(), currentConnectedRoom) != checked.end()};

                if (isChecked) continue;
                else checkList.push(RoomInfo{currentConnectedRoom, currentCount + 1, currentPath + "->" + std::string{currentConnectedRoom->ID}});
            }
        }
        if (minCount == std::numeric_limits<int>::max()) return std::pair<int, std::string>{-1, ""};
        else return std::pair<int, std::string>{(minCount - 1), minPath};
    }

    /////////////////////////////////////////////////////////////////
    // UTILITY

    void printConnections()
    {
        std::cout << ID << " Connections: ";
        for (size_t i = 0; i < connectedCount; i++)
            if (connectedPtr[i]) std::cout << connectedPtr[i]->ID << ' ';
        std::cout << '\n';
    }

    private:

    template <typename iter_t, typename = typename std::enable_if<std::is_pointer<typename std::iterator_traits<iter_t>::value_type>::value>>
    iter_t find(iter_t startIter, iter_t endIter, typename std::iterator_traits<iter_t>::value_type val)
    {
        for (;startIter != endIter; startIter++)
            if (*startIter == val) return startIter;
        return startIter;
    }

    void reallocate(unsigned newSize)
    {
        Room** newMemoryPtr = new Room*[newSize];
        std::copy(newMemoryPtr, newMemoryPtr + connectedCount, newMemoryPtr);
        delete[] connectedPtr;
        connectedPtr = newMemoryPtr;
        connectedCount = newSize;
    }
};

int main()
{
    /*  Выбираемся из лабиринта при помощи алгоритма «поиск в ширину» (BFS) на С++

        Допустим, имеется лабиринт, такой, как на следующем рисунке, и мы хотим перейти от входа к выходу за наименьшее возможное количество шагов.
        За один шаг будем считать любой переход из одной комнаты в другую. В нашем лабиринте 11 комнат, и у каждой из них – уникальное имя, например,
        “A”, “B”, т.д. Итак, наша цель – перейти из комнаты “S” в комнату “I”.
        
        Алгоритм вычислит и выведет на экран кратчайший путь от входа в лабиринт до выхода из лабиринта. 
        Этот путь имеет длину 4 и выглядит так: “S” -> “B” -> “C” -> “J” -> “I”.                                                                        */

    // Условие выхода - попасть в финальную комнату, поэтому переход "Финальная комната -> выход" не учитывается
    
    Room A{'A'}, B{'B'}, C{'C'}, D{'D'}, E{'E'}, F{'F'}, G{'G'}, H{'H'}, I{'I'}, J{'J'}, S{'S'};
    
    A.connectWith(S);
    
    S.connectWith(E); // Если убрать эту связь то результат будет аналогичен примеру из условия
    S.connectWith(B);
    S.connectWith(D);

    E.connectWith(G);
    B.connectWith(D);
    B.connectWith(C);
    C.connectWith(J);
    D.connectWith(G);
    G.connectWith(H);
    G.connectWith(J);
    G.connectWith(F);

    J.connectWith(I);
    H.connectWith(F);
    H.connectWith(I);

    A.printConnections();
    B.printConnections();
    C.printConnections();
    D.printConnections();
    E.printConnections();
    F.printConnections();
    G.printConnections();
    H.printConnections();
    I.printConnections();
    J.printConnections();
    S.printConnections();
    
    std::pair<int, std::string> result = S.findShortestPath(I);
    std::cout << result.first << " (" << result.second << ')';
}