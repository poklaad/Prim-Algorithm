#include <iostream>
#include <cstdlib>
#include <ctime>
#define INF 2147483647

using namespace std;


//генератор входных данных
int** data_generator(int &vert) {
	int** graph = new int* [vert];
	for (int i = 0; i < vert; i++) {
		graph[i] = new int[vert];
		for (int j = i + 1; j < vert; j++) {
			graph[i][j] = (rand()%3 == 0 ? 0 : rand()%90 + 10); //проверка на %3 - дл€ создани€ более разреженного графа
		}
		graph[i][i] = 0;
		for (int j = i; j >= 0; j--) {
			graph[i][j] = graph[j][i];
		}
	}
	return graph;
}


//алгоритм ѕрима
pair<int, int>* PrimAlg(int** graph, int vert, pair<int, int>* span_edges, int &count) {
	pair<int, pair <int, int>>* edgesToChoose = new pair<int, pair <int, int>> [vert]; // неупор€доченный массив ребер дл€ выбора; 
																					   // первое - номер еще не добавленной вершины; 
																					   // второе - номер вершины, к которой оптимальнее всего присоединить эту вершину;
																					   // третье - вес такого ребра.
	for (int j = 0; j < vert; j++) { // первое задание элементов неупор€доченного массива ребер
		edgesToChoose[j] = make_pair(j, make_pair(0, graph[j][0]));
		++count;
	}
	for (int i = 0; i < vert-1; i++) { //цикл пока не будут добавлены все вершины
		int min_edge = INF;
		int toAdd1, toAdd2; //toAdd1 - еще не добавленна€ вершина, toAdd2 - к которой будет присоединена toAdd1
		int k = 0;
		for (int j = 0; j < vert - i; j++) {//проход по всем оставшимс€ вершинам
			count += 3;
			if (min_edge > edgesToChoose[j].second.second && edgesToChoose[j].second.second != 0) { //выбор минимального ребра
				min_edge = edgesToChoose[j].second.second;
				toAdd1 = edgesToChoose[j].first;
				toAdd2 = edgesToChoose[j].second.first;
				k = j;
			}
		}
		++count;
		span_edges[i] = make_pair(toAdd2, toAdd1);
		edgesToChoose[k] = edgesToChoose[vert - i - 1];
		for (int j = 1; j < vert - i - 1; j++) { // обновление неупор€доченного массива ребер
			++count;
			if (graph[toAdd1][edgesToChoose[j].first] != 0 && (graph[toAdd1][edgesToChoose[j].first] < edgesToChoose[j].second.second || edgesToChoose[j].second.second == 0)) {
				edgesToChoose[j] = make_pair(edgesToChoose[j].first, make_pair(toAdd1, graph[edgesToChoose[j].first][toAdd1]));
			}
		}
	}
	return span_edges;
}


int main() {
	srand(time(0));
	for (int c = 0; c < 10; c++)
	{

		int vert;
		int count = 0;

		//генераци€ графа
		vert = 1000 * (c + 1); //количество вершин в графе
		int** graph = data_generator(vert);


		//вывод исходного графа
		//cout << "Original graph:" << endl << "Count of vertices: " << vert << endl << "Graph: " << endl;
		cout << vert << ' ';
		/*for (int i = 0; i < vert; i++) {
			for (int j = 0; j < vert; j++) {
				cout << graph[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;*/

		//применение алгоритма ѕрима
		pair<int, int>* span_edges = new pair<int, int>[vert - 1];
		span_edges = PrimAlg(graph, vert, span_edges, count);

		//¬ывод минимального остовного графа
		//cout << "Minimal spanning graph:" << endl << "edges  :  weight" << endl;
		/*for (int i = 0; i < vert - 1; i++) {
			cout << span_edges[i].first << "---" << span_edges[i].second << "  :  " << graph[span_edges[i].first][span_edges[i].second] << endl;
		}*/
		//cout << endl << "Number of comparison operations: " << count;// << endl << c;
		cout << count << endl;

		for (int i = 0; i < vert; i++) {
			delete[] graph[i];
		}
		delete[] graph;
		delete[] span_edges;

	}
	return 0;
}