#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> GenerateFullGraph(int);

/*1.4. [# 25] Задача коммивояжера.
	Для графа, заданного матрицей смежности найти гамильтонов цикл минимальной суммарной стоимости.Предполагается, что граф задан матрицей смежности.
	Решить задачу для 𝑁=10, 𝑁=15, где 𝑁 – количество вершин в графе. Оценить время работы программы для входа 𝑁=20 и 𝑁=50.
*/
int main(int argc, char* argv[])
{
	int m_graphSize = 5;
	vector<vector<int>> graph = GenerateFullGraph(m_graphSize);
	
	return 0;
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
	if (in.is_open()) {
		int x = 0, y = 0, weight = 0;
		while (!in.eof()) {  //init array
			in >> x >> y >> weight;
			matrix[x][y] = weight;
			matrix[y][x] = weight;
		}
	}
	in.close();
	return matrix;
}