/********************************************************************************
** Form generated from reading UI file 'qtmusiceditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMUSICEDITOR_H
#define UI_QTMUSICEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTMusicEditorClass
{
public:
    QAction *actionOpen;
    QAction *actionOpenAudio;
    QWidget *centralWidget;
    QDockWidget *LogWidget;
    QWidget *LogWidgetContents;
    QPlainTextEdit *plainTextEdit;
    QWidget *SceneWidget;
    QScrollArea *SpectrumWidget;
    QWidget *SpectrumWidgetContents;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTMusicEditorClass)
    {
        if (QTMusicEditorClass->objectName().isEmpty())
            QTMusicEditorClass->setObjectName(QStringLiteral("QTMusicEditorClass"));
        QTMusicEditorClass->resize(1247, 910);
        actionOpen = new QAction(QTMusicEditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpenAudio = new QAction(QTMusicEditorClass);
        actionOpenAudio->setObjectName(QStringLiteral("actionOpenAudio"));
        centralWidget = new QWidget(QTMusicEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LogWidget = new QDockWidget(centralWidget);
        LogWidget->setObjectName(QStringLiteral("LogWidget"));
        LogWidget->setGeometry(QRect(955, -2, 281, 271));
        LogWidget->setStyleSheet(QStringLiteral(" background-color:rgba(191, 191, 191, 191)"));
        LogWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        LogWidgetContents = new QWidget();
        LogWidgetContents->setObjectName(QStringLiteral("LogWidgetContents"));
        plainTextEdit = new QPlainTextEdit(LogWidgetContents);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 281, 251));
        LogWidget->setWidget(LogWidgetContents);
        SceneWidget = new QWidget(centralWidget);
        SceneWidget->setObjectName(QStringLiteral("SceneWidget"));
        SceneWidget->setGeometry(QRect(0, 273, 1241, 581));
        SceneWidget->setStyleSheet(QStringLiteral(" background-color:rgba(191, 191, 191, 191)"));
        SpectrumWidget = new QScrollArea(centralWidget);
        SpectrumWidget->setObjectName(QStringLiteral("SpectrumWidget"));
        SpectrumWidget->setGeometry(QRect(0, 0, 951, 271));
        SpectrumWidget->setStyleSheet(QStringLiteral(" background-color:rgba(191, 191, 191, 191)"));
        SpectrumWidget->setWidgetResizable(true);
        SpectrumWidgetContents = new QWidget();
        SpectrumWidgetContents->setObjectName(QStringLiteral("SpectrumWidgetContents"));
        SpectrumWidgetContents->setGeometry(QRect(0, 0, 949, 269));
        SpectrumWidget->setWidget(SpectrumWidgetContents);
        QTMusicEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTMusicEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1247, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        QTMusicEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTMusicEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTMusicEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTMusicEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTMusicEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpenAudio);

        retranslateUi(QTMusicEditorClass);

        QMetaObject::connectSlotsByName(QTMusicEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTMusicEditorClass)
    {
        QTMusicEditorClass->setWindowTitle(QApplication::translate("QTMusicEditorClass", "QTMusicEditor", 0));
        actionOpen->setText(QApplication::translate("QTMusicEditorClass", "openConf", 0));
        actionOpenAudio->setText(QApplication::translate("QTMusicEditorClass", "openAudio", 0));
        menuFile->setTitle(QApplication::translate("QTMusicEditorClass", "file", 0));
    } // retranslateUi

};

namespace Ui {
    class QTMusicEditorClass: public Ui_QTMusicEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMUSICEDITOR_H
