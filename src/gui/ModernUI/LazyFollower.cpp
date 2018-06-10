/*
 * LazyFollower.cpp - A utility to help implement UI smoothing
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

#include "LazyFollower.h"
#include <QtMath>

LazyFollower::LazyFollower(LazyFollowable* followable, float initValue, float fractionPerFrame)
{
	m_followable = followable;
	m_currentTarget = initValue;
	m_currentValue = initValue;
	m_frac = fractionPerFrame;
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

LazyFollower::LazyFollower()
{
	m_followable = nullptr;
	m_currentTarget = 0;
	m_currentValue = 0;
	m_frac = 0.1;
	m_timer = nullptr;
}

void LazyFollower::updateTarget(float input)
{
	m_currentTarget = input;
	if (!m_timer->isActive())
		m_timer->start(qRound(1000/60.0));
}

void LazyFollower::setFractionPerFrame(float frac)
{
	m_frac = frac;
}

void LazyFollower::update()
{
	m_currentValue = m_currentTarget + (m_currentValue - m_currentTarget) * m_frac;
	m_followable->setFollowValue(m_currentValue);
	if (qAbs(m_currentValue - m_currentTarget) < 0.0001)
	{
		m_currentValue = m_currentTarget;
		m_timer->stop();
	}
}
