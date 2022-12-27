/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Sep 10 10:42:38 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrir;
    QAction *actionSave_Tour;
    QAction *actionExit;
    QAction *actionAcerca_de;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QComboBox *comboBox_7;
    QComboBox *comboBox_8;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_7;
    QSpinBox *spinBox_8;
    QLineEdit *lE_Before;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lE_After;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *pB_Draw;
    QSpinBox *sB_Total;
    QPushButton *pB_VNS;
    QSpinBox *sB_PopSize;
    QLabel *label_14;
    QLineEdit *lE_Instance;
    QLabel *label_15;
    QMenuBar *menuBar;
    QMenu *menuArchivo;
    QMenu *menuAyuda;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(600, 400));
        MainWindow->setMaximumSize(QSize(600, 400));
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName(QString::fromUtf8("actionAbrir"));
        actionAbrir->setIconVisibleInMenu(false);
        actionSave_Tour = new QAction(MainWindow);
        actionSave_Tour->setObjectName(QString::fromUtf8("actionSave_Tour"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAcerca_de = new QAction(MainWindow);
        actionAcerca_de->setObjectName(QString::fromUtf8("actionAcerca_de"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 230, 121, 27));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 20, 131, 27));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(30, 60, 131, 27));
        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(30, 100, 131, 27));
        comboBox_4 = new QComboBox(centralWidget);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(30, 140, 131, 27));
        comboBox_5 = new QComboBox(centralWidget);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(30, 180, 131, 27));
        comboBox_6 = new QComboBox(centralWidget);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(30, 220, 131, 27));
        comboBox_7 = new QComboBox(centralWidget);
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));
        comboBox_7->setGeometry(QRect(30, 260, 131, 27));
        comboBox_8 = new QComboBox(centralWidget);
        comboBox_8->setObjectName(QString::fromUtf8("comboBox_8"));
        comboBox_8->setGeometry(QRect(30, 300, 131, 27));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(190, 20, 71, 27));
        spinBox->setMaximum(9999);
        spinBox->setValue(0);
        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(190, 60, 71, 27));
        spinBox_2->setMaximum(9999);
        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(190, 100, 71, 27));
        spinBox_3->setMaximum(9999);
        spinBox_4 = new QSpinBox(centralWidget);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(190, 140, 71, 27));
        spinBox_4->setMaximum(9999);
        spinBox_5 = new QSpinBox(centralWidget);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setGeometry(QRect(190, 180, 71, 27));
        spinBox_5->setMaximum(9999);
        spinBox_6 = new QSpinBox(centralWidget);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));
        spinBox_6->setGeometry(QRect(190, 220, 71, 27));
        spinBox_6->setMaximum(9999);
        spinBox_7 = new QSpinBox(centralWidget);
        spinBox_7->setObjectName(QString::fromUtf8("spinBox_7"));
        spinBox_7->setGeometry(QRect(190, 260, 71, 27));
        spinBox_7->setMaximum(9999);
        spinBox_8 = new QSpinBox(centralWidget);
        spinBox_8->setObjectName(QString::fromUtf8("spinBox_8"));
        spinBox_8->setGeometry(QRect(190, 300, 71, 27));
        spinBox_8->setMaximum(9999);
        lE_Before = new QLineEdit(centralWidget);
        lE_Before->setObjectName(QString::fromUtf8("lE_Before"));
        lE_Before->setGeometry(QRect(380, 180, 113, 27));
        lE_Before->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 0, 67, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 0, 67, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 21, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 60, 21, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 16, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 140, 21, 17));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 180, 16, 17));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 220, 21, 17));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 260, 21, 17));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 300, 16, 17));
        lE_After = new QLineEdit(centralWidget);
        lE_After->setObjectName(QString::fromUtf8("lE_After"));
        lE_After->setGeometry(QRect(380, 300, 113, 27));
        lE_After->setReadOnly(true);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(390, 160, 101, 17));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(390, 280, 91, 20));
        pB_Draw = new QPushButton(centralWidget);
        pB_Draw->setObjectName(QString::fromUtf8("pB_Draw"));
        pB_Draw->setGeometry(QRect(497, 20, 91, 27));
        sB_Total = new QSpinBox(centralWidget);
        sB_Total->setObjectName(QString::fromUtf8("sB_Total"));
        sB_Total->setGeometry(QRect(420, 230, 61, 27));
        sB_Total->setMinimum(1);
        sB_Total->setValue(1);
        pB_VNS = new QPushButton(centralWidget);
        pB_VNS->setObjectName(QString::fromUtf8("pB_VNS"));
        pB_VNS->setGeometry(QRect(490, 230, 98, 27));
        sB_PopSize = new QSpinBox(centralWidget);
        sB_PopSize->setObjectName(QString::fromUtf8("sB_PopSize"));
        sB_PopSize->setGeometry(QRect(410, 120, 59, 27));
        sB_PopSize->setMinimum(1);
        sB_PopSize->setValue(10);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(390, 100, 111, 17));
        lE_Instance = new QLineEdit(centralWidget);
        lE_Instance->setObjectName(QString::fromUtf8("lE_Instance"));
        lE_Instance->setGeometry(QRect(372, 20, 121, 27));
        lE_Instance->setReadOnly(true);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(400, 0, 67, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menuArchivo = new QMenu(menuBar);
        menuArchivo->setObjectName(QString::fromUtf8("menuArchivo"));
        menuAyuda = new QMenu(menuBar);
        menuAyuda->setObjectName(QString::fromUtf8("menuAyuda"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArchivo->menuAction());
        menuBar->addAction(menuAyuda->menuAction());
        menuArchivo->addAction(actionAbrir);
        menuArchivo->addAction(actionSave_Tour);
        menuArchivo->addAction(actionExit);
        menuAyuda->addAction(actionAcerca_de);

        retranslateUi(MainWindow);
        QObject::connect(actionAbrir, SIGNAL(triggered()), MainWindow, SLOT(update()));

        comboBox_8->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VNS Prober", 0, QApplication::UnicodeUTF8));
        actionAbrir->setText(QApplication::translate("MainWindow", "Open...", 0, QApplication::UnicodeUTF8));
        actionSave_Tour->setText(QApplication::translate("MainWindow", "Save Tour", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionAcerca_de->setText(QApplication::translate("MainWindow", "About...", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Apply Heuristics", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Heuristics", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Iterations", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Lenght before", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Lenght after", 0, QApplication::UnicodeUTF8));
        pB_Draw->setText(QApplication::translate("MainWindow", "Draw", 0, QApplication::UnicodeUTF8));
        pB_VNS->setText(QApplication::translate("MainWindow", "Apply VNS", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Population size", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Instance", 0, QApplication::UnicodeUTF8));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuAyuda->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
