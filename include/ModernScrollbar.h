/*
 * ModernScrollbar.h - A scrollbar widget for the Modern UI
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

#ifndef MODERNSCROLLBAR_H
#define MODERNSCROLLBAR_H

#include <QWidget>
#include <QPainter>

class ModernScrollbar : public QWidget
{
	Q_OBJECT

public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	ModernScrollbar(QWidget * _parent = NULL, const QString & _name = QString());
	virtual ~ModernScrollbar();
	void setVertical();
	void setHorizontal();
	void setStart(float start);
	void setWidth(float width);
	void setTotalSize(float size);
	void tickForward();
	void tickBackward();
	void tryMoveTo(float newStartValue);
	void tryMoveStartTo(float newStartValue);
	void tryMoveEndTo(float newEndValue);
	void setMinimumScrollbarWidth(float width);
	void setHandleResizingEnabled(bool enabled);

protected:
	virtual void paintEvent(QPaintEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);

private:
	QPainter m_canvas;
	bool m_isHorizontal;
	float m_startValue;
	float m_endValue;
	float m_totalSize;
	float m_tickSize;
	float m_minimumWidth;
	float m_delta;
	bool m_isInDragOperation;
	bool m_isInStartMoveOperation;
	bool m_isInEndMoveOperation;
	bool m_isHandleResizingEnabled;
	void drawArrow(QPainter *canvas, Direction direction);
	float mousePosToValue(QPoint pos);
	float valueToPixels(float value);
};

#endif
