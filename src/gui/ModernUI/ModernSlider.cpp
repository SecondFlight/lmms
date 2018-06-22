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
	m_value = 0.8;
	m_inDragOperation = false;
	m_handleInsideColorLight = s_handleInsideColorLight;
	m_handleInsideColorDark = s_handleInsideColorDark;
	m_handleOutsideColorLight = s_handleOutsideColorLight;
	m_handleOutsideColorDark = s_handleOutsideColorDark;
	m_handleSquish = 1 - (s_handleHeight - 3)/(float)s_handleHeight;
	m_lazyFollower = new LazyFollower(this, 6, {m_value, m_handleInsideColorLight, m_handleInsideColorDark, m_handleOutsideColorLight, m_handleOutsideColorDark, m_handleSquish}, {0.6, 0.6, 0.6, 0.6, 0.6, 0.85});
	m_highlightColor = QColor(22, 156, 116);
	setMouseTracking(true);
}

ModernSlider::~ModernSlider()
{
	delete m_lazyFollower;
}

void ModernSlider::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	float yScaleFactor = getScaleFactor();
	float handleTop = getHandleTop()*yScaleFactor;
	m_canvas.scale(width()/(float)s_handleWidth, width()/(float)s_handleWidth);

	// background groove
	QRect grooveBackground = QRect(QPoint(s_handleWidth/2 - 2, 0), QSize(4, height() * yScaleFactor));
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.setPen(Qt::NoPen);
	m_canvas.drawRect(grooveBackground);

	QRect grooveHighlight = QRect(QPoint(s_handleWidth/2 - 1, handleTop + s_handleHeight/2), QPoint(s_handleWidth/2, height() * yScaleFactor - 2));
	m_canvas.setBrush(QBrush(m_highlightColor));
	m_canvas.drawRect(grooveHighlight);



	// handle
	m_canvas.setRenderHint(QPainter::Antialiasing);

	QRectF handleBackground = QRectF(QPointF(0, handleTop), QSizeF(s_handleWidth, s_handleHeight));
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.drawRoundedRect(handleBackground, 2, 2);

	QRectF handleOutside = QRectF(QPointF(1, handleTop + 1), QSizeF(s_handleWidth - 2, s_handleHeight - 2));
	QLinearGradient handleOutsideGrad = QLinearGradient(QPointF(0, handleTop), QPointF(0, handleTop + s_handleHeight));
	handleOutsideGrad.setColorAt(0, QColor(m_handleOutsideColorLight, m_handleOutsideColorLight, m_handleOutsideColorLight));
	handleOutsideGrad.setColorAt(1, QColor(m_handleOutsideColorDark, m_handleOutsideColorDark, m_handleOutsideColorDark));
	m_canvas.setBrush(QBrush(handleOutsideGrad));
	m_canvas.drawRoundedRect(handleOutside, 2, 2);

	QRectF handleInside = QRectF(QPointF(1, handleTop + s_handleHeight*m_handleSquish), QPointF(s_handleWidth - 1, handleTop + s_handleHeight - (m_handleSquish*s_handleHeight)));
	int lightShade = m_handleInsideColorLight;
	int darkShade = m_handleInsideColorDark;
	QLinearGradient handleInsideGrad = QLinearGradient(QPointF(0, handleTop + (m_handleSquish*s_handleHeight)), QPointF(0, handleTop + s_handleHeight - (m_handleSquish*s_handleHeight)));

	// Slight color increase for the top of the handle inside
	// yay shading
	handleInsideGrad.setColorAt(0, QColor(darkShade + 5, darkShade + 5, darkShade + 5));
	handleInsideGrad.setColorAt(0.5, QColor(lightShade, lightShade, lightShade));
	handleInsideGrad.setColorAt(1, QColor(darkShade, darkShade, darkShade));

	m_canvas.setBrush(QBrush(handleInsideGrad));
	m_canvas.drawRoundedRect(handleInside, 1, 1);

	m_canvas.setPen(QPen(QBrush(m_highlightColor), 1));
	m_canvas.drawLine(QPointF(1.5, handleTop + s_handleHeight/2 + 0.5), QPointF(s_handleWidth - 1.5, handleTop + s_handleHeight/2 + 0.5));
}

void ModernSlider::mousePressEvent(QMouseEvent *event)
{
	if (isMouseYInsideHandle(event->y()))
	{
		this->setCursor(Qt::BlankCursor);
		m_storedCursorPos = cursor().pos();
		m_potentialNewValue = m_value;
		int handleTop = getHandleTop();
		m_inDragOperation = true;
		m_mouseDistanceFromHandleTop = event->y() - handleTop;
		m_lazyFollower->updateTarget(1, s_handleInsideColorLightClicked);
		m_lazyFollower->updateTarget(2, s_handleInsideColorDarkClicked);
		m_lazyFollower->updateTarget(3, s_handleOutsideColorLightClicked);
		m_lazyFollower->updateTarget(4, s_handleOutsideColorDarkClicked);
	}
	update();
}

void ModernSlider::mouseMoveEvent(QMouseEvent *event)
{
	if (m_inDragOperation)
	{
		float delta = m_storedCursorPos.y() - cursor().pos().y();
		QCursor c = cursor();
		c.setPos(m_storedCursorPos);
		setCursor(c);
		m_potentialNewValue += delta*s_movementScalingFactor;
		if (m_potentialNewValue > 1)
			m_lazyFollower->updateTarget(0, 1);
		else if (m_potentialNewValue < 0)
			m_lazyFollower->updateTarget(0, 0);
		else
			m_lazyFollower->updateTarget(0, m_potentialNewValue);
	}

	if (isMouseYInsideHandle(event->y()))
	{
		m_lazyFollower->updateTarget(5, 1 - (s_handleHeight - 5)/(float)s_handleHeight);
	}
	else
	{
		m_lazyFollower->updateTarget(5, 1 - (s_handleHeight - 3)/(float)s_handleHeight);
	}
}

void ModernSlider::mouseReleaseEvent(QMouseEvent *event)
{
	this->setCursor(Qt::ArrowCursor);

	// Set cursor position to the middle of the handle
	QCursor c = cursor();
	float scaleFactor = 1 - getScaleFactor();
	c.setPos(this->mapToGlobal(QPoint(width()/2, (s_handleHeight/scaleFactor) + (1 - m_value)*height()*scaleFactor)));
	setCursor(c);

	m_inDragOperation = false;
	m_lazyFollower->updateTarget(1, s_handleInsideColorLight);
	m_lazyFollower->updateTarget(2, s_handleInsideColorDark);
	m_lazyFollower->updateTarget(3, s_handleOutsideColorLight);
	m_lazyFollower->updateTarget(4, s_handleOutsideColorDark);
	update();
}

void ModernSlider::leaveEvent(QEvent *event)
{
	m_lazyFollower->updateTarget(5, 1 - (s_handleHeight - 3)/(float)s_handleHeight);
}

bool ModernSlider::isMouseYInsideHandle(int y)
{
	float handleTop = getHandleTop();
	float handleBottom = handleTop + s_handleHeight*(1/getScaleFactor());
	return y > handleTop && y < handleBottom;
}

void ModernSlider::setFollowValues(QVector<float> values)
{
	m_value = values[0];
	m_handleInsideColorLight = values[1];
	m_handleInsideColorDark = values[2];
	m_handleOutsideColorLight = values[3];
	m_handleOutsideColorDark = values[4];
	m_handleSquish = values[5];
	update();
}

int ModernSlider::getHandleTop()
{
	return qRound(((height() - s_handleHeight*(1/getScaleFactor()))) * (1 - m_value));
}

float ModernSlider::getScaleFactor()
{
	return s_handleWidth/(float)width();
}

void ModernSlider::setMuted()
{
	m_highlightColor = QColor(49, 49, 49);
	update();
}

void ModernSlider::setUnmuted()
{
	m_highlightColor = QColor(22, 156, 116);
	update();
}
