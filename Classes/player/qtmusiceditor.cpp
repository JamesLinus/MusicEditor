#include "qtmusiceditor.h"
#include "Global.h"
#include "PlayerShow.h"
QTMusicEditor::QTMusicEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.SpectrumWidget->setWidget(new PlayerShow);
	g_editor = this;
}

QTMusicEditor::~QTMusicEditor()
{

}
