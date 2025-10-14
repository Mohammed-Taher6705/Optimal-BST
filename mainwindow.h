#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "OBSTWidget.h"
#include "BST.h"
#include <QLineEdit>

class MainWindow: public QMainWindow
{

    Q_OBJECT;



public:
    explicit MainWindow(QWidget* parent =nullptr);
    ~MainWindow();

private slots :
    void createTreeFromInput();
    void updateFrequency();
    void addNode();
    void deleteNode();

    void displayOBSTCost();

private:
    OBSTWidget* obstWidget;
    BST* tree;
    QLineEdit * numberEdit;

    QLineEdit* frequencyEdit;
    QList<QPair<int , int>> numberFrequencyPairs;


};

#endif // MAINWINDOW_H
