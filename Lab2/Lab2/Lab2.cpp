#include <fstream>
#include <iostream>
#include <vector>
/*
2.5. [# 50] Раскрасить заданный граф, используя алгоритм Ершова.
Вход. Первая строка исходного файла содержит целое число 𝑣 (1 ≤ 𝑣 ≤ 400) –
количество вершин. В последующих 𝑣 строках содержатся по 𝑣 чисел, разделенных
пробелами: вес ребер между вершинами. Вершины пронумерованы от 1 до 𝑣
Выход. В 𝑣 строчках вывести по два числа: номер вершин (от 1 до 𝑣) и номер цвета
вершины (нумерация цветов начинается с 1)
*/

using namespace std;

// Функция для раскраски графа с использованием алгоритма Ершова
vector<int> colorGraph(const vector<vector<int>>& graph) {
    int v = graph.size();
    vector<int> colors(v, 0); // Вектор цветов вершин
    vector<bool> usedColors(v, false); // Вектор использованных цветов

    // Проходим по всем вершинам графа
    for (int i = 0; i < v; i++) {
        // Обнуляем список использованных цветов для текущей вершины
        for (int j = 0; j < v; j++) {
            usedColors[j] = false;
        }

        // Проходим по всем соседним вершинам и отмечаем использованные цвета
        for (int j = 0; j < v; j++) {
            if (graph[i][j] == 1 && colors[j] != 0) {
                usedColors[colors[j] - 1] = true;
            }
            ++iterationCount;
        }

        // Ищем первый доступный цвет для текущей вершины
        int color;
        for (color = 1; color <= v; color++) {
            if (!usedColors[color - 1]) {
                break;
            }
        }

        // Записываем найденный цвет для текущей вершины
        colors[i] = color;
    }

    return colors;
}

int main() {
    int v;
    ifstream in("test.txt");
    in >> v;

    // Создание и инициализация графа
    vector<vector<int>> graph(v, vector<int>(v));
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            in >> graph[i][j];
        }
    }

    // Раскраска графа
    vector<int> colors = colorGraph(graph);

    // Вывод номеров вершин и их цветов
    for (int i = 0; i < v; i++) {
        cout << (i + 1) << " " << colors[i] << endl;
    }


    cout << "Iterations = "<< iterationCount << endl;

    return 0;
}