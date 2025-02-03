// TreeWindow.h
#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "OBSTWidget.h"  // Include the OBSTWidget for tree visualization
#include "BST.h"  // Assuming BST is the tree class

class TreeWindow : public QWidget {
    Q_OBJECT

public:
    explicit TreeWindow(BST* tree, QWidget* parent = nullptr)
        : QWidget(parent), obstWidget(new OBSTWidget(this)), tree(tree) {
        QVBoxLayout* layout = new QVBoxLayout;

        // Set the BST for the widget to draw
        obstWidget->setBST(tree);

        // Add the widget to display the tree
        layout->addWidget(obstWidget);

        setLayout(layout);
        setWindowTitle("Tree Visualization");
        resize(600, 400);  // Adjust size of the window as needed
    }

private:
    OBSTWidget* obstWidget;
    BST* tree;
};

#endif // TREEWINDOW_H
