#ifndef _WIDGETS_INTERFACEKIT_H_
#define _WIDGETS_INTERFACEKIT_H_

/*
 *  widgets_interfacekit.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_common.h"

class PhidgetsInterfaceKit;

class SensorWidget
{
public:
	SensorWidget(PhidgetsInterfaceKit* phidget, int index);
	~SensorWidget();

	Wt::WContainerWidget* CreateWidget();
	void SetValue(int sensor_value);
	
private:
	PhidgetsInterfaceKit* m_phidget;
	int m_index;
  Wt::WLineEdit* m_raw_value_edit;
	Wt::WComboBox* m_function_dropdown;
  Wt::WLineEdit* m_converted_value_edit;
};

class WidgetsInterfaceKit : public WidgetsCommon
{
public:
  WidgetsInterfaceKit(PhidgetsInterfaceKit* phidget, PhidgetApplication* application);
  virtual ~WidgetsInterfaceKit();

public: //From WidgetsCommon
	virtual int GetSerial();
	virtual void OnDigitalInputChanged(int index, bool state);
  virtual void OnDigitalOutputChanged(int index, bool state);
	virtual void OnRatiometricChanged(bool state);
  virtual void OnSensorChanged(int index, int sensor_value);

protected:
	virtual Wt::WContainerWidget* CreateWidget();

private:
	/* In Wt thread */
	void OnWtRatiometricStateChanged(Wt::WCheckBox* checkbox);
	void OnWtOutputStateChanged(Wt::WCheckBox* checkbox);

private:
	PhidgetsInterfaceKit* m_phidget;
	
	Wt::WCheckBox* m_ratiometric_checkbox;
	SensorWidget** m_sensor_widget_array;
	int m_sensor_widget_array_length;
	Wt::WCheckBox** m_input_checkbox_array;
	int m_input_checkbox_array_length;
	Wt::WCheckBox** m_output_checkbox_array;
	int m_output_checkbox_array_length;
};

#endif // _WIDGETS_INTERFACEKIT_H_
