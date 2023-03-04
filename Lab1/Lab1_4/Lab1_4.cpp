#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

struct Result;
using namespace std;
vector<vector<int>> GenerateFullGraph(int);
vector<Result> SearchAllPathLong(const vector<vector<int>> &graphInMatrix, int graphSize, size_t& iterablesCount);
size_t GetRoadLongByRoadPath(const vector<size_t> &roadPath, const vector<vector<int>> &graphInMatrix);
void PrintResult(const double elapsedTime, const size_t iterablesCount,const unsigned short vectorSize);

struct Result
{
    std::vector<size_t> roadPath;
    size_t roadLong;
};

/*1.4. [# 25] Задача коммивояжера.
	Для графа, заданного матрицей смежности найти гамильтонов цикл минимальной суммарной стоимости.Предполагается, что граф задан матрицей смежности.
	Решить задачу для 𝑁=10, 𝑁=15, где 𝑁 – количество вершин в графе. Оценить время работы программы для входа 𝑁=20 и 𝑁=50.
*/
int main(int argc, char *argv[])
{
    size_t iterablesCount = 0;
    constexpr int graphSize = 10;
    const vector<vector<int>> graphInMatrix = GenerateFullGraph(graphSize);
    boost::timer timer;
    timer.restart();
    const vector<Result> allRoadResults = SearchAllPathLong(graphInMatrix, graphSize, iterablesCount);
    Result shortestRoadOnTheAllRoads;
    shortestRoadOnTheAllRoads.roadLong = INT32_MAX;

    for (const auto &allRoadResult : allRoadResults)
    {
        if (allRoadResult.roadLong < shortestRoadOnTheAllRoads.roadLong)
            shortestRoadOnTheAllRoads = allRoadResult;
    }
    cout << "Short road is : ";
    for (const auto roadPathElement : shortestRoadOnTheAllRoads.roadPath)
    {
        cout << roadPathElement << " ";
    }
    cout << endl <<"Road long is : " << shortestRoadOnTheAllRoads.roadLong << endl;
    PrintResult(timer.elapsed(), iterablesCount, graphSize);
    return 1;
}

vector<vector<int>> GenerateFullGraph(int matrixSize)
{
    std::ofstream out("fullGraph.txt");
    out.clear();
    for (int j = 1; j <= matrixSize; j++)
    {
        for (int i = 1; i <= matrixSize; i++)
        {
            if (j < i)
            {
                out << j << " " << i << " " << (rand() % 50 + 1);
                if (j == (matrixSize - 1) && i == (matrixSize))
                {
                    continue;
                }
                out << std::endl;
            }
        }
    }
    out.close();
    matrixSize++; // нужно для работы с нулями
    vector<vector<int>> matrix(matrixSize, vector<int>(matrixSize, INT32_MAX));
    ifstream in("fullGraph.txt");
    if (in.is_open())
    {
        int x = 0, y = 0, weight = 0;
        while (!in.eof())
        {
            //init array
            in >> x >> y >> weight;
            matrix[x][y] = weight;
            matrix[y][x] = weight;
        }
    }
    else
    {
        throw exception("Error in open file");
    }
    in.close();
    return matrix;
}

vector<Result> SearchAllPathLong(const vector<vector<int>> &graphInMatrix, const int graphSize, size_t& iterablesCount)
{
    vector<Result> allRoadResult;
    vector<size_t> roadPath;
    for (int i = 1; i <= graphSize; i++)
        roadPath.push_back(i);
    do
    {
        iterablesCount++;
        allRoadResult.push_back({roadPath, GetRoadLongByRoadPath(roadPath, graphInMatrix)});
    }
    while (std::next_permutation(roadPath.begin(), roadPath.end()));
    return allRoadResult;
}

size_t GetRoadLongByRoadPath(const vector<size_t> &roadPath, const vector<vector<int>> &graphInMatrix)
{
    size_t longOfTheRoad = 0;
    for (size_t i = 0; i < roadPath.size(); i++)
    {
        if (i + 1 < roadPath.size())
            longOfTheRoad += graphInMatrix[roadPath[i]][roadPath[i + 1]];
        else
            longOfTheRoad += graphInMatrix[roadPath[i]][roadPath[1]];
    }  
    return longOfTheRoad;
}

boost::multiprecision::cpp_int Factorial(const int number)
{
    boost::multiprecision::cpp_int num = 1;
    for (int i = 1; i <= number; i++)
        num = num * i;
    return num;
}

void PrintResult(const double elapsedTime, const size_t iterablesCount,const unsigned short vectorSize)
{
    std::cout << "Permutation for vector size = " << vectorSize << ", generate in " << round(elapsedTime * 100) / 100.0 << " seconds." << std::endl;
    std::cout << "Iteration count = " << iterablesCount << ".\n";
    const boost::multiprecision::cpp_dec_float_50 oneIterableTime = elapsedTime/ iterablesCount;
    std::cout << "Average for one Iteration = " << oneIterableTime << std::endl;
	
    std::cout << "Average for vector size = 10 is " << oneIterableTime *  Factorial(10).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
    std::cout << "Average for vector size = 15 is " << oneIterableTime *  Factorial(15).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
    std::cout << "Average for vector size = 20 is " << oneIterableTime *  Factorial(20).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
    std::cout << "Average for vector size = 50 is " << oneIterableTime * Factorial(50).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;
    std::cout << "Average for vector size = 100 is " << oneIterableTime * Factorial(100).convert_to<boost::multiprecision::cpp_dec_float_50>() << " seconds." << std::endl;	
}
