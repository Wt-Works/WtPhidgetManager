/*
 *  app.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "app.h"

#include <Wt/WContainerWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WServer>

#include "app_manager.h"
#include "phidget_manager.h"

#define SYNC_WIDGET(x)      WidgetsCommon* widget = FindWidgetBySerial(serial);\
                            if (widget) widget->x();

#define SYNC_WIDGET1(x,y)   WidgetsCommon* widget = FindWidgetBySerial(serial);\
                            if (widget) widget->x(y);

#define SYNC_WIDGET2(x,y,z) WidgetsCommon* widget = FindWidgetBySerial(serial);\
                            if (widget) widget->x(y,z);
                       

PhidgetApplication::PhidgetApplication(const Wt::WEnvironment& env)
: Wt::WApplication(env),
  m_tab_widget(NULL),
  m_tab_list(NULL)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&m_tab_mutex, &attr);
	pthread_mutexattr_destroy(&attr);

	enableUpdates(true);
	setTitle("Phidget Manager");
 
  m_tab_widget = new Wt::WTabWidget(root());
	m_tab_widget->setStyleClass("tabwidget");

	::GetApplicationManager()->OnAppCreated(this);
	::GetPhidgetManager()->RequestAllPhidgets(this);
}

PhidgetApplication::~PhidgetApplication()
{
	Lock();

	::GetApplicationManager()->OnAppDestroyed(this);

	TabInfo* item = m_tab_list;
	TabInfo* next;
	while (item)
	{
		next = item->m_next_tab;
		delete item;
		item = next;
	}
	m_tab_list = NULL;
	
	Unlock();
	pthread_mutex_destroy(&m_tab_mutex);
}

void PhidgetApplication::SetWidget(int serial, WidgetsCommon* widget, const Wt::WString& label)
{
	if (!widget)
		return;

	Lock();

	TabInfo* item = FindTabInfoBySerial(serial);
	if (!item)
	{
		item = new TabInfo();
		item->m_serial = serial;
		item->m_previous_tab = NULL;
		item->m_next_tab = m_tab_list;
		if (m_tab_list)
		{
			m_tab_list->m_previous_tab = item;
		}
		m_tab_list = item;
	}
	
	item->m_widget = widget;

	Wt::WContainerWidget* tab_widget = item->m_widget->GetWidget();
	m_tab_widget->addTab(tab_widget, label, Wt::WTabWidget::PreLoading);
	m_tab_widget->setCurrentWidget(tab_widget);

	Unlock();

	triggerUpdate();
}

void PhidgetApplication::OnAttached(int serial)
{
	Lock();

	WidgetsCommon* widget = FindWidgetBySerial(serial);
	if (widget)
	{
		Unlock();
		return;
	}

	::GetPhidgetManager()->RequestTab(this, serial); //Will end up in a call to SetWidget

	Unlock();
}

void PhidgetApplication::OnDetached(int serial)
{
	Lock();

	TabInfo* item = FindTabInfoBySerial(serial);
	if (!item)
	{
		Unlock();
		return;
	}

	if (item->m_previous_tab)
	{
		item->m_previous_tab->m_next_tab = item->m_next_tab;
	}

	if (item->m_next_tab)
	{
		item->m_next_tab->m_previous_tab = item->m_previous_tab;
	}

	if (m_tab_list == item)
	{
		m_tab_list = item->m_next_tab;
	}
	
	m_tab_widget->removeTab(item->m_widget->GetWidget());
	triggerUpdate();

	delete item;

	Unlock();
}

void PhidgetApplication::OnDigitalInputChanged(int serial, int index, bool state)
{
	SYNC_WIDGET2(OnDigitalInputChanged, index, state);
}

void PhidgetApplication::OnDigitalOutputChanged(int serial, int index, bool state)
{
	SYNC_WIDGET2(OnDigitalOutputChanged, index, state);
}

void PhidgetApplication::OnGotRFIDTag(int serial, const char* tag, CPhidgetRFID_Protocol protocol)
{
	SYNC_WIDGET2(OnGotRFIDTag, tag, protocol);
}

void PhidgetApplication::OnLostRFIDTag(int serial)
{
	SYNC_WIDGET(OnLostRFIDTag);
}

void PhidgetApplication::OnOnboardLEDChanged(int serial, bool state)
{
	SYNC_WIDGET1(OnOnboardLEDChanged, state);
}

void PhidgetApplication::OnRatiometricChanged(int serial, bool state)
{
	SYNC_WIDGET1(OnRatiometricChanged, state);
}

void PhidgetApplication::OnRFIDAntennaChanged(int serial, bool state)
{
	SYNC_WIDGET1(OnRFIDAntennaChanged, state);
}

void PhidgetApplication::OnSensorChanged(int serial, int index, int sensor_value)
{
	SYNC_WIDGET2(OnSensorChanged, index, sensor_value);
}

void PhidgetApplication::OnServoAccelerationChanged(int serial, int index, double acceleration)
{
	SYNC_WIDGET2(OnServoAccelerationChanged, index, acceleration);
}

void PhidgetApplication::OnServoCurrentChanged(int serial, int index, double current)
{
	SYNC_WIDGET2(OnServoCurrentChanged, index, current);
}

void PhidgetApplication::OnServoPositionChanged(int serial, int index, double position)
{
	SYNC_WIDGET2(OnServoPositionChanged, index, position);
}

void PhidgetApplication::OnServoSpeedRampingChanged(int serial, int index, bool speed_ramping)
{
	SYNC_WIDGET2(OnServoSpeedRampingChanged, index, speed_ramping);
}

void PhidgetApplication::OnServoTypeChanged(int serial, int index, CPhidget_ServoType type)
{
	SYNC_WIDGET2(OnServoTypeChanged, index, type);
}

void PhidgetApplication::OnServoVelocityChanged(int serial, int index, double velocity)
{
	SYNC_WIDGET2(OnServoVelocityChanged, index, velocity);
}

void PhidgetApplication::OnServoVelocityLimitChanged(int serial, int index, double velocity_limit)
{
	SYNC_WIDGET2(OnServoVelocityLimitChanged, index, velocity_limit);
}

void PhidgetApplication::OnTagWritten(int serial, const char* new_tag, CPhidgetRFID_Protocol protocol)
{
	SYNC_WIDGET2(OnTagWritten, new_tag, protocol);
}

TabInfo* PhidgetApplication::FindTabInfoBySerial(int serial)
{
	Lock();

	TabInfo* tab = m_tab_list;
	while (tab)
	{
		if (tab->m_serial == serial)
			break;

		tab = tab->m_next_tab;
	}

	Unlock();
	return tab;
}

WidgetsCommon* PhidgetApplication::FindWidgetBySerial(int serial)
{
	TabInfo* tab = FindTabInfoBySerial(serial);
	return tab ? tab->m_widget : NULL;
}
