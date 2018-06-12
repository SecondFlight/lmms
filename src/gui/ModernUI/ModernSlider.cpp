/*
 * ModernSlider.cpp - A slider widget for the Modern UI
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

#include "ModernSlider.h"

ModernSlider::ModernSlider(QWidget *_parent, const QString &_name):
	QWidget(_parent)
{
	// You know, these should probably go in a constants file somewhere
	setMaximumWidth(18);
	setMinimumWidth(18);
	// height is to be set by whatever is creating the widget

	m_value = 0.8;
	m_inDragOperation = false;
}

ModernSlider::~ModernSlider()
{
}

void ModernSlider::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	//m_canvas.setRenderHint(QPainter::Antialiasing);

	float handleTop = getHandleTop();

	QRect grooveBackground = QRect(QPoint(s_handleWidth/2 - 2, 0), QSize(4, height()));
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.setPen(Qt::PenStyle::NoPen);
	m_canvas.drawRect(grooveBackground);

	QRect grooveHighlight = QRect(QPoint(s_handleWidth/2 - 1, handleTop + s_handleHeight/2), QPoint(s_handleWidth/2, height() - 2));	m_canvas.setBrush(QBrush(QColor(25, 126, 96)));
	m_canvas.drawRect(grooveHighlight);

	QRectF handleBackground = QRectF(QPointF(0, handleTop), QSizeF(s_handleWidth, s_handleHeight));
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.drawRect(handleBackground/*, 2, 2*/);

	QRectF handleInside = QRectF(QPointF(1, handleTop + 1), QSizeF(s_handleWidth - 3, s_handleHeight - 3));
	m_canvas.setBrush(QBrush(QColor(94, 94, 94)));
	m_canvas.setPen(QPen(QBrush(QColor(112, 112, 112)), 1));
	m_canvas.drawRect(handleInside/*, 2, 2*/);

	m_canvas.setPen(QPen(QBrush(QColor(202, 202, 202)), 1));
	m_canvas.drawLine(QPointF(4, handleTop + s_handleHeight/2), QPointF(s_handleWidth - 5, handleTop + s_handleHeight/2));
}

void ModernSlider::mousePressEvent(QMouseEvent *event)
{
	float handleTop = getHandleTop();
	float yVal = event->y();
	float handleBottom = handleTop + s_handleHeight;
	if (yVal > handleTop && yVal < handleBottom)
	{
		m_inDragOperation = true;
		m_mouseDistanceFromHandleTop = event->y() - handleTop;
	}
}

void ModernSlider::mouseMoveEvent(QMouseEvent *event)
{
	if (m_inDragOperation)
	{
		float y = event->y();
		float h = height();
		float potentialNewValue = (y - m_mouseDistanceFromHandleTop)/(h - s_handleHeight);// * ((height() - s_handleHeight)/height());
		if (potentialNewValue > 1)
			m_value = 1;
		else if (potentialNewValue < 0)
			m_value = 0;
		else
			m_value = potentialNewValue;
	}
	update();
}

void ModernSlider::mouseReleaseEvent(QMouseEvent *event)
{
	m_inDragOperation = false;
}

float ModernSlider::getHandleTop()
{
	return ((height() - s_handleHeight)) * m_value;
}
