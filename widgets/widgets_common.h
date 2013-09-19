#ifndef _WIDGETS_COMMON_H_
#define _WIDGETS_COMMON_H_

/*
 *  widgets_common.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WContainerWidget>
#include <Wt/WLength>
#include "phidget21.h"

#include "../global.h"


class PhidgetApplication;
class PhidgetsCommon;

class WidgetsCommon
{
public:
  WidgetsCommon(PhidgetApplication* application);
  virtual ~WidgetsCommon();

public:
	virtual void OnDigitalInputChanged(int UNUSED(index), bool UNUSED(state)) {}
  virtual void OnDigitalOutputChanged(int UNUSED(index), bool UNUSED(state)) {}
  virtual void OnGotRFIDTag(const char* UNUSED(tag), CPhidgetRFID_Protocol UNUSED(protocol)) {}
  virtual void OnLostRFIDTag() {}
	virtual void OnOnboardLEDChanged(bool UNUSED(state)) {}
	virtual void OnRFIDAntennaChanged(bool UNUSED(state)) {}
	virtual void OnRatiometricChanged(bool UNUSED(state)) {}
  virtual void OnSensorChanged(int UNUSED(index), int UNUSED(sensor_value)) {}
	virtual void OnServoAccelerationChanged(int UNUSED(index), double UNUSED(acceleration)) {}
	virtual void OnServoCurrentChanged(int UNUSED(index), double UNUSED(current)) {}
	virtual void OnServoPositionChanged(int UNUSED(index), double UNUSED(position)) {}
	virtual void OnServoSpeedRampingChanged(int UNUSED(index), bool UNUSED(speed_ramping)) {}
	virtual void OnServoTypeChanged(int UNUSED(index), CPhidget_ServoType UNUSED(type)) {}
	virtual void OnServoVelocityChanged(int UNUSED(index), double UNUSED(velocity)) {}
	virtual void OnServoVelocityLimitChanged(int UNUSED(index), double UNUSED(velocity_limit)) {}
	virtual void OnTagWritten(const char* UNUSED(new_tag), CPhidgetRFID_Protocol UNUSED(protocol)) {}

public:
	Wt::WContainerWidget* GetWidget();
	PhidgetApplication* GetApplication() const {return m_application;}
	virtual int GetSerial() = 0;

protected:
	virtual Wt::WContainerWidget* CreateWidget();
	virtual Wt::WLength GetLeftColumnWidth();

private:
	Wt::WContainerWidget* m_widget;
	PhidgetApplication* m_application;
};

#endif // _WIDGETS_COMMON_H_
