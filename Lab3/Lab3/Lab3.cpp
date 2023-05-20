#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;


#include <iostream>
#include <vector>

using namespace std;

// Функция для вычисления определителя матрицы
int determinant(vector<vector<int>>& mat, int n) {
    int det = 0;

    if (n == 1) {
        return mat[0][0];
    } else if (n == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    } else {
        vector<vector<int>> submat(n - 1, vector<int>(n - 1));
        for (int k = 0; k < n; k++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j != k) {
                        submat[subi][subj] = mat[i][j];
                        subj++;
                    }
                }
                subi++;
            }
            det += (k % 2 == 0 ? 1 : -1) * mat[0][k] * determinant(submat, n - 1);
        }
    }
    return det;
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

    // Создание матрицы лапласа 
    vector<vector<int>> laplacian(v, vector<int>(v, 0));
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i != j) {
                laplacian[i][i] += graph[i][j];
                laplacian[i][j] = -graph[i][j];
            }
        }
    }

    // Вычисление определителя лапласа
    int det = determinant(laplacian, v - 1);

    // Вывод количества остовных деревьев
    cout << "Result " << det << endl;

    return 0;
}
