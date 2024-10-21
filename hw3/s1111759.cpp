#include <iostream>
#include <fstream>
#define INT_MAX 1000000   //�w�]�L���j�O1000000 

using namespace std;

const int NumVertices = 7;  //�T�w���I�ƶq 

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && found[i] == 0) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void printPath(int parent[], int j, int cost[][NumVertices]) {  //�C�L���|  
    if (parent[j] == -1)  //�p�G parent[j] == -1 ��ܬO�_�I 
        cout << " " << j + 1;
    else {
        printPath(parent, parent[j], cost);
        cout << " -(" << cost[parent[j]][j] << ")-> " << j + 1;
    }
}

void shortestPath(int v, int cost[][NumVertices], int dist[], int n, int f[]) {
    int i, u, w;
    int parent[n];

    for (i = 0; i < n; i++) {
        f[i] = 0;
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[v - 1] = 0;

    for (i = 0; i < n - 1; i++) {
        u = choose(dist, n, f);
        f[u] = 1;
        for (w = 0; w < n; w++) {
            if (f[w] == 0 && cost[u][w] != 0 && dist[u] != INT_MAX && dist[u] + cost[u][w] < dist[w]) {
                dist[w] = dist[u] + cost[u][w];
                parent[w] = u;
            }
        }
    }

    for (w = 0; w < n; w++) {  // ��ܵ��G 
        cout << "---------------------------------------------" << endl;
        cout << "�q���I " << v << " �쳻�I " << w + 1 << " ���̵u�Z�����G" << dist[w] << endl;
        cout << "     ���|�G";
        printPath(parent, w, cost);
        cout << endl;
    }
}

int main() {
    int adjMatrix[NumVertices][NumVertices];
    int distance[NumVertices];
    int found[NumVertices];

    
    ifstream matrixFile("Matrix.txt");       // �qMatrix.txtŪ����� 
    if (!matrixFile) {
        cerr << "Unable to open Matrix.txt";
        return 1;
    }

    cout << "�x�}���e�G" << endl;            // ��X�x�}���e 
    for (int i = 0; i < NumVertices; ++i) {
        for (int j = 0; j < NumVertices; ++j) {
            matrixFile >> adjMatrix[i][j];
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }cout << endl;


    matrixFile.close();

    int source;
    cout << "�п�J�X�o�I(1~7)�G";
    cin >> source;

    if (source < 0 || source >= NumVertices) {
        cerr << "�L�Ī��X�o�I";
        return 1;
    }

    shortestPath(source, adjMatrix, distance, NumVertices, found);
    
   
    
    return 0;
}

