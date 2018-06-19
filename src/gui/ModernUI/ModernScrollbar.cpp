/*
 * ModernScrollbar.cpp - A scrollbar widget for the Modern UI
 *
 * Copyright (c) 2018 Joshua Wade <lastname/firstinitial/at/southern/dot/edu>
 * Original UI design by Budislav Stepanov
 *
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include "ModernScrollbar.h"

#include <QMouseEvent>
#include <QHoverEvent>

ModernScrollbar::ModernScrollbar(QWidget *_parent, const QString &_name):
	QWidget(_parent)
{
	m_startValue = 0;
	m_endValue = 1;
	m_totalSize = 1;
	m_isHorizontal = false;
	m_tickSize = 0.05;
	m_minimumWidth = 0.05;
	m_isInDragOperation = false;
	m_isInStartMoveOperation = false;
	m_isInEndMoveOperation = false;
	m_isHandleResizingEnabled = true;
	m_handleInsideColor = s_handleShade;

	m_lazyFollower = new LazyFollower(this, 1, {s_handleShade}, {0.6});

	this->setMouseTracking(true);
}

ModernScrollbar::~ModernScrollbar()
{
	delete m_lazyFollower;
}

void ModernScrollbar::setFollowValues(QVector<float> values)
{
	m_handleInsideColor = values[0];
	update();
}

void ModernScrollbar::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	QColor borderColor = QColor(43, 43, 43);
	QColor backgroundColor = QColor(54, 54, 54);
	QColor handleColor = QColor(m_handleInsideColor, m_handleInsideColor, m_handleInsideColor);
	QColor handleBorderColor = QColor(112, 112, 112);

	QRect border = QRect(QPoint(0, 0), QPoint(width(), height()));
	m_canvas.setPen(Qt::NoPen);
	m_canvas.setBrush(QBrush(borderColor));
	m_canvas.drawRect(border);

	QRect background = QRect(QPoint(1, 1), QPoint(width() - 2, height() - 2));
	m_canvas.setBrush(QBrush(backgroundColor));
	m_canvas.drawRect(background);

	m_canvas.setRenderHint(QPainter::Antialiasing);

	if (m_isHorizontal)
	{
		drawArrow(&m_canvas, ModernScrollbar::LEFT);
		drawArrow(&m_canvas, ModernScrollbar::RIGHT);
	}
	else
	{
		drawArrow(&m_canvas, ModernScrollbar::UP);
		drawArrow(&m_canvas, ModernScrollbar::DOWN);
	}

	QRectF handle;

	if (m_isHorizontal)
		handle = QRectF(QPointF(16.5 + m_startValue*m_totalSize*(width()-33), 1.5), QPointF(16.5 + m_endValue*m_totalSize*(width()-33), height() - 1.5));
	else
		handle = QRectF(QPointF(1.5, 16.5 + m_startValue*m_totalSize*(height()-33)), QPointF(width() - 1.5, 16.5 + m_endValue*m_totalSize*(height()-33)));
	m_canvas.setBrush(QBrush(handleColor));
	m_canvas.setPen(QPen(QBrush(handleBorderColor), 1));
	m_canvas.drawRoundedRect(handle, 0.2, 0.2);
}

void ModernScrollbar::mousePressEvent(QMouseEvent *event)
{
	if (m_isHorizontal)
	{
		if (event->x() < height())
		{
			tickBackward();
			return;
		}
		else if (event->x() > (width() - height()))
		{
			tickForward();
			return;
		}
	}
	else
	{
		if (event->y() < width())
		{
			tickBackward();
			return;
		}
		else if (event->y() > (height() - width()))
		{
			tickForward();
			return;
		}
	}

	float mousePosValue = mousePosToValue(event->pos());

	if (m_isHandleResizingEnabled && qAbs(valueToPixels(mousePosValue) - valueToPixels(m_startValue)) < 3)
	{
		m_delta = mousePosToValue(event->pos()) - m_startValue;
		m_isInStartMoveOperation = true;
	}
	else if (m_isHandleResizingEnabled && qAbs(valueToPixels(mousePosValue) - valueToPixels(m_endValue)) < 3)
	{
		m_delta = mousePosToValue(event->pos()) - m_endValue;
		m_isInEndMoveOperation = true;
	}
	else if (mousePosValue > m_startValue && mousePosValue < m_endValue)
	{
		m_delta = mousePosToValue(event->pos()) - m_startValue;
		m_isInDragOperation = true;
	}
	// At this point we've ruled everything out except pageup/pagedown
	else
	{
		float delta = m_endValue - m_startValue;
		if (mousePosValue > m_endValue)
		{
			m_startValue += delta;
			m_endValue += delta;
		}
		else if (mousePosValue < m_startValue)
		{
			m_startValue -= delta;
			m_endValue -= delta;
		}
		update();
	}
}

void ModernScrollbar::mouseMoveEvent(QMouseEvent *event)
{
	float mousePosValue = mousePosToValue(event->pos());

	if (m_isInDragOperation || m_isInStartMoveOperation || m_isInEndMoveOperation ||
			(mousePosValue > m_startValue && mousePosValue < m_endValue))
		m_lazyFollower->updateTarget(0, s_handleClickedShade);
	else
		m_lazyFollower->updateTarget(0, s_handleShade);

	if (m_isInDragOperation)
	{
		tryMoveTo(mousePosToValue(event->pos()) - m_delta);
		return;
	}

	if (m_isInStartMoveOperation)
	{
		tryMoveStartTo(mousePosToValue(event->pos()) - m_delta);
		return;
	}

	if (m_isInEndMoveOperation)
	{
		tryMoveEndTo(mousePosToValue(event->pos()) - m_delta);
		return;
	}

	if (m_isHandleResizingEnabled &&
			(qAbs(valueToPixels(mousePosValue) - valueToPixels(m_startValue)) < 3 ||
			qAbs(valueToPixels(mousePosValue) - valueToPixels(m_endValue)) < 3))
	{
		if (m_isHorizontal)
			this->setCursor(Qt::SizeHorCursor);
		else
			this->setCursor(Qt::SizeVerCursor);
		m_lazyFollower->updateTarget(0, s_handleClickedShade);
	}
	else
		this->setCursor(Qt::ArrowCursor);
}

void ModernScrollbar::mouseReleaseEvent(QMouseEvent *event)
{
	m_isInDragOperation = false;
	m_isInStartMoveOperation = false;
	m_isInEndMoveOperation = false;
}

/*void ModernScrollbar::enterEvent(QEvent *event)
{

}*/

void ModernScrollbar::leaveEvent(QEvent *event)
{
	m_lazyFollower->updateTarget(0, s_handleShade);
}

float ModernScrollbar::mousePosToValue(QPoint pos)
{
	float pixelOffset;

	if (m_isHorizontal)
	{
		pixelOffset = pos.x();
		return (pixelOffset - height()) / (width() - (height() * 2));
	}
	else
	{
		pixelOffset = pos.y();
		return (pixelOffset - width()) / (height() - (width() * 2));
	}
}

float ModernScrollbar::valueToPixels(float value)
{
	int scrollbarSize;
	if (m_isHorizontal)
		scrollbarSize = width() - (height() * 2);
	else
		scrollbarSize = height() - (width() * 2);

	return (value * scrollbarSize) / m_totalSize;
}

void ModernScrollbar::tryMoveTo(float newStartValue)
{
	float currentWidth = m_endValue - m_startValue;

	if (newStartValue < 0)
	{
		m_endValue = m_endValue - m_startValue;
		m_startValue = 0;
	}
	else if (newStartValue > m_totalSize - currentWidth)
	{
		m_startValue = m_totalSize - currentWidth;
		m_endValue = m_totalSize;
	}
	else
	{
		m_startValue = newStartValue;
		m_endValue = newStartValue + currentWidth;
	}
	update();
}

void ModernScrollbar::tryMoveStartTo(float newStartValue)
{
	if (newStartValue < 0)
		m_startValue = 0;
	else if (newStartValue > (m_endValue - m_minimumWidth))
		m_startValue = m_endValue - m_minimumWidth;
	else
		m_startValue = newStartValue;
	update();
}

void ModernScrollbar::tryMoveEndTo(float newEndValue)
{
	if (newEndValue > m_totalSize)
		m_endValue = m_totalSize;
	else if (newEndValue < (m_startValue + m_minimumWidth))
		m_endValue = m_startValue + m_minimumWidth;
	else
		m_endValue = newEndValue;
	update();
}

void ModernScrollbar::setVertical()
{
	m_isHorizontal = false;
}

void ModernScrollbar::setHorizontal()
{
	m_isHorizontal = true;
}

void ModernScrollbar::setStart(float start)
{
	m_startValue = start;
	update();
}

void ModernScrollbar::setWidth(float width)
{
	m_endValue = width + m_startValue;
	update();
}

void ModernScrollbar::setTotalSize(float size)
{
	m_totalSize = size;
	update();
}

void ModernScrollbar::drawArrow(QPainter* canvas, Direction direction)
{
	QPointF top;
	QPointF bottom1;
	QPointF bottom2;

	if (direction == ModernScrollbar::LEFT)
	{
		top = QPointF(5, height()/2.0);
		bottom1 = QPointF(11, 4);
		bottom2 = QPointF(11, height() - 4);
	}
	else if (direction == ModernScrollbar::RIGHT)
	{
		top = QPointF(width() - 5, height()/2.0);
		bottom1 = QPointF(width() - 11, 4);
		bottom2 = QPointF(width() - 11, height() - 4);
	}
	else if (direction == ModernScrollbar::UP)
	{
		top = QPointF(width()/2.0, 5);
		bottom1 = QPointF(4, 11);
		bottom2 = QPointF(width() - 4, 11);
	}
	else if (direction == ModernScrollbar::DOWN)
	{
		top = QPointF(width()/2.0, height() - 5);
		bottom1 = QPointF(4, height() - 11);
		bottom2 = QPointF(width() - 4, height() - 11);
	}

	QPainterPath path;
	path.moveTo(top);
	path.lineTo(bottom1);
	path.lineTo(bottom2);

	canvas->setPen(QPen(QColor(137, 137, 137)));
	canvas->fillPath(path, QColor(137, 137, 137));
}

void ModernScrollbar::tickForward()
{
	if (m_endValue + m_tickSize <= m_totalSize)
	{
		m_startValue += m_tickSize;
		m_endValue += m_tickSize;
	}
	else
	{
		if (qAbs(m_totalSize - m_endValue) < 0.0005)
			return;

		float actualTickSize = m_totalSize - m_endValue;

		m_startValue += actualTickSize;
		m_endValue += actualTickSize;
	}
	update();
}

void ModernScrollbar::tickBackward()
{
	if (m_startValue - m_tickSize >= 0)
	{
		m_startValue -= m_tickSize;
		m_endValue -= m_tickSize;
	}
	else
	{
		if (m_startValue < 0.0005)
			return;

		m_endValue -= m_startValue;
		m_startValue -= m_startValue;
	}
	update();
}

void ModernScrollbar::setMinimumScrollbarWidth(float width)
{
	m_minimumWidth = width;
}

void ModernScrollbar::setHandleResizingEnabled(bool enabled)
{
	m_isHandleResizingEnabled = enabled;
}
