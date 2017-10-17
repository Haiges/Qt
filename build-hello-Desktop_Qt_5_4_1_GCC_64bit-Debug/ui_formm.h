/********************************************************************************
** Form generated from reading UI file 'formm.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMM_H
#define UI_FORMM_H

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

class Ui_Formm
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *OkButton;
    QPushButton *CancelButton;

    void setupUi(QWidget *Formm)
    {
        if (Formm->objectName().isEmpty())
            Formm->setObjectName(QStringLiteral("Formm"));
        Formm->resize(400, 300);
        layoutWidget = new QWidget(Formm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 50, 296, 75));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        OkButton = new QPushButton(layoutWidget);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        horizontalLayout_2->addWidget(OkButton);

        CancelButton = new QPushButton(layoutWidget);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        horizontalLayout_2->addWidget(CancelButton);


        verticalLayout->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Formm);

        QMetaObject::connectSlotsByName(Formm);
    } // setupUi

    void retranslateUi(QWidget *Formm)
    {
        Formm->setWindowTitle(QApplication::translate("Formm", "Form", 0));
        label->setText(QApplication::translate("Formm", "&Cell Localtion", 0));
        OkButton->setText(QApplication::translate("Formm", "Ok", 0));
        CancelButton->setText(QApplication::translate("Formm", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class Formm: public Ui_Formm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMM_H
