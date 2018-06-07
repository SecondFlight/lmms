/*
 * ModernKnob.cpp - A knob widget for the Modern UI
 *
 * Copyright (c) 2018 Joshua Wade <lastname/firstinitial/at/southern/dot/edu>
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

#include "ModernKnob.h"

ModernKnob::ModernKnob(QWidget * _parent, const QString & _name):
	QWidget( _parent )
{

}

ModernKnob::~ModernKnob()
{
}

void ModernKnob::paintEvent(QPaintEvent *event)
{
	QPainter m_canvas(this);

	m_canvas.setRenderHint(QPainter::RenderHint::Antialiasing);

	QPen pen = QPen(QColor(26, 218, 225));
	pen.setWidthF(3.3);
	m_canvas.setPen(pen);

	QRectF rectangle = QRectF(QPointF(1.5, 1.5), QSizeF(width()-3, height()-3));
	m_canvas.drawArc(rectangle, -(360*16*3)/20, (360*16*8)/10);

	m_canvas.setBackground(QBrush(QColor(255, 0, 0)));
}
