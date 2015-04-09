/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Mar 30 14:53:08 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QSpinBox *nodes;
    QSpinBox *minimumDegree;
    QSpinBox *maximumDegree;
    QSpinBox *distance;
    QSpinBox *area;
    QSpinBox *numberOfRegions;
    QSpinBox *length;
    QSpinBox *breadth;
    QRadioButton *fixedRegions;
    QRadioButton *fexibleRegions;
    QComboBox *comboBox;
    QCheckBox *measures;
    QCheckBox *bc;
    QCheckBox *dc;
    QCheckBox *ec;
    QCheckBox *cc;
    QSpinBox *numberOfSimulations;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QGroupBox *groupBox;
    QLabel *label_7;
    QDoubleSpinBox *alpha;
    QLabel *label_6;
    QDoubleSpinBox *beta;
    QLabel *label_15;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(740, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(550, 510, 151, 41));
        nodes = new QSpinBox(centralWidget);
        nodes->setObjectName(QString::fromUtf8("nodes"));
        nodes->setGeometry(QRect(40, 90, 61, 31));
        nodes->setMinimum(3);
        nodes->setMaximum(1000);
        nodes->setValue(5);
        minimumDegree = new QSpinBox(centralWidget);
        minimumDegree->setObjectName(QString::fromUtf8("minimumDegree"));
        minimumDegree->setGeometry(QRect(150, 90, 151, 31));
        minimumDegree->setMinimum(1);
        minimumDegree->setMaximum(999);
        minimumDegree->setValue(2);
        maximumDegree = new QSpinBox(centralWidget);
        maximumDegree->setObjectName(QString::fromUtf8("maximumDegree"));
        maximumDegree->setGeometry(QRect(350, 90, 161, 31));
        maximumDegree->setMinimum(1);
        maximumDegree->setMaximum(999);
        maximumDegree->setValue(2);
        distance = new QSpinBox(centralWidget);
        distance->setObjectName(QString::fromUtf8("distance"));
        distance->setGeometry(QRect(560, 90, 141, 31));
        area = new QSpinBox(centralWidget);
        area->setObjectName(QString::fromUtf8("area"));
        area->setGeometry(QRect(40, 220, 71, 31));
        area->setMinimum(6);
        area->setMaximum(100000);
        area->setValue(10);
        numberOfRegions = new QSpinBox(centralWidget);
        numberOfRegions->setObjectName(QString::fromUtf8("numberOfRegions"));
        numberOfRegions->setGeometry(QRect(40, 390, 151, 31));
        numberOfRegions->setMinimum(1);
        numberOfRegions->setMaximum(99999);
        length = new QSpinBox(centralWidget);
        length->setObjectName(QString::fromUtf8("length"));
        length->setGeometry(QRect(230, 390, 81, 31));
        length->setMinimum(1);
        length->setMaximum(99999);
        length->setValue(2);
        breadth = new QSpinBox(centralWidget);
        breadth->setObjectName(QString::fromUtf8("breadth"));
        breadth->setGeometry(QRect(370, 390, 81, 31));
        breadth->setMinimum(1);
        breadth->setMaximum(99999);
        breadth->setValue(5);
        fixedRegions = new QRadioButton(centralWidget);
        fixedRegions->setObjectName(QString::fromUtf8("fixedRegions"));
        fixedRegions->setGeometry(QRect(40, 320, 141, 26));
        fixedRegions->setChecked(true);
        fexibleRegions = new QRadioButton(centralWidget);
        fexibleRegions->setObjectName(QString::fromUtf8("fexibleRegions"));
        fexibleRegions->setGeometry(QRect(210, 320, 161, 26));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(570, 220, 121, 31));
        measures = new QCheckBox(centralWidget);
        measures->setObjectName(QString::fromUtf8("measures"));
        measures->setGeometry(QRect(30, 450, 251, 26));
        bc = new QCheckBox(centralWidget);
        bc->setObjectName(QString::fromUtf8("bc"));
        bc->setGeometry(QRect(30, 490, 181, 26));
        dc = new QCheckBox(centralWidget);
        dc->setObjectName(QString::fromUtf8("dc"));
        dc->setGeometry(QRect(30, 520, 171, 26));
        ec = new QCheckBox(centralWidget);
        ec->setObjectName(QString::fromUtf8("ec"));
        ec->setGeometry(QRect(300, 490, 161, 21));
        cc = new QCheckBox(centralWidget);
        cc->setObjectName(QString::fromUtf8("cc"));
        cc->setGeometry(QRect(300, 530, 161, 26));
        numberOfSimulations = new QSpinBox(centralWidget);
        numberOfSimulations->setObjectName(QString::fromUtf8("numberOfSimulations"));
        numberOfSimulations->setGeometry(QRect(500, 390, 181, 31));
        numberOfSimulations->setMinimum(1);
        numberOfSimulations->setMaximum(99999);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 60, 67, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 60, 151, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(350, 60, 171, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(560, 60, 141, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(500, 360, 181, 21));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(230, 360, 67, 21));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(370, 360, 67, 21));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(40, 360, 161, 21));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(40, 190, 81, 21));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(570, 190, 131, 21));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(40, 20, 91, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_13->setFont(font);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 140, 67, 21));
        label_14->setFont(font);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(180, 160, 301, 101));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border:1px solid #d0d0d0;\n"
"\n"
"}"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 30, 71, 21));
        alpha = new QDoubleSpinBox(groupBox);
        alpha->setObjectName(QString::fromUtf8("alpha"));
        alpha->setGeometry(QRect(40, 60, 71, 31));
        alpha->setMinimum(0.01);
        alpha->setMaximum(1);
        alpha->setSingleStep(0.1);
        alpha->setValue(0.5);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 30, 67, 21));
        beta = new QDoubleSpinBox(groupBox);
        beta->setObjectName(QString::fromUtf8("beta"));
        beta->setGeometry(QRect(180, 60, 61, 31));
        beta->setMinimum(0.1);
        beta->setMaximum(1);
        beta->setSingleStep(0.05);
        beta->setValue(0.8);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(40, 280, 67, 21));
        label_15->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        fexibleRegions->raise();
        groupBox->raise();
        pushButton->raise();
        nodes->raise();
        minimumDegree->raise();
        maximumDegree->raise();
        distance->raise();
        area->raise();
        numberOfRegions->raise();
        length->raise();
        breadth->raise();
        fixedRegions->raise();
        comboBox->raise();
        measures->raise();
        bc->raise();
        dc->raise();
        ec->raise();
        cc->raise();
        numberOfSimulations->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_8->raise();
        label_9->raise();
        label_10->raise();
        label_11->raise();
        label_12->raise();
        label_13->raise();
        label_14->raise();
        label_15->raise();
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(beta, alpha);
        QWidget::setTabOrder(alpha, pushButton);
        QWidget::setTabOrder(pushButton, minimumDegree);
        QWidget::setTabOrder(minimumDegree, nodes);
        QWidget::setTabOrder(nodes, maximumDegree);
        QWidget::setTabOrder(maximumDegree, distance);
        QWidget::setTabOrder(distance, area);
        QWidget::setTabOrder(area, numberOfRegions);
        QWidget::setTabOrder(numberOfRegions, length);
        QWidget::setTabOrder(length, breadth);
        QWidget::setTabOrder(breadth, fixedRegions);
        QWidget::setTabOrder(fixedRegions, fexibleRegions);
        QWidget::setTabOrder(fexibleRegions, comboBox);
        QWidget::setTabOrder(comboBox, measures);
        QWidget::setTabOrder(measures, bc);
        QWidget::setTabOrder(bc, dc);
        QWidget::setTabOrder(dc, ec);
        QWidget::setTabOrder(ec, cc);
        QWidget::setTabOrder(cc, numberOfSimulations);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Network Topologies Generator", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Begin Simulation", 0, QApplication::UnicodeUTF8));
        fixedRegions->setText(QApplication::translate("MainWindow", "Fixed regions", 0, QApplication::UnicodeUTF8));
        fexibleRegions->setText(QApplication::translate("MainWindow", "Flexible regions", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Uniform", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Random", 0, QApplication::UnicodeUTF8)
        );
        measures->setText(QApplication::translate("MainWindow", "Do you want to enable Measures?", 0, QApplication::UnicodeUTF8));
        bc->setText(QApplication::translate("MainWindow", "Betwenness Centrality", 0, QApplication::UnicodeUTF8));
        dc->setText(QApplication::translate("MainWindow", "Degree Centrality", 0, QApplication::UnicodeUTF8));
        ec->setText(QApplication::translate("MainWindow", "Efficiency Centrality", 0, QApplication::UnicodeUTF8));
        cc->setText(QApplication::translate("MainWindow", "Closeness Centrality", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Nodes (N)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Minimum degree \342\214\251\316\264\342\214\252min", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Maximum degree \342\214\251\316\264\342\214\252max", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Minimum distance ( \316\271 )", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Number of Simulations ( \317\206 )", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Length", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Breadth", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Number of Regions ( R )", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Area ( \342\210\232A )", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Nodes distribution", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Network", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Plane", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", " Waxman", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Alpha ( \316\261 )", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", " Beta ( \316\262 )", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Region", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
