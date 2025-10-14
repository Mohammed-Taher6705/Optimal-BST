#include "OBSTWidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMessageBox>

OBSTWidget::OBSTWidget(QWidget* parent) : QWidget(parent), tree(nullptr) {}

OBSTWidget::~OBSTWidget() {}

void OBSTWidget::setBST(BST* tree) {
    this->tree = tree;
    update();  // Trigger a repaint
}

void OBSTWidget::paintEvent(QPaintEvent* event) {
    if (tree != nullptr) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::lightGray));

        // Start drawing from the root node, at a fixed starting position
        drawNode(painter, tree->getRoot(), width() / 2, 50, 1);
    }
}

void OBSTWidget::drawNode(QPainter& painter, BSTNode* node, int x, int y, int level) {
    if (node == nullptr) return;

    // Draw the node (circle with the key inside)
    painter.drawEllipse(x - 20, y - 20, 40, 40);
    painter.drawText(x - 10, y + 5, QString::number(node->key));

    // Calculate horizontal offset for child nodes
    int baseOffset = 300; // Base offset between nodes
    int offset = baseOffset / (level + 1); // Reduce offset as level increases

    // Draw the left and right branches (if any)
    if (node->left != nullptr) {
        painter.drawLine(x, y, x - offset, y + 60); // Line to the left child
        drawNode(painter, node->left, x - offset, y + 60, level + 1);
    }
    if (node->right != nullptr) {
        painter.drawLine(x, y, x + offset, y + 60); // Line to the right child
        drawNode(painter, node->right, x + offset, y + 60, level + 1);
    }
}

int OBSTWidget::calculateOBSTCost(BSTNode* node, int level) {
    if (node == nullptr)
        return 0;

    // Calculate the cost by multiplying frequency by level
    int cost = node->frequency * level;  // Multiply by frequency

    // Recursively calculate the cost for left and right subtrees
    cost += calculateOBSTCost(node->left, level + 1);
    cost += calculateOBSTCost(node->right, level + 1);

    return cost;
}
