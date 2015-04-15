#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "Plane.hpp"
#include "Measure.hpp"
#include "Suurballe.hpp"
#include "FileWriter.hpp"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

     int simulations = 1;

     Graph graph; // cria objeto grafo

     graph.setNumberOfNodes( ui->nodes->value() ); //número de nós

     graph.setMinimumDegree(ui->minimumDegree->value());//grau mínimo

     graph.setMaximumDegree(ui->maximumDegree->value());//grau máximo

     graph.setMinimumDistanceOfNode(ui->distance->value());//distância mínima entre dois nós

     graph.memsetGraph();

     /**
      * Configurações do plano
      */

     Plane plane;

     plane.setArea(ui->area->value()); //valor da raiz da area

     /**
      * Verifica tipo de configuração para as regiões
      * Caso o usuário inserir somente o número de regiões
      * Então será calculado a largura e o comprimento.
      */
     if (ui->fexibleRegions->isChecked())
     {
        plane.setLength(ui->length->value());//comprimento

        plane.setBreadth(ui->breadth->value());//largura

     }
     else
     {

        plane.setNumberRegions(ui->numberOfRegions->value());

        plane.setRegionsMeasures();
     }

     plane.setWaxmanParameters(ui->alpha->value(),ui->beta->value());

     qDebug()<<ui->nodesDistribution->currentText();

     if(ui->nodesDistribution->currentText() == "Uniform")
     {
         plane.setDistributionType(0);
     }
     else
     {
         plane.setDistributionType(1);
     }

     try
     {
        plane.limitArea(graph.getNumberOfNodes());
     }
     catch(const char *error)
     {
        cout<<error<<endl;
     }

     plane.initialize(graph);


     /**
      * Verifica se o número de ligações foi atingido
      * Se sim verifica se a topologia gerada é sobrevivente
      * Do contrário realiza sorteio randômico de nós até atingir
      * o limit e máximo, verificando-se a sobrevivência
      */

     int notMax = std::numeric_limits<int>::max();

     cout<<"Interligação das regiões já realizada"<<endl;

     while( graph.getNumberOfEdges() < graph.getMinimumNumberOfEdges() && notMax >= 2)
     {
        notMax = plane.randomLink(graph);
     }

     cout<<"Interligação randomizada"<<endl;

     while( graph.getNumberOfEdges() < graph.getMaximumNumberOfEdges() && notMax >= 2)
     {
        notMax = plane.randomLink(graph);
     }

     cout<<"Finaliza ligações"<<endl;

     if(ui->measures->isChecked())
     {

         Measure measures;

         vector<Node> _nodes = graph.getNodes();
         measures.initialize( _nodes,graph.getNumberOfNodes() ); //obtêm as medidas de centralidade para cada nó da rede

         cout<<"measures"<<endl;
     }


     Suurballe s;

     bool survivor = s.execute(graph);

    cout<<"survivor "<<survivor<<endl;

    if(survivor)
    {
        FileWriter file;
        
        if (simulations == 1)
        {
            file.writeCoordinatesTopologies(graph,plane);
        }

        file.writeTopologies(graph,plane);

        simulations++;
    }
}

void MainWindow::on_fixedRegions_clicked()
{
    ui->numberOfRegions->setEnabled(true);

    ui->breadth->setEnabled(false);
    ui->length->setEnabled(false);
}

void MainWindow::on_fexibleRegions_clicked()
{
    ui->numberOfRegions->setEnabled(false);

    ui->breadth->setEnabled(true);
    ui->length->setEnabled(true);
}
