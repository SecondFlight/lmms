/*
 * GuiTest.cpp - A simple little plugin for testing the Modern UI
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

#include "GuiTest.h"

#include "embed.h"


extern "C"
{

Plugin::Descriptor PLUGIN_EXPORT guitest_plugin_descriptor =
{
	STRINGIFY( PLUGIN_NAME ),
	"GuiTest",
	QT_TRANSLATE_NOOP( "pluginBrowser", "A plugin for testing the Modern UI" ),
	"<lastname/firstinitial/at/southern/dot/edu/>",
	0x0100,
	Plugin::Effect,
	new PluginPixmapLoader("logo"),
	NULL,
	NULL
};

}


GuiTestEffect::GuiTestEffect(Model* parent, const Descriptor::SubPluginFeatures::Key* key) :
	Effect( &guitest_plugin_descriptor, parent, key ),
	m_guiTestControls( this )
{
	m_frameTimer = QElapsedTimer();
	m_frameTimer.start();
}


GuiTestEffect::~GuiTestEffect()
{
}


bool GuiTestEffect::processAudioBuffer(sampleFrame *buffer, const fpp_t frames)
{
	for (int i = 0; i < frames; i++)
	{
		if (buffer[i][0] > m_currentMaxL)
			m_currentMaxL = qAbs(buffer[i][0]);
		if (buffer[i][1] > m_currentMaxR)
			m_currentMaxR = qAbs(buffer[i][1]);
	}
	if (m_frameTimer.nsecsElapsed() > ((qint64)1000*(qint64)1000000)/60)
	{
		m_guiTestControls.m_dialog->m_volumeMeter3->updateValues(m_currentMaxL, m_currentMaxR);
		m_guiTestControls.m_dialog->m_volumeMeter1->updateValues(m_currentMaxL, m_currentMaxR);
		m_guiTestControls.m_dialog->m_volumeMeter2->updateValues(m_currentMaxL, m_currentMaxR);
		m_frameTimer.restart();
		m_currentMaxL = 0;
		m_currentMaxR = 0;
	}
	return true;
}


extern "C"
{

// necessary for getting instance out of shared lib
PLUGIN_EXPORT Plugin * lmms_plugin_main( Model* parent, void* data )
{
	return new GuiTestEffect( parent, static_cast<const Plugin::Descriptor::SubPluginFeatures::Key *>( data ) );
}

}
