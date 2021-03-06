/**
 * Definições de função-membro que aparecem em Measure.cpp
 */
#include "Brandes.hpp"

 using namespace std;

 class Measure
 {
 public:

 	Measure();
 	~Measure();


 	double getDegreeCentrality(int);
	double getBetweennessCentrality(int);
	double getClosenessCentrality(int);
	double getEfficientCentrality(int);


	void setDegreeCentrality(int,double);
	void setBetweennessCentrality(int,double);
	void setClosenessCentrality(int,double);
	void setEfficientCentrality(int, double);


	void degreeCentrality(vector<Node> &);
	void betweennessCentrality(vector<Node> &);
	void closenessCentrality(vector<Node> &, vector<vector <int> >);
	void efficientCentrality(vector<Node> &, vector<vector <int> >);	

 	double geodesic(vector<Node>,int);
 	int nodeSearch(vector< vector<int> > &, int, int);
 	void initialize(Graph &,int,bool,bool,bool,bool);
 	int pathsSearch(vector<Node>, int, int,vector< vector<int>> &);

private:

	vector<Node> nodes;
	int numberOfNodes;
	int centralNode;	//nó central em relação a centralidade de intermediação
 };