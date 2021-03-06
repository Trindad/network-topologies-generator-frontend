#include "FileWriter.hpp"
#include <QDir>

FileWriter::FileWriter()
{

	this->simulation = 0;
	this->lastSimulation = 0;
	this->row = 1;
}

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

void FileWriter::openFile()
{
	//txt
    string date = returnCurrentTimeAndDate();
    QString temp = QDir::homePath();
    temp.append("/simulations");
    /**
     * Cria diretório caso não exista
     */
    QDir dir(temp);

    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    temp.append("/topology_");

    temp.append(QString::fromStdString(date));
    temp.append(".txt");

    string file = temp.toStdString();
    // cout << file << endl;

    this->output.open(file);

    this->dateTime = date;
}


void FileWriter::createXls()
{
    //xls
   this->hFmt.setFontBold(true);
   
}

void FileWriter::writeCoordinatesTopologies(Graph g, Plane plane)
{

	if (this->output.good())
	{
		vector < vector<int> > coordinates = plane.getCoordinates();

	    /**
	     * Escreve no arquivo as posições(x,y) de cada nó no grafo
	     * A ordem de inserção é crescente
	     */
	    this->output<<" X\t"<<"Y "<<endl;

	    for (int u = 0; u < g.getNumberOfNodes(); u++)
		{
			char str[255];
            sprintf(str," %*d  %*d ", 2, coordinates[u][0], 4, coordinates[u][1]);
	        this->output<<str<<endl;
		}
	}
	else
	{
		exit(1);
	}
}

void FileWriter::writeTopologies(Graph g, int s, int topology)
{
	vector < vector<int> > graph = vector< vector<int> > (g.getNumberOfNodes(),vector<int>(g.getNumberOfNodes(),0));
	vector<Node> node = g.getNodes();
	
	if (s > this->simulation)
	{
		this->output<<"\nSimulation "<<s<<endl;

		this->lastSimulation = this->simulation;
		this->simulation = s;
	}

	this->output<<"Topology "<<topology<<endl;
	this->topology = topology;

	this->output<<" From "<<" To "<<" Distance "<<endl;

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
            sprintf(str," %*d  %*d  %*.3f ", 2, u, 4, v, 8, euclidean[count]);

			this->output<<str<<"\n";
        	count++;
		}
	}
}

void FileWriter::writeMeasures(Graph &graph, bool bc, bool ec, bool dc, bool cc)
{
	int it = this->row,node = 0;

    
	string str = "Simulation( "+to_string(this->simulation)+" )";
    string cell = "A"+to_string(this->row);

    this->xlsx.write(cell.c_str(),str.c_str(),this->hFmt);
   	
    str = "Topology( "+to_string(this->topology)+" )";
    cell = "B"+to_string(this->row);

    this->xlsx.write(cell.c_str(),str.c_str(),this->hFmt);
	this->row++;

	//insere o nó respectivo
	
   	it = this->row;

	cell = "A"+to_string(this->row);
   	this->xlsx.write(cell.c_str(), "Node", this->hFmt);
   	it++;

	for ( ; node < graph.getNumberOfNodes(); node++)
	{
		this->xlsx.write(it,1,node);
		it++;
	}

	//escreve dados da centralidade de intermediação no arquivo
	if (bc)
	{
		cell = "B"+to_string(this->row);
		this->xlsx.write(cell.c_str(), "Between Centrality", this->hFmt);

   	    vector<Node> node = graph.getNodes();
        it = this->row+1;

        for (int u = 0;  u < graph.getNumberOfNodes(); u++) 
        {   
//	      	cout<<"bc( "<<u<<") = "<<betweenCentrality<<endl;
            string temp = to_string( node[u].getBetweennessCentrality() );
            // cout<<"temp betweenCentrality "<<temp<<" "<<node[u].getBetweenCentrality()<<endl;
            this->xlsx.write(it, 2, temp.c_str() );

	        it++;
	   	}
	}

	//escreve dados da centralidade de eficiência
	if (ec)
	{
		cell = "E"+to_string(this->row);
		this->xlsx.write(cell.c_str(), "Efficient Centrality", this->hFmt);
	
        vector<Node> node = graph.getNodes();
        it = this->row+1;

        for (int u = 0; u < graph.getNumberOfNodes(); u++)
		{

            string temp = to_string( node[u].getEfficientCentrality() );
            this->xlsx.write(it,5, temp.c_str());

            it++;
		}
	}

	//centralidade do grau
	if (dc)
	{
		cell = "D"+to_string(this->row);
		this->xlsx.write(cell.c_str(), "Degree Centrality", this->hFmt);
	
        vector<Node> node = graph.getNodes();
        it = this->row+1;

        for (int u = 0; u < graph.getNumberOfNodes(); u++)
		{
            string temp = to_string( node[u].getDegreeCentrality() );
			this->xlsx.write(it,4, temp.c_str());

            it++;
		}
	}

	//centralidade de proximidade
	if (cc)
	{
		cell = "C"+to_string(this->row);
		this->xlsx.write(cell.c_str(), "Closeness Centrality", this->hFmt);
	
        vector<Node> node = graph.getNodes();
        it = this->row+1;

        for (int u = 0; u < graph.getNumberOfNodes(); u++)
		{
            string temp = to_string(node[u].getClosenessCentrality());
			this->xlsx.write(it,3, temp.c_str());

            it++;
   		}
	}

	this->row = it+2;
}


void FileWriter::closeFileMeasures()
{

    QString temp = QDir::homePath();
    temp.append("/simulations/measure_");
    temp.append(QString::fromStdString(this->dateTime));
    temp.append(".xlsx");

    xlsx.saveAs(temp);
}

void FileWriter::closeFileTopologies()
{
	this->output.close();
}
