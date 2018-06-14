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

#include "ModernVolumeMeter.h"

ModernVolumeMeter::ModernVolumeMeter(QWidget *_parent, const QString &_name):
	QWidget( _parent )
{
	m_lValue = 1;
	m_rValue = 0.8;
}

ModernVolumeMeter::~ModernVolumeMeter()
{
}

void ModernVolumeMeter::updateValues(float l, float r)
{
	m_lValue = l;
	m_rValue = r;
}

void ModernVolumeMeter::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	QRect background = QRect(QPoint(0, 0), QSize(width(), height()));
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.setPen(Qt::NoPen);
	m_canvas.drawRect(background);

	int meterBackgroundWidth = width()/2 - 3;

	QRect leftMeterBackground = QRect(QPoint(3, 3), QSize(meterBackgroundWidth, height() - 6));
	QRect rightMeterBackground = QRect(QPoint(3 + meterBackgroundWidth + 1, 3), QSize(meterBackgroundWidth, height() - 6));
	m_canvas.setBrush(QBrush(QColor(61, 61, 61)));
	m_canvas.drawRect(leftMeterBackground);
	m_canvas.drawRect(rightMeterBackground);

	QRect leftMeter = QRect(QPoint(3, (height() - 6) - (height() - 6) * m_lValue + 3), QPoint(width() - 3 - meterBackgroundWidth - 2, height() - 4));
	QRect rightMeter = QRect(QPoint(3 + meterBackgroundWidth + 1, (height() - 6) - (height() - 6) * m_rValue + 3), QPoint(width() - 4, height() - 4));
	QLinearGradient grad = QLinearGradient(QPoint(0, 0), QPoint(0, height()));
	grad.setColorAt(0, QColor(10, 195, 140));
	grad.setColorAt(1, QColor(70, 131, 94));
	m_canvas.setBrush(grad);
	m_canvas.drawRect(leftMeter);
	m_canvas.drawRect(rightMeter);
}
