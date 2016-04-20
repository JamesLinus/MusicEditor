#pragma once
#include <QWidget>
#include "libzplay.h"

using namespace libZPlay;

class VolumeButton;
class RhythmController;
QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QPushButton;
class QSlider;
QT_END_NAMESPACE

class PlayerShow : public QWidget
{
	Q_OBJECT
public:
	PlayerShow(QWidget* parent = 0);
	~PlayerShow();


private:
	void createUi();
	void createMenus();
	void createShortcuts();
	void connectUi();

protected:
	enum Mode {
		NoMode,
		RecordMode,
		GenerateToneMode,
		LoadFileMode
	};

	void setMode(Mode mode);

protected slots:
	void play();
	void pause();
	void openFile();
	void updatePosition(qint64 position);
	void updateDuration(qint64 duration);
	void setPosition(int position);
	void updateInfo();
	void setVolume(int volume);
	void forwardMusic_clicked();
	void backwardMusic_clicked();
	void setRate25();
	void setRate50();
	void setRate75();
	void setRate100();
protected:
	void timerEvent(QTimerEvent *event);
	void addInfoToRhyWidget();
private:
	Mode                    m_mode;
	QPushButton*            m_modeButton;
	QPushButton*            m_pauseButton;
	QPushButton*            m_playButton;
	QPushButton*            m_settingsButton;
	QPushButton*			m_forwardButton;
	QPushButton*			m_backwardButton;
	VolumeButton *			volumeButton;
	RhythmController*		rcWidget;
	QPushButton*			m_p25RateButton;
	QPushButton*			m_p50RateButton;
	QPushButton*			m_p75RateButton;
	QPushButton*			m_p100RateButton;

	QSlider *				positionSlider;
	QLabel*					m_timeLabel;
	QMenu*                  m_modeMenu;
	QAction*                m_loadFileAction;
	QString					mFilename;
	QWidget*				SpectrumWidget;
	ZPlay *					m_zplayer;
	
	int						m_nTimerId;
	QLabel*					Title;
	QLabel*					Artist;
	QLabel*					Album;
	TStreamTime				m_musictime;
	
};

