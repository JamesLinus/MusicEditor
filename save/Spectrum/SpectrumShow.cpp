#include "SpectrumShow.h"
#include "engine.h"
#include "levelmeter.h"
#include "waveform.h"
#include "progressbar.h"
#include "settingsdialog.h"
#include "spectrograph.h"
#include "tonegeneratordialog.h"
#include "utils.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStyle>
#include <QMenu>
#include <QFileDialog>
#include <QTimerEvent>
#include <QMessageBox>

const int NullTimerId = -1;

SpectrumShow::SpectrumShow(QWidget *parent)
	: QWidget(parent)
	, m_mode(NoMode)
	, m_engine(new Engine(this))
#ifndef DISABLE_WAVEFORM
	, m_waveform(new Waveform(this))
#endif
	, m_progressBar(new ProgressBar(this))
	, m_spectrograph(new Spectrograph(this))
	, m_levelMeter(new LevelMeter(this))
	, m_modeButton(new QPushButton(this))
	, m_recordButton(new QPushButton(this))
	, m_pauseButton(new QPushButton(this))
	, m_playButton(new QPushButton(this))
	, m_settingsButton(new QPushButton(this))
	, m_infoMessageTimerId(NullTimerId)
	, m_settingsDialog(new SettingsDialog(
	m_engine->availableAudioInputDevices(),
	m_engine->availableAudioOutputDevices(),
	this))
	, m_toneGeneratorDialog(new ToneGeneratorDialog(this))
	, m_modeMenu(new QMenu(this))
	, m_loadFileAction(0)
	, m_generateToneAction(0)
	, m_recordAction(0)
{
	m_spectrograph->setParams(SpectrumNumBands, SpectrumLowFreq, SpectrumHighFreq);

	createUi();
	connectUi();
}

SpectrumShow::~SpectrumShow()
{

}

//-----------------------------------------------------------------------------
// Public slots
//-----------------------------------------------------------------------------
//�����ŵ�״̬�ı�����ô˷���
void SpectrumShow::stateChanged(QAudio::Mode mode, QAudio::State state)
{
	Q_UNUSED(mode);

	updateButtonStates();

	if (QAudio::ActiveState != state && QAudio::SuspendedState != state) {
		m_levelMeter->reset();
		m_spectrograph->reset();
	}
}

//mode�л����ú�˷���
void SpectrumShow::formatChanged(const QAudioFormat &format)
{
	infoMessage(formatToString(format), NullMessageTimeout);

#ifndef DISABLE_WAVEFORM
	if (QAudioFormat() != format) {
		m_waveform->initialize(format, WaveformTileLength,
			WaveformWindowDuration);
	}
#endif
}

//�ػ�Ƶ��ͼ�͸�������
void SpectrumShow::spectrumChanged(qint64 position, qint64 length,
	const FrequencySpectrum &spectrum)
{
	m_progressBar->windowChanged(position, length);
	m_spectrograph->spectrumChanged(spectrum);
}

void SpectrumShow::infoMessage(const QString &message, int timeoutMs)
{
	if (NullTimerId != m_infoMessageTimerId) {
		killTimer(m_infoMessageTimerId);
		m_infoMessageTimerId = NullTimerId;
	}

	if (NullMessageTimeout != timeoutMs)
		m_infoMessageTimerId = startTimer(timeoutMs);
}

void SpectrumShow::errorMessage(const QString &heading, const QString &detail)
{
	QMessageBox::warning(this, heading, detail, QMessageBox::Close);
}

void SpectrumShow::timerEvent(QTimerEvent *event)
{
	Q_ASSERT(event->timerId() == m_infoMessageTimerId);
	Q_UNUSED(event) // suppress warnings in release builds
		killTimer(m_infoMessageTimerId);
	m_infoMessageTimerId = NullTimerId;
}

void SpectrumShow::audioPositionChanged(qint64 position)
{
#ifndef DISABLE_WAVEFORM
	m_waveform->audioPositionChanged(position);
#else
	Q_UNUSED(position)
#endif
}

//�����ĳ���
void SpectrumShow::bufferLengthChanged(qint64 length)
{
	m_progressBar->bufferLengthChanged(length);
}


//-----------------------------------------------------------------------------
// Private slots
//-----------------------------------------------------------------------------

void SpectrumShow::showFileDialog()
{
	const QString dir;
	const QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Audio file"), dir, "Audio Files(*.wav *.mp3)");
	if (fileNames.count()) {
		reset();
		setMode(LoadFileMode);
		m_engine->loadFile(fileNames.front());
		updateButtonStates();
	}
	else {
		updateModeMenu();
	}
}

void SpectrumShow::showSettingsDialog()
{
	m_settingsDialog->exec();
	if (m_settingsDialog->result() == QDialog::Accepted) {
		m_engine->setAudioInputDevice(m_settingsDialog->inputDevice());
		m_engine->setAudioOutputDevice(m_settingsDialog->outputDevice());
		m_engine->setWindowFunction(m_settingsDialog->windowFunction());
	}
}

//����Ƶ�׵ĶԻ���
void SpectrumShow::showToneGeneratorDialog()
{
	m_toneGeneratorDialog->exec();
	if (m_toneGeneratorDialog->result() == QDialog::Accepted) {
		reset();
		setMode(GenerateToneMode);
		const qreal amplitude = m_toneGeneratorDialog->amplitude();
		if (m_toneGeneratorDialog->isFrequencySweepEnabled()) {
			//m_engine->generateSweptTone(amplitude);
		}
		else {
			const qreal frequency = m_toneGeneratorDialog->frequency();
			const Tone tone(frequency, amplitude);
			//m_engine->generateTone(tone);
			updateButtonStates();
		}
	}
	else {
		updateModeMenu();
	}
}

void SpectrumShow::initializeRecord()
{
	reset();
	setMode(RecordMode);
	/*if (m_engine->initializeRecord())
		updateButtonStates();*/
}


//-----------------------------------------------------------------------------
// Private functions
//-----------------------------------------------------------------------------

void SpectrumShow::createUi()
{
	createMenus();

	QVBoxLayout *windowLayout = new QVBoxLayout(this);
	
	QScopedPointer<QHBoxLayout> analysisLayout(new QHBoxLayout);
	analysisLayout->addWidget(m_waveform);
	analysisLayout->addWidget(m_spectrograph);
	analysisLayout->addWidget(m_levelMeter);
	windowLayout->addLayout(analysisLayout.data());
	analysisLayout.take();

	const QSize buttonSize(30, 30);

	m_modeButton->setText(tr("Mode"));

	m_recordIcon = QIcon(":/icon/Resources/record.png");
	m_recordButton->setIcon(m_recordIcon);
	m_recordButton->setEnabled(false);
	m_recordButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_recordButton->setMinimumSize(buttonSize);

	m_pauseIcon = style()->standardIcon(QStyle::SP_MediaPause);
	m_pauseButton->setIcon(m_pauseIcon);
	m_pauseButton->setEnabled(false);
	m_pauseButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_pauseButton->setMinimumSize(buttonSize);

	m_playIcon = style()->standardIcon(QStyle::SP_MediaPlay);
	m_playButton->setIcon(m_playIcon);
	m_playButton->setEnabled(false);
	m_playButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_playButton->setMinimumSize(buttonSize);

	m_settingsIcon = QIcon(":/icon/Resources/settings.png");
	m_settingsButton->setIcon(m_settingsIcon);
	m_settingsButton->setEnabled(true);
	m_settingsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_settingsButton->setMinimumSize(buttonSize);

	QScopedPointer<QHBoxLayout> buttonPanelLayout(new QHBoxLayout);
	buttonPanelLayout->addStretch();
	buttonPanelLayout->addWidget(m_modeButton);
	buttonPanelLayout->addWidget(m_recordButton);
	buttonPanelLayout->addWidget(m_pauseButton);
	buttonPanelLayout->addWidget(m_playButton);
	buttonPanelLayout->addWidget(m_settingsButton);

	QWidget *buttonPanel = new QWidget(this);
	buttonPanel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	buttonPanel->setLayout(buttonPanelLayout.data());
	buttonPanelLayout.take(); // ownership transferred to buttonPanel

	QScopedPointer<QHBoxLayout> bottomPaneLayout(new QHBoxLayout);
	bottomPaneLayout->addWidget(buttonPanel);
	windowLayout->addLayout(bottomPaneLayout.data());
	bottomPaneLayout.take(); // ownership transferred to windowLayout

	// Apply layout

	setLayout(windowLayout);
}

void SpectrumShow::connectUi()
{
	CHECKED_CONNECT(m_pauseButton, SIGNAL(clicked()),
		m_engine, SLOT(suspend()));

	CHECKED_CONNECT(m_playButton, SIGNAL(clicked()),
		m_engine, SLOT(startPlayback()));

	CHECKED_CONNECT(m_settingsButton, SIGNAL(clicked()),
		this, SLOT(showSettingsDialog()));

	CHECKED_CONNECT(m_engine, SIGNAL(stateChanged(QAudio::Mode, QAudio::State)),
		this, SLOT(stateChanged(QAudio::Mode, QAudio::State)));

	CHECKED_CONNECT(m_engine, SIGNAL(formatChanged(const QAudioFormat &)),
		this, SLOT(formatChanged(const QAudioFormat &)));

	m_progressBar->bufferLengthChanged(m_engine->bufferLength());

	CHECKED_CONNECT(m_engine, SIGNAL(bufferLengthChanged(qint64)),
		this, SLOT(bufferLengthChanged(qint64)));

	CHECKED_CONNECT(m_engine, SIGNAL(dataLengthChanged(qint64)),
		this, SLOT(updateButtonStates()));

	CHECKED_CONNECT(m_engine, SIGNAL(recordPositionChanged(qint64)),
		m_progressBar, SLOT(recordPositionChanged(qint64)));

	CHECKED_CONNECT(m_engine, SIGNAL(playPositionChanged(qint64)),
		m_progressBar, SLOT(playPositionChanged(qint64)));

	CHECKED_CONNECT(m_engine, SIGNAL(recordPositionChanged(qint64)),
		this, SLOT(audioPositionChanged(qint64)));

	CHECKED_CONNECT(m_engine, SIGNAL(playPositionChanged(qint64)),
		this, SLOT(audioPositionChanged(qint64)));

	CHECKED_CONNECT(m_engine, SIGNAL(levelChanged(qreal, qreal, int)),
		m_levelMeter, SLOT(levelChanged(qreal, qreal, int)));

	CHECKED_CONNECT(m_engine, SIGNAL(spectrumChanged(qint64, qint64, const FrequencySpectrum &)),
		this, SLOT(spectrumChanged(qint64, qint64, const FrequencySpectrum &)));

	CHECKED_CONNECT(m_engine, SIGNAL(infoMessage(QString, int)),
		this, SLOT(infoMessage(QString, int)));

	CHECKED_CONNECT(m_engine, SIGNAL(errorMessage(QString, QString)),
		this, SLOT(errorMessage(QString, QString)));

	CHECKED_CONNECT(m_spectrograph, SIGNAL(infoMessage(QString, int)),
		this, SLOT(infoMessage(QString, int)));

#ifndef DISABLE_WAVEFORM
	CHECKED_CONNECT(m_engine, SIGNAL(bufferChanged(qint64, qint64, const QByteArray &)),
		m_waveform, SLOT(bufferChanged(qint64, qint64, const QByteArray &)));
#endif
}

void SpectrumShow::createMenus()
{
	//Ϊ��ť�����˵�
	m_modeButton->setMenu(m_modeMenu);

	m_generateToneAction = m_modeMenu->addAction(tr("Play generated tone"));
	//¼��
	m_recordAction = m_modeMenu->addAction(tr("Record and play back"));
	//����
	m_loadFileAction = m_modeMenu->addAction(tr("Play file"));

	m_loadFileAction->setCheckable(true);
	m_generateToneAction->setCheckable(true);
	m_recordAction->setCheckable(true);

	connect(m_loadFileAction, SIGNAL(triggered(bool)), this, SLOT(showFileDialog()));
	connect(m_generateToneAction, SIGNAL(triggered(bool)), this, SLOT(showToneGeneratorDialog()));
	connect(m_recordAction, SIGNAL(triggered(bool)), this, SLOT(initializeRecord()));
}

void SpectrumShow::updateButtonStates()
{
	const bool recordEnabled = ((QAudio::AudioOutput == m_engine->mode() ||
		(QAudio::ActiveState != m_engine->state() &&
		QAudio::IdleState != m_engine->state())) &&
		RecordMode == m_mode);
	m_recordButton->setEnabled(recordEnabled);

	const bool pauseEnabled = (QAudio::ActiveState == m_engine->state() ||
		QAudio::IdleState == m_engine->state());
	m_pauseButton->setEnabled(pauseEnabled);

	const bool playEnabled = (/*m_engine->dataLength() &&*/
		(QAudio::AudioOutput != m_engine->mode() ||
		(QAudio::ActiveState != m_engine->state() &&
		QAudio::IdleState != m_engine->state())));
	m_playButton->setEnabled(playEnabled);
}

void SpectrumShow::reset()
{
#ifndef DISABLE_WAVEFORM
	m_waveform->reset();
#endif
	m_engine->reset();
	m_levelMeter->reset();
	m_spectrograph->reset();
	m_progressBar->reset();
}

void SpectrumShow::setMode(Mode mode)
{
	m_mode = mode;
	updateModeMenu();
}

void SpectrumShow::updateModeMenu()
{
	m_loadFileAction->setChecked(LoadFileMode == m_mode);
	m_generateToneAction->setChecked(GenerateToneMode == m_mode);
	m_recordAction->setChecked(RecordMode == m_mode);
}

