#include "PlayerShow.h"
#include "QLayout"
#include "volumeButton.h"
#include "FontChina.h"
#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStyle>
#include <QMenu>
#include <QFileDialog>
#include <QTimerEvent>
#include <QMessageBox>
#include <QSlider>
#include "RhythmController.h"

PlayerShow::PlayerShow(QWidget* parent)
	:QWidget(parent), m_mode(NoMode)
	, m_modeButton(new QPushButton(this)), m_pauseButton(new QPushButton(this)), rcWidget(new RhythmController)
	, m_playButton(new QPushButton(this)), m_settingsButton(new QPushButton(this))
	, volumeButton(new VolumeButton(this)), positionSlider(new QSlider(Qt::Horizontal, this)), m_modeMenu(new QMenu(this))
	, SpectrumWidget(new QWidget), m_zplayer(CreateZPlay()), Title(new QLabel(FontChina::G2U("歌曲名"))), Artist(new QLabel(FontChina::G2U("艺术家"))), Album(new QLabel(FontChina::G2U("专辑")))
	, m_forwardButton(new QPushButton(this)), m_backwardButton(new QPushButton(this))
	, m_p25RateButton(new QPushButton(FontChina::G2U("25"))), m_p50RateButton(new QPushButton(FontChina::G2U("50"))), m_p75RateButton(new QPushButton(FontChina::G2U("75"))), m_p100RateButton(new QPushButton(FontChina::G2U("100")))
{
	createUi();
	connectUi();
	m_nTimerId = startTimer(50);
}

PlayerShow::~PlayerShow()
{
}

void PlayerShow::createUi()
{
	Title->setMaximumHeight(30);
	Artist->setMaximumHeight(30);
	Album->setMaximumHeight(30);
	createMenus();
	QVBoxLayout* windowLayout = new QVBoxLayout;
	QHBoxLayout* hlayout = new QHBoxLayout;
	SpectrumWidget->setMinimumSize(QSize(400, 250));
	SpectrumWidget->setMaximumSize(QSize(400, 250));
	hlayout->addWidget(SpectrumWidget);

	QHBoxLayout* infoLayout = new QHBoxLayout;
	infoLayout->addWidget(Title);
	infoLayout->addWidget(Artist);
	infoLayout->addWidget(Album);
	QHBoxLayout* analysisLayout = new QHBoxLayout;
	m_modeButton->setIcon(QIcon(":/icon/Resources/record.png"));
	m_modeButton->setText("Mode");
	analysisLayout->addWidget(m_modeButton);
	m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	m_forwardButton->setIcon(QIcon(":/icon/Resources/fast_forward.png"));
	m_backwardButton->setIcon(QIcon(":/icon/Resources/rewind.png"));
	analysisLayout->addWidget(m_forwardButton);
	analysisLayout->addWidget(m_backwardButton);
	analysisLayout->addWidget(m_pauseButton);
	m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	analysisLayout->addWidget(m_playButton);
	m_timeLabel = new QLabel(FontChina::G2U("00:00"));
	m_timeLabel->setMinimumWidth(m_timeLabel->sizeHint().width());
	analysisLayout->addWidget(m_timeLabel);
	volumeButton->setVolume(100);
	analysisLayout->addWidget(volumeButton);
	m_settingsButton->setIcon(QIcon(":/icon/Resources/settings.png"));
	analysisLayout->addWidget(m_settingsButton);
	QVBoxLayout* controlLayout = new QVBoxLayout;
	controlLayout->setMargin(0);
	controlLayout->addLayout(infoLayout);
	controlLayout->addLayout(analysisLayout);
	QHBoxLayout* sliLayout = new QHBoxLayout;
	sliLayout->addWidget(positionSlider);
	m_p25RateButton->setMaximumSize(QSize(30, 30));
	m_p50RateButton->setMaximumSize(QSize(30, 30));
	m_p75RateButton->setMaximumSize(QSize(30, 30));
	m_p100RateButton->setMaximumSize(QSize(30, 30));
	sliLayout->addWidget(m_p25RateButton);
	sliLayout->addWidget(m_p50RateButton);
	sliLayout->addWidget(m_p75RateButton);
	sliLayout->addWidget(m_p100RateButton);
	controlLayout->addLayout(sliLayout);
	controlLayout->addWidget(rcWidget);
	hlayout->addLayout(controlLayout);
	windowLayout->addLayout(hlayout);
	setLayout(windowLayout);
}

void PlayerShow::connectUi()
{
	createShortcuts();
	connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
	connect(m_playButton, SIGNAL(clicked()), this, SLOT(play()));
	connect(m_settingsButton, SIGNAL(clicked()), this, SLOT(showSettingsDialog()));
	connect(positionSlider, SIGNAL(valueChanged(int)), this, SLOT(setPosition(int)));
	connect(volumeButton, SIGNAL(volumeChanged(int)), this, SLOT(setVolume(int)));
	connect(m_loadFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
	connect(m_forwardButton, SIGNAL(clicked()), this, SLOT(forwardMusic_clicked()));
	connect(m_backwardButton, SIGNAL(clicked()), this, SLOT(backwardMusic_clicked()));

	connect(m_p25RateButton, SIGNAL(clicked()), this, SLOT(setRate25()));
	connect(m_p50RateButton, SIGNAL(clicked()), this, SLOT(setRate50()));
	connect(m_p75RateButton, SIGNAL(clicked()), this, SLOT(setRate75()));
	connect(m_p100RateButton, SIGNAL(clicked()), this, SLOT(setRate100()));
}

void PlayerShow::createMenus()
{
	m_modeButton->setMenu(m_modeMenu);
	m_loadFileAction = m_modeMenu->addAction(FontChina::G2U("打开文件"));
	m_loadFileAction->setCheckable(true);
}

void PlayerShow::createShortcuts()
{
	QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, this);
	connect(increaseShortcut, SIGNAL(activated()), volumeButton, SLOT(increaseVolume()));

	QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, this);
	connect(decreaseShortcut, SIGNAL(activated()), volumeButton, SLOT(descreaseVolume()));

	QShortcut* forwardMusicShortcut = new QShortcut(Qt::Key_Right, this);
	connect(forwardMusicShortcut, SIGNAL(activated()), this, SLOT(forwardMusic_clicked()));

	QShortcut* backwardMusicShortcut = new QShortcut(Qt::Key_Left, this);
	connect(backwardMusicShortcut, SIGNAL(activated()), this, SLOT(backwardMusic_clicked()));
}

void PlayerShow::openFile()
{
	const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
	const QString filePath =
		QFileDialog::getOpenFileName(this, tr("Open File"),
		musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
		tr("MP3 files (*.mp3);;WAV files (*.wav);;OGG files (*.ogg);;All files (*.*)"));
	mFilename = filePath;
	if (!filePath.isEmpty())
		play();
}

void PlayerShow::setVolume(int volume)
{
	m_zplayer->SetPlayerVolume(volume, volume);
}

void PlayerShow::updatePosition(qint64 position)
{
	positionSlider->setValue(position);
	QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
	QString totalTime = "";
	totalTime = QString::number(m_musictime.hms.minute) + ":" + QString::number(m_musictime.hms.second);
	m_timeLabel->setText(totalTime + "/" + duration.toString(tr("mm:ss")));
}

void PlayerShow::updateDuration(qint64 duration)
{
	positionSlider->setRange(0, duration);
	positionSlider->setEnabled(duration > 0);
	positionSlider->setPageStep(duration / 10);
}

void PlayerShow::setPosition(int position)
{
	TStreamTime mTime;
	m_zplayer->GetPosition(&mTime);
	unsigned int curTime = mTime.hms.minute * 60000 + mTime.hms.second * 1000 + mTime.hms.millisecond;
	if (qAbs(curTime - position) > 1000){
		TStreamTime pTime;
		pTime.ms = position - curTime;
		if (position < curTime){
			m_zplayer->Seek(tfMillisecond, &pTime, smFromCurrentBackward);
		}
		else{
			m_zplayer->Seek(tfMillisecond, &pTime, smFromCurrentForward);
		}
	}
}

void PlayerShow::timerEvent(QTimerEvent *event)
{
	TStreamStatus status;
	m_zplayer->GetStatus(&status);
	if (status.fPlay == 0)
		return; // exit checking loop

	TStreamTime pTime;
	m_zplayer->GetPosition(&pTime);
	qint64 position = pTime.hms.minute * 60000 + pTime.hms.second * 1000 + pTime.hms.millisecond;
	qint64 pos = pTime.ms;
	if (position != 0)
		updatePosition(position);
	// draw FFT graph on desktop window
	m_zplayer->DrawFFTGraphOnHWND((HWND)SpectrumWidget->winId(), 0, 0, 400, 250);
	rcWidget->setCurPos(position);
}

void PlayerShow::forwardMusic_clicked()
{
	TStreamTime pTime;
	m_zplayer->GetPosition(&pTime);
	qint64 position = pTime.hms.minute * 60000 + pTime.hms.second * 1000 + pTime.hms.millisecond;
	position += 2000;
	updatePosition(position);
}

void PlayerShow::backwardMusic_clicked()
{
	TStreamTime pTime;
	m_zplayer->GetPosition(&pTime);
	qint64 position = pTime.hms.minute * 60000 + pTime.hms.second * 1000 + pTime.hms.millisecond;
	position -= 2000;
	if (position < 0)position = 0;
	updatePosition(position);
}

void PlayerShow::setRate25()
{
	m_zplayer->SetRate(25);
}

void PlayerShow::setRate50()
{
	m_zplayer->SetRate(50);
}

void PlayerShow::setRate75()
{
	m_zplayer->SetRate(75);
}

void PlayerShow::setRate100()
{
	m_zplayer->SetRate(100);
}

void PlayerShow::updateInfo()
{
	TID3InfoEx id3_info;
	m_zplayer->LoadFileID3Ex(mFilename.toStdString().c_str(), sfAutodetect, &id3_info, 1);
	std::string info;
	info += FontChina::G2U("歌曲名:");
	if (id3_info.Title)
		info += id3_info.Title;
	Title->setText(info.c_str());
	info = "";
	info += FontChina::G2U("艺术家:");
	if (id3_info.Artist)
		info += id3_info.Artist;
	Artist->setText(info.c_str());
	info = "";
	info += FontChina::G2U("专辑:");
	if (id3_info.Album)
		info += id3_info.Album;
	Album->setText(info.c_str());
	TStreamInfo pInfo;
	m_zplayer->GetStreamInfo(&pInfo);
	m_musictime.hms.minute = pInfo.Length.hms.minute;
	m_musictime.hms.second = pInfo.Length.hms.second;
	m_musictime.hms.millisecond = pInfo.Length.hms.millisecond;
	unsigned int duration = m_musictime.hms.minute * 60000 + m_musictime.hms.second * 1000 + m_musictime.hms.millisecond;
	updateDuration(duration);
	addInfoToRhyWidget();
}

void PlayerShow::addInfoToRhyWidget()
{
	unsigned int duration = m_musictime.hms.minute * 60000 + m_musictime.hms.second * 1000 + m_musictime.hms.millisecond;
	rcWidget->setPosition(duration);
	rcWidget->setBmp(127);
	rcWidget->setOffset(2000);
	rcWidget->setMeasure(4);
	rcWidget->setLiasion(2);
	rcWidget->createRhythm();
}

void PlayerShow::play()
{
	static QString oldfilename = "";
	if (oldfilename != mFilename){
		oldfilename = mFilename;
		int result = m_zplayer->OpenFile(mFilename.toStdString().c_str(), sfAutodetect);
		if (result == 0){
			m_zplayer->Release();
			m_zplayer = NULL;
		}
		else{
			m_zplayer->SetFFTGraphParam(gpGraphType, gtAreaLeftOnTop);
			m_zplayer->SetFFTGraphParam(gpHorizontalScale, gsLinear);
			updateInfo();
		}
	}
	m_zplayer->Play();
}

void PlayerShow::pause()
{
	m_zplayer->Pause();
}
