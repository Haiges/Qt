/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GotoCellDia
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *OkButton;
    QPushButton *CancelButton;

    void setupUi(QWidget *GotoCellDia)
    {
        if (GotoCellDia->objectName().isEmpty())
            GotoCellDia->setObjectName(QStringLiteral("GotoCellDia"));
        GotoCellDia->resize(400, 300);
        GotoCellDia->setMinimumSize(QSize(400, 300));
        widget = new QWidget(GotoCellDia);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 150, 296, 75));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        OkButton = new QPushButton(widget);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        horizontalLayout_2->addWidget(OkButton);

        CancelButton = new QPushButton(widget);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        horizontalLayout_2->addWidget(CancelButton);


        verticalLayout->addLayout(horizontalLayout_2);

        QWidget::setTabOrder(lineEdit, OkButton);
        QWidget::setTabOrder(OkButton, CancelButton);

        retranslateUi(GotoCellDia);

        QMetaObject::connectSlotsByName(GotoCellDia);
    } // setupUi

    void retranslateUi(QWidget *GotoCellDia)
    {
        GotoCellDia->setWindowTitle(QApplication::translate("GotoCellDia", "GotocellDia", 0));
        label->setText(QApplication::translate("GotoCellDia", "&Cell Localtion", 0));
        OkButton->setText(QApplication::translate("GotoCellDia", "Ok", 0));
        CancelButton->setText(QApplication::translate("GotoCellDia", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class GotoCellDia: public Ui_GotoCellDia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
