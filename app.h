#ifndef _PHIDGET_APP_H_
#define _PHIDGET_APP_H_

/*
 *  app.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WTabWidget>
#include "phidget21.h"

#include "widgets/widgets_common.h"


struct TabInfo {
	int m_serial;
	WidgetsCommon* m_widget;
	TabInfo* m_previous_tab;
	TabInfo* m_next_tab;
};


class PhidgetApplication : public Wt::WApplication
{
public:
  PhidgetApplication(const Wt::WEnvironment& env);
  ~PhidgetApplication();
	
	void SetWidget(int serial, WidgetsCommon* widget, const Wt::WString& label);

public:
  void OnAttached(int serial);
  void OnDetached(int serial);
  void OnDigitalInputChanged(int serial, int index, bool state);
  void OnDigitalOutputChanged(int serial, int index, bool state);
  void OnGotRFIDTag(int serial, const char* tag, CPhidgetRFID_Protocol protocol);
  void OnLostRFIDTag(int serial);
	void OnOnboardLEDChanged(int serial, bool state);
	void OnRatiometricChanged(int serial, bool state);
	void OnRFIDAntennaChanged(int serial, bool state);
  void OnSensorChanged(int serial, int index, int sensor_value);
	void OnServoAccelerationChanged(int serial, int index, double acceleration);
	void OnServoCurrentChanged(int serial, int index, double current);
	void OnServoPositionChanged(int serial, int index, double position);
  void OnServoTypeChanged(int serial, int index, CPhidget_ServoType type);
	void OnServoVelocityChanged(int serial, int index, double velocity);
	void OnTagWritten(int serial, const char* new_tag, CPhidgetRFID_Protocol protocol);

private:
	TabInfo* FindTabInfoBySerial(int serial);
	WidgetsCommon* FindWidgetBySerial(int serial);

private:
	void Lock() {pthread_mutex_lock(&m_tab_mutex);}
	void Unlock() {pthread_mutex_unlock(&m_tab_mutex);}

private:
	Wt::WTabWidget* m_tab_widget;

	TabInfo* m_tab_list;

	pthread_mutex_t m_tab_mutex;
};

#endif // _PHIDGET_APP_H_
