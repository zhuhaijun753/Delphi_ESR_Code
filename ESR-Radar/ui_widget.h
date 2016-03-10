/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include <planview.h>
#include <sensorview.h>
#include <tableview.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *PB_Connect;
    QLabel *LB_Title_CAN;
    QPushButton *PB_Start;
    QPushButton *PB_Stop;
    QPushButton *PB_Recode_Start;
    QPushButton *PB_Recode_Stop;
    QLabel *LB_Title_Data;
    QPushButton *PB_Read;
    QLabel *LB_Title_PlanView;
    QLabel *LB_Title_DataView;
    planview *Wid_PlanView;
    sensorview *Wid_SensorView;
    tableview *Wid_TableView;
    QLabel *LB_Title_DataView_2;
    QRadioButton *RB_Polar;
    QLabel *LB_Title_Data_2;
    QRadioButton *RB_Rectangular;
    QLabel *LB_Title_VideoMode;
    QPushButton *PB_Video_Start_Stop;
    QSlider *HS_Video_SliderBar;
    QSpinBox *SB_Frame_Number;
    QCheckBox *CB_Video;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1190, 720);
        Widget->setMinimumSize(QSize(1190, 720));
        Widget->setMaximumSize(QSize(1190, 720));
        Widget->setStyleSheet(QLatin1String("QToolTip\n"
"{\n"
"     border: 1px solid black;\n"
"     background-color: #ffa02f;\n"
"     padding: 1px;\n"
"     border-radius: 3px;\n"
"     opacity: 100;\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"    background: transparent;\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"    background: #444;\n"
"    border: 1px solid #000;\n"
"    background-color: QLinearGradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:1 #212121,\n"
"        stop:0.4 #343434/*,\n"
"        stop:0.2 #3"
                        "43434,\n"
"        stop:0.1 #ffaa00*/\n"
"    );\n"
"    margin-bottom:-1px;\n"
"    padding-bottom:1px;\n"
"}\n"
"\n"
"QMenu\n"
"{\n"
"    border: 1px solid #000;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"    padding: 2px 20px 2px 20px;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:disabled\n"
"{\n"
"    color: #404040;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QAbstractItemView\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);\n"
"}\n"
"\n"
"QWidget:focus\n"
"{\n"
"    /*border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);\n"
"    padding: 1px;\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b"
                        "1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #ffaa00;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"QComboBox:hover,QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: "
                        "0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"\n"
"QComboBox:on\n"
"{\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"    selection-background-color: #ffaa00;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView\n"
"{\n"
"    border: 2px solid darkgray;\n"
"    selection-background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QComboBox::drop-down\n"
"{\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"\n"
"     border-left-width: 0px;\n"
"     border-left-color: darkgray;\n"
"     border-left-style: solid; /* just a single line */\n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 3px;\n"
" }\n"
"\n"
"QComboBox::down-arrow\n"
"{\n"
"    image: url(:/Images/Image/down_ar"
                        "row.png);\n"
"\n"
"}\n"
"\n"
"QGroupBox:focus\n"
"{\n"
"border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QTextEdit:focus\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"     height: 7px;\n"
"     margin: 0px 16px 0 16px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
""
                        "      subcontrol-position: right;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"      width: 7px;\n"
"      margin: 16px 0 16px 0;\n"
"      border: 1px solid #222222;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"      background: "
                        "QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      height: 14px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\n"
"      height: 14px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar::add-pa"
                        "ge:vertical, QScrollBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QPlainTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QHeaderView::section\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"}\n"
"\n"
"QCheckBox:disabled\n"
"{\n"
"color: #414141;\n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"    text-align: center;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button\n"
"{\n"
"    text-align: center;\n"
"    spacing: 1px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, st"
                        "op:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button:hover, QDockWidget::float-button:hover\n"
"{\n"
"    background: #242424;\n"
"}\n"
"\n"
"QDockWidget::close-button:pressed, QDockWidget::float-button:pressed\n"
"{\n"
"    padding: 1px -1px -1px 1px;\n"
"}\n"
"\n"
"QMainWindow::separator\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #4c4c4c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QMainWindow::separator:hover\n"
"{\n"
"\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QToolBar::handle\n"
"{\n"
"     spacing: 3px; /* spacing between it"
                        "ems in the tool bar */\n"
"     background: url(:/Images/handle.png);\n"
"}\n"
"\n"
"QMenu::separator\n"
"{\n"
"    height: 2px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    margin-left: 10px;\n"
"    margin-right: 5px;\n"
"}\n"
"\n"
"QProgressBar\n"
"{\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"    background-color: #d7801a;\n"
"    width: 2.15px;\n"
"    margin: 0.5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    color: #b1b1b1;\n"
"    border: 1px solid #444;\n"
"    border-bottom-style: none;\n"
"    background-color: #323232;\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"    padding-top: 3px;\n"
"    padding-bottom: 2px;\n"
"    margin-right: -1px;\n"
"	width:124px;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #444;\n"
"    top: 1px;\n"
"}\n"
"\n"
""
                        "QTabBar::tab:last\n"
"{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:first:!selected\n"
"{\n"
" margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */\n"
"\n"
"\n"
"    border-top-left-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected\n"
"{\n"
"    /*color: #b1b1b1;*/\n"
"	color: #212121;\n"
"    border-bottom-style: solid;\n"
"    margin-top: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    margin-bottom: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover\n"
"{\n"
"    /*border-top: 2px solid #ffaa00;\n"
"    padding-bottom: 3px;*/\n"
"	color: #b1b1b1;\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2"
                        ":1, stop:1 #212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ffaa00);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked, QRadioButton::indicator:unchecked{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked\n"
"{\n"
"    background-color: qradialgradient(\n"
"        cx: 0.5, cy: 0.5,\n"
"        fx: 0.5, fy: 0.5,\n"
"        radius: 1.0,\n"
"        stop: 0.25 #ffaa00,\n"
"        stop: 0.3 #323232\n"
"    );\n"
"}\n"
"\n"
"QCheckBox::indicator{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"QRadioButton::indicator\n"
"{\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:hover, QCheckBox::indicator:hover\n"
"{\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image: url(:/Images/Image/checkbox.png);\n"
"}\n"
"\n"
"QCheckBox::indicat"
                        "or:disabled, QRadioButton::indicator:disabled\n"
"{\n"
"    border: 1px solid #444;\n"
"}\n"
"QSpinBox{\n"
"	border: 1px solid #444;\n"
"}\n"
"QSpinBox::up-button{\n"
"\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button{\n"
"\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button{\n"
"\n"
"}\n"
"\n"
"QTableWidget{\n"
"	background-color: #323232;\n"
"}\n"
"\n"
"\n"
"QSlider::groove:horizontal {\n"
"height: 4px;\n"
"background: #d7801a;\n"
"margin: 2px 0;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
" background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"border-width: 1px;\n"
"border-color: #1e1e1e;\n"
"border-style: solid;\n"
"border-radius: 6;\n"
"width: 16px;\n"
"margin: -7px 0;\n"
"border-radius: 8px;\n"
"}"));
        PB_Connect = new QPushButton(Widget);
        PB_Connect->setObjectName(QStringLiteral("PB_Connect"));
        PB_Connect->setGeometry(QRect(150, 10, 110, 23));
        PB_Connect->setCursor(QCursor(Qt::PointingHandCursor));
        LB_Title_CAN = new QLabel(Widget);
        LB_Title_CAN->setObjectName(QStringLiteral("LB_Title_CAN"));
        LB_Title_CAN->setGeometry(QRect(10, 13, 121, 16));
        PB_Start = new QPushButton(Widget);
        PB_Start->setObjectName(QStringLiteral("PB_Start"));
        PB_Start->setGeometry(QRect(270, 10, 110, 23));
        PB_Start->setCursor(QCursor(Qt::PointingHandCursor));
        PB_Stop = new QPushButton(Widget);
        PB_Stop->setObjectName(QStringLiteral("PB_Stop"));
        PB_Stop->setGeometry(QRect(390, 10, 110, 23));
        PB_Stop->setCursor(QCursor(Qt::PointingHandCursor));
        PB_Recode_Start = new QPushButton(Widget);
        PB_Recode_Start->setObjectName(QStringLiteral("PB_Recode_Start"));
        PB_Recode_Start->setGeometry(QRect(580, 10, 110, 23));
        PB_Recode_Start->setCursor(QCursor(Qt::PointingHandCursor));
        PB_Recode_Stop = new QPushButton(Widget);
        PB_Recode_Stop->setObjectName(QStringLiteral("PB_Recode_Stop"));
        PB_Recode_Stop->setGeometry(QRect(700, 10, 110, 23));
        PB_Recode_Stop->setCursor(QCursor(Qt::PointingHandCursor));
        LB_Title_Data = new QLabel(Widget);
        LB_Title_Data->setObjectName(QStringLiteral("LB_Title_Data"));
        LB_Title_Data->setGeometry(QRect(510, 13, 61, 16));
        PB_Read = new QPushButton(Widget);
        PB_Read->setObjectName(QStringLiteral("PB_Read"));
        PB_Read->setGeometry(QRect(150, 40, 110, 23));
        PB_Read->setCursor(QCursor(Qt::PointingHandCursor));
        LB_Title_PlanView = new QLabel(Widget);
        LB_Title_PlanView->setObjectName(QStringLiteral("LB_Title_PlanView"));
        LB_Title_PlanView->setGeometry(QRect(10, 70, 110, 16));
        LB_Title_DataView = new QLabel(Widget);
        LB_Title_DataView->setObjectName(QStringLiteral("LB_Title_DataView"));
        LB_Title_DataView->setGeometry(QRect(490, 70, 141, 16));
        Wid_PlanView = new planview(Widget);
        Wid_PlanView->setObjectName(QStringLiteral("Wid_PlanView"));
        Wid_PlanView->setGeometry(QRect(10, 100, 461, 601));
        Wid_SensorView = new sensorview(Widget);
        Wid_SensorView->setObjectName(QStringLiteral("Wid_SensorView"));
        Wid_SensorView->setGeometry(QRect(490, 100, 681, 91));
        Wid_TableView = new tableview(Widget);
        Wid_TableView->setObjectName(QStringLiteral("Wid_TableView"));
        Wid_TableView->setGeometry(QRect(490, 240, 681, 463));
        LB_Title_DataView_2 = new QLabel(Widget);
        LB_Title_DataView_2->setObjectName(QStringLiteral("LB_Title_DataView_2"));
        LB_Title_DataView_2->setGeometry(QRect(489, 210, 141, 16));
        RB_Polar = new QRadioButton(Widget);
        RB_Polar->setObjectName(QStringLiteral("RB_Polar"));
        RB_Polar->setGeometry(QRect(915, 12, 51, 20));
        RB_Polar->setChecked(true);
        LB_Title_Data_2 = new QLabel(Widget);
        LB_Title_Data_2->setObjectName(QStringLiteral("LB_Title_Data_2"));
        LB_Title_Data_2->setGeometry(QRect(820, 13, 81, 16));
        RB_Rectangular = new QRadioButton(Widget);
        RB_Rectangular->setObjectName(QStringLiteral("RB_Rectangular"));
        RB_Rectangular->setGeometry(QRect(970, 12, 91, 20));
        LB_Title_VideoMode = new QLabel(Widget);
        LB_Title_VideoMode->setObjectName(QStringLiteral("LB_Title_VideoMode"));
        LB_Title_VideoMode->setGeometry(QRect(10, 43, 111, 16));
        PB_Video_Start_Stop = new QPushButton(Widget);
        PB_Video_Start_Stop->setObjectName(QStringLiteral("PB_Video_Start_Stop"));
        PB_Video_Start_Stop->setGeometry(QRect(270, 40, 31, 23));
        HS_Video_SliderBar = new QSlider(Widget);
        HS_Video_SliderBar->setObjectName(QStringLiteral("HS_Video_SliderBar"));
        HS_Video_SliderBar->setGeometry(QRect(310, 42, 181, 19));
        HS_Video_SliderBar->setOrientation(Qt::Horizontal);
        SB_Frame_Number = new QSpinBox(Widget);
        SB_Frame_Number->setObjectName(QStringLiteral("SB_Frame_Number"));
        SB_Frame_Number->setGeometry(QRect(500, 40, 61, 22));
        SB_Frame_Number->setAlignment(Qt::AlignCenter);
        CB_Video = new QCheckBox(Widget);
        CB_Video->setObjectName(QStringLiteral("CB_Video"));
        CB_Video->setGeometry(QRect(582, 41, 61, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Delphi ESR Sensor Application - REDONE TECHNOLOGIES CO.., LTD", 0));
        PB_Connect->setText(QApplication::translate("Widget", "Connect", 0));
        LB_Title_CAN->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#ffffff;\">CAN Bus Mode</span></p></body></html>", 0));
        PB_Start->setText(QApplication::translate("Widget", "Start", 0));
        PB_Stop->setText(QApplication::translate("Widget", "Stop", 0));
        PB_Recode_Start->setText(QApplication::translate("Widget", "Recode Start", 0));
        PB_Recode_Stop->setText(QApplication::translate("Widget", "Recode Stop", 0));
        LB_Title_Data->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#ffffff;\">Recode</span></p></body></html>", 0));
        PB_Read->setText(QApplication::translate("Widget", "Read to Data", 0));
        LB_Title_PlanView->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#ffffff;\">PlanView</span></p></body></html>", 0));
        LB_Title_DataView->setText(QApplication::translate("Widget", "<html><head/><body><p><a name=\"tw-target-text\"/><span style=\" font-family:'inherit'; font-size:11pt; font-weight:600; color:#ffffff;\">S</span><span style=\" font-family:'inherit'; font-size:11pt; font-weight:600; color:#ffffff;\">ensorView</span></p></body></html>", 0));
        LB_Title_DataView_2->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-family:'inherit'; font-size:11pt; font-weight:600; color:#ffffff;\">TableView</span></p></body></html>", 0));
        RB_Polar->setText(QApplication::translate("Widget", "Polar", 0));
        LB_Title_Data_2->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#ffffff;\">Coordinate</span></p></body></html>", 0));
        RB_Rectangular->setText(QApplication::translate("Widget", "Rectangular", 0));
        LB_Title_VideoMode->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#ffffff;\">Video Mode</span></p></body></html>", 0));
        PB_Video_Start_Stop->setText(QApplication::translate("Widget", "\342\226\266", 0));
        CB_Video->setText(QApplication::translate("Widget", "Video ", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
