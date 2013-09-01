/*
 *  phidgets_common.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_common.h"


PhidgetsCommon::PhidgetsCommon(int serial)
: m_serial(serial)
{
}

PhidgetsCommon::~PhidgetsCommon()
{
}

Wt::WString PhidgetsCommon::GetPhidgetName()
{
	CPhidgetHandle handle = GetHandle();
	if (!handle)
		return Wt::WString("[NULL]");

	int errorcode;
	const char* string_value;
	if (EPHIDGET_OK != (errorcode=CPhidget_getDeviceName(handle, &string_value)))
	{
		if (EPHIDGET_OK != CPhidget_getErrorDescription(errorcode, &string_value))
		{
			return Wt::WString("[ERROR]");
		}
	}
	return Wt::WString(string_value, Wt::UTF8);
}
