#ifndef OBSTWIDGET_H
#define OBSTWIDGET_H

#include <QWidget>
#include "BST.h"

class OBSTWidget : public QWidget {
    Q_OBJECT

public:
    explicit OBSTWidget(QWidget* parent = nullptr);
    ~OBSTWidget();

    void setBST(BST* tree);  // Set the tree to be drawn
    int calculateOBSTCost(BSTNode* node, int level);  // Calculate OBST cost by multiplying frequency by level

protected:
    void paintEvent(QPaintEvent* event) override;  // Override paintEvent to draw the tree

private:
    void drawNode(QPainter& painter, BSTNode* node, int x, int y, int level);

    BST* tree;  // The tree to be drawn
};

#endif // OBSTWIDGET_H
