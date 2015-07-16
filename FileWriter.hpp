#include <chrono>
#include <ctime>
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>

#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxconditionalformatting.h"

#include "Plane.hpp"

using namespace QXlsx;

class FileWriter
{
public:
	FileWriter();
	~FileWriter();

	void openFile();
	string returnCurrentTimeAndDate();
    void createXls();
	void writeCoordinatesTopologies(Graph, Plane);
    void writeTopologies(Graph,int,int);
	void writeMeasures(Graph &,bool,bool,bool,bool);
	void closeFileTopologies();
	void closeFileMeasures();

private:
	string dateTime; 	//armazena data e hora
	ofstream output;	//arquivo onde será armazenado as topologias geradas
	Document xlsx;		//arquivo xls
	Format hFmt;		//formato 
	int row;			//guarda a linha da ultima topologia gravada
	int simulation;		//guarda a simulação anterior
	int lastSimulation; //número da simulação anterior
	int topology;		//armazena número da topologia no momento 
};
