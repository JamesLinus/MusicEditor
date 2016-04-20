#pragma once
#include <QWidget>
#include "QTime"

class QPainter;
class RhythmController : public QWidget
{
	Q_OBJECT
public:
	RhythmController(QWidget* parent = 0);
	~RhythmController();

	void setPosition(qint64 pos);
	void setBmp(int bmp);
	void setOffset(int offset);
	void createRhythm();
	void setMeasure(int num);
	void setLiasion(int num);
	void setCurPos(qint64 pos);
protected:
	struct SmallClap{
		qint64* poss;
		int num = 0;
	};
	struct SmallSection{
		int startpos = 0;
		int endpos = 0;
		int numClap = 0;
		SmallClap** claps = NULL;
	};
	void paintEvent(QPaintEvent * event);
	void drawTargetRect(QPainter* painter);
	void drawRhythm(QPainter* painter);
	void drawClap(QPainter* painter, qint64 width);
	void deleteRhythm();
	void mousePressEvent(QMouseEvent *);
	int transPosToWidth(qint64 pos);
private slots:


private:
	

protected:
	int				bmp;
	//��ʼ��ƫ��
	int				music_offset;
	//���ֵ�ʱ��
	qint64			position;
	//ÿһ����ʲô����
	int				liasion;
	//һС�ڶ�����
	int				measure;

	int				clapSize;
	int				m_curPos;
	bool			m_isStart;
	qint64			m_startPos;
	QVector<SmallSection*> secVec;
};

