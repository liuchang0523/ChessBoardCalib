/********************************************************************************
** Form generated from reading UI file 'stereo_calib.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEREO_CALIB_H
#define UI_STEREO_CALIB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_stereo_calibClass
{
public:
    QAction *actionCalib;
    QAction *actionStereo;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QCustomPlot *customPlot;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *stereo_calibClass)
    {
        if (stereo_calibClass->objectName().isEmpty())
            stereo_calibClass->setObjectName(QStringLiteral("stereo_calibClass"));
        stereo_calibClass->resize(1045, 743);
        stereo_calibClass->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        actionCalib = new QAction(stereo_calibClass);
        actionCalib->setObjectName(QStringLiteral("actionCalib"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/stereo_calib/Resources/color_thresholder_load_camera_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalib->setIcon(icon);
        actionStereo = new QAction(stereo_calibClass);
        actionStereo->setObjectName(QStringLiteral("actionStereo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/stereo_calib/Resources/camera_calibrator_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStereo->setIcon(icon1);
        centralWidget = new QWidget(stereo_calibClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        gridLayout->addWidget(customPlot, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 6);
        gridLayout->setRowStretch(1, 1);
        stereo_calibClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(stereo_calibClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        stereo_calibClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actionCalib);
        mainToolBar->addAction(actionStereo);

        retranslateUi(stereo_calibClass);

        QMetaObject::connectSlotsByName(stereo_calibClass);
    } // setupUi

    void retranslateUi(QMainWindow *stereo_calibClass)
    {
        stereo_calibClass->setWindowTitle(QApplication::translate("stereo_calibClass", "stereo_calib", Q_NULLPTR));
        actionCalib->setText(QApplication::translate("stereo_calibClass", "Calib", Q_NULLPTR));
        actionStereo->setText(QApplication::translate("stereo_calibClass", "Stereo", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class stereo_calibClass: public Ui_stereo_calibClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEREO_CALIB_H
