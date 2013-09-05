/*
 *  phidgets_advancedservo.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_advancedservo.h"

//#include <stdio.h>
#include "../app_manager.h"
#include "../global.h"
#include "../phidget_manager.h"
#include "../widgets/widgets_advancedservo.h"


int OnPhidgetAttachAdvancedServo(CPhidgetHandle handle, void* ptr)
{
  return static_cast<PhidgetsAdvancedServo*>(ptr)->OnPhidgetAttach(handle);
}

int OnPhidgetDetachAdvancedServo(CPhidgetHandle handle, void* ptr)
{
	PhidgetsAdvancedServo* as = static_cast<PhidgetsAdvancedServo*>(ptr);
  int status = as->OnPhidgetDetach(handle);
	delete as;
	return status;
}
#if 0
int OnPhidgetInputChangeHandler(CPhidgetInterfaceKitHandle handle, void* ptr, int index, int input_state)
{
  return static_cast<PhidgetsInterfaceKit*>(ptr)->OnPhidgetInputChangeHandler(handle, index, input_state);
}

int OnPhidgetSensorChangeHandler(CPhidgetInterfaceKitHandle handle, void* ptr, int index, int sensor_value)
{
  return static_cast<PhidgetsInterfaceKit*>(ptr)->OnPhidgetSensorChangeHandler(handle, index, sensor_value);
}
#endif

PhidgetsAdvancedServo::PhidgetsAdvancedServo(int serial)
: PhidgetsCommon(serial),
  m_advancedservo_handle(NULL)
{
}

PhidgetsAdvancedServo::~PhidgetsAdvancedServo()
{
	CPhidget_close(GetHandle());
	CPhidget_delete(GetHandle());
}

bool PhidgetsAdvancedServo::Init()
{
	return (EPHIDGET_OK == CPhidgetAdvancedServo_create(&m_advancedservo_handle) &&
	    EPHIDGET_OK == CPhidget_set_OnAttach_Handler(GetHandle(), ::OnPhidgetAttachAdvancedServo, this) &&
	    EPHIDGET_OK == CPhidget_set_OnDetach_Handler(GetHandle(), ::OnPhidgetDetachAdvancedServo, this) &&
#if 0
	    EPHIDGET_OK == CPhidgetInterfaceKit_set_OnInputChange_Handler(m_interfacekit_handle, ::OnPhidgetInputChangeHandler, this) &&
	    EPHIDGET_OK == CPhidgetInterfaceKit_set_OnSensorChange_Handler(m_interfacekit_handle, ::OnPhidgetSensorChangeHandler, this) &&
#endif
	    EPHIDGET_OK == CPhidget_open(GetHandle(), GetSerial()));
}

WidgetsCommon* PhidgetsAdvancedServo::CreateWidget(PhidgetApplication* application)
{
	return new WidgetsAdvancedServo(this, application);
}

int PhidgetsAdvancedServo::OnPhidgetAttach(CPhidgetHandle handle)
{
	if (handle != GetHandle())
		return EPHIDGET_UNEXPECTED;
#if 0
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
#endif	
	::GetApplicationManager()->OnPhidgetAttached(GetSerial());
	return EPHIDGET_OK;
}

int PhidgetsAdvancedServo::OnPhidgetDetach(CPhidgetHandle handle)
{
	if (handle != GetHandle())
		return EPHIDGET_UNEXPECTED;

	::GetPhidgetManager()->OnDetach(GetSerial());
	return EPHIDGET_OK;
}
#if 0
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
#endif