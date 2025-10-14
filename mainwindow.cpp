#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QListWidget>
#include <QPair>
#include <QSortFilterProxyModel>
#include <QInputDialog>  // Include for QInputDialog

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), obstWidget(new OBSTWidget(this)), tree(new BST()) {
    // Set up the main window layout
    QVBoxLayout* layout = new QVBoxLayout;

    // Create input fields for numbers and frequencies
    QFormLayout* inputLayout = new QFormLayout;

    // Input for numbers and frequencies
    QLabel* numbersLabel = new QLabel("Enter Numbers and Frequencies:");
    numberEdit = new QLineEdit(this);
    frequencyEdit = new QLineEdit(this);

    // Add input fields for numbers and frequencies
    inputLayout->addRow("Number:", numberEdit);
    inputLayout->addRow("Frequency:", frequencyEdit);

    layout->addWidget(numbersLabel);
    layout->addLayout(inputLayout);

    // Add a button to insert the values into the BST
    QPushButton* insertButton = new QPushButton("Insert and Sort by Frequency", this);
    layout->addWidget(insertButton);

    // Add the widget to display the tree
    layout->addWidget(obstWidget, 1);  // This line is modified to make the tree widget resizable

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Connect the button to handle insertion
    connect(insertButton, &QPushButton::clicked, this, &MainWindow::createTreeFromInput);

    // Add a button to display the OBST cost
    QPushButton* obstCostButton = new QPushButton("Display OBST Cost", this);
    layout->addWidget(obstCostButton);
    connect(obstCostButton, &QPushButton::clicked, this, &MainWindow::displayOBSTCost);

    // Add buttons for updating frequency, adding, and deleting nodes
    QPushButton* updateFrequencyButton = new QPushButton("Update Frequency", this);
    QPushButton* addNodeButton = new QPushButton("Add Node", this);
    QPushButton* deleteNodeButton = new QPushButton("Delete Node", this);

    // Connect buttons to respective slots
    connect(updateFrequencyButton, &QPushButton::clicked, this, &MainWindow::updateFrequency);
    connect(addNodeButton, &QPushButton::clicked, this, &MainWindow::addNode);
    connect(deleteNodeButton, &QPushButton::clicked, this, &MainWindow::deleteNode);

    // Add buttons to the layout
    layout->addWidget(updateFrequencyButton);
    layout->addWidget(addNodeButton);
    layout->addWidget(deleteNodeButton);

    // Set the BST for the widget to draw
    obstWidget->setBST(tree);
}

MainWindow::~MainWindow() {
    delete tree;
}

void MainWindow::createTreeFromInput() {
    // Clear the current tree
    delete tree;
    tree = new BST();

    // Retrieve user input from QLineEdit widgets
    QString numbersText = numberEdit->text();
    QString frequenciesText = frequencyEdit->text();

    // Split the input text into lists (assuming space-separated)
    QStringList numbersList = numbersText.split(" ");
    QStringList frequenciesList = frequenciesText.split(" ");

    if (numbersList.size() != frequenciesList.size()) {
        QMessageBox::warning(this, "Input Error", "Numbers and Frequencies must have the same count!");
        return;
    }

    // Clear the previous pairs (in case the function is called multiple times)
    numberFrequencyPairs.clear();

    // Check each frequency and number entered by the user
    for (int i = 0; i < frequenciesList.size(); ++i) {
        bool okFrequency;
        int frequency = frequenciesList[i].toInt(&okFrequency);

        // Check if the frequency is a valid positive integer
        if (!okFrequency || frequency <= 0) {
            QMessageBox::warning(this, "Input Error", "Invalid frequency entered for number: " + numbersList[i]);
            return; // Return early to prevent further processing
        }
    }

    // Populate the list of pairs (number, frequency)
    for (int i = 0; i < numbersList.size(); ++i) {
        bool okNumber, okFrequency;
        int number = numbersList[i].toInt(&okNumber);
        int frequency = frequenciesList[i].toInt(&okFrequency);

        if (okNumber && okFrequency) {
            numberFrequencyPairs.append(qMakePair(number, frequency));
        } else {
            QMessageBox::warning(this, "Input Error", "Please enter valid numbers and frequencies.");
            return;
        }
    }

    // Sort the list based on frequency in descending order
    std::sort(numberFrequencyPairs.begin(), numberFrequencyPairs.end(),
              [](const QPair<int, int>& a, const QPair<int, int>& b) {
                  return a.second > b.second;  // Sort by frequency in descending order
              });

    // Insert the sorted numbers into the BST based on frequency
    for (const QPair<int, int>& pair : numberFrequencyPairs) {
        tree->insert(pair.first, pair.second);  // Insert the number 'frequency' times
    }

    // Set a larger size for the OBSTWidget (tree display area)
    obstWidget->setMinimumSize(600, 400);  // Adjust the size as needed

    // Update the widget to redraw the tree
    obstWidget->setBST(tree);
}


void MainWindow::updateFrequency() {
    QString nodeKey = QInputDialog::getText(this, "Update Frequency", "Enter Node Key:");
    QString newFrequency = QInputDialog::getText(this, "Update Frequency", "Enter New Frequency:");

    bool okKey, okFreq;
    int key = nodeKey.toInt(&okKey);
    int freq = newFrequency.toInt(&okFreq);

    if (okKey && okFreq) {
        delete tree;
        tree = new BST();

        // Update the frequency of the node and rebuild the tree
        for (auto& pair : numberFrequencyPairs) {
            if (pair.first == key) {
                pair.second = freq;
            }
        }

        // Reinsert sorted numbers into the BST
        std::sort(numberFrequencyPairs.begin(), numberFrequencyPairs.end(),
                  [](const QPair<int, int>& a, const QPair<int, int>& b) {
                      return a.second > b.second;
                  });

        for (const auto& pair : numberFrequencyPairs) {
            for (int i = 0; i < pair.second; ++i) {
                tree->insert(pair.first);
            }
        }

        obstWidget->setBST(tree);
    } else {
        QMessageBox::warning(this, "Input Error", "Invalid input for key or frequency.");
    }
}

void MainWindow::addNode() {
    QString nodeKey = QInputDialog::getText(this, "Add Node", "Enter Node Key:");

    bool ok;
    int key = nodeKey.toInt(&ok);

    if (ok) {
        // Prompt the user for the frequency of the new node
        QString frequencyText = QInputDialog::getText(this, "Enter Frequency", "Enter the frequency for the node:");

        bool okFrequency;
        int frequency = frequencyText.toInt(&okFrequency);

        if (okFrequency && frequency > 0) {
            // Add the node's frequency to the pair list
            bool nodeFound = false;
            for (auto& pair : numberFrequencyPairs) {
                if (pair.first == key) {
                    pair.second += frequency;  // If the node exists, update the frequency
                    nodeFound = true;
                    break;
                }
            }

            if (!nodeFound) {
                // If the node does not exist, add a new pair
                numberFrequencyPairs.append(qMakePair(key, frequency));
            }

            // Clear and rebuild the tree based on updated frequencies
            delete tree;
            tree = new BST();

            // Sort the list based on frequency in descending order
            std::sort(numberFrequencyPairs.begin(), numberFrequencyPairs.end(),
                      [](const QPair<int, int>& a, const QPair<int, int>& b) {
                          return a.second > b.second;  // Sort by frequency in descending order
                      });

            // Insert the node with the highest frequency first (as root)
            const QPair<int, int>& highestFreqPair = numberFrequencyPairs.first();
            tree->insert(highestFreqPair.first, highestFreqPair.second);

            // Insert the remaining nodes
            for (int i = 1; i < numberFrequencyPairs.size(); ++i) {
                const QPair<int, int>& pair = numberFrequencyPairs[i];
                for (int j = 0; j < pair.second; ++j) {
                    tree->insert(pair.first);  // Insert the number 'frequency' times
                }
            }

            // Update the widget to redraw the tree
            obstWidget->setBST(tree);
        } else {
            QMessageBox::warning(this, "Input Error", "Please enter a valid frequency.");
        }
    } else {
        QMessageBox::warning(this, "Input Error", "Invalid input for key.");
    }
}

void MainWindow::deleteNode() {
    // Get the node key to delete
    QString nodeKey = QInputDialog::getText(this, "Delete Node", "Enter Node Key:");

    bool ok;
    int key = nodeKey.toInt(&ok);

    if (ok) {
        // 1. Remove the node from the tree
        tree->remove(key);

        // 2. Remove the node from the frequency list
        for (int i = 0; i < numberFrequencyPairs.size(); ++i) {
            if (numberFrequencyPairs[i].first == key) {
                numberFrequencyPairs.removeAt(i);
                break;
            }
        }

        // 3. Re-sort the frequency list based on frequency in descending order
        std::sort(numberFrequencyPairs.begin(), numberFrequencyPairs.end(),
                  [](const QPair<int, int>& a, const QPair<int, int>& b) {
                      return a.second > b.second;  // Sort by frequency in descending order
                  });

        // 4. Rebuild the tree based on the sorted frequency list
        delete tree;  // Delete the old tree
        tree = new BST();  // Create a new tree

        // Insert the numbers into the tree based on the sorted frequency list
        for (const QPair<int, int>& pair : numberFrequencyPairs) {
            for (int i = 0; i < pair.second; ++i) {
                tree->insert(pair.first);  // Insert the number 'frequency' times
            }
        }

        // 5. Update the visualization (obstWidget) to reflect the new tree
        obstWidget->setBST(tree);

    } else {
        QMessageBox::warning(this, "Input Error", "Invalid input for key.");
    }
}

void MainWindow::displayOBSTCost() {
    int cost = obstWidget->calculateOBSTCost(tree->getRoot(), 1);
    QMessageBox::information(this, "OBST Cost", "The OBST cost is: " + QString::number(cost));
}
