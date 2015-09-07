/********************************************************************************
** Form generated from reading UI file 'frmmessagebox.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMESSAGEBOX_H
#define UI_FRMMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMessageBox
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lab_Ico;
    QLabel *lab_Title;
    QWidget *widget_menu;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnMenu_Close;
    QWidget *widget_main;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *labIcoMain;
    QLabel *labInfo;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *frmMessageBox)
    {
        if (frmMessageBox->objectName().isEmpty())
            frmMessageBox->setObjectName(QStringLiteral("frmMessageBox"));
        frmMessageBox->resize(303, 143);
        verticalLayout = new QVBoxLayout(frmMessageBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        widget_title = new QWidget(frmMessageBox);
        widget_title->setObjectName(QStringLiteral("widget_title"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_title->sizePolicy().hasHeightForWidth());
        widget_title->setSizePolicy(sizePolicy);
        widget_title->setMinimumSize(QSize(100, 28));
        horizontalLayout_2 = new QHBoxLayout(widget_title);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lab_Ico = new QLabel(widget_title);
        lab_Ico->setObjectName(QStringLiteral("lab_Ico"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lab_Ico->sizePolicy().hasHeightForWidth());
        lab_Ico->setSizePolicy(sizePolicy1);
        lab_Ico->setMinimumSize(QSize(31, 0));
        lab_Ico->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lab_Ico);

        lab_Title = new QLabel(widget_title);
        lab_Title->setObjectName(QStringLiteral("lab_Title"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lab_Title->sizePolicy().hasHeightForWidth());
        lab_Title->setSizePolicy(sizePolicy2);
        lab_Title->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lab_Title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lab_Title);

        widget_menu = new QWidget(widget_title);
        widget_menu->setObjectName(QStringLiteral("widget_menu"));
        sizePolicy1.setHeightForWidth(widget_menu->sizePolicy().hasHeightForWidth());
        widget_menu->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(widget_menu);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnMenu_Close = new QPushButton(widget_menu);
        btnMenu_Close->setObjectName(QStringLiteral("btnMenu_Close"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy3);
        btnMenu_Close->setMinimumSize(QSize(40, 0));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);
        btnMenu_Close->setFlat(true);

        horizontalLayout->addWidget(btnMenu_Close);


        horizontalLayout_2->addWidget(widget_menu);


        verticalLayout->addWidget(widget_title);

        widget_main = new QWidget(frmMessageBox);
        widget_main->setObjectName(QStringLiteral("widget_main"));
        widget_main->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        verticalLayout_2 = new QVBoxLayout(widget_main);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        groupBox = new QGroupBox(widget_main);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        labIcoMain = new QLabel(groupBox);
        labIcoMain->setObjectName(QStringLiteral("labIcoMain"));
        labIcoMain->setGeometry(QRect(10, 10, 45, 45));
        labIcoMain->setStyleSheet(QStringLiteral("border-image: url(:/image/info.png);"));
        labInfo = new QLabel(groupBox);
        labInfo->setObjectName(QStringLiteral("labInfo"));
        labInfo->setGeometry(QRect(70, 10, 211, 41));
        labInfo->setScaledContents(false);
        labInfo->setWordWrap(true);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 271, 34));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnOk = new QPushButton(layoutWidget);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        btnOk->setCursor(QCursor(Qt::PointingHandCursor));
        btnOk->setFocusPolicy(Qt::StrongFocus);
        btnOk->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/update.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon);
        btnOk->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(btnOk);

        btnCancel = new QPushButton(layoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setCursor(QCursor(Qt::PointingHandCursor));
        btnCancel->setFocusPolicy(Qt::StrongFocus);
        btnCancel->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon1);
        btnCancel->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(btnCancel);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout->addWidget(widget_main);


        retranslateUi(frmMessageBox);

        QMetaObject::connectSlotsByName(frmMessageBox);
    } // setupUi

    void retranslateUi(QDialog *frmMessageBox)
    {
        frmMessageBox->setWindowTitle(QApplication::translate("frmMessageBox", "\346\217\220\347\244\272", 0));
        lab_Ico->setText(QString());
        lab_Title->setText(QApplication::translate("frmMessageBox", "\346\217\220\347\244\272", 0));
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("frmMessageBox", "\345\205\263\351\227\255", 0));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        groupBox->setTitle(QString());
        labIcoMain->setText(QString());
        labInfo->setText(QApplication::translate("frmMessageBox", "\347\241\256\345\256\232\350\246\201\345\210\240\351\231\244\345\220\227?", 0));
        btnOk->setText(QApplication::translate("frmMessageBox", "\347\241\256\345\256\232(&O)", 0));
        btnCancel->setText(QApplication::translate("frmMessageBox", "\345\217\226\346\266\210(&C)", 0));
    } // retranslateUi

};

namespace Ui {
    class frmMessageBox: public Ui_frmMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMESSAGEBOX_H
