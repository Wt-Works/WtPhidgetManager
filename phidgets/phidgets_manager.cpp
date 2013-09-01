/*
 *  phidgets_manager.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_manager.h"

#include "../app_manager.h"
#include "../global.h"
#include "../widgets/widgets_manager.h"


PhidgetsManager::PhidgetsManager()
: PhidgetsCommon(0)
{
}

bool PhidgetsManager::Init()
{
	//This is a virtual device. "Attach" immediately
	::GetApplicationManager()->OnPhidgetAttached(GetSerial());
	return true;
}

Wt::WString PhidgetsManager::GetPhidgetName()
{
	return Wt::WString::tr("General Info");
}

WidgetsCommon* PhidgetsManager::CreateWidget(PhidgetApplication* application)
{
	return new WidgetsManager(this, application);
}
