#include"RwriteLabel.h"
RectLabel::RectLabel(QWidget* parent)
{
	
}

void RectLabel::mouseReleaseEvent(QMouseEvent* event)
{
	isPressedWidget = false;
	if (event->button() == Qt::LeftButton)
	{
		
		if (m_startPT.x() > m_endPT.x() && m_startPT.y() > m_endPT.y())
		{
			QPoint tmp = m_startPT;
			m_startPT = m_endPT;
			m_endPT = tmp;
		}
	}
	
}

void RectLabel::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		if (isPressedWidget)
		{
			m_endPT = event->pos();
			if (abs(m_endPT.x()) > this->width())
			{
				m_endPT.setX(this->width());
			}
			if (abs(m_endPT.y()) > this->height())
			{
				m_endPT.setY(this->height());
			}
			if (m_endPT.x() < 0)
			{
				m_endPT.setX(0);
			}
			if (m_endPT.y() < 0)
			{
				m_endPT.setY(0);
			}
			update();
		}
	}
}

void RectLabel::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		emit sig_current_wind(true);
		m_endPT = m_startPT = event->pos();
		isPressedWidget = true;
		update();
	}
	else if(event->buttons() == Qt::RightButton)
	{
		emit sig_current_wind(true);
		isPressedWidget = false;
		update();
		
		
	}
	
	//QLabel::mousePressEvent(event);
}

void RectLabel::paintEvent(QPaintEvent* e)
{
	QLabel::paintEvent(e);
	QPainter painter(this);
	if (isPressedWidget)
	{
		QRect rect = QRect(m_startPT, m_endPT);
		painter.drawRect(rect);
		float painter_width = m_endPT.x() - m_startPT.x();
		float painter_height= m_endPT.y() - m_startPT.y();

		//qDebug()<< "painter_width:" << painter_width << ",painter_height:" << painter_height;
		if (painter_width < 0 && painter_height < 0)
		{
			emit sig_painter_size(m_endPT, m_startPT, painter_width, painter_height);
		}
		else
		{
			emit sig_painter_size(m_startPT, m_endPT, painter_width, painter_height);
		}
	}




}