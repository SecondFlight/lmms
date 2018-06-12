/*
 * ModernKnob.cpp - A knob widget for the Modern UI
 * Original UI design by Budislav Stepanov
 *
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
	m_value = 0.5;
	m_mousePressed = false;
	m_followValue = 0.5;
	m_follower = new LazyFollower(this, 0.5, 0.8);
}

ModernKnob::~ModernKnob()
{
}

void ModernKnob::paintEvent(QPaintEvent *event)
{
	/*
	 * Hi!
	 * Here are some notes about quirks as I develop them:
	 *
	 *
	 * You may see lines like this a lot:
	 * pen.setWidthF(width()/(35/3.3));
	 * This one is just a few lines down.
	 *
	 * Here's what's going on: I designed this based on
	 * Budislav's 35-pixel knob (the bigger one of the two
	 * in his design). The math here is saying, "What is 3.3
	 * pixels out of 35 possible when the entire knob is
	 * scaled up to {width()} pixels?"
	 *
	 *
	 *
	 * DrawArc takes 16ths of a degree as input. The angle
	 * measurements start at zero pointing right, and count
	 * up turning counterclockwise, just like you probably
	 * learned in math.
	 *
	 *
	 *
	 * There are a few lines that have something like this:
	 * ...width()/(35/(width()*0.001 + 14.5))...
	 * This is to modify a value depending on how big the
	 * knob is. The shadows tend to stand out too much
	 * when the knob is >100 pixels big.
	 */

	QPainter m_canvas(this);

	m_canvas.setRenderHint(QPainter::RenderHint::Antialiasing);

	QPen pen = QPen(QColor(70, 81, 94));
	pen.setWidthF(width()/(35/3.3));
	pen.setCapStyle(Qt::FlatCap);
	m_canvas.setPen(pen);

	float outerRingTopLeft = width()/(35/1.7);
	float outerRingSize = width() - width()/(35/3.4);

	QRectF outerRingRect = QRectF(QPointF(outerRingTopLeft, outerRingTopLeft), QSizeF(outerRingSize, outerRingSize));
	m_canvas.drawArc(outerRingRect, -(360*16*7)/20, -(360*16*8)/10);

	pen = QPen(QColor(26, 218, 225));
	pen.setCapStyle(Qt::FlatCap);
	pen.setWidthF(width()/(35/3.3));
	m_canvas.setPen(pen);

	m_canvas.drawArc(outerRingRect, -(360*16*7)/20, -(360*16*8*m_followValue)/10);

	// Maybe gradient this to transparent for bigger sizes?
	float darkCircleTopLeft = width()/(35/6.0);
	float darkCircleSize = width() - width()/(35/12.0);
	QRectF darkCircleRect = QRectF(QPointF(darkCircleTopLeft, darkCircleTopLeft), QSizeF(darkCircleSize, darkCircleSize));
	QRadialGradient darkCircleGrad = QRadialGradient(QPointF(width()/2.0, height()/2.0), width()/(35/11.5)); // 11.5 doesn't look good at very large sizes
	darkCircleGrad.setColorAt(0, QColor(30, 33, 37));
	darkCircleGrad.setColorAt(0.95, QColor(30, 33, 37));
	darkCircleGrad.setColorAt(1, QColor(0, 0, 0, 0));
	QBrush brush = QBrush(darkCircleGrad);
	m_canvas.setPen(Qt::PenStyle::NoPen);
	m_canvas.setBrush(brush);
	m_canvas.drawEllipse(darkCircleRect);

	float lightCircleTopLeft = width()/(35/7.0);
	float lightCircleSize = width() - width()/(35/14.0);
	QRectF lightCircleRect = QRectF(QPointF(lightCircleTopLeft, lightCircleTopLeft), QSizeF(lightCircleSize, lightCircleSize));
	// This will need to be rotated depending on the knob value
	QLinearGradient lightCircleGrad = QLinearGradient(QPointF(width()/2, width()/(35/7.0)), QPointF(width()/2, width() - width()/(35/14.0)));
	lightCircleGrad.setColorAt(0, QColor(91, 109, 127));
	lightCircleGrad.setColorAt(0.5, QColor(82, 96, 113));
	lightCircleGrad.setColorAt(1, QColor(73, 85, 99));
	brush = QBrush(lightCircleGrad);
	m_canvas.setBrush(brush);
	m_canvas.drawEllipse(lightCircleRect);

	float highlightCircleTopLeft = width()/(35/(8.0 - width()*.002));
	float highlightCircleSize = width() - width()/(35/(16.0 - width()*.004));
	QRectF highlightCircleRect = QRectF(QPointF(highlightCircleTopLeft, highlightCircleTopLeft), QSizeF(highlightCircleSize, highlightCircleSize));
	QRadialGradient highlightCircleGrad = QRadialGradient(QPointF(width()/2.0, height()/4.0), width()/(35/11.5));
	highlightCircleGrad.setColorAt(0, QColor(121, 135, 151));
	//highlightCircleGrad.setColorAt(0.95, QColor(30, 33, 37));
	highlightCircleGrad.setColorAt(1, QColor(0, 0, 0, 0));
	pen = QPen(QBrush(highlightCircleGrad), width()/(35/(2.0 - width()*.004)));
	m_canvas.setPen(pen);
	m_canvas.setBrush(Qt::BrushStyle::NoBrush);
	m_canvas.drawArc(highlightCircleRect, 0, 16*180);
	m_canvas.setPen(Qt::PenStyle::NoPen);

	m_canvas.translate(width()*.5, height()*.5);
	m_canvas.rotate((m_value - 0.5) * 360 * (4.0/5));

	//-(width()*.5) fixes centering
	QRectF markerRect = QRectF(QPointF(width()/2.0 - width()/(35/1.5)-(width()*.5), height()/2.0 - height()/(35/10.5)-(width()*.5)), QSizeF(width()/(35/3.0), height()/(35/8.0)));
	QRectF markerShadowRectLeft = QRectF(QPointF(width()/2.0 - width()/(35/3.5)-(width()*.5), height()/2.0 - height()/(35/10.5)-(width()*.5)), QSizeF(width()/(35/3.0), height()/(35/8.0)));
	QRectF markerShadowRectRight = QRectF(QPointF(width()/2.0 + width()/(35/1.5)-(width()*.5), height()/2.0 - height()/(35/10.5)-(width()*.5)), QSizeF(width()/(35/3.0), height()/(35/8.0)));
	QRectF markerShadowRectBottom = QRectF(QPointF(width()/2.0 - width()/(35/2.5)-(width()*.5), height()/2.0 - height()/(35/2.5)-(width()*.5)), QSizeF(width()/(35/5.0), height()/(35/2.0)));

	QRadialGradient markerShadowGradLeft = QRadialGradient(QPointF(width()/2.0 + width()/(35/(width() * 0.003 + 13.8))-(width()*.5), height()/2.0 - height()/(35/7.0)-(width()*.5)), width()/(35/16.95));
	markerShadowGradLeft.setColorAt(0, QColor(30, 37, 46));
	markerShadowGradLeft.setColorAt(0.9, QColor(30, 37, 46));
	markerShadowGradLeft.setColorAt(1, QColor(0, 0, 0, 0));

	QRadialGradient markerShadowGradRight = QRadialGradient(QPointF(width()/2.0 - width()/(35/(width() * 0.003 + 13.8))-(width()*.5), height()/2.0 - height()/(35/7.0)-(width()*.5)), width()/(35/16.95));
	markerShadowGradRight.setColorAt(0, QColor(30, 37, 46));
	markerShadowGradRight.setColorAt(0.9, QColor(30, 37, 46));
	markerShadowGradRight.setColorAt(1, QColor(0, 0, 0, 0));

	QRadialGradient markerShadowGradBottom = QRadialGradient(QPointF(/*width()/2.0-(width()*.5)*/0, height()/2.0 - height()/(35/(2.7 + width()*.003))-(width()*.5)), width()/(35/2.0));
	markerShadowGradBottom.setColorAt(0, QColor(30, 37, 46));
	markerShadowGradRight.setColorAt(0.9, QColor(30, 37, 46));
	markerShadowGradBottom.setColorAt(1, QColor(0, 0, 0, 0));

	//brush = QBrush(QColor(181, 201, 226));
	m_canvas.setBrush(QBrush(markerShadowGradRight));
	m_canvas.drawRect(markerShadowRectRight);
	m_canvas.setBrush(QBrush(markerShadowGradLeft));
	m_canvas.drawRect(markerShadowRectLeft);
	m_canvas.setBrush(QBrush(markerShadowGradBottom));
	m_canvas.drawRect(markerShadowRectBottom);

	brush = QBrush(QColor(181, 201, 226));
	m_canvas.setBrush(brush);
	m_canvas.drawRect(markerRect);
}

void ModernKnob::mousePressEvent(QMouseEvent * event)
{
	m_mousePressed = true;
	m_storedCursorPos = cursor().pos();
	setCursor(Qt::BlankCursor);
}


void ModernKnob::mouseMoveEvent(QMouseEvent * event)
{
	QCursor c = cursor();
	float delta = c.pos().y() - m_storedCursorPos.y();
	c.setPos(m_storedCursorPos);
	setCursor(c);

	float potentialValue = m_value - delta / 300;
	if (potentialValue > 1)
		m_value = 1;
	else if (potentialValue < 0)
		m_value = 0;
	else
		m_value = potentialValue;
	m_follower->updateTarget(m_value);
	update();
}



void ModernKnob::mouseReleaseEvent(QMouseEvent * event)
{
	m_mousePressed = false;
	setCursor(Qt::ArrowCursor);
}
