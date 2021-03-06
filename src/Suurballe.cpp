/**
 * Algoritmo de roteamento
 */

#include "Suurballe.hpp"

Suurballe::Suurballe(){}

Suurballe::~Suurballe(){}

void Suurballe::insertSubtree(Graph graph, tree<int> &tr, typename tree<int>::iterator root,vector<int> nodes, vector<int> &controller, int source)
{
    // cout<<"source "<<source<<endl;
    Node node = graph.getNodeAtPosition(source);
    vector<int> adjacents = node.getAdjacentsNodes();
    typename tree<int>::iterator temp;
    typename tree<int>::iterator newRoot;
    int newSource = source;

    // for (unsigned int w = 0; w < nodes.size(); w++)
    // {
    //     cout<<" "<<nodes[w];
    // }
    // cout<<endl;
    if (find(this->nodeInTree.begin(),this->nodeInTree.end(),source) == this->nodeInTree.end())
    {
        this->nodeInTree.push_back(source);
    }

    unsigned  int it = 0;

    while( adjacents.size() > it )
    {
        if (controller[ adjacents[it] ] == -1)
        {
            temp = tr.append_child( root, adjacents[it] );

            controller[ adjacents[it] ] = adjacents[it];

            if (find(this->nodeInTree.begin(),this->nodeInTree.end(),adjacents[it]) == this->nodeInTree.end())
            {
                this->nodeInTree.push_back(adjacents[it]);
            }

            if( find(nodes.begin(),nodes.end(),adjacents[it]) != nodes.end() )
            {
                newRoot = temp;
                newSource = adjacents[it];
            }
        }


        it++;
    }

    int n = nodes.size()-1;
    // cout<<"n "<<n<<" "<<nodes[n]<<endl;
    if (source == nodes[n] )
    {
        // cout<<"cai fora"<<endl;
        return;
    }

    insertSubtree(graph,tr,newRoot,nodes,controller,newSource);
}

tree<int> Suurballe::makeTree(Graph graph, vector<int> nodes, int source)
{
    vector<Node> auxiliar;
    auxiliar = graph.getNodes();

    tree<int> tr;

    tree<int>::iterator root, top;

    top = tr.begin();
    root = tr.insert( top, source );

    vector<int> controller = vector<int> (this->numberOfNodes,-1);

    controller[source] = source;

    insertSubtree(graph,tr,root,nodes,controller,source);

    // cout<<endl;
    // kptree::print_tree_bracketed(tr,cout); //imprime árvore
    // cout<<endl;

    return tr;
}

/**
 * Atualiza peso dos nós da árvore para 0
 * e as demais ligações aplica a função:
 * w'(u,v) = w (w,u) - d(s,v) + d(s,u) 
 */
void Suurballe::updateEdgesWeight(const tree<int>& t, typename tree<int>::iterator iRoot, vector<int> nodes, Graph & graph, int source)
{
    if( t.empty() )
    {
        return;
    }

    if (t.number_of_children(iRoot) == 0)
    {
        return;
    }
    else
    {
        // child1, ..., childn
        int siblingNum;

        typename tree<int>::sibling_iterator iChildren;
        double weight = 0.0f ;//w'(u,v) = w (w,u) - d(s,v) + d(s,u)

        for (iChildren = t.begin(iRoot), siblingNum = 0; iChildren != t.end(iRoot); ++iChildren, ++siblingNum)
        {
            weight = 0.0f;
            int u = *iRoot, v = *iChildren;   
             /**
             * Remove arestas do caminho mínimo de ida
             * Deixando somente as arestas de volta
             */
            if ( (nodes[ u ] == u || u == source) && ( nodes[ v ] == v || v == source) )
            {
                graph.setWeightEdgeDirected(u,v,weight);

                graph.setWeightEdgeDirected(v,u,weight);

                graph.removeNode(u,v);
            }
            else if (find(this->nodeInTree.begin(),this->nodeInTree.end(),u) != this->nodeInTree.end() && find(this->nodeInTree.begin(),this->nodeInTree.end(),v) != this->nodeInTree.end() )
            {
                graph.setWeightEdgeDirected(u,v,weight);

                weight = this->distance[v][u] - this->distance[source][u] + this->distance[source][v];
                graph.setWeightEdgeDirected(v,u,weight);

                
            }
            else
            {
                weight = this->distance[u][v] - this->distance[source][v] + this->distance[source][u];

                graph.setWeightEdgeDirected(u,v,weight);

                u = *iChildren, v = *iRoot;

                weight = this->distance[u][v] - this->distance[source][v] + this->distance[source][u];

                graph.setWeightEdgeDirected(u,v,weight);

            }

            this->treePath[v][u] = 1;
            this->treePath[u][v] = 1;

            updateEdgesWeight(t,iChildren,nodes,graph,source);
        }
    }
}

/**
 * Todas as arestas da árvore receberão peso 0
 * Os demais nós será aplicado a fórmula proposta:
 *      w'(u,v) = w (w,u) - d(s,v) + d(s,u)
 */
void Suurballe::changeEdgesWeights(Graph & graph, tree<int> tr, vector<int> nodes)
{
    int source = *tr.begin();

    /**
     * Percore árvore atualizando o peso das ligações u --> v
     * Se o nodo esta no caminho o peso passa a ser 0 (zero)
     * Do contrário aplica a equação proposta por Suurballe
     * Sendo s o source e u e v nós pertencentes a árvore
     *      w'(u,v) = w (u,v) - d(s,v) + d(s,u)
     */

    typename tree<int>::sibling_iterator iRoot = tr.begin();


    unsigned int count = 0;

    vector<int> temp = vector<int> (this->numberOfNodes,-1);

    while( count < nodes.size() )
    {
        temp[ nodes[count] ] = nodes[count];

        count++;
    }

    updateEdgesWeight(tr,iRoot,temp,graph,source);//atualiza peso e remove ligações

    /**
     * Atualiza nós não pertencentes a árvore
     */
    vector<Node> n = graph.getNodes();
    for (unsigned int u = 0; u < this->nodeInTree.size(); u++)
    {
        vector<int> adjacents = n[u].getAdjacentsNodes();

        for (unsigned int v = 0; v < adjacents.size(); v++)
        {
            double weight = 0.0f;
            int w = adjacents[v];

            if (this->treePath[u][v] == 0)
            {
                weight = this->distance[u][w] - this->distance[source][w] + this->distance[source][u];
                
                graph.setWeightEdgeDirected(u,w,weight);

                weight = this->distance[w][u] - this->distance[source][u] + this->distance[source][w];
                
                graph.setWeightEdgeDirected(w,u,weight);

                this->treePath[w][u] = 1;
                this->treePath[u][w] = 1;
            }
        }
    }

}

void Suurballe::makePathVector(vector<int> p1,vector<int> &p2, vector<int> &inPath)
{
    for ( unsigned int u = 0; u < p1.size()-1; u++)
    {
        p2.push_back( p1[u] );
        p2.push_back( p1[u+1] );

        inPath[ p1[u] ] = p1[u];
        inPath[ p1[u+1] ] = p1[u+1];
    }
}

vector<int> Suurballe::disjointPath(int target)
{
    vector<int> path;

    int u = target;

    path.push_back( target );

    while( this->parent[u] != -1 )
    {
        path.push_back( this->parent[u] );
        u = this->parent[u];
    }

    reverse( path.begin(),path.end() );//inverte caminho

    return path;
}

/**
 * armazena nós visitados em visited
 */
bool Suurballe::findPath(Graph &g, vector<Node> nodes,int source, int target)
{
    if( this->visited[source] == 1 || source == target ) return true;

    this->visited[source] = 1;

    vector<int> adjacents = nodes[source].getAdjacentsNodes();

    for( int u = 0; u < this->numberOfNodes; u++)
    {
        //verifica se existe ligação
        if ( find(adjacents.begin(),adjacents.end(),u) != adjacents.end() )
        {
            g.removeNode(source,u);
            this->parent[u] = source;

            if( findPath(g, nodes,u,target) ) return true;
        }
    }

    return false;
}

bool Suurballe::makeSubgraphDisjointPaths(Graph &g, int source, int target)
{
    vector<Node> nodes = g.getNodes();

    //nó origem com mais de uma aresta de saída
    if ( nodes[source].getAdjacentsNodes().size() >= 3 )
    {
        return false;
    }

    //nó destino possui aresta de saída
    if ( nodes[target].getAdjacentsNodes().size() >= 1 )
    {
        return false;
    }

    int count = 0;

    vector<vector<int>> p;

    while(count < 2)
    {

        this->visited = vector<int> (g.getNumberOfNodes(),0);
        this->parent = vector<int> (g.getNumberOfNodes(),-1);

        findPath(g,nodes,source,target);

        p.push_back( disjointPath(target) );

        nodes = g.getNodes();
        count++;
    }

    nodes = g.getNodes();

    //verifica se os nós não possuem mais nenhuma ligação
    for (int u = 0; u < g.getNumberOfNodes(); u++)
    {
        if (nodes[u].getAdjacentsNodes().size() >= 1 )
        {
            return false;
        }
    }


    return true;
}

bool Suurballe::makeDisjointPaths(vector<int> path1, vector<int> path2)
{

    vector<int> p1,p2;

    vector<int> temp = vector<int> (this->numberOfNodes,-1);

    makePathVector(path1,p1,temp);
    makePathVector(path2,p2,temp);

    /**
     * Remover arestas invertidas
     * Dos caminhos mínimos p1 e p2
     */

    for ( unsigned int u = 0; u < p1.size()-1; u+=2)
    {
        for (unsigned int v = 0; v < p2.size()-1; v+=2)
        {
            //exclui enlace
            if (p1[u] == p2[v+1] && p1[u+1] == p2[v])
            {
                p1.erase( p1.begin() + u );
                p1.erase( p1.begin() + ( u + 1 ) );

                p2.erase( p2.begin() + v );
                p2.erase( p2.begin() + ( v + 1 ) );
            }
        }
    }

    Graph g;

    g.setNumberOfNodes(this->numberOfNodes);

    g.memsetGraph();

    /**
     * Insere as arestas e seus respectivos pesos
     */
    g.setMaximumDegree(g.getNumberOfNodes()-1);
    g.setMinimumDegree(1);

    unsigned int u = 0;

    for (u = 0; u < p1.size(); u+=2)
    {
        g.setEdgeDirected(p1[u],p1[u+1]);

    }

    for (u = 0; u < p2.size(); u+=2)
    {
        g.setEdgeDirected(p2[u],p2[u+1]);

    }

    int source = path1[0];
    int target = path1[ path1.size()-1 ];

    /**
     * Verifica se existem duas arestas de saída no source
     * E duas arestas de entrada no target, além disso deve
     * haver uma de entrada e uma de saída nos nós restantes
     */

    return makeSubgraphDisjointPaths(g,source,target);
}

bool Suurballe::execute(Graph & graph)
{

    bool survivor = false;

    this->numberOfPaths = 0;

    Dijkstra dijkstra;

    this->numberOfNodes = graph.getNumberOfNodes();

    this->distance = vector<vector<int>> (this->numberOfNodes,vector<int>( this->numberOfNodes,0) );

    int n = 0, v = 0;
   
    /**
     * Para cada par de nós (u,v)
     * Obtêm caminho mínimo
     */
    for (int u = 0; u < this->numberOfNodes-1; u++)
    {
        for(v = u+1; v < this->numberOfNodes; v++)
        {
            this->distance[u][v] = this->distance[v][u] = dijkstra.execute(graph,u,v);
            
            this->path.push_back( dijkstra.shortestPath(v) );

            if ( path[n].size() <= 1)
            {
                return survivor;
            }

            n++;
        }
    }

    this->numberOfPaths = n;

    // cout<<"numberOfPaths "<<this->numberOfPaths<<endl;

    int iterator = 0;
    double dist = 0;

    for ( int u = 0; u < this->numberOfNodes-1; u++)
    {
        for (v = u+1; v < this->numberOfNodes; v++)
        {
            Graph auxiliar = graph;

            /**
             * mudança de peso nas arestas
             * Monta árvore a partir do nó u
             */
            this->treePath = vector<vector<int>> (this->numberOfNodes,vector<int>(this->numberOfNodes,0)); 
            // cout<<"\n----------------------"<<u<<" "<<v <<"---------------------------"<<endl;
            // for (unsigned int w = 0; w < path[iterator].size(); w++)
            // {
            //     cout<<" "<<path[iterator][w];
            // }
            // cout<<endl;

            tree<int> tr = makeTree(auxiliar, this->path[iterator], u);
           
            changeEdgesWeights(auxiliar, tr, this->path[iterator]);
          
            dist =  dijkstra.execute(auxiliar,u,v);

            if ( dist == std::numeric_limits<double>::max() )
            {
                return false;
            }

            vector<int> newPath = dijkstra.shortestPath(v);

            //não encontrou caminho
            if (newPath.size() <= 1)
            {
                return false;
            }

            survivor = makeDisjointPaths(path[iterator],newPath);

            if (survivor == false)
            {
                return false;
            }

            this->nodeInTree.empty();

            iterator++;
        }
    }
 
    return survivor;
}
