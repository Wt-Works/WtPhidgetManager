/*
 *  phidgets_interfacekit.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_interfacekit.h"

#include <stdio.h>
#include "../app_manager.h"
#include "../global.h"
#include "../phidget_manager.h"
#include "../widgets/widgets_interfacekit.h"


int OnPhidgetAttachInterfaceKit(CPhidgetHandle handle, void* ptr)
{
  return static_cast<PhidgetsInterfaceKit*>(ptr)->OnPhidgetAttach(handle);
}

int OnPhidgetDetachInterfaceKit(CPhidgetHandle handle, void* ptr)
{
	PhidgetsInterfaceKit* ik = static_cast<PhidgetsInterfaceKit*>(ptr);
  int status = ik->OnPhidgetDetach(handle);
	delete ik;
	return status;
}

int OnPhidgetInputChangeHandler(CPhidgetInterfaceKitHandle handle, void* ptr, int index, int input_state)
{
  return static_cast<PhidgetsInterfaceKit*>(ptr)->OnPhidgetInputChangeHandler(handle, index, input_state);
}

int OnPhidgetSensorChangeHandler(CPhidgetInterfaceKitHandle handle, void* ptr, int index, int sensor_value)
{
  return static_cast<PhidgetsInterfaceKit*>(ptr)->OnPhidgetSensorChangeHandler(handle, index, sensor_value);
}


PhidgetsInterfaceKit::PhidgetsInterfaceKit(int serial)
: PhidgetsCommon(serial),
  m_interfacekit_handle(NULL)
{
}

PhidgetsInterfaceKit::~PhidgetsInterfaceKit()
{
	CPhidget_close(GetHandle());
	CPhidget_delete(GetHandle());
}

bool PhidgetsInterfaceKit::Init()
{
	return (EPHIDGET_OK == CPhidgetInterfaceKit_create(&m_interfacekit_handle) &&
	    EPHIDGET_OK == CPhidget_set_OnAttach_Handler(GetHandle(), ::OnPhidgetAttachInterfaceKit, this) &&
	    EPHIDGET_OK == CPhidget_set_OnDetach_Handler(GetHandle(), ::OnPhidgetDetachInterfaceKit, this) &&
	    EPHIDGET_OK == CPhidgetInterfaceKit_set_OnInputChange_Handler(m_interfacekit_handle, ::OnPhidgetInputChangeHandler, this) &&
	    EPHIDGET_OK == CPhidgetInterfaceKit_set_OnSensorChange_Handler(m_interfacekit_handle, ::OnPhidgetSensorChangeHandler, this) &&
	    EPHIDGET_OK == CPhidget_open(GetHandle(), GetSerial()));
}

WidgetsCommon* PhidgetsInterfaceKit::CreateWidget(PhidgetApplication* application)
{
	return new WidgetsInterfaceKit(this, application);
}

int PhidgetsInterfaceKit::OnPhidgetAttach(CPhidgetHandle handle)
{
	if (handle != GetHandle())
		return EPHIDGET_UNEXPECTED;

	int status;
	int count;
	if (EPHIDGET_OK != (status=CPhidgetInterfaceKit_getSensorCount(GetNativeHandle(), &count)))
		return status;

	int i;
	for (i=0; i<count; i++)
	{
		int rate;
		if (EPHIDGET_OK == CPhidgetInterfaceKit_getDataRateMin(GetNativeHandle(), i, &rate))
		{
			if (1000 < rate)
				rate=1000;

			CPhidgetInterfaceKit_setSensorChangeTrigger(GetNativeHandle(), i, 1);
			CPhidgetInterfaceKit_setDataRate(GetNativeHandle(), i, rate);
		}
	}
	
	::GetApplicationManager()->OnPhidgetAttached(GetSerial());
	return EPHIDGET_OK;
}

int PhidgetsInterfaceKit::OnPhidgetDetach(CPhidgetHandle handle)
{
	if (handle != GetHandle())
		return EPHIDGET_UNEXPECTED;

	::GetPhidgetManager()->OnDetach(GetSerial());
	return EPHIDGET_OK;
}

int PhidgetsInterfaceKit::OnPhidgetInputChangeHandler(CPhidgetInterfaceKitHandle handle, int index, int input_state)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetDigitalInputChanged(GetSerial(), index, PTRUE==input_state);
	return EPHIDGET_OK;
}

int PhidgetsInterfaceKit::OnPhidgetSensorChangeHandler(CPhidgetInterfaceKitHandle handle, int index, int sensor_value)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetSensorChanged(GetSerial(), index, sensor_value);
	return EPHIDGET_OK;
}
