/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *widget_2;
    QToolButton *toolButton;
    QFrame *line;
    QLabel *label;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QFrame *line_2;
    QLabel *label_30;
    QWidget *widget_4;
    QPushButton *modifier_2;
    QLineEdit *Nom_Client_2;
    QLineEdit *PRENOM_Client_2;
    QLineEdit *NUMC_Client_2;
    QDateTimeEdit *DATES_Client_2;
    QPushButton *pushButton_2;
    QPushButton *ajouter_2;
    QPushButton *supprimer_2;
    QComboBox *TYPE_2;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_5;
    QComboBox *comboBoxTri;
    QLabel *label_23;
    QLineEdit *CIN_Client_2;
    QLabel *label_31;
    QLabel *label_32;
    QToolButton *stat_methods;
    QToolButton *exportToPDF;
    QLabel *label_9;
    QPushButton *pushButtonRecherche;
    QLineEdit *lineEditRecherche;
    QComboBox *METHODEP_Client_2;
    QLineEdit *ADRESSE_Client_2;
    QWidget *widget_methods;
    QTableView *tableView_2;
    QPushButton *btnUploadPhoto;
    QLabel *IMAGE_Client_2;
    QComboBox *comboBoxRecherche;
    QPushButton *map_2;
    QWidget *modifier_3;
    QWidget *widget_5;
    QPushButton *modifier_4;
    QLineEdit *Nom_Clientm;
    QLineEdit *PRENOM_Clientm;
    QLineEdit *NUMC_Clientm;
    QDateTimeEdit *DATES_Clientm;
    QComboBox *TYPEm;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_33;
    QLineEdit *CIN_Clientm;
    QLabel *label_17;
    QLineEdit *ADRESSE_Clientm;
    QComboBox *METHODEP_Clientm;
    QWidget *widget_3;
    QToolButton *toolButton_6;
    QFrame *line_3;
    QLabel *label_18;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QFrame *line_4;
    QLabel *label_42;
    QWidget *map;
    QQuickWidget *quickWidget_Map_View;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1318, 823);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, -50, 1341, 761));
        page = new QWidget();
        page->setObjectName("page");
        widget_2 = new QWidget(page);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(10, 20, 231, 841));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:#092939;"));
        toolButton = new QToolButton(widget_2);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(30, 120, 91, 81));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../Images/Screenshots/Screenshot 2024-10-01 232919.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(100, 100));
        line = new QFrame(widget_2);
        line->setObjectName("line");
        line->setGeometry(QRect(40, 300, 118, 3));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 230, 161, 41));
        label->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 900 12pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label->setTextFormat(Qt::PlainText);
        label_24 = new QLabel(widget_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(40, 330, 191, 31));
        label_24->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_25 = new QLabel(widget_2);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(40, 370, 191, 20));
        label_25->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_26 = new QLabel(widget_2);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(40, 440, 181, 31));
        label_26->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_27 = new QLabel(widget_2);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(40, 400, 181, 31));
        label_27->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
""));
        label_28 = new QLabel(widget_2);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(40, 480, 181, 31));
        label_28->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
""));
        label_29 = new QLabel(widget_2);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(40, 520, 221, 31));
        label_29->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        line_2 = new QFrame(widget_2);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 470, 16, 41));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 187, 23);"));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_30 = new QLabel(widget_2);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(40, 680, 161, 41));
        label_30->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"color: rgb(76, 187, 23);\n"
"font: 900 12pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
""));
        label_30->setTextFormat(Qt::PlainText);
        widget_4 = new QWidget(page);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(190, 50, 1171, 821));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        modifier_2 = new QPushButton(widget_4);
        modifier_2->setObjectName("modifier_2");
        modifier_2->setGeometry(QRect(860, 610, 121, 41));
        modifier_2->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        Nom_Client_2 = new QLineEdit(widget_4);
        Nom_Client_2->setObjectName("Nom_Client_2");
        Nom_Client_2->setGeometry(QRect(70, 60, 231, 31));
        Nom_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        PRENOM_Client_2 = new QLineEdit(widget_4);
        PRENOM_Client_2->setObjectName("PRENOM_Client_2");
        PRENOM_Client_2->setGeometry(QRect(70, 130, 231, 31));
        PRENOM_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        NUMC_Client_2 = new QLineEdit(widget_4);
        NUMC_Client_2->setObjectName("NUMC_Client_2");
        NUMC_Client_2->setGeometry(QRect(70, 270, 231, 31));
        NUMC_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        DATES_Client_2 = new QDateTimeEdit(widget_4);
        DATES_Client_2->setObjectName("DATES_Client_2");
        DATES_Client_2->setGeometry(QRect(70, 470, 231, 31));
        DATES_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(840, 170, 101, 31));
        pushButton_2->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        ajouter_2 = new QPushButton(widget_4);
        ajouter_2->setObjectName("ajouter_2");
        ajouter_2->setGeometry(QRect(60, 660, 241, 41));
        ajouter_2->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        supprimer_2 = new QPushButton(widget_4);
        supprimer_2->setObjectName("supprimer_2");
        supprimer_2->setGeometry(QRect(1000, 610, 121, 41));
        supprimer_2->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        TYPE_2 = new QComboBox(widget_4);
        TYPE_2->addItem(QString());
        TYPE_2->addItem(QString());
        TYPE_2->addItem(QString());
        TYPE_2->addItem(QString());
        TYPE_2->setObjectName("TYPE_2");
        TYPE_2->setGeometry(QRect(70, 400, 231, 31));
        TYPE_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 30, 201, 20));
        label_2->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color:black\n"
";"));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 100, 211, 20));
        label_6->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 240, 211, 20));
        label_3->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 300, 211, 31));
        label_4->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_8 = new QLabel(widget_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(70, 370, 211, 31));
        label_8->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_5 = new QLabel(widget_4);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 440, 191, 20));
        label_5->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;\n"
""));
        comboBoxTri = new QComboBox(widget_4);
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->addItem(QString());
        comboBoxTri->setObjectName("comboBoxTri");
        comboBoxTri->setGeometry(QRect(950, 170, 141, 31));
        comboBoxTri->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        label_23 = new QLabel(widget_4);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(70, 170, 211, 20));
        label_23->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        CIN_Client_2 = new QLineEdit(widget_4);
        CIN_Client_2->setObjectName("CIN_Client_2");
        CIN_Client_2->setGeometry(QRect(70, 200, 231, 31));
        CIN_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        label_31 = new QLabel(widget_4);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(950, 20, 201, 21));
        label_31->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color:black\n"
";"));
        label_32 = new QLabel(widget_4);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(990, 70, 201, 20));
        label_32->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color:black\n"
";"));
        stat_methods = new QToolButton(widget_4);
        stat_methods->setObjectName("stat_methods");
        stat_methods->setGeometry(QRect(1100, 60, 41, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../Images/Screenshots/STATISTICS-1024.webp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        stat_methods->setIcon(icon1);
        stat_methods->setIconSize(QSize(50, 50));
        exportToPDF = new QToolButton(widget_4);
        exportToPDF->setObjectName("exportToPDF");
        exportToPDF->setGeometry(QRect(1100, 10, 41, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../Images/Screenshots/Adobe_PDF-logo-84B633809C-seeklogo.com.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        exportToPDF->setIcon(icon2);
        exportToPDF->setIconSize(QSize(50, 50));
        label_9 = new QLabel(widget_4);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(70, 510, 211, 20));
        label_9->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        pushButtonRecherche = new QPushButton(widget_4);
        pushButtonRecherche->setObjectName("pushButtonRecherche");
        pushButtonRecherche->setGeometry(QRect(560, 170, 141, 31));
        pushButtonRecherche->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        lineEditRecherche = new QLineEdit(widget_4);
        lineEditRecherche->setObjectName("lineEditRecherche");
        lineEditRecherche->setGeometry(QRect(380, 170, 161, 31));
        lineEditRecherche->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        METHODEP_Client_2 = new QComboBox(widget_4);
        METHODEP_Client_2->addItem(QString());
        METHODEP_Client_2->addItem(QString());
        METHODEP_Client_2->setObjectName("METHODEP_Client_2");
        METHODEP_Client_2->setGeometry(QRect(70, 540, 231, 31));
        METHODEP_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        ADRESSE_Client_2 = new QLineEdit(widget_4);
        ADRESSE_Client_2->setObjectName("ADRESSE_Client_2");
        ADRESSE_Client_2->setGeometry(QRect(70, 330, 231, 31));
        ADRESSE_Client_2->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        widget_methods = new QWidget(widget_4);
        widget_methods->setObjectName("widget_methods");
        widget_methods->setGeometry(QRect(350, 520, 501, 201));
        tableView_2 = new QTableView(widget_4);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(370, 220, 751, 301));
        tableView_2->setStyleSheet(QString::fromUtf8("font-family:bold;"));
        btnUploadPhoto = new QPushButton(widget_4);
        btnUploadPhoto->setObjectName("btnUploadPhoto");
        btnUploadPhoto->setGeometry(QRect(190, 600, 141, 29));
        IMAGE_Client_2 = new QLabel(widget_4);
        IMAGE_Client_2->setObjectName("IMAGE_Client_2");
        IMAGE_Client_2->setGeometry(QRect(40, 600, 141, 20));
        comboBoxRecherche = new QComboBox(widget_4);
        comboBoxRecherche->addItem(QString());
        comboBoxRecherche->addItem(QString());
        comboBoxRecherche->addItem(QString());
        comboBoxRecherche->setObjectName("comboBoxRecherche");
        comboBoxRecherche->setGeometry(QRect(710, 170, 71, 31));
        comboBoxRecherche->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        map_2 = new QPushButton(widget_4);
        map_2->setObjectName("map_2");
        map_2->setGeometry(QRect(620, 610, 121, 41));
        map_2->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        stackedWidget->addWidget(page);
        modifier_3 = new QWidget();
        modifier_3->setObjectName("modifier_3");
        widget_5 = new QWidget(modifier_3);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(200, 40, 1171, 901));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        modifier_4 = new QPushButton(widget_5);
        modifier_4->setObjectName("modifier_4");
        modifier_4->setGeometry(QRect(860, 610, 121, 41));
        modifier_4->setStyleSheet(QString::fromUtf8("color: white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:bold;\n"
"border-radius:15px;\n"
"background-color:#4CBB17;"));
        Nom_Clientm = new QLineEdit(widget_5);
        Nom_Clientm->setObjectName("Nom_Clientm");
        Nom_Clientm->setGeometry(QRect(70, 50, 231, 31));
        Nom_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        PRENOM_Clientm = new QLineEdit(widget_5);
        PRENOM_Clientm->setObjectName("PRENOM_Clientm");
        PRENOM_Clientm->setGeometry(QRect(70, 130, 231, 31));
        PRENOM_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        NUMC_Clientm = new QLineEdit(widget_5);
        NUMC_Clientm->setObjectName("NUMC_Clientm");
        NUMC_Clientm->setGeometry(QRect(70, 270, 231, 31));
        NUMC_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        DATES_Clientm = new QDateTimeEdit(widget_5);
        DATES_Clientm->setObjectName("DATES_Clientm");
        DATES_Clientm->setGeometry(QRect(70, 470, 231, 31));
        DATES_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        TYPEm = new QComboBox(widget_5);
        TYPEm->setObjectName("TYPEm");
        TYPEm->setGeometry(QRect(70, 400, 231, 31));
        TYPEm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        label_10 = new QLabel(widget_5);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(80, 20, 201, 20));
        label_10->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color:black\n"
";"));
        label_11 = new QLabel(widget_5);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(70, 100, 211, 20));
        label_11->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_12 = new QLabel(widget_5);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(80, 240, 211, 20));
        label_12->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_13 = new QLabel(widget_5);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(80, 300, 211, 31));
        label_13->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_14 = new QLabel(widget_5);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(80, 370, 211, 31));
        label_14->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        label_15 = new QLabel(widget_5);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(80, 440, 191, 20));
        label_15->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;\n"
""));
        label_33 = new QLabel(widget_5);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(80, 170, 211, 20));
        label_33->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        CIN_Clientm = new QLineEdit(widget_5);
        CIN_Clientm->setObjectName("CIN_Clientm");
        CIN_Clientm->setGeometry(QRect(70, 200, 231, 31));
        CIN_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        label_17 = new QLabel(widget_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(80, 510, 211, 20));
        label_17->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-family:bold;\n"
"color: black;"));
        ADRESSE_Clientm = new QLineEdit(widget_5);
        ADRESSE_Clientm->setObjectName("ADRESSE_Clientm");
        ADRESSE_Clientm->setGeometry(QRect(70, 330, 231, 31));
        ADRESSE_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        METHODEP_Clientm = new QComboBox(widget_5);
        METHODEP_Clientm->setObjectName("METHODEP_Clientm");
        METHODEP_Clientm->setGeometry(QRect(70, 540, 231, 31));
        METHODEP_Clientm->setStyleSheet(QString::fromUtf8("border: 2px solid #4CBB17;\n"
"border-radius:15px;"));
        widget_3 = new QWidget(modifier_3);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(-30, -80, 231, 841));
        widget_3->setStyleSheet(QString::fromUtf8("background-color:#092939;"));
        toolButton_6 = new QToolButton(widget_3);
        toolButton_6->setObjectName("toolButton_6");
        toolButton_6->setGeometry(QRect(30, 120, 91, 81));
        toolButton_6->setIcon(icon);
        toolButton_6->setIconSize(QSize(100, 100));
        line_3 = new QFrame(widget_3);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(40, 300, 118, 3));
        line_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        label_18 = new QLabel(widget_3);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(40, 230, 161, 41));
        label_18->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 900 12pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_18->setTextFormat(Qt::PlainText);
        label_36 = new QLabel(widget_3);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(40, 330, 191, 31));
        label_36->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_37 = new QLabel(widget_3);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(40, 370, 191, 20));
        label_37->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_38 = new QLabel(widget_3);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(40, 440, 181, 31));
        label_38->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_39 = new QLabel(widget_3);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(40, 400, 181, 31));
        label_39->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
""));
        label_40 = new QLabel(widget_3);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(40, 480, 181, 31));
        label_40->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
""));
        label_41 = new QLabel(widget_3);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(40, 520, 221, 31));
        label_41->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        line_4 = new QFrame(widget_3);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(-10, 470, 16, 41));
        line_4->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 187, 23);"));
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        label_42 = new QLabel(widget_3);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(40, 680, 161, 41));
        label_42->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI Black\";\n"
"color: rgb(76, 187, 23);\n"
"font: 900 12pt \"Segoe UI Black\";\n"
"font: 12pt \"Segoe UI\";\n"
""));
        label_42->setTextFormat(Qt::PlainText);
        stackedWidget->addWidget(modifier_3);
        map = new QWidget();
        map->setObjectName("map");
        quickWidget_Map_View = new QQuickWidget(map);
        quickWidget_Map_View->setObjectName("quickWidget_Map_View");
        quickWidget_Map_View->setGeometry(QRect(510, 130, 801, 561));
        quickWidget_Map_View->setResizeMode(QQuickWidget::SizeRootObjectToView);
        stackedWidget->addWidget(map);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1318, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Page d'accueil", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Services ", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Mat\303\251riel", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Transaction", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Clients ", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "se d\303\251connecter", nullptr));
        modifier_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "trier par", nullptr));
        ajouter_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        supprimer_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        TYPE_2->setItemText(0, QCoreApplication::translate("MainWindow", "desinfectation", nullptr));
        TYPE_2->setItemText(1, QCoreApplication::translate("MainWindow", "maison", nullptr));
        TYPE_2->setItemText(2, QCoreApplication::translate("MainWindow", "chantier", nullptr));
        TYPE_2->setItemText(3, QCoreApplication::translate("MainWindow", "usines", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "nom du client ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Prenom du client", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Numero du client", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "adresse", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "type de service requis", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "date de service", nullptr));
        comboBoxTri->setItemText(0, QCoreApplication::translate("MainWindow", "NOM_Client", nullptr));
        comboBoxTri->setItemText(1, QCoreApplication::translate("MainWindow", "PRENOM_Client", nullptr));
        comboBoxTri->setItemText(2, QCoreApplication::translate("MainWindow", "METHODEP_Client", nullptr));

        label_23->setText(QCoreApplication::translate("MainWindow", "CIN du client", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "exporter en PDF", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "statistiques", nullptr));
        stat_methods->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        exportToPDF->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Methode de paiement", nullptr));
        pushButtonRecherche->setText(QCoreApplication::translate("MainWindow", "rechercher par", nullptr));
        lineEditRecherche->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        METHODEP_Client_2->setItemText(0, QCoreApplication::translate("MainWindow", "en ligne", nullptr));
        METHODEP_Client_2->setItemText(1, QCoreApplication::translate("MainWindow", "sur place", nullptr));

        btnUploadPhoto->setText(QCoreApplication::translate("MainWindow", "telecharger photo", nullptr));
        IMAGE_Client_2->setText(QCoreApplication::translate("MainWindow", "la photo", nullptr));
        comboBoxRecherche->setItemText(0, QCoreApplication::translate("MainWindow", "NOM_Client", nullptr));
        comboBoxRecherche->setItemText(1, QCoreApplication::translate("MainWindow", "PRENOM_Client", nullptr));
        comboBoxRecherche->setItemText(2, QCoreApplication::translate("MainWindow", "TYPE", nullptr));

        map_2->setText(QCoreApplication::translate("MainWindow", "Map", nullptr));
        modifier_4->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "nom du client ", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Prenom du client", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Numero du client", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "adresse", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "type de service requis", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "date de service", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "CIN du client", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Methode de paiement", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Page d'accueil", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Services ", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Mat\303\251riel", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Transaction", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "Clients ", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "se d\303\251connecter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
