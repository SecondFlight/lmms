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
#include "ModernKnob.h"
#include "ModernToggleSwitch.h"
#include "ModernSlider.h"
#include "ModernButton.h"
#include "ModernScrollbar.h"


GuiTestControlDialog::GuiTestControlDialog(GuiTestControls *controls):
	EffectControlDialog(controls)
{
	setAutoFillBackground(true);

	QPalette pal;
	pal.setColor(QPalette::ColorRole::Background, QColor(82, 82, 82));
	setPalette( pal );

	setFixedSize(1600, 800);

	/*ModernKnob* knob1 = new ModernKnob(this);
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
	knob3->move(QPoint(340, 100));*/

	/*ModernKnob* knob4 = new ModernKnob(this);
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
	knob6->move(QPoint(700, 100));*/

	/*ModernToggleSwitch* toggleSwitch1 = new ModernToggleSwitch(this);
	toggleSwitch1->setMaximumHeight(20);
	toggleSwitch1->setMaximumWidth(20);
	toggleSwitch1->setMinimumHeight(20);
	toggleSwitch1->setMinimumWidth(20);
	toggleSwitch1->adjustSize();
	toggleSwitch1->move(QPoint(100, 200));*/

	ModernSlider* slider1 = new ModernSlider(this);
	slider1->setMaximumHeight(105);
	slider1->setMinimumHeight(105);
	slider1->setMaximumWidth(18);
	slider1->setMinimumWidth(18);
	slider1->adjustSize();
	slider1->move(500, 100);

	ModernSlider* slider2 = new ModernSlider(this);
	slider2->setMaximumHeight(315);
	slider2->setMinimumHeight(315);
	slider2->setMaximumWidth(54);
	slider2->setMinimumWidth(54);
	slider2->adjustSize();
	slider2->move(350, 100);

	m_volumeMeter1 = new ModernVolumeMeter(this);
	m_volumeMeter1->setMaximumHeight(105);
	m_volumeMeter1->setMinimumHeight(105);
	m_volumeMeter1->setMaximumWidth(13);
	m_volumeMeter1->setMinimumWidth(13);
	m_volumeMeter1->adjustSize();
	m_volumeMeter1->move(483, 100);

	m_volumeMeter2 = new ModernVolumeMeter(this);
	m_volumeMeter2->setMaximumHeight(315);
	m_volumeMeter2->setMinimumHeight(315);
	m_volumeMeter2->setMaximumWidth(39);
	m_volumeMeter2->setMinimumWidth(39);
	m_volumeMeter2->adjustSize();
	m_volumeMeter2->move(700, 50);

	m_volumeMeter3 = new ModernVolumeMeter(this);
	m_volumeMeter3->setMaximumHeight(26);
	m_volumeMeter3->setMinimumHeight(26);
	m_volumeMeter3->setMaximumWidth(11);
	m_volumeMeter3->setMinimumWidth(11);
	m_volumeMeter3->adjustSize();
	m_volumeMeter3->move(450, 100);

	ModernButton* button1 = new ModernButton(this);
	button1->setMaximumHeight(20);
	button1->setMinimumHeight(20);
	button1->setMaximumWidth(28);
	button1->setMinimumWidth(28);
	button1->adjustSize();
	button1->move(20, 20);

	ModernButton* button2 = new ModernButton(this);
	button2->setMaximumHeight(20);
	button2->setMinimumHeight(20);
	button2->setMinimumWidth(20);
	button2->setMaximumWidth(20);
	button2->adjustSize();
	button2->move(50, 20);
	button2->setSticky(true);

	ModernButton* button3 = new ModernButton(this);
	button3->setMaximumHeight(20);
	button3->setMinimumHeight(20);
	button3->setMaximumWidth(39);
	button3->setMinimumWidth(39);
	button3->adjustSize();
	button3->move(72, 20);

	ModernButton* button4 = new ModernButton(this);
	button4->setMaximumHeight(20);
	button4->setMinimumHeight(20);
	button4->setMaximumWidth(50);
	button4->setMinimumWidth(50);
	button4->adjustSize();
	button4->move(113, 20);
	button4->setText("+ Peak");

	ModernScrollbar* scrollbar1 = new ModernScrollbar(this);
	scrollbar1->setMaximumHeight(347);
	scrollbar1->setMinimumHeight(347);
	scrollbar1->setMaximumWidth(16);
	scrollbar1->setMinimumWidth(16);
	scrollbar1->adjustSize();
	scrollbar1->move(800, 20);
	scrollbar1->setVertical();
	scrollbar1->setStart(0);
	scrollbar1->setWidth(0.1);

	ModernScrollbar* scrollbar2 = new ModernScrollbar(this);
	scrollbar2->setMaximumHeight(16);
	scrollbar2->setMinimumHeight(16);
	scrollbar2->setMaximumWidth(347);
	scrollbar2->setMinimumWidth(347);
	scrollbar2->adjustSize();
	scrollbar2->move(20, 700);
	scrollbar2->setHorizontal();
	scrollbar2->setStart(0.2);
	scrollbar2->setWidth(0.3);
}
