/*
 * ModernButton.cpp - A button widget for the Modern UI
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

#include "ModernButton.h"

ModernButton::ModernButton(QWidget *_parent, const QString &_name):
	QWidget(_parent)
{
	m_value = false;
}

ModernButton::~ModernButton()
{
}

void ModernButton::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	m_canvas.setRenderHint(QPainter::Antialiasing);

	QRectF handleBackground = QRectF(QPointF(0, 0), QSizeF(width(), height()));
	m_canvas.setPen(Qt::NoPen);
	m_canvas.setBrush(QBrush(QColor(43, 43, 43)));
	m_canvas.drawRoundedRect(handleBackground, 1, 1);

	QRectF handleInside = QRectF(QPointF(1.5, 1.5), QSizeF(width() - 3, height() - 3));
	m_canvas.setBrush(QBrush(QColor(94, 94, 94)));
	m_canvas.setPen(QPen(QBrush(QColor(112, 112, 112)), 1));
	m_canvas.drawRoundedRect(handleInside, 0.25, 0.25);
}

void ModernButton::mousePressEvent(QMouseEvent *event)
{
}
