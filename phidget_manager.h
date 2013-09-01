#ifndef _PHIDGET_MANAGER_H_
#define _PHIDGET_MANAGER_H_

/*
 *  phidget_manager.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidget21.h"
#include <pthread.h>

#include "global.h"

class PhidgetApplication;
class PhidgetsCommon;

struct PhidgetsInfo {
	PhidgetsCommon* m_phidget;
	PhidgetsInfo* m_previous_phidget;
	PhidgetsInfo* m_next_phidget;
};


class PhidgetManager
{
public:
  PhidgetManager();
  ~PhidgetManager();

public:
  int OnAttach(CPhidgetHandle handle);
  int OnDetach(int serial);

	CPhidgetManagerHandle GetPhidgetManager() const {return m_manager;}

public:
	void RequestAllPhidgets(PhidgetApplication* app);
	void RequestTab(PhidgetApplication* app, int serial);

public:
	PhidgetsInfo* FindPhidgetBySerial(int serial);
	PhidgetsInfo* FindPhidgetByHandle(CPhidgetHandle handle);
	PhidgetsInfo* FindPhidgetInList(const PhidgetsCommon* phidget);

private:
	void AddPhidgetToList(PhidgetsCommon* phidget);
	void RemovePhidgetFromList(PhidgetsCommon* phidget);

private:
	void Lock() {pthread_mutex_lock(&m_phidget_mutex);}
	void Unlock() {pthread_mutex_unlock(&m_phidget_mutex);}

private:
  CPhidgetManagerHandle m_manager;
	PhidgetsInfo* m_phidget_list;

	pthread_mutex_t m_phidget_mutex;
};

#endif // _PHIDGET_MANAGER_H_
