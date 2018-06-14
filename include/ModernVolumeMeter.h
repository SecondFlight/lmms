/*
 * ModernVolumeMeter.h - A volume meter widget for the Modern UI
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

#include <QWidget>
#include <QPainter>

class ModernVolumeMeter : public QWidget
{
	Q_OBJECT

public:
	ModernVolumeMeter(QWidget * _parent = NULL, const QString & _name = QString());
	virtual ~ModernVolumeMeter();
	void updateValues(float l, float r);

protected:
	virtual void paintEvent(QPaintEvent * event);

private:
	QPainter m_canvas;
	float m_lValue;
	float m_rValue;

	static const int s_borderWidth = 1;
};
