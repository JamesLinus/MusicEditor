#ifndef QTMUSICEDITOR_H
#define QTMUSICEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_qtmusiceditor.h"

namespace Ui{
	class QTMusicEditor;
}

class QTMusicEditor : public QMainWindow
{
	Q_OBJECT

public:
	QTMusicEditor(QWidget *parent = 0);
	~QTMusicEditor();
	Ui::QTMusicEditorClass& getUI(){ return ui; }
private:
	Ui::QTMusicEditorClass ui;
};

#endif // QTMUSICEDITOR_H
