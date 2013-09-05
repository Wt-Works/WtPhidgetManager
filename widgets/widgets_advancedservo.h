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
#if 0
	void SetRatiometric(bool ratiometric);
	void SetValue(int sensor_value);
#endif
private:
#if 0
	/* In Wt thread */
	void OnWtFunctionChanged();
#endif
private:
	PhidgetsAdvancedServo* m_phidget;
	int m_index;
#if 0
	bool m_ratiometric;
  Wt::WLineEdit* m_raw_value_edit;
	Wt::WComboBox* m_function_dropdown;
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
#if 0
	virtual void OnDigitalInputChanged(int index, bool state);
  virtual void OnDigitalOutputChanged(int index, bool state);
	virtual void OnRatiometricChanged(bool state);
  virtual void OnSensorChanged(int index, int sensor_value);
#endif
protected:
	virtual Wt::WContainerWidget* CreateWidget();

private:
	/* In Wt thread */
	void OnWtRatiometricStateChanged(Wt::WCheckBox* checkbox);
	void OnWtOutputStateChanged(Wt::WCheckBox* checkbox);

private:
#if 0
	void UpdateSensorFunctionDropdowns(bool ratiometric);
#endif
private:
	PhidgetsAdvancedServo* m_phidget;
#if 0
	Wt::WCheckBox* m_ratiometric_checkbox;
	SensorWidget** m_sensor_widget_array;
	int m_sensor_widget_array_length;
	Wt::WCheckBox** m_input_checkbox_array;
	int m_input_checkbox_array_length;
	Wt::WCheckBox** m_output_checkbox_array;
	int m_output_checkbox_array_length;
#endif
};

#endif // _WIDGETS_ADVANCEDSERVO_H_
