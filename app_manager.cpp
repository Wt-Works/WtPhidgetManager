/*
 *  app_manager.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "app_manager.h"

#include "app.h"
#include "global.h"
#include <Wt/WServer>

#define NOTIFY_APP(x)     Lock();\
                          PhidgetApplicationInfo* item = GetApplicationList();\
                          while (item) {\
                            Wt::WServer::instance()->post(item->m_application->sessionId(),\
                              item->m_application->bind(boost::bind(&PhidgetApplication::x, item->m_application, serial)));\
                            item = item->m_next_application;\
                          }\
                          Unlock();

#define NOTIFY_APP2(x,y,z) Lock();\
                           PhidgetApplicationInfo* item = GetApplicationList();\
                           while (item) {\
                             Wt::WServer::instance()->post(item->m_application->sessionId(),\
                               item->m_application->bind(boost::bind(&PhidgetApplication::x, item->m_application, serial, y, z)));\
                             item = item->m_next_application;\
                           }\
                           Unlock();

#define SYNC_APP1(x,y) Lock();\
                       PhidgetApplicationInfo* item = GetApplicationList();\
                       while (item) {\
                         if (trigger_app != item->m_application) {\
                           Wt::WServer::instance()->post(item->m_application->sessionId(),\
                             item->m_application->bind(boost::bind(&PhidgetApplication::x, item->m_application, serial, y)));\
                         }\
                         item = item->m_next_application;\
                       }\
                       Unlock();

#define SYNC_APP2(x,y,z) Lock();\
                         PhidgetApplicationInfo* item = GetApplicationList();\
                         while (item) {\
                           if (trigger_app != item->m_application) {\
                             Wt::WServer::instance()->post(item->m_application->sessionId(),\
                               item->m_application->bind(boost::bind(&PhidgetApplication::x, item->m_application, serial, y, z)));\
                           }\
                           item = item->m_next_application;\
                         }\
                         Unlock();


ApplicationManager::ApplicationManager()
: m_application_list(NULL)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&m_application_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

ApplicationManager::~ApplicationManager()
{
	Lock();

	PhidgetApplicationInfo* item;
	while (NULL!=(item=m_application_list))
	{
		m_application_list = m_application_list->m_next_application;
		delete item;
	}

	Unlock();
	pthread_mutex_destroy(&m_application_mutex);
}

void ApplicationManager::OnAppCreated(PhidgetApplication* app)
{
	AddApplicationToList(app);
}

void ApplicationManager::OnAppDestroyed(PhidgetApplication* app)
{
	RemoveApplicationFromList(app);
}

void ApplicationManager::OnPhidgetAttached(int serial)
{
	NOTIFY_APP(OnAttached);
}

void ApplicationManager::OnPhidgetDetached(int serial)
{
	NOTIFY_APP(OnDetached);
}

void ApplicationManager::OnPhidgetDigitalInputChanged(int serial, int index, bool state)
{
	NOTIFY_APP2(OnDigitalInputChanged, index, state);
}

void ApplicationManager::OnPhidgetGotRFIDTag(int serial, const char* tag, CPhidgetRFID_Protocol protocol)
{
	NOTIFY_APP2(OnGotRFIDTag, tag, protocol);
}

void ApplicationManager::OnPhidgetLostRFIDTag(int serial)
{
	NOTIFY_APP(OnLostRFIDTag);
}

void ApplicationManager::OnPhidgetSensorChanged(int serial, int index, int sensor_value)
{
	NOTIFY_APP2(OnSensorChanged, index, sensor_value);
}

void ApplicationManager::OnPhidgetServoAccelerationChanged(int serial, int index, double acceleration)
{
	NOTIFY_APP2(OnServoAccelerationChanged, index, acceleration);
}

void ApplicationManager::OnPhidgetServoCurrentChanged(int serial, int index, double current)
{
	NOTIFY_APP2(OnServoCurrentChanged, index, current);
}

void ApplicationManager::OnPhidgetServoPositionChanged(int serial, int index, double position)
{
	NOTIFY_APP2(OnServoPositionChanged, index, position);
}

void ApplicationManager::OnPhidgetServoVelocityChanged(int serial, int index, double velocity)
{
	NOTIFY_APP2(OnServoVelocityChanged, index, velocity);
}

void ApplicationManager::OnWtDigitalOutputChanged(const PhidgetApplication* trigger_app, int serial, int index, bool state)
{
	SYNC_APP2(OnDigitalOutputChanged, index, state);
}

void ApplicationManager::OnWtOnboardLEDChanged(const PhidgetApplication* trigger_app, int serial, bool state)
{
	SYNC_APP1(OnOnboardLEDChanged, state);
}

void ApplicationManager::OnWtRatiometricChanged(const PhidgetApplication* trigger_app, int serial, bool state)
{
	SYNC_APP1(OnRatiometricChanged, state);
}

void ApplicationManager::OnWtRFIDAntennaChanged(const PhidgetApplication* trigger_app, int serial, bool state)
{
	SYNC_APP1(OnRFIDAntennaChanged, state);
}

void ApplicationManager::OnWtServoAccelerationChanged(const PhidgetApplication* trigger_app, int serial, int index, double acceleration)
{
	SYNC_APP2(OnServoAccelerationChanged, index, acceleration);
}

void ApplicationManager::OnWtServoSpeedRampingChanged(const PhidgetApplication* trigger_app, int serial, int index, bool speed_ramping)
{
	SYNC_APP2(OnServoSpeedRampingChanged, index, speed_ramping);
}

void ApplicationManager::OnWtServoTypeChanged(const PhidgetApplication* trigger_app, int serial, int index, CPhidget_ServoType type)
{
	SYNC_APP2(OnServoTypeChanged, index, type);
}

void ApplicationManager::OnWtServoVelocityLimitChanged(const PhidgetApplication* trigger_app, int serial, int index, double velocity_limit)
{
	SYNC_APP2(OnServoVelocityLimitChanged, index, velocity_limit);
}

void ApplicationManager::OnWtTagWritten(const PhidgetApplication* trigger_app, int serial, const char* new_tag, CPhidgetRFID_Protocol protocol)
{
	SYNC_APP2(OnTagWritten, new_tag, protocol);
}

void ApplicationManager::AddApplicationToList(PhidgetApplication* application)
{
	Lock();

	if (!application || FindApplicationInList(application))
	{
		Unlock();
		return;
	}

	PhidgetApplicationInfo* item = new PhidgetApplicationInfo();

	if (m_application_list)
		m_application_list->m_previous_application = item;

	item->m_application = application;
	item->m_previous_application = NULL;
	item->m_next_application = m_application_list;

	m_application_list = item;
	
	Unlock();
}

void ApplicationManager::RemoveApplicationFromList(PhidgetApplication* application)
{
	Lock();

	PhidgetApplicationInfo* item = FindApplicationInList(application);
	if (!item)
	{
		Unlock();
		return;
	}

	if (item->m_previous_application)
		item->m_previous_application->m_next_application = item->m_next_application;
	
	if (item->m_next_application)
		item->m_next_application->m_previous_application = item->m_previous_application;
	
	if (m_application_list == item)
		m_application_list = item->m_next_application;
	
	delete item;

	Unlock();
}

PhidgetApplicationInfo* ApplicationManager::FindApplicationInList(const PhidgetApplication* application)
{
	Lock();

	PhidgetApplicationInfo* item = m_application_list;
	while (item)
	{
		if (item->m_application == application)
			break;

		item = item->m_next_application;
	}

	Unlock();
	return item;
}
