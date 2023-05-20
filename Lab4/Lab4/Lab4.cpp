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
/**
 * @param v -
 * @param visited -
 * @param graph -
 * @param match -
 */
bool dfs(int v, vector<bool>& visited, const vector<vector<int>>& graph, vector<int>& match)
{
    if (visited[v])
    {
        return false;
    }
    visited[v] = true;

    for (size_t i = 0; i < graph[v].size(); i++)
    {
        int to = graph[v][i];
        //если -1 то еще не добавлена
        if (match[to] == -1 || dfs(match[to], visited, graph, match))
        {
            match[to] = v;
            return true;
        }
    }
    return false;
}

vector<vector<int>> ParseTextFile(string fileName)
{
    int p, q;
    string line;
    ifstream in(fileName);
    if (!in.is_open())
    {
        throw exception("file not found!");
    }
    in >> p >> q;
    vector<vector<int>> graph(p, vector<int>(q));

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            in >> graph[i][j];
        }
    }
    in.close();
    return graph;
}

int main()
{
    string fileName = "test.txt";
    vector<vector<int>> graph = ParseTextFile(fileName);
    vector<int> match(graph.at(0).size(), -1);

    for (int v = 0; v < static_cast<int>(graph.size()); ++v)
    {
        vector<bool> visited(graph.size(), false);
        dfs(v, visited, graph, match);
    }

    if (find(match.begin(), match.end(), -1) != match.end()) {
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
        for (int i = 0; i < graph.size(); ++i)
        {
            cout << match[i] << ", " << i << endl;
        }
    }

    return 0;
}