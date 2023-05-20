#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
// /*
// 4.2. [# 50] Задан двудольный граф 𝐺 = 𝐺(𝑋, 𝐸, 𝑌), где 𝑋, 𝑌 – множество вершин, |𝑋| = |𝑌| = 𝑛; 𝐸 – множество ребер.
// В заданном двудольном графе найти полное паросочетание, воспользовавшись алгоритмом Куна.
// Вход. Двудольный граф 𝐺 = 𝐺(𝑋, 𝐸, 𝑌) задается матрицей 𝐴[1. . 𝑝, 1. . 𝑞], 𝑝 = |𝑋|, 𝑞 =
// |𝑌|, в которой 𝐴[𝑥, 𝑦] = 1, если есть ребро (𝑥, 𝑦) и 𝐴[𝑥, 𝑦] = 0, если такого ребра нет.
// Первая строка входного файла содержит два числа 𝑝, 𝑞 (1 ≤ 𝑝, 𝑞 ≤ 100) – количество
// вершин в каждой доле. В последующих 𝑝 строках содержатся по 𝑞 чисел матрицы 𝐴.
// Вершины в каждой доле пронумерованы от 1.
// Выход. В первой строчке Yes либо No, в зависимости от того есть максимальное
// паросочетание или нет. Во втором случае, следующих 𝑛 строчках по два числа –
// вершины, соединенные ребром (первое число – первая доля, второе – вторая).
// */
using namespace std;

bool dfs(int v, vector<bool>& visited, vector<int>& match, const vector<vector<int>>& graph)
{
    if (visited[v])
    {
        return false;
    }
    visited[v] = true;

    for (size_t i = 0; i < graph[v].size(); i++)
    {
        int to = graph[v][i];
        if (match[to] == -1 || dfs(match[to], visited, match, graph))
        {
            match[to] = v;
            return true;
        }
    }
    return false;
}

void ParseTextFile(ifstream& in, vector<vector<int>>& graph, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            in >> graph[i][j];
        }
    }
    in.close();
}

vector<int> FindCompleteMatching(vector<vector<int>>& arr, int size)
{
    vector<vector<int>> ribsList(size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (arr[i][j] == 1)
            {
                ribsList[i].push_back(j);
            }
        }
    }

    vector<int> matchingList(size, -1);
    vector<bool> used;

    for (int v = 0; v < size; ++v)
    {
        used.assign(size, false);
        dfs(v, used, matchingList, ribsList);
    }

    return matchingList;
}

int main()
{
    string fileName = "test.txt";
    ifstream input(fileName);
    if (!input.is_open())
    {
        cout << "File not found";
        return 1;
    }
    int matrixSize, rowSize;
    input >> matrixSize >> rowSize;

    vector<vector<int>> graph(matrixSize, vector<int>(matrixSize, 0));
    ParseTextFile(input, graph, matrixSize);

    vector<int> match = FindCompleteMatching(graph, matrixSize);

    if (find(match.begin(), match.end(), -1) != match.end())
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "Yes" << endl;
        for (int i = 0; i < graph.size(); ++i)
        {
            cout << match[i] + 1 << ", " << i + 1 << endl;
        }
    }

    return 0;
}