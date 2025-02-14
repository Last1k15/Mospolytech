#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>

std::string bfs(std::unordered_map<char, std::unordered_set<char>>& connectionMap, char startNode, char finishNode)
{
    std::queue<std::string> order;
    std::unordered_set<char> cache;
    std::string best;
    best.resize(connectionMap.size());
    order.push(std::string{startNode});
    while (!order.empty())
    {
        std::string currentPath {order.front()};
        char currentNode {currentPath.back()};
        order.pop();
        cache.insert(currentNode);
        for (char node : connectionMap[currentNode])
        {
            if (cache.find(node) != cache.end()) continue;
            else order.push(currentPath + node);
            if (node == finishNode)
            {
                best = best.size() > currentPath.size() ? currentPath : best;
                break;
            }
        }
    }
    return best;
}

int main()
{
    /*  Выбираемся из лабиринта при помощи алгоритма «поиск в ширину» (BFS) на С++

        Допустим, имеется лабиринт, такой, как на следующем рисунке, и мы хотим перейти от входа к выходу за наименьшее возможное количество шагов.
        За один шаг будем считать любой переход из одной комнаты в другую. В нашем лабиринте 11 комнат, и у каждой из них – уникальное имя, например,
        “A”, “B”, т.д. Итак, наша цель – перейти из комнаты “S” в комнату “I”.
        
        Алгоритм вычислит и выведет на экран кратчайший путь от входа в лабиринт до выхода из лабиринта. 
        Этот путь имеет длину 4 и выглядит так: “S” -> “B” -> “C” -> “J” -> “I”.                                                                        */
    
    std::unordered_map<char, std::unordered_set<char>> connectionMap
    {
        {'S', {'A','E','D','B'}},
        {'A', {'S'}},
        {'E', {'S', 'G'}},
        {'D', {'S', 'B', 'G'}},
        {'B', {'S', 'D', 'C'}},
        {'C', {'B', 'J'}},
        {'G', {'H', 'F', 'E', 'D', 'J'}},
        {'F', {'H', 'G'}},
        {'H', {'F', 'G', 'I'}},
        {'J', {'I', 'G', 'C'}},
        {'I', {'H', 'J'}},
    };
    std::string answer {bfs(connectionMap, 'S', 'I')};
    std::cout << answer.size() << '\t' << answer;
}
