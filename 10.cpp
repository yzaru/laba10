#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstdlib>
#include <ctime>

#define INF std::numeric_limits<int>::max()

// Функция для генерации случайной матрицы смежности для неориентированного графа
void generateUndirectedGraph(std::vector<std::vector<int>>& matrix, int n, int max_weight) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                int weight = rand() % max_weight + 1;
                matrix[i][j] = matrix[j][i] = weight;
            }
        }
    }
}

// Функция для генерации случайной матрицы смежности для ориентированного графа
void generateDirectedGraph(std::vector<std::vector<int>>& matrix, int n, int max_weight) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                int weight = rand() % max_weight + 1;
                matrix[i][j] = weight;
            }
        }
    }
}

// Функция для вывода матрицы смежности
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            if (value == INF) {
                std::cout << " INF";
            } else {
                std::cout << " " << value;
            }
        }
        std::cout << "\n";
    }
}

// Алгоритм Дейкстры с использованием std::queue
void dijkstra(const std::vector<std::vector<int>>& matrix, int start, std::vector<int>& dist) {
    int n = matrix.size();
    std::vector<bool> visited(n, false);
    dist.assign(n, INF);
    dist[start] = 0;

    std::queue<int> queue;
    queue.push(start);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && matrix[u][v] != INF && dist[u] + matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + matrix[u][v];
                queue.push(v);
            }
        }
    }
}

// Вычисление радиуса, диаметра, центральных и периферийных вершин
void calculateGraphProperties(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    std::vector<int> eccentricity(n);
    int radius = INF, diameter = 0;

    for (int i = 0; i < n; i++) {
        std::vector<int> dist;
        dijkstra(matrix, i, dist);

        int max_dist = 0;
        for (int d : dist) {
            if (d != INF && d > max_dist) {
                max_dist = d;
            }
        }
        eccentricity[i] = max_dist;
        if (max_dist < radius) radius = max_dist;
        if (max_dist > diameter) diameter = max_dist;
    }

    std::cout << "Радиус графа: " << radius << "\n";
    std::cout << "Диаметр графа: " << diameter << "\n";

    std::cout << "Центральные вершины: ";
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == radius) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";

    std::cout << "Периферийные вершины: ";
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == diameter) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    srand(time(NULL));

    int n, max_weight;
    std::cout << "Введите количество вершин графа: ";
    std::cin >> n;
    std::cout << "Введите максимальный вес ребра: ";
    std::cin >> max_weight;

    std::vector<std::vector<int>> undirectedGraph(n, std::vector<int>(n, INF));
    std::vector<std::vector<int>> directedGraph(n, std::vector<int>(n, INF));

    std::cout << "Матрица смежности для неориентированного графа:\n";
    generateUndirectedGraph(undirectedGraph, n, max_weight);
    printMatrix(undirectedGraph);
    calculateGraphProperties(undirectedGraph);

    std::cout << "\nМатрица смежности для ориентированного графа:\n";
    generateDirectedGraph(directedGraph, n, max_weight);
    printMatrix(directedGraph);
    calculateGraphProperties(directedGraph);

    return 0;
}
