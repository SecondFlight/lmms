/*
 * ModernToggleSwitch.cpp - A toggle switch widget for the Modern UI
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

#include "ModernToggleSwitch.h"

ModernToggleSwitch::ModernToggleSwitch(QWidget *_parent, const QString &_name):
	QWidget(_parent)
{
	m_value = false;
}

ModernToggleSwitch::~ModernToggleSwitch()
{
}

void ModernToggleSwitch::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	// I don't think I want antialiasing here. I have gradients, but
	// this is a square widget and I want the edges to be crisp.
	//m_canvas.setRenderHint(QPainter::RenderHint::Antialiasing);

	QRect lightBackground = QRect(QPoint(1, 1), QPoint(width() - 1, height() - 1));
	QLinearGradient lightBackgroundGradient = QLinearGradient(QPoint(0, 2), QPoint(0, height() - 1));
	lightBackgroundGradient.setColorAt(0, QColor(36, 43, 50));
	lightBackgroundGradient.setColorAt(1, QColor(29, 33, 39));
	m_canvas.setPen(Qt::PenStyle::NoPen);
	QBrush brush = QBrush(lightBackgroundGradient);
	m_canvas.setBrush(brush);
	m_canvas.drawRect(lightBackground);
}

void ModernToggleSwitch::mousePressEvent(QMouseEvent *event)
{
	m_value = !m_value;
	update();
}
