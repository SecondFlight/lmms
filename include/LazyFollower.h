/*
 * LazyFollower.h - A utility to help implement UI smoothing
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

#include <QTimer>
#include <QWidget>
#include <QVector>

#ifndef LAZYFOLLOWER_H
#define LAZYFOLLOWER_H

class LazyFollowable
{
public:
	virtual void setFollowValues(QVector<float> values) = 0;
};

class LazyFollower : public QObject
{
	Q_OBJECT
public:
	LazyFollower(LazyFollowable* followable, int numFollowValues, QVector<float> initValues, QVector<float> fractionsPerFrame);
	LazyFollower();
	void updateTarget(QVector<float> inputs);
	void updateTarget(int index, float input);
	void setFractionPerFrame(QVector<float> fracs);
	void setFractionPerFrame(int index, float frac);

protected slots:
	void update();

private:
	LazyFollowable* m_followable;

	int m_numFollowValues;
	QTimer* m_timer;
	QVector<float> m_currentTargets;
	QVector<float> m_currentValues;
	QVector<float> m_fracs;
};

#endif
