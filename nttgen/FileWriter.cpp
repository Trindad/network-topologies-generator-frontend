#include "FileWriter.hpp"

FileWriter::FileWriter(){}

FileWriter::~FileWriter(){}

string FileWriter::returnCurrentTimeAndDate()
{
    time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%d_%m_%Y_%T",timeinfo);

	return buffer;
}

void FileWriter::writeCoordinatesTopologies(Graph g, Plane plane)
{
	if (this->output.good())
	{
		string fileName = "topology_";
	    string date = returnCurrentTimeAndDate();
	    string extension = ".txt";

	    string file = fileName+date+extension;

	    this->output.open(file);

	    this->dateTime = date;


		vector < vector<int> > coodinates = plane.getCoordinates();

	    /**
	     * Escreve no arquivo as posições(x,y) de cada nó no grafo
	     * A ordem de inserção é crescente
	     */
	    this->output<<" Row "<<" Column "<<endl;

	    for (int u = 0; u < g.getNumberOfNodes(); u++)
		{
			char str[255];
            sprintf(str," %*d  %*d ", 2, coodinates[u][0], 4, coodinates[u][1]);
	        this->output<<str<<endl;
		}
	}
	else
	{
		exit(1);
	}
}

void FileWriter::writeTopologies(Graph g, Plane plane)
{
	vector < vector<int> > graph = vector< vector<int> > (g.getNumberOfNodes(),vector<int>(g.getNumberOfNodes(),0));
	vector<Node> node = g.getNodes();
	

	this->output<<"\n From "<<" To "<<" Distance "<<endl;
    for (int u = 0; u < g.getNumberOfNodes(); u++)
	{
		vector<int> adj = node[u].getAdjacentsNodes();
		vector<double> euclidean = node[u].getEuclideanDistance();
		
		unsigned int count = 0, n = adj.size();

		while(count < n)
		{
			int v = adj[count];

	        if(graph[u][v] == 1 || graph[v][u] == 1)
	        {
	        	count++;
	            continue;
	        }

	        graph[u][v] = graph[v][u] = 1;

	        char str[255];
            sprintf(str," %*d  %*d  %*f ", 2, u, 4, v, 8, euclidean[count]);

			this->output<<str<<"\n";
        	count++;
		}
	}
}

void FileWriter::writeMeasures()
{

}

void FileWriter::closeFile()
{
	this->output.close();
}
