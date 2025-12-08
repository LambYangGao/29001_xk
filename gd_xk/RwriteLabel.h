#include <qlabel.h>
#include <qobject.h>
#include<QMouseEvent>
#include <qpainter.h>
#include <qpoint.h>
#include<iostream>
#include<qdebug.h>
class RectLabel :public QLabel
{
	Q_OBJECT
public:
	explicit RectLabel(QWidget* parent = 0);
protected:
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* p);
private:
	bool isPressedWidget;
	QPoint m_startPT;
	QPoint m_endPT;
signals:
	void sig_painter_size(QPoint startPT, QPoint endPT,float width, float height);
	void sig_current_wind(bool currentState);
};
