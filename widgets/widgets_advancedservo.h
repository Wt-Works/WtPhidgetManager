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
	ServoWidget(PhidgetsAdvancedServo* phidget, int index);
	~ServoWidget();

	Wt::WContainerWidget* CreateWidget();
	void SetVelocity(double velocity);
	void SetPosition(double position);
	void SetCurrent(double current);

private:
#if 0
	/* In Wt thread */
	void OnWtFunctionChanged();
#endif
private:
	PhidgetsAdvancedServo* m_phidget;
	int m_index;
//	Wt::WComboBox* m_servo_dropdown;
  Wt::WSlider* m_position_slider;
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
	virtual void OnServoVelocityChanged(int index, double velocity);
	virtual void OnServoPositionChanged(int index, double position);
	virtual void OnServoCurrentChanged(int index, double current);

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
