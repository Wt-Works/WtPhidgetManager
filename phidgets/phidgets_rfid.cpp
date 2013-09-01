/*
 *  phidgets_rfid.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_rfid.h"

#include "../app_manager.h"
#include "../global.h"
#include "../phidget_manager.h"
#include "../widgets/widgets_rfid.h"


int OnPhidgetAttachRFID(CPhidgetHandle handle, void* ptr)
{
  return static_cast<PhidgetsRFID*>(ptr)->OnPhidgetAttach(handle);
}

int OnPhidgetDetachRFID(CPhidgetHandle handle, void* ptr)
{
  PhidgetsRFID* rfid = static_cast<PhidgetsRFID*>(ptr);
  int status = rfid->OnPhidgetDetach(handle);
	delete rfid;
	return status;
}

int OnPhidgetTagHandler(CPhidgetRFIDHandle handle, void* ptr, char* tag, CPhidgetRFID_Protocol protocol)
{
  return static_cast<PhidgetsRFID*>(ptr)->OnPhidgetTagHandler(handle, tag, protocol);
}

int OnPhidgetTagLostHandler(CPhidgetRFIDHandle handle, void* ptr, char* tag, CPhidgetRFID_Protocol protocol)
{
  return static_cast<PhidgetsRFID*>(ptr)->OnPhidgetTagLostHandler(handle, tag, protocol);
}


PhidgetsRFID::PhidgetsRFID(int serial)
: PhidgetsCommon(serial),
  m_rfid_handle(NULL)
{
}

PhidgetsRFID::~PhidgetsRFID()
{
	CPhidget_close(GetHandle());
	CPhidget_delete(GetHandle());
}

bool PhidgetsRFID::Init()
{
	return (EPHIDGET_OK == CPhidgetRFID_create(&m_rfid_handle) &&
	    EPHIDGET_OK == CPhidget_set_OnAttach_Handler(GetHandle(), ::OnPhidgetAttachRFID, this) &&
	    EPHIDGET_OK == CPhidget_set_OnDetach_Handler(GetHandle(), ::OnPhidgetDetachRFID, this) &&
	    EPHIDGET_OK == CPhidgetRFID_set_OnTag2_Handler(m_rfid_handle, ::OnPhidgetTagHandler, this) &&
	    EPHIDGET_OK == CPhidgetRFID_set_OnTagLost2_Handler(m_rfid_handle, ::OnPhidgetTagLostHandler, this) &&
	    EPHIDGET_OK == CPhidget_open(GetHandle(), GetSerial()));
}

WidgetsCommon* PhidgetsRFID::CreateWidget(PhidgetApplication* application)
{
	return new WidgetsRFID(this, application);
}

int PhidgetsRFID::OnPhidgetAttach(CPhidgetHandle handle)
{
	if (handle != GetHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetAttached(GetSerial());
	return EPHIDGET_OK;
}

int PhidgetsRFID::OnPhidgetDetach(CPhidgetHandle handle)
{
	if (handle != GetHandle())
		return EPHIDGET_UNEXPECTED;

	::GetPhidgetManager()->OnDetach(GetSerial());
	return EPHIDGET_OK;
}

int PhidgetsRFID::OnPhidgetTagHandler(CPhidgetRFIDHandle handle, char* tag, CPhidgetRFID_Protocol protocol)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetGotRFIDTag(GetSerial(), tag, protocol);
  return EPHIDGET_OK;
}

int PhidgetsRFID::OnPhidgetTagLostHandler(CPhidgetRFIDHandle handle, char* /*tag*/, CPhidgetRFID_Protocol /*protocol*/)
{
	if (handle != GetNativeHandle())
		return EPHIDGET_UNEXPECTED;

	::GetApplicationManager()->OnPhidgetLostRFIDTag(GetSerial());
  return EPHIDGET_OK;
}

bool PhidgetsRFID::CanWriteTags() const
{
	char dummy;
	//Read-only devices will return EPHIDGET_UNSUPPORTED, Read-Write-devices will return EPHIDGET_INVALIDARG
	return (EPHIDGET_INVALIDARG==CPhidgetRFID_write(GetNativeHandle(), &dummy, static_cast<CPhidgetRFID_Protocol>(NOT_A_PROTOCOL), PFALSE));
}
