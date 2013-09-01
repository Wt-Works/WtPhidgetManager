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


class PhidgetApplication;
class PhidgetsCommon;

class WidgetsCommon
{
public:
  WidgetsCommon(PhidgetApplication* application);
  virtual ~WidgetsCommon();

public:
	virtual void OnDigitalInputChanged(int /*index*/, bool /*state*/) {}
  virtual void OnDigitalOutputChanged(int /*index*/, bool /*state*/) {}
  virtual void OnGotRFIDTag(const char* /*tag*/, CPhidgetRFID_Protocol /*protocol*/) {}
  virtual void OnLostRFIDTag() {}
	virtual void OnOnboardLEDChanged(bool /*state*/) {}
	virtual void OnRFIDAntennaChanged(bool /*state*/) {}
	virtual void OnRatiometricChanged(bool /*state*/) {}
  virtual void OnSensorChanged(int /*index*/, int /*sensor_value*/) {}
	virtual void OnTagWritten(const char* /*new_tag*/, CPhidgetRFID_Protocol /*protocol*/) {}

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
