#ifndef _APP_MANAGER_H_
#define _APP_MANAGER_H_

/*
 *  app_manager.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidget21.h"
#include <pthread.h>


class PhidgetApplication;
struct PhidgetApplicationInfo {
	PhidgetApplication* m_application;
	PhidgetApplicationInfo* m_previous_application;
	PhidgetApplicationInfo* m_next_application;
};


class ApplicationManager
{
public:
  ApplicationManager();
  ~ApplicationManager();

public:
	void OnAppCreated(PhidgetApplication* app);
	void OnAppDestroyed(PhidgetApplication* app);
	
public: //Events from physical Phidgets
  void OnPhidgetAttached(int serial);
  void OnPhidgetDetached(int serial);
  void OnPhidgetDigitalInputChanged(int serial, int index, bool state);
  void OnPhidgetGotRFIDTag(int serial, const char* tag, CPhidgetRFID_Protocol protocol);
  void OnPhidgetLostRFIDTag(int serial);
  void OnPhidgetSensorChanged(int serial, int index, int sensor_value);
	void OnPhidgetServoAccelerationChanged(int serial, int index, double acceleration);
	void OnPhidgetServoVelocityChanged(int serial, int index, double velocity);
	void OnPhidgetServoPositionChanged(int serial, int index, double position);
	void OnPhidgetServoCurrentChanged(int serial, int index, double current);

public: //Events from browser. Sync other applications
	void OnWtDigitalOutputChanged(const PhidgetApplication* trigger_app, int serial, int index, bool state);
	void OnWtOnboardLEDChanged(const PhidgetApplication* trigger_app, int serial, bool state);
	void OnWtRatiometricChanged(const PhidgetApplication* trigger_app, int serial, bool state);
	void OnWtRFIDAntennaChanged(const PhidgetApplication* trigger_app, int serial, bool state);
	void OnWtServoTypeChanged(const PhidgetApplication* trigger_app, int serial, int index, CPhidget_ServoType type);
	void OnWtTagWritten(const PhidgetApplication* trigger_app, int serial, const char* new_tag, CPhidgetRFID_Protocol protocol);

private:
	PhidgetApplicationInfo* GetApplicationList() {return m_application_list;}
	PhidgetApplicationInfo* FindApplicationInList(const PhidgetApplication* application);
	void AddApplicationToList(PhidgetApplication* application);
	void RemoveApplicationFromList(PhidgetApplication* application);

private:
	void Lock() {pthread_mutex_lock(&m_application_mutex);}
	void Unlock() {pthread_mutex_unlock(&m_application_mutex);}

private:
	PhidgetApplicationInfo* m_application_list;

	pthread_mutex_t m_application_mutex;
};

#endif // _APP_MANAGER_H_
