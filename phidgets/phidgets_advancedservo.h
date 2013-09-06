#ifndef _PHIDGETS_ADVANCEDSERVO_H_
#define _PHIDGETS_ADVANCEDSERVO_H_

/*
 *  phidgets_advancedservo.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_common.h"


class PhidgetsAdvancedServo : public PhidgetsCommon
{
public:
  PhidgetsAdvancedServo(int serial);
  virtual ~PhidgetsAdvancedServo();

public: //From PhidgetsCommon
	virtual bool Init();
	virtual CPhidgetHandle GetHandle() {return reinterpret_cast<CPhidgetHandle>(m_advancedservo_handle);}
	virtual WidgetsCommon* CreateWidget(PhidgetApplication* application);

public:
	virtual CPhidgetAdvancedServoHandle GetNativeHandle() const {return m_advancedservo_handle;}

public:
	int OnPhidgetAttach(CPhidgetHandle handle);
	int OnPhidgetDetach(CPhidgetHandle handle);
	int OnVelocityChangeHandler(CPhidgetAdvancedServoHandle handle, int index, double velocity);
	int OnPositionChangeHandler(CPhidgetAdvancedServoHandle handle, int index, double position);
	int OnCurrentChangeHandler(CPhidgetAdvancedServoHandle handle, int index, double current);

private:
	CPhidgetAdvancedServoHandle m_advancedservo_handle;
};

#endif // _PHIDGETS_ADVANCEDSERVO_H_
