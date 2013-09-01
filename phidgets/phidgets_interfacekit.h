#ifndef _PHIDGETS_INTERFACEKIT_H_
#define _PHIDGETS_INTERFACEKIT_H_

/*
 *  phidgets_interfacekit.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_common.h"


class PhidgetsInterfaceKit : public PhidgetsCommon
{
public:
  PhidgetsInterfaceKit(int serial);
  virtual ~PhidgetsInterfaceKit();

public: //From PhidgetsCommon
	virtual bool Init();
	virtual CPhidgetHandle GetHandle() {return reinterpret_cast<CPhidgetHandle>(m_interfacekit_handle);}
	virtual WidgetsCommon* CreateWidget(PhidgetApplication* application);

public:
	virtual CPhidgetInterfaceKitHandle GetNativeHandle() const {return m_interfacekit_handle;}

public:
	int OnPhidgetAttach(CPhidgetHandle handle);
	int OnPhidgetDetach(CPhidgetHandle handle);
	int OnPhidgetInputChangeHandler(CPhidgetInterfaceKitHandle handle, int index, int input_state);
	int OnPhidgetSensorChangeHandler(CPhidgetInterfaceKitHandle handle, int index, int sensor_value);

private:
	CPhidgetInterfaceKitHandle m_interfacekit_handle;
};

#endif // _PHIDGETS_INTERFACEKIT_H_
