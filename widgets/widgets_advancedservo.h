#ifndef _WIDGETS_ADVANCEDSERVO_H_
#define _WIDGETS_ADVANCEDSERVO_H_

/*
 *  widgets_advancedservo.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_common.h"

class PhidgetsAdvancedServo;

class ServoWidget
{
public:
	ServoWidget(PhidgetsAdvancedServo* phidget, PhidgetApplication* application, int serial, int index);
	~ServoWidget();

	Wt::WContainerWidget* CreateWidget();
	void SetType(CPhidget_ServoType type);
	void SetAcceleration(double acceleration);
	void SetCurrent(double current);
	void SetPosition(double position);
	void SetVelocity(double velocity);

private:
	/* In Wt thread */
	void OnWtTypeChanged();

private:
	void UpdateControlValues();

private:
	PhidgetsAdvancedServo* m_phidget;
	PhidgetApplication* m_application;
	int m_serial;
	int m_index;
	Wt::WComboBox* m_servo_type_dropdown;
  Wt::WSlider* m_acceleration_slider;
  Wt::WSlider* m_velocity_slider;
  Wt::WSlider* m_position_slider;
  Wt::WLineEdit* m_current_value_edit; //As in, electrical current
#if 0
  Wt::WLineEdit* m_converted_value_edit;
	int m_default_ratiometric_index;
	int m_default_non_ratiometric_index;
#endif
};

class WidgetsAdvancedServo : public WidgetsCommon
{
public:
  WidgetsAdvancedServo(PhidgetsAdvancedServo* phidget, PhidgetApplication* application);
  virtual ~WidgetsAdvancedServo();

public: //From WidgetsCommon
	virtual int GetSerial();
	virtual void OnServoAccelerationChanged(int index, double acceleration);
	virtual void OnServoCurrentChanged(int index, double current);
	virtual void OnServoPositionChanged(int index, double position);
	virtual void OnServoTypeChanged(int index, CPhidget_ServoType type);
	virtual void OnServoVelocityChanged(int index, double velocity);

protected:
	virtual Wt::WContainerWidget* CreateWidget();

private:
	/* In Wt thread */
	//void OnWtRatiometricStateChanged(Wt::WCheckBox* checkbox);
	//void OnWtOutputStateChanged(Wt::WCheckBox* checkbox);

private:
	PhidgetsAdvancedServo* m_phidget;
	ServoWidget** m_servo_widget_array;
	int m_servo_widget_array_length;
};

#endif // _WIDGETS_ADVANCEDSERVO_H_
