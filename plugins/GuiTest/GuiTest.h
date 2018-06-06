/*
 * GuiTest.h - A simple little plugin for testing the Modern UI
 *
 * Copyright (c) 2018 Joshua Wade <lastname/firstinitial/at/southern/dot/edu/>
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


#ifndef GUITEST_H
#define GUITEST_H

#include "Effect.h"
#include "GuiTestControls.h"

class GuiTestEffect : public Effect
{
public:
	GuiTestEffect (Model* parent, const Descriptor::SubPluginFeatures::Key* key);
	virtual ~GuiTestEffect();
	virtual bool processAudioBuffer(sampleFrame* buffer, const fpp_t frames);

	virtual EffectControls* controls()
	{
		return &m_guiTestControls;
	}

private:
	GuiTestControls m_guiTestControls;

	friend class GuiTestControls;
};

#endif
