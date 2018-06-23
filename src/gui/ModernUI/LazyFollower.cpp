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

#include "GuiApplication.h"
#include "MainWindow.h"

#include <QtMath>

LazyFollower::LazyFollower(LazyFollowable* followable, int numFollowValues, QVector<float> initValues, QVector<float> fractionsPerFrame)
{
	m_followable = followable;
	m_currentTargets = initValues;
	m_currentValues = initValues;
	m_fracs = fractionsPerFrame;
	m_numFollowValues = numFollowValues;
	m_stopped = true;
	connect(gui->mainWindow(), SIGNAL(periodicUpdate()), this, SLOT(update()));
}

LazyFollower::LazyFollower()
{
	m_followable = nullptr;
	m_currentTargets = QVector<float>();
	m_currentValues = QVector<float>();
	m_fracs = QVector<float>();
	m_stopped = true;
}

void LazyFollower::updateTarget(QVector<float> inputs)
{
	m_currentTargets = inputs;
	m_stopped = false;
}

void LazyFollower::updateTarget(int index, float input)
{
	m_currentTargets[index] = input;
	m_stopped = false;
}

float LazyFollower::getTarget(int index)
{
	return m_currentTargets[index];
}

void LazyFollower::setFractionPerFrame(QVector<float> fracs)
{
	m_fracs = fracs;
}

void LazyFollower::setFractionPerFrame(int index, float frac)
{
	m_fracs[index] = frac;
}

void LazyFollower::update()
{
	if (m_stopped)
		return;

	bool allValuesStopped = true;
	for (int i = 0; i < m_numFollowValues; i++)
	{
		m_currentValues[i] = m_currentTargets[i] + (m_currentValues[i] - m_currentTargets[i]) * m_fracs[i];
		allValuesStopped = allValuesStopped && (qAbs(m_currentValues[i] - m_currentTargets[i]) < 0.0001);
	}

	if (allValuesStopped)
	{
		for (int i = 0; i < m_numFollowValues; i++)
			m_currentValues[i] = m_currentTargets[i];
		m_stopped = true;
	}

	m_followable->setFollowValues(m_currentValues);
}
