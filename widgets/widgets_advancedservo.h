#ifndef _WIDGETS_ADVANCEDSERVO_H_
#define _WIDGETS_ADVANCEDSERVO_H_

/*
 *  widgets_advancedservo.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_common.h"

class WidgetsAdvancedServo;
class ServoWidget
{
public:
	ServoWidget(WidgetsAdvancedServo* widget, const Wt::WLength& left_column_width, PhidgetApplication* application, int serial, int index);
	~ServoWidget();

	Wt::WContainerWidget* CreateWidget();
	void SetType(CPhidget_ServoType type);
	void SetSpeedRamping(bool speed_ramping);
	void SetAcceleration(double acceleration);
	void SetCurrent(double current);
	void SetPosition(double position);
	void SetVelocity(double velocity);
	void SetVelocityLimit(double velocity_limit);

private:
	/* In Wt thread */
	void OnWtAccelerationChanged(Wt::WSlider* slider);
	void OnWtPositionChanged(Wt::WSlider* slider);
	void OnWtVelocityLimitChanged(Wt::WSlider* slider);
	void OnWtSpeedRampingChanged(Wt::WCheckBox* checkbox);
	void OnWtTypeChanged();

private:
	void UpdateControlValues();

private:
	WidgetsAdvancedServo* m_widget;
	Wt::WLength m_left_column_width;
	PhidgetApplication* m_application;
	int m_serial;
	int m_index;
	Wt::WComboBox* m_servo_type_dropdown;
	Wt::WCheckBox* m_speed_ramping_checkbox;
  Wt::WSlider* m_acceleration_slider;
  Wt::WLineEdit* m_velocity_value_edit;
  Wt::WSlider* m_velocity_limit_slider;
  Wt::WSlider* m_position_slider;
  Wt::WLineEdit* m_current_value_edit; //As in, electrical current
};

class PhidgetsAdvancedServo;
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
	virtual void OnServoSpeedRampingChanged(int index, bool speed_ramping);
	virtual void OnServoTypeChanged(int index, CPhidget_ServoType type);
	virtual void OnServoVelocityChanged(int index, double velocity);
	virtual void OnServoVelocityLimitChanged(int index, double velocity_limit);

public:
	PhidgetsAdvancedServo* GetPhidget() const {return m_phidget;}
	
protected:
	virtual Wt::WContainerWidget* CreateWidget();

private:
	/* In Wt thread */

private:
	PhidgetsAdvancedServo* m_phidget;
	ServoWidget** m_servo_widget_array;
	int m_servo_widget_array_length;
};

#endif // _WIDGETS_ADVANCEDSERVO_H_
