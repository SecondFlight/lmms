/*
 * ModernButton.h - A button widget for the Modern UI
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

#ifndef MODERNBUTTON_H
#define MODERNBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QString>

class ModernButton : public QWidget
{
	Q_OBJECT

public:
	ModernButton(QWidget * _parent = NULL, const QString & _name = QString());
	virtual ~ModernButton();

	void setOff();
	void setOn();
	void setSticky(bool sticky);
	void setText(QString text);

protected:
	virtual void paintEvent(QPaintEvent * event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent * event);

private:
	QPainter m_canvas;
	bool m_value;
	bool m_mousePressed;
	bool m_isSticky;
	bool m_hasText;
	QString m_text;
};

#endif
