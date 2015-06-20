#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
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
     ui->error->setText(QString::fromUtf8(""));
     ui->pushButton->setEnabled(false);

     int simulation = 1;
     FileWriter file;

     Graph graph; // cria objeto grafo

     graph.setNumberOfNodes( ui->nodes->value() ); //número de nós

     graph.setMinimumDegree(ui->minimumDegree->value());//grau mínimo

     graph.setMaximumDegree(ui->maximumDegree->value());//grau máximo

     graph.setMinimumDistanceOfNode(ui->distance->value());//distância mínima entre dois nós

     graph.setMaximumAverageDegree(ui->max_average_degree->value());

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
        ui->error->setText(QString::fromUtf8("2N ≤ R ≤ N²\n"));
        ui->pushButton->setEnabled(true);
        return;
     }

     try
     {
        graph.limitDegree();
     }
     catch(const char *error)
     {
        ui->error->setText(QString::fromUtf8("2 ≤ Maximum Degree ≤ N-1\n"));
        ui->pushButton->setEnabled(true);
        return;
     }

     plane.setNumberOfSimulations(ui->numberOfSimulations->value());

     while( simulation <= plane.getNumberOfSimulations() )
     {
        graph.memsetGraph();

        plane.initialize(graph,simulation);

         /**
          * Verifica se o número de ligações foi atingido
          * Se sim verifica se a topologia gerada é sobrevivente
          * Do contrário realiza sorteio randômico de nós até atingir
          * o limit e máximo, verificando-se a sobrevivência
          */

         int notMax = std::numeric_limits<int>::max();
         int topology = 1;

         while( ( graph.getNumberOfEdges() < graph.getMinimumNumberOfEdges() && notMax >= 2) && ( (graph.getAverageDegree() < graph.getMaximumAverageDegree() ) && notMax >= 2) )
         {
            notMax = plane.randomLink(graph);
            cout<<" "<<notMax<<endl;
         }


        Suurballe s;

        bool survivor = s.execute(graph);

        cout<<"survivor "<<survivor<<endl;

        if(survivor)
        {
            if (simulation == 1)
            {
                file.openFile();
                file.writeCoordinatesTopologies(graph,plane);
            }

            file.writeTopologies(graph,plane,simulation,topology);


            if(ui->measures->isChecked() && survivor)
            {
                cout<<"Measures"<<endl;
                if (simulation == 1)
                {
                    file.createXls(ui->bc->isChecked(),ui->cc->isChecked(),ui->dc->isChecked(),ui->ec->isChecked());
                }
                Measure measures;
                
                measures.initialize( graph,graph.getNumberOfNodes(),ui->bc->isChecked(),ui->cc->isChecked(),ui->dc->isChecked(),ui->ec->isChecked() ); //obtêm as medidas de centralidade para cada nó da rede

                file.writeMeasures(graph,ui->bc->isChecked(),ui->ec->isChecked(),ui->dc->isChecked(),ui->cc->isChecked());
            }

            topology++;
        }

        survivor = false;

        int nEdges = graph.getNumberOfEdges();


        while( (graph.getNumberOfEdges() < graph.getMaximumNumberOfEdges() && notMax >= 2) && ( (graph.getAverageDegree() < graph.getMaximumAverageDegree() ) && notMax >= 2) )
        {
            notMax = plane.randomLink(graph);
            cout<<" "<<notMax<<endl;
            if (graph.getNumberOfEdges() > nEdges)
            {
                nEdges = graph.getNumberOfEdges();

                Suurballe suurballe;

                survivor = suurballe.execute(graph);

                cout<<"survivor "<<survivor<<endl;
                if(survivor)
                {
                    if (simulation == 1 && topology == 1)
                    {
                        file.openFile();
                        file.writeCoordinatesTopologies(graph,plane);
                    }

                    file.writeTopologies(graph,plane,simulation,topology);

                    if(ui->measures->isChecked())
                    {
                        cout<<"Measure"<<endl;
                        if (simulation == 1)
                        {
                            file.createXls(ui->bc->isChecked(),ui->cc->isChecked(),ui->dc->isChecked(),ui->ec->isChecked());
                        }

                         Measure measures;

                         measures.initialize(graph,graph.getNumberOfNodes(),ui->bc->isChecked(),ui->cc->isChecked(),ui->dc->isChecked(),ui->ec->isChecked() ); //obtêm as medidas de centralidade para cada nó da rede

                         file.writeMeasures(graph,ui->bc->isChecked(),ui->ec->isChecked(),ui->dc->isChecked(),ui->cc->isChecked());
                    }

                    topology++;
                }

                survivor = false;
            }
        }

        simulation++;
     }

     cout<<"\nmax degree "<<graph.getAverageDegree()<<endl;
     file.closeFileTopologies();
     file.closeFileMeasures();
     ui->pushButton->setEnabled(true);
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

void MainWindow::on_measures_clicked()
{
    if(ui->measures->isChecked())
    {
        ui->bc->setEnabled(true);
        ui->ec->setEnabled(true);
        ui->cc->setEnabled(true);
        ui->dc->setEnabled(true);
    }
    else
    {
        ui->bc->setEnabled(false);
        ui->ec->setEnabled(false);
        ui->cc->setEnabled(false);
        ui->dc->setEnabled(false);
    }
}
