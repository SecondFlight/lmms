/*
 * GuiTestControlDialog.cpp - A simple little plugin for testing the Modern UI
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

#include <QLayout>

#include "GuiTestControlDialog.h"
#include "GuiTestControls.h"
#include "embed.h"
#include "../../src/gui/ModernUI/ModernKnob.h" // oops


GuiTestControlDialog::GuiTestControlDialog(GuiTestControls *controls):
	EffectControlDialog(controls)
{
	setAutoFillBackground(true);

	QPalette pal;
	pal.setColor(QPalette::ColorRole::Background, QColor(52, 62, 74));
	setPalette( pal );

	setFixedSize(1200, 580);

	ModernKnob* knob1 = new ModernKnob(this);
	knob1->setMaximumSize(17, 17);
	knob1->setMinimumSize(17, 17);
	knob1->adjustSize();
	knob1->move(QPoint(100, 100));

	ModernKnob* knob2 = new ModernKnob(this);
	knob2->setMaximumSize(25, 25);
	knob2->setMinimumSize(25, 25);
	knob2->adjustSize();
	knob2->move(QPoint(220, 100));

	ModernKnob* knob3 = new ModernKnob(this);
	knob3->setMaximumSize(35, 35);
	knob3->setMinimumSize(35, 35);
	knob3->adjustSize();
	knob3->move(QPoint(340, 100));

	ModernKnob* knob4 = new ModernKnob(this);
	knob4->setMaximumSize(50, 50);
	knob4->setMinimumSize(50, 50);
	knob4->adjustSize();
	knob4->move(QPoint(460, 100));

	ModernKnob* knob5 = new ModernKnob(this);
	knob5->setMaximumSize(100, 100);
	knob5->setMinimumSize(100, 100);
	knob5->adjustSize();
	knob5->move(QPoint(580, 100));

	ModernKnob* knob6 = new ModernKnob(this);
	knob6->setMaximumSize(350, 350);
	knob6->setMinimumSize(350, 350);
	knob6->adjustSize();
	knob6->move(QPoint(700, 100));
}
