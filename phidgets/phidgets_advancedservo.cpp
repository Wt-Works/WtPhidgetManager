/*
 *  phidgets_advancedservo.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_advancedservo.h"

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

int OnVelocityChangeHandler(CPhidgetAdvancedServoHandle handle, void* ptr, int index, double velocity)
{
	return static_cast<PhidgetsAdvancedServo*>(ptr)->OnVelocityChangeHandler(handle, index, velocity);
}

int OnPositionChangeHandler(CPhidgetAdvancedServoHandle handle, void* ptr, int index, double position)
{
	return static_cast<PhidgetsAdvancedServo*>(ptr)->OnPositionChangeHandler(handle, index, position);
}

int OnCurrentChangeHandler(CPhidgetAdvancedServoHandle handle, void* ptr, int index, double current)
{
	return static_cast<PhidgetsAdvancedServo*>(ptr)->OnCurrentChangeHandler(handle, index, current);
}
 

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
	    EPHIDGET_OK == CPhidgetAdvancedServo_set_OnVelocityChange_Handler(m_advancedservo_handle, ::OnVelocityChangeHandler, this) &&
	    EPHIDGET_OK == CPhidgetAdvancedServo_set_OnPositionChange_Handler(m_advancedservo_handle, ::OnPositionChangeHandler, this) &&
	    EPHIDGET_OK == CPhidgetAdvancedServo_set_OnCurrentChange_Handler(m_advancedservo_handle, ::OnCurrentChangeHandler, this) &&
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

int PhidgetsAdvancedServo::OnVelocityChangeHandler(CPhidgetAdvancedServoHandle handle, int index, double velocity)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetServoVelocityChanged(GetSerial(), index, velocity);
	return EPHIDGET_OK;
}

int PhidgetsAdvancedServo::OnPositionChangeHandler(CPhidgetAdvancedServoHandle handle, int index, double position)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetServoPositionChanged(GetSerial(), index, position);

	//Disengage servo if error or it is not moving anymore
	int stopped;
	if (EPHIDGET_OK != CPhidgetAdvancedServo_getStopped(handle, index, &stopped) || PTRUE==stopped)
	{
		CPhidgetAdvancedServo_setEngaged(handle, index, PTRUE);
	}

	return EPHIDGET_OK;
}

int PhidgetsAdvancedServo::OnCurrentChangeHandler(CPhidgetAdvancedServoHandle handle, int index, double current)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetServoCurrentChanged(GetSerial(), index, current);
	return EPHIDGET_OK;
}
