/********************************************************************************
** Form generated from reading UI file 'start_page.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_PAGE_H
#define UI_START_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start_page
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox_row;
    QLabel *label_2;
    QSpinBox *spinBox_col;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_show;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QPushButton *pushButton_save;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *start_page)
    {
        if (start_page->objectName().isEmpty())
            start_page->setObjectName(QStringLiteral("start_page"));
        start_page->resize(622, 491);
        verticalLayout = new QVBoxLayout(start_page);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(start_page);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        spinBox_row = new QSpinBox(start_page);
        spinBox_row->setObjectName(QStringLiteral("spinBox_row"));
        spinBox_row->setMinimum(5);
        spinBox_row->setMaximum(12);
        spinBox_row->setValue(9);

        horizontalLayout->addWidget(spinBox_row);

        label_2 = new QLabel(start_page);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_2);

        spinBox_col = new QSpinBox(start_page);
        spinBox_col->setObjectName(QStringLiteral("spinBox_col"));
        spinBox_col->setMinimum(5);
        spinBox_col->setMaximum(12);
        spinBox_col->setValue(12);

        horizontalLayout->addWidget(spinBox_col);


        horizontalLayout_2->addLayout(horizontalLayout);

        label_3 = new QLabel(start_page);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        doubleSpinBox = new QDoubleSpinBox(start_page);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setValue(25);

        horizontalLayout_2->addWidget(doubleSpinBox);

        label_4 = new QLabel(start_page);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        label_show = new QLabel(start_page);
        label_show->setObjectName(QStringLiteral("label_show"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_show->sizePolicy().hasHeightForWidth());
        label_show->setSizePolicy(sizePolicy1);
        label_show->setMinimumSize(QSize(604, 402));
        label_show->setScaledContents(false);
        label_show->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_show);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(start_page);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        pushButton_save = new QPushButton(start_page);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        horizontalLayout_3->addWidget(pushButton_save);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(start_page);

        QMetaObject::connectSlotsByName(start_page);
    } // setupUi

    void retranslateUi(QWidget *start_page)
    {
        start_page->setWindowTitle(QApplication::translate("start_page", "\347\241\256\350\256\244\346\243\213\347\233\230\346\240\274\345\260\272\345\257\270", Q_NULLPTR));
        label->setText(QApplication::translate("start_page", "\350\241\214\350\247\222\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("start_page", "\345\210\227\350\247\222\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("start_page", "\351\227\264\351\232\224\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("start_page", "mm", Q_NULLPTR));
        label_show->setText(QString());
        pushButton->setText(QApplication::translate("start_page", "\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("start_page", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class start_page: public Ui_start_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_PAGE_H
