/*
 * ModernVolumeMeter.cpp - A volume meter widget for the Modern UI
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

#include <cmath>
#include <QtMath>

#include "ModernVolumeMeter.h"

ModernVolumeMeter::ModernVolumeMeter(QWidget *_parent, const QString &_name):
	QWidget( _parent )
{
	m_lValue = 0;
	m_rValue = 0;
	m_lValueRaw = 0;
	m_rValueRaw = 0;
	m_lActual = 0;
	m_rActual = 0;
	m_fallAmtPerFrame = 0.07;
}

ModernVolumeMeter::~ModernVolumeMeter()
{
}

void ModernVolumeMeter::updateValues(float l, float r)
{
	m_lActual = l;
	m_rActual = r;

	m_lValueRaw -= m_fallAmtPerFrame;
	m_rValueRaw -= m_fallAmtPerFrame;

	if (m_lActual > m_lValueRaw)
		m_lValueRaw = m_lActual;
	if (m_rActual > m_rValueRaw)
		m_rValueRaw = m_rActual;

	m_lValue = qPow(m_lValueRaw, 0.1);
	m_rValue = qPow(m_rValueRaw, 0.1);

	update();
}

float ModernVolumeMeter::rawToDb(float raw)
{
	return 10 * log10(raw);
}

void ModernVolumeMeter::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	QRect background = QRect(QPoint(0, 0), QSize(width(), height()));
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.setPen(Qt::NoPen);
	m_canvas.drawRect(background);

	int meterBackgroundWidth = width()/2 - s_borderWidth;

	QRect leftMeterBackground = QRect(QPoint(s_borderWidth, s_borderWidth), QSize(meterBackgroundWidth, height() - s_borderWidth*2));
	QRect rightMeterBackground = QRect(QPoint(s_borderWidth + meterBackgroundWidth + 1, s_borderWidth), QSize(meterBackgroundWidth, height() - s_borderWidth*2));
	m_canvas.setBrush(QBrush(QColor(61, 61, 61)));
	m_canvas.drawRect(leftMeterBackground);
	m_canvas.drawRect(rightMeterBackground);

	float clipPoint = 0.845;

	QRect leftMeter = QRect(QPoint(s_borderWidth, (height() - s_borderWidth*2) - (height() - s_borderWidth*2) * (m_lValue * clipPoint) + s_borderWidth), QPoint(width() - s_borderWidth - meterBackgroundWidth - s_borderWidth - 1, height() - s_borderWidth - 1));
	QRect rightMeter = QRect(QPoint(s_borderWidth + meterBackgroundWidth + 1, (height() - s_borderWidth*2) - (height() - s_borderWidth*2) * (m_rValue * clipPoint) + s_borderWidth), QPoint(width() - s_borderWidth - 1, height() - s_borderWidth - 1));
	QLinearGradient grad = QLinearGradient(QPoint(0, 0), QPoint(0, height()));
	grad.setColorAt(0, QColor(229, 0, 49));
	grad.setColorAt((1 - clipPoint - 0.001), QColor(229, 0, 49));
	grad.setColorAt((1 - clipPoint), QColor(229, 167, 0));
	grad.setColorAt(0.3010, QColor(229, 167, 0));
	grad.setColorAt(0.3011, QColor(10, 196, 140));
	grad.setColorAt(1, QColor(7, 132, 94));
	m_canvas.setBrush(grad);
	m_canvas.drawRect(leftMeter);
	m_canvas.drawRect(rightMeter);
}
