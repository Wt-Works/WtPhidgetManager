/*
 *  phidget_manager.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidget_manager.h"

#include "app.h"
#include "app_manager.h"
#include "phidgets/phidgets_advancedservo.h"
#include "phidgets/phidgets_interfacekit.h"
#include "phidgets/phidgets_manager.h"
#include "phidgets/phidgets_rfid.h"


int OnAttachManager(CPhidgetHandle handle, void* ptr) {
  return static_cast<PhidgetManager*>(ptr)->OnAttach(handle);
}


PhidgetManager::PhidgetManager()
: m_manager(NULL),
  m_phidget_list(NULL)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_phidget_mutex, &attr);
	pthread_mutexattr_destroy(&attr);

	Lock();

	CPhidgetManager_create(&m_manager);
	CPhidgetManager_set_OnAttach_Handler(m_manager, ::OnAttachManager, this);
	CPhidgetManager_open(m_manager);

	OnAttach(NULL); //Special case to create a tab for the Manager tab

	int handle_count;
	CPhidgetHandle* handle_array;
	if (EPHIDGET_OK == CPhidgetManager_getAttachedDevices(m_manager, &handle_array, &handle_count))
	{
		int i;
		for (i=0; i<handle_count; i++)
		{
			OnAttach(handle_array[i]);
		}
		
		CPhidgetManager_freeAttachedDevicesArray(handle_array);
	}

	Unlock();
}

PhidgetManager::~PhidgetManager()
{
	Lock();

	PhidgetsInfo* item;
	while (NULL!=(item=m_phidget_list))
	{
		m_phidget_list = m_phidget_list->m_next_phidget;
		delete item;
	}

  CPhidgetManager_close(m_manager);
  CPhidgetManager_delete(m_manager);

	Unlock();
	pthread_mutex_destroy(&m_phidget_mutex);
}

int PhidgetManager::OnAttach(CPhidgetHandle handle)
{
	Lock();

	if (FindPhidgetByHandle(handle))
	{
		Unlock();
		return EPHIDGET_OK; //We've already attached it
	}

	PhidgetsCommon* item;
	if (NULL == handle) //Manager tab
	{
		item = new PhidgetsManager();
	}
	else
	{
		int status;
		int serial;
		CPhidget_DeviceClass device_class;
		if (EPHIDGET_OK != (status=CPhidget_getDeviceClass(handle, &device_class)) ||
		    EPHIDGET_OK != CPhidget_getSerialNumber(handle, &serial))
		{
			Unlock();
			return status;
		}

		switch(device_class)
		{
			case PHIDCLASS_ADVANCEDSERVO: item = new PhidgetsAdvancedServo(serial); break;
			case PHIDCLASS_INTERFACEKIT: item = new PhidgetsInterfaceKit(serial); break;
			case PHIDCLASS_RFID: item = new PhidgetsRFID(serial); break;
			default: {
				         Unlock();
				         return EPHIDGET_UNSUPPORTED;
				       }
		}
	}
		
	if (!item)
	{
		Unlock();
		return EPHIDGET_NOMEMORY;
	}

	if (!item->Init())
	{
		delete item;
		Unlock();
		return EPHIDGET_UNEXPECTED;
	}
	AddPhidgetToList(item);

	Unlock();
	return EPHIDGET_OK;
}

int PhidgetManager::OnDetach(int serial)
{
	Lock();

	PhidgetsInfo* item = FindPhidgetBySerial(serial);
	if (!item)
	{
		Unlock();
		return EPHIDGET_OK; //We've already detached it
	}
	
	::GetApplicationManager()->OnPhidgetDetached(item->m_phidget->GetSerial());
	RemovePhidgetFromList(item->m_phidget);

	Unlock();
	return EPHIDGET_OK;
}

void PhidgetManager::RequestAllPhidgets(PhidgetApplication* app)
{
	if (!app)
		return;

	Lock();

	PhidgetsInfo* item = m_phidget_list;
	while (item)
	{
		app->OnAttached(item->m_phidget->GetSerial());
		item = item->m_next_phidget;
	}

	Unlock();
}

void PhidgetManager::RequestTab(PhidgetApplication* app, int serial)
{
	PhidgetsInfo* item = FindPhidgetBySerial(serial);
	if (!app || !item)
		return;

	WidgetsCommon* widget = item->m_phidget->CreateWidget(app);
	if (widget)
	{
		app->SetWidget(serial, widget, item->m_phidget->GetPhidgetName());
	}
}

PhidgetsInfo* PhidgetManager::FindPhidgetBySerial(int serial)
{
	Lock();

	PhidgetsInfo* item = m_phidget_list;
	while (item)
	{
		if (item->m_phidget->GetSerial() == serial)
			break;
		
		item = item->m_next_phidget;
	}

	Unlock();
	return item;
}

PhidgetsInfo* PhidgetManager::FindPhidgetByHandle(CPhidgetHandle handle)
{
	if (!handle)
		return FindPhidgetBySerial(0);

	int serial;
	if (EPHIDGET_OK != CPhidget_getSerialNumber(handle, &serial))
		return NULL;

	return FindPhidgetBySerial(serial);
}

PhidgetsInfo* PhidgetManager::FindPhidgetInList(const PhidgetsCommon* phidget)
{
	Lock();

	PhidgetsInfo* item = m_phidget_list;
	while (item)
	{
		if (item->m_phidget == phidget)
			break;
		
		item = item->m_next_phidget;
	}

	Unlock();
	return item;
}

void PhidgetManager::AddPhidgetToList(PhidgetsCommon* phidget)
{
	Lock();

	if (!phidget || FindPhidgetInList(phidget))
	{
		Unlock();
		return;
	}

	PhidgetsInfo* item = new PhidgetsInfo();

	if (m_phidget_list)
		m_phidget_list->m_previous_phidget = item;

	item->m_phidget = phidget;
	item->m_previous_phidget = NULL;
	item->m_next_phidget = m_phidget_list;

	m_phidget_list = item;

	Unlock();
}

void PhidgetManager::RemovePhidgetFromList(PhidgetsCommon* phidget)
{
	Lock();

	PhidgetsInfo* item = FindPhidgetInList(phidget);
	if (!item)
	{
		Unlock();
		return;
	}

	//Remove from linked list
	if (item->m_previous_phidget)
		item->m_previous_phidget->m_next_phidget = item->m_next_phidget;
	
	if (item->m_next_phidget)
		item->m_next_phidget->m_previous_phidget = item->m_previous_phidget;

	//Update list pointer
	if (m_phidget_list == item)
		m_phidget_list = item->m_next_phidget;

	//Don't free memory here, it is done in Phidget ::OnDetached

	Unlock();
}
