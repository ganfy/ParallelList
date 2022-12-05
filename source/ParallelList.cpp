#include "ParallelList.h"
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <random>
#include <thread>
#include <iterator>
#include <vector>

using namespace std;

int main() {
	//LLP<int> lista;
	//lista.add(5);
	//lista.print();
	//lista.add(15);
	//lista.print();
	//lista.add(25);
	//lista.print();
	//lista.add(1);
	//lista.print();
	//lista.add(3);
	//lista.print();
	//lista.add(3);
	//lista.print();
	//cout << lista.contains(5) << endl;
	//lista.delet(5);
	//lista.print();
	//lista.delet(25);
	//lista.print();
	//cout << lista.contains(5) << endl;

	LLP<int> lista2;
	thread th1(add<int>(&lista2, 10, 100), 100);
	thread th2(dlt<int>(&lista2, 10, 100), 100);
	th1.join();
	th2.join();
	lista2.print();

	return 0;
}