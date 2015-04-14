#include "FileWrite.hpp"

FileWriter(){}

~FileWriter(){}

void FileWriter::writeTopologies(Graph g, Plane p)
{
    
	vector < vector<int> > coodinates = plane.getCoordinates();
	vector < vector<int> > adjacents = vector< vector<int> > (g.getNumberOfNodes(),vector<int>(g.getNumberOfNodes(),0));

	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

	end = std::chrono::system_clock::now();
 
    time_t end_time = chrono::system_clock::to_time_t(end);

	string fileName = "topology_"+ ;
    string date = ctime(&end_time);			//obtêm a data 
    date = date.substr(0, date.size()-1);	//elimina ultimo caractere lixo
    string extension = ".txt";

    string file = fileName+date+extension;

	ofstream output;

    output.open(file);

    this->dateTime = date;

    /**
     * Escreve no arquivo as posições de cada nó no grafo
     * A ordem de inserção é crescente
     */
	for (int i = 0; i < g.getNumberOfNodes(); i++)
	{
		output<<" "<<coodinates[i][0]<<" "<<coodinates[i][1]<<endl;
	}

	for (int i = 0; i < g.getNumberOfNodes(); i++)
	{
		
	}

}

void FileWriter::writeMeasures()
{

}
