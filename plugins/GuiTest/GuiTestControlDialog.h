/*
 * GuiTestControlDialog.h - A simple little plugin for testing the Modern UI
 *
 * Copyright (c) 2018 Joshua Wade <lastname/firstinitial/at/southern/dot/edu>
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

#ifndef GUITEST_CONTROL_DIALOG_H
#define GUITEST_CONTROL_DIALOG_H

#include "EffectControlDialog.h"
#include "ModernVolumeMeter.h"


class GuiTestControls;


class GuiTestControlDialog : public EffectControlDialog
{
	Q_OBJECT
public:
	GuiTestControlDialog(GuiTestControls* controls);
	virtual ~GuiTestControlDialog()
	{
	}
	ModernVolumeMeter* m_volumeMeter1;
	ModernVolumeMeter* m_volumeMeter2;
	ModernVolumeMeter* m_volumeMeter3;

};

#endif
