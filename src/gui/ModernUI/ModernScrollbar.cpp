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

ModernScrollbar::ModernScrollbar(QWidget *_parent, const QString &_name):
	QWidget(_parent)
{
	m_startValue = 0;
	m_endValue = 1;
	m_isHorizontal = false;
}

ModernScrollbar::~ModernScrollbar()
{
}

void ModernScrollbar::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	QColor borderColor = QColor(43, 43, 43);
	QColor backgroundColor = QColor(54, 54, 54);
	QColor handleColor = QColor(94, 94, 94);
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
		handle = QRectF(QPointF(16.5 + m_startValue*(width()-33), 1.5), QPointF(16.5 + m_endValue*(width()-33), height() - 1.5));
	else
		handle = QRectF(QPointF(1.5, 16.5 + m_startValue*(height()-33)), QPointF(width() - 1.5, 16.5 + m_endValue*(height()-33)));
	m_canvas.setBrush(QBrush(handleColor));
	m_canvas.setPen(QPen(QBrush(handleBorderColor), 1));
	m_canvas.drawRoundedRect(handle, 0.2, 0.2);
}

void ModernScrollbar::mousePressEvent(QMouseEvent *event)
{
}

void ModernScrollbar::setVertical()
{
	m_isHorizontal = false;
}

void ModernScrollbar::setHorizontal()
{
	m_isHorizontal = true;
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
