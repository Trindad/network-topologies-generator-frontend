#include <chrono>
#include <ctime>
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>
#include "Plane.hpp"

class FileWriter
{
public:
	FileWriter();
	~FileWriter();

	string returnCurrentTimeAndDate();
	void writeCoordinatesTopologies(Graph, Plane);
	void writeTopologies(Graph,Plane,int);
	void writeMeasures();
	void closeFile();

private:
	string dateTime; //armazena data e hora
	ofstream output; //arquivo onde será armazenado as topologias geradas 
};
