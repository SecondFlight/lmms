/*
 * ModernKnob.h - A knob widget for the Modern UI
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


#ifndef MODERNKNOB_H
#define MODERNKNOB_H

#include <QWidget>
#include <QPainter>

//#include "templates.h"
#include "LazyFollower.h"


class /*EXPORT*/ ModernKnob : public QWidget, public LazyFollowable//, public FloatModelView
{
	Q_OBJECT

public:
	ModernKnob(QWidget * _parent = NULL, const QString & _name = QString());
	virtual ~ModernKnob();
	inline virtual void setFollowValue(float value)
	{
		m_followValue = value;
		update();
	}

protected:
	virtual void paintEvent(QPaintEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);

private:
	int m_size;
	QPainter m_canvas;
	float m_value;
	float m_followValue;
	bool m_mousePressed;
	QPoint m_storedCursorPos;
	LazyFollower* m_follower;
};

#endif
