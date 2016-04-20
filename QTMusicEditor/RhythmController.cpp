#include "RhythmController.h"
#include "QPainter"
#include "Global.h"
#include "QTimer"
#include "QDebug"

RhythmController::RhythmController(QWidget* parent)
	:QWidget(parent)
{
	bmp = 120;
	music_offset = 0;
	position = 0;
	measure = 4;
	liasion = 2;
	clapSize = 50;
	m_isStart = false;
}

RhythmController::~RhythmController()
{
}

void RhythmController::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);
	auto rec = rect();
	QPen pen;
	pen.setColor(QColor(255, 255, 255));
	painter.setPen(pen);
	painter.drawLine(QLine(rec.left(), rec.bottom()-5, rec.right(), rec.bottom()-5));
	drawTargetRect(&painter);
	drawRhythm(&painter);
}

void RhythmController::drawTargetRect(QPainter* painter)
{
	QPen pen;
	pen.setColor(QColor(255, 0, 0));
	auto oldpen = painter->pen();
	painter->setPen(pen);
	auto rec = rect();
	QRect sourceRect(QPoint(rec.right()/3, rec.top()), QSize(2, rec.bottom() - rec.top()));
	painter->drawRect(sourceRect);
	painter->setPen(oldpen);
}

void RhythmController::drawRhythm(QPainter* painter)
{
	if (secVec.size() == 0)return;
	auto clapTime = 60000 / (double)bmp;
	auto rec = rect();
	auto size = rec.width() / clapSize + 1;
	auto widthpos = rec.right() / 3;
	int index = 0;
	double rate = clapTime / clapSize;
	m_startPos = m_curPos - widthpos * rate;
	for (int i = 0; i < secVec.size(); i++){ 
		auto section = secVec.at(i);
		if (section->endpos > m_startPos){
			index = i;
			break;
		}
	}
	auto section = secVec.at(index);
	auto off = section->startpos - m_startPos;
	off = off / rate;
	for (int i = index;; i++){
		int width = off + clapSize*measure*(i - index);
		if (width > rec.right()){
			break;
		}
		QRect re(QPoint(width, rec.bottom()-40), QSize(1, 35));
		painter->drawRect(re);
		drawClap(painter, width);
	}
}

void RhythmController::drawClap(QPainter* painter, qint64 width)
{
	int count = measure - 1;
	auto rec = rect();
	for (int i = 0; i <= count; i++){
		int width_ = width + i*clapSize;
		if (i != 0){
			QRect re(QPoint(width_, rec.bottom() - 30), QSize(1, 25));
			painter->drawRect(re);
		}
		QPen pen;
		pen.setColor(QColor(255, 0, 0));
		auto oldpen = painter->pen();
		painter->setPen(pen);
		for (int k = 1; k <= liasion - 1; k++){
			QRect re2(QPoint(width_ + k*(clapSize / liasion), rec.bottom() - 20), QSize(1, 15));
			painter->drawRect(re2);
		}
		painter->setPen(oldpen);
	}
}

void RhythmController::createRhythm()
{
	deleteRhythm();
	double per = 60000 / bmp;
	double liaison = per / liasion;
	double meaTime = per * measure;
	int nummea = (position - music_offset) / meaTime;
	int pos = music_offset;
	for (int i = 0; i < nummea; i++){
		SmallSection* section = new SmallSection;
		section->numClap = measure;
		section->claps = new SmallClap*[section->numClap];
		section->startpos = pos;
		section->endpos = pos + meaTime;
		int clapPos = pos;
		for (int k = 0; k < section->numClap; k++){
			clapPos += per * k;
			SmallClap* clap = new SmallClap;
			section->claps[k] = clap;
			clap->num = liasion;
			clap->poss = new qint64[clap->num];
			for (int n = 0; n < clap->num; n++){
				clap->poss[n] = clapPos + n*liaison;
			}
		}
		secVec.push_back(section);
		pos += meaTime;
	}
	m_curPos = 0;
	m_isStart = true;
}

void RhythmController::deleteRhythm()
{
	for (int i = 0; i < secVec.size(); i++){
		auto section = secVec.at(i);
		for (int k = 0; k < section->numClap; k++){
			auto clap = section->claps[k];
			delete[] clap->poss;
			delete[] clap;
		}
		delete section;
	}
	secVec.clear();
}

int RhythmController::transPosToWidth(qint64 pos)
{
	auto clapTime = 60000 / (double)bmp;
	double rate = clapTime / clapSize;
	auto off = pos - m_startPos;
	off = off / rate;
	return off;
}

void RhythmController::mousePressEvent(QMouseEvent * event)
{
}

void RhythmController::setPosition(qint64 pos)
{
	position = pos;
}

void RhythmController::setBmp(int bmp)
{
	this->bmp = bmp;
}

void RhythmController::setOffset(int off)
{
	music_offset = off;
}

void RhythmController::setMeasure(int num)
{
	this->measure = num;
}

void RhythmController::setLiasion(int num)
{
	liasion = num;
}

void RhythmController::setCurPos(qint64 pos)
{
	m_curPos = pos;
	this->update();
}