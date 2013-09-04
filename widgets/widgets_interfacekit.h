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
	SensorWidget(PhidgetsInterfaceKit* phidget, int index, bool ratiometric);
	~SensorWidget();

	Wt::WContainerWidget* CreateWidget();
	void SetRatiometric(bool ratiometric);
	void SetValue(int sensor_value);
	
private:
	/* In Wt thread */
	void OnWtFunctionChanged();

private:
	PhidgetsInterfaceKit* m_phidget;
	int m_index;
	bool m_ratiometric;
  Wt::WLineEdit* m_raw_value_edit;
	Wt::WComboBox* m_function_dropdown;
  Wt::WLineEdit* m_converted_value_edit;
	int m_default_ratiometric_index;
	int m_default_non_ratiometric_index;
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
	void UpdateSensorFunctionDropdowns(bool ratiometric);

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
