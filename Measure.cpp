#include "Measure.hpp"

Measure::Measure(){}


Measure::~Measure(){}

double Measure::getDegreeCentrality(int index)
{
    return this->nodes[index].getDegreeCentrality();
}


double Measure::getBetweennessCentrality(int index)
{
    return this->nodes[index].getBetweennessCentrality();
}


double Measure::getClosenessCentrality(int index)
{
    return this->nodes[index].getClosenessCentrality();
}


double Measure::getEfficientCentrality(int index)
{
    return nodes[index].getEfficientCentrality();
}


void Measure::setDegreeCentrality(int index,double value)
{
    nodes[index].setDegreeCentrality(value);
}


void Measure::setBetweennessCentrality(int index,double value)
{
    nodes[index].setBetweennessCentrality(value);
}


void Measure::setClosenessCentrality(int index,double value)
{
    nodes[index].setClosenessCentrality(value);
}


void Measure::setEfficientCentrality(int index, double value)
{
    nodes[index].setEfficientCentrality(value);
}

void Measure::initialize(Graph &graph,int n, bool bc, bool cc, bool dc, bool ec)
{

    vector<Node> nodes = graph.getNodes();

    this->numberOfNodes = n;

    ofstream out;

    out.open("out");

    if (bc || cc || ec)
    {
        vector< vector<int> > graph = vector< vector<int> > ( n, vector<int> ( n,0 ) );
        /**
         * Gera matriz de adjacência do grafo a partir do vetor de nós
         */
        for ( int i = 0; i < this->numberOfNodes; i++)
        {
            vector <int> adjacents = nodes[i].getAdjacentsNodes();

            for (unsigned int j = 0; j < adjacents.size(); j++)
            {
                graph[i][ adjacents[j] ] = 1;//atribui ligação
            }
        }

        Brandes brandes (this->numberOfNodes);

        /**
         * Encontra todos os caminhos mínimos entre pares de nós do grafo
         */
        for (int i = 0; i < this->numberOfNodes; i++)
        {
            brandes.execute(graph,i,nodes);
            // brandes.printShortestPaths();
        }


        /**
         * Obtendo medidas de centralidade
         */

        vector< vector <int> > shortestPath = brandes.getShortestPath();

        if (bc)
        {
            betweennessCentrality(nodes);       //centralidade de intermediação
        }

        if (cc)
        { 
            closenessCentrality(nodes,shortestPath);    //centralidade de proximidade
        }

        if (ec)
        {
            efficientCentrality(nodes,shortestPath);        //centralidade de eficiência
        }

    }

    if (dc)
    {  
        degreeCentrality(nodes);                        //centralidade de grau
    }

    graph.setNodesMeasures(nodes);

}


void Measure::degreeCentrality(vector<Node> &nodes)
{

    int maximumDegree = -1;

    for (int i = 0; i < this->numberOfNodes; i++)
    {
        int degree = nodes[i].getDegree();

        nodes[i].setDegreeCentrality(degree);

        double relative = ( (double)degree / (double)(this->numberOfNodes-1) );

        nodes[i].setRelativeDegreeCentrality(relative);

        if (maximumDegree < degree)
        {
            maximumDegree = degree;
        }
    }
}


void Measure::closenessCentrality(vector<Node> &nodes, vector<vector <int> > shortestPath)
{
    for (int i = 0; i < this->numberOfNodes;i++)
    {
        double sum = 0;
        /**
         * Guarda a soma das distância de i para
         * os demais nós do grafo.
         */
        for (int j = 0; j < this->numberOfNodes; j++)
        {
            sum += shortestPath[i][j];
        }

        double cc = (double)( 1.0f / sum );

        nodes[i].setClosenessCentrality(cc);
    }
}


void Measure::efficientCentrality(vector<Node> &nodes, vector<vector <int> > shortestPath)
{

    for (int i = 0; i < this->numberOfNodes;i++)
    {
        int longestPath = 0;

        /**
         * Guarda a soma das distância de i para
         * os demais nós do grafo.
         */
        for (int j = 0; j < this->numberOfNodes; j++)
        {
            if (shortestPath[i][j] >  longestPath)
            {
                longestPath = shortestPath[i][j];

                double auxiliar = (double)shortestPath[i][j];

                double ef = (double) ( 1 / auxiliar ) ;

                nodes[i].setEfficientCentrality(ef);
            }
        }

    }
}

void Measure::betweennessCentrality(vector<Node> & nodes)
{
    int node = 0;
    double bc = -1.0;

    for (int v = 0; v < this->numberOfNodes; v++)
    {
        double value =  geodesic(nodes,v);
        nodes[v].setBetweennessCentrality(value);

        if (bc < value)
        {
          bc = value;
          node = v;
        }
    }

    this->centralNode = node;//armazena nó com a centralidade maior
}

/**
 * Calcula a centralidade de intermediação a partir das geodésicas obtidas
 * pelo algoritmo de Brandes e em seguida retorna a medida.
 */
double Measure::geodesic(vector<Node> nodes,int source)
{
  // cout<<"GEODESIC "<<this->numberOfNodes<<" "<<source<<endl;

  double bc = 0.0f;
  int i = 0, j = 0, n = this->numberOfNodes;

  for (i = 0; i < n-1; i++)
  {
    if (i == source)
    {
        continue;
    }

    for (j = i+1; j < n; j++)
    {

      if (j != source && i != j && i != source)
      {
        // cout<<"j "<<j<<" i "<<i<<" source "<<source<<endl;
        vector< vector<int> > paths;

        int nPaths = pathsSearch(nodes,i,j,paths);//número de geodésicas de i até j

        int nNodes = nodeSearch(paths,source,nPaths);
        // cout<<" "<<nPaths<<" "<<nNodes<<endl;

        bc = bc + ( (double)nNodes / (double)nPaths );

        paths.clear();
      }
    }
  }

  return bc;
}

/**
 * Encontra o número de caminhos que contêm o vértice de destino
 */
int Measure::pathsSearch(vector<Node> nodes, int source, int target, vector< vector<int> > &paths)
{

    if (source == target)
    {
        return 0;
    }

    int nPaths = 0;

    unsigned int n = nodes[source].getNumberOfPaths(), k = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        int auxiliar = nodes[source].getNumberOfNodesFromPath(i)-1;

        if ( nodes[source].returnNode(i,auxiliar) == target )
        {
            paths.push_back(vector<int>(auxiliar+1));

            for (k = 0; k <= auxiliar; k++)
            {
                paths[nPaths][k] = nodes[source].returnNode(i,k);
            }

            nPaths++;
        }
    }

    return nPaths;
}

/**
 *Busca vertice em um ou mais caminhos
 *parametros de entrada: caminhos e o vertice a ser buscado e o numero de caminhos minimos a ser buscado
 *retorna o numero de vezes que o vertice foi encontrado
 */
int Measure::nodeSearch(vector< vector<int> > &paths, int node, int nPaths)
{
    int count = 0;

    for (int i = 0; i < nPaths; i++)
    {
        for (unsigned int j = 0; j < paths[i].size(); j++)
        {
          if (node == paths[i][j])
          {
            count++;
          }
        }
    }
    
    return count;
}
