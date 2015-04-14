#include <chrono>
#include <ctime>
#include "Graph.hpp"

class FileWriter
{
public:
	FileWriter();
	~FileWriter();

	void writeTopologies(Graph,Plane);
	void writeMeasures();

private:
	string dateTime; //armazena data e hora 
};