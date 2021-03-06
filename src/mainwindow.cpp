#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QDesktopServices>//para abrir help
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

    connect(ui->actionOpen_help, SIGNAL(triggered()), this, SLOT(on_help_clicked()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openNewWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewWindow()
{
    this->aboutWindow = new About(this);
    this->aboutWindow->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->error->setText(QString::fromUtf8(""));
     ui->error->setText(QString::fromUtf8(""));
     ui->pushButton->setEnabled(false);
     ui->pushButton->setText("Simulating...");
     ui->pushButton->repaint();
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
    // cout<<ui->bc->isChecked()<< ui->cc->isChecked()<< ui->dc->isChecked()<< ui->ec->isChecked()<<endl;

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

     // qDebug()<<ui->nodesDistribution->currentText();

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
        ui->pushButton->setText("Begin simulation");
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
        ui->pushButton->setText("Begin simulation");
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

            if (graph.getAverageDegree() >= graph.getMaximumAverageDegree())
            {
                break;
            }
         }


        Suurballe s;

        bool survivor = s.execute(graph);

        // cout<<"survivor "<<survivor<<endl;

        if(survivor)
        {
            if (simulation == 1)
            {
                file.openFile();
                file.writeCoordinatesTopologies(graph,plane);
            }

            file.writeTopologies(graph,simulation,topology);


            if( (ui->bc->isChecked() || ui->cc->isChecked() || ui->dc->isChecked() || ui->ec->isChecked() ) && survivor)
            {
                // cout<<"\n Measures"<<endl;
                if (simulation)
                {
                    file.createXls();
                }
                Measure measures;
                
                measures.initialize( graph,graph.getNumberOfNodes(),ui->bc->isChecked(),ui->cc->isChecked(),ui->dc->isChecked(),ui->ec->isChecked() ); //obtêm as medidas de centralidade para cada nó da rede

                file.writeMeasures(graph,ui->bc->isChecked(),ui->ec->isChecked(),ui->dc->isChecked(),ui->cc->isChecked());
            }

            topology++;
        }

        int nEdges = graph.getNumberOfEdges();


        while( (graph.getNumberOfEdges() < graph.getMaximumNumberOfEdges() && notMax >= 2) && ( (graph.getAverageDegree() < graph.getMaximumAverageDegree() ) && notMax >= 2) )
        {
            notMax = plane.randomLink(graph);
          
            if (graph.getNumberOfEdges() > nEdges)
            {
                nEdges = graph.getNumberOfEdges();

                /**
                 * Executa algoritmo se Suurballe somente 
                 * se a rede não for sobrevivente
                 */
                if (survivor == false)
                {
                    Suurballe suurballe;

                    survivor = suurballe.execute(graph);
                }

                // cout<<"survivor "<<survivor<<endl;
                if(survivor)
                {
                    if (simulation == 1 && topology == 1)
                    {
                        file.openFile();
                        file.writeCoordinatesTopologies(graph,plane);
                    }

                    file.writeTopologies(graph,simulation,topology);

                    if( (ui->bc->isChecked() || ui->cc->isChecked() || ui->dc->isChecked() || ui->ec->isChecked() ) && survivor )
                    {
                        if (simulation)
                        {
                            file.createXls();
                        }

                         Measure measures;

                         measures.initialize(graph,graph.getNumberOfNodes(),ui->bc->isChecked(),ui->cc->isChecked(),ui->dc->isChecked(),ui->ec->isChecked() ); //obtêm as medidas de centralidade para cada nó da rede

                         file.writeMeasures(graph,ui->bc->isChecked(),ui->ec->isChecked(),ui->dc->isChecked(),ui->cc->isChecked());
                    }

                    topology++;
                }

                if (graph.getAverageDegree() >= graph.getMaximumAverageDegree())
                {
                    break;
                }

                survivor = false;
            }
        }

        simulation++;
     }

     QString message = "Simulation complete. File located at \"";
     message.append(QDir::homePath());
     message.append("/simulations\"");

     ui->error->setText(message);

     file.closeFileTopologies();
     if (ui->bc->isChecked() || ui->cc->isChecked() || ui->dc->isChecked() || ui->ec->isChecked())
     {
        file.closeFileMeasures();
     }
     ui->pushButton->setEnabled(true);
     ui->pushButton->setText("Begin simulation");
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
    if(ui->bc->isChecked())
    {
        ui->bc->setEnabled(true);
    }
    else
    {
        ui->bc->setEnabled(false);
    }

    if(ui->ec->isChecked())
    {
        ui->ec->setEnabled(true);
    }
    else
    {
        ui->ec->setEnabled(false);
    }

    if(ui->cc->isChecked())
    {
        ui->cc->setEnabled(true);
    }
    else
    {
        ui->cc->setEnabled(false);
    }

    if(ui->dc->isChecked())
    {

        ui->dc->setEnabled(true);
    }
    else
    {
        ui->dc->setEnabled(false);
    }
}

void MainWindow::on_help_clicked()
{
    QDesktopServices::openUrl(QUrl(QString::fromStdString(this->appPath+"/help/index.html"), QUrl::TolerantMode));
}
