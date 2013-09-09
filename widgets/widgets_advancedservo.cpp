/*
 *  widgets_advancedservo.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_advancedservo.h"
#include <Wt/WComboBox>
#include <Wt/WHBoxLayout>
#include <Wt/WLineEdit>
#include <Wt/WSlider>
#if 0
#include <Wt/WCheckBox>
#include <Wt/WGroupBox>
#include <Wt/WServer>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WText>
#include <Wt/WVBoxLayout>
#endif
#include "../app.h"
#include "../app_manager.h"
#include "../global.h"
#include "../phidgets/phidgets_advancedservo.h"
#include "../phidget_manager.h"
#include "../utils/servo.h"


ServoWidget::ServoWidget(PhidgetsAdvancedServo* phidget, int index)
: m_phidget(phidget),
  m_index(index)
{
}

ServoWidget::~ServoWidget()
{
}

Wt::WContainerWidget* ServoWidget::CreateWidget()
{
	Wt::WContainerWidget* servo_container = new Wt::WContainerWidget();
  Wt::WHBoxLayout* hbox = new Wt::WHBoxLayout(servo_container);

	m_servo_type_dropdown = new Wt::WComboBox();
	::GetServoUtils()->PopulateTypeDropdown(m_servo_type_dropdown);
//	m_servo_type_dropdown->activated().connect(boost::bind(&ServoWidget::OnWtTypeChanged, this));
	hbox->addWidget(m_servo_type_dropdown);
	
  m_position_slider = new Wt::WSlider();
	hbox->addWidget(m_position_slider);

  m_velocity_slider = new Wt::WSlider();
	hbox->addWidget(m_velocity_slider);

	m_current_value_edit = new Wt::WLineEdit();
	m_current_value_edit->setEnabled(false);
	hbox->addWidget(m_current_value_edit);

	return servo_container;
}

void ServoWidget::SetVelocity(double UNUSED(velocity))
{
}

void ServoWidget::SetPosition(double position)
{
	m_position_slider->setValue(position);
}

void ServoWidget::SetCurrent(double UNUSED(current))
{
}

#if 0
void SensorWidget::SetRatiometric(bool ratiometric)
{
	if (m_ratiometric)
		m_default_ratiometric_index = m_function_dropdown->currentIndex();
	else
		m_default_non_ratiometric_index = m_function_dropdown->currentIndex();

	m_ratiometric = ratiometric;
	::GetSensorFunctions()->PopulateDropdown(m_function_dropdown, m_ratiometric);
	m_function_dropdown->setCurrentIndex(m_ratiometric ? m_default_ratiometric_index : m_default_non_ratiometric_index);
	OnWtFunctionChanged();
}

void SensorWidget::SetValue(int sensor_value)
{
	m_raw_value_edit->setText(Wt::WString::tr("GeneralArg").arg(sensor_value));
	m_converted_value_edit->setText(::GetSensorFunctions()->ConvertSensorValue(m_function_dropdown->currentIndex(), sensor_value, m_ratiometric));
}

void SensorWidget::OnWtFunctionChanged()
{
	const Wt::WString& value = m_raw_value_edit->text();
	if (value.empty())
		return;

	SetValue(StringUtil::ToInt(value));
}
#endif


WidgetsAdvancedServo::WidgetsAdvancedServo(PhidgetsAdvancedServo* phidget, PhidgetApplication* application)
: WidgetsCommon(application),
  m_phidget(phidget),
	m_servo_widget_array(NULL),
	m_servo_widget_array_length(0)
{
}

WidgetsAdvancedServo::~WidgetsAdvancedServo()
{
	int i;
	for (i=0; i<m_servo_widget_array_length; i++)
	{
		delete m_servo_widget_array[i];
	}
	delete[] m_servo_widget_array;
}

int WidgetsAdvancedServo::GetSerial()
{
	return m_phidget->GetSerial();
}

void WidgetsAdvancedServo::OnServoVelocityChanged(int index, double velocity)
{
	if (0<=index && m_servo_widget_array_length>index)
	{
		m_servo_widget_array[index]->SetVelocity(velocity);
		GetApplication()->triggerUpdate();
	}
}

void WidgetsAdvancedServo::OnServoPositionChanged(int index, double position)
{
	if (0<=index && m_servo_widget_array_length>index)
	{
		m_servo_widget_array[index]->SetPosition(position);
		GetApplication()->triggerUpdate();
	}
}

void WidgetsAdvancedServo::OnServoCurrentChanged(int index, double current)
{
	if (0<=index && m_servo_widget_array_length>index)
	{
		m_servo_widget_array[index]->SetCurrent(current);
		GetApplication()->triggerUpdate();
	}
}

Wt::WContainerWidget* WidgetsAdvancedServo::CreateWidget()
{
	Wt::WContainerWidget* tab_container = new Wt::WContainerWidget();
#if 0
  Wt::WVBoxLayout* vbox = new Wt::WVBoxLayout(tab_container);
	
	Wt::WGroupBox* spesific_box = new Wt::WGroupBox(Wt::WString::tr("PhidgetInterfaceKit"));
	vbox->addWidget(spesific_box);

  Wt::WHBoxLayout* hbox = new Wt::WHBoxLayout(spesific_box);
	Wt::WTable* table = new Wt::WTable();
	hbox->addWidget(table);

	table->columnAt(0)->setWidth(GetLeftColumnWidth());
	table->columnAt(1)->setWidth(Wt::WLength::Auto);

	int row = 0;
  int i, int_value;
	bool ratiometric = true;

	/* Ratiometric */
  table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Ratiometric")));
  m_ratiometric_checkbox = new Wt::WCheckBox();
  table->elementAt(row++, 1)->addWidget(m_ratiometric_checkbox);
	m_ratiometric_checkbox->changed().connect(boost::bind(&WidgetsInterfaceKit::OnWtRatiometricStateChanged, this, m_ratiometric_checkbox));
  if (EPHIDGET_OK == CPhidgetInterfaceKit_getRatiometric(m_phidget->GetNativeHandle(), &int_value))
  {
		ratiometric = (PTRUE == int_value);
    m_ratiometric_checkbox->setChecked(ratiometric);
  }

  /* Sensors */
	if (EPHIDGET_OK == CPhidgetInterfaceKit_getSensorCount(m_phidget->GetNativeHandle(), &int_value))
	{
		m_sensor_widget_array_length = int_value;
		m_sensor_widget_array = new SensorWidget*[m_sensor_widget_array_length];

		for (i=0; i<m_sensor_widget_array_length; i++)
		{
			m_sensor_widget_array[i] = new SensorWidget(m_phidget, i, ratiometric);

			table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("SensorArgs").arg(i)));

      table->elementAt(row++, 1)->addWidget(m_sensor_widget_array[i]->CreateWidget());
		}
	}

	/* Input */
	if (EPHIDGET_OK == CPhidgetInterfaceKit_getInputCount(m_phidget->GetNativeHandle(), &int_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Input")));

		Wt::WTable* input_table = new Wt::WTable();
		table->elementAt(row++, 1)->addWidget(input_table);
		
		m_input_checkbox_array_length = int_value;
		m_input_checkbox_array = new Wt::WCheckBox*[m_input_checkbox_array_length];

		for (i=0; i<m_input_checkbox_array_length; i++)
		{
			m_input_checkbox_array[i] = new Wt::WCheckBox();
			Wt::WTableCell* cell = input_table->elementAt(0, i);
			cell->addWidget(m_input_checkbox_array[i]);
			cell->setContentAlignment(Wt::AlignCenter|Wt::AlignMiddle);
			
			cell = input_table->elementAt(1, i);
			cell->addWidget(new Wt::WText(Wt::WString::tr("GeneralArg").arg(i)));
			cell->setContentAlignment(Wt::AlignCenter|Wt::AlignMiddle);

			int input_state;
			if (EPHIDGET_OK == CPhidgetInterfaceKit_getInputState(m_phidget->GetNativeHandle(), i, &input_state))
			{
				m_input_checkbox_array[i]->setChecked(PTRUE == input_state);
			}
			m_input_checkbox_array[i]->setEnabled(false);
		}
	}

	/* Output */
	if (EPHIDGET_OK == CPhidgetInterfaceKit_getOutputCount(m_phidget->GetNativeHandle(), &int_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Output")));

		Wt::WTable* output_table = new Wt::WTable();
		table->elementAt(row++, 1)->addWidget(output_table);
		
		m_output_checkbox_array_length = int_value;
		m_output_checkbox_array = new Wt::WCheckBox*[m_output_checkbox_array_length];

		for (i=0; i<m_output_checkbox_array_length; i++)
		{
			m_output_checkbox_array[i] = new Wt::WCheckBox();
			m_output_checkbox_array[i]->changed().connect(boost::bind(&WidgetsInterfaceKit::OnWtOutputStateChanged, this, m_output_checkbox_array[i]));

			Wt::WTableCell* cell = output_table->elementAt(0, i);
			cell->addWidget(m_output_checkbox_array[i]);
			cell->setContentAlignment(Wt::AlignCenter|Wt::AlignMiddle);
			
			cell = output_table->elementAt(1, i);
			cell->addWidget(new Wt::WText(Wt::WString::tr("GeneralArg").arg(i)));
			cell->setContentAlignment(Wt::AlignCenter|Wt::AlignMiddle);

      int output_state;
      if (EPHIDGET_OK == CPhidgetInterfaceKit_getOutputState(m_phidget->GetNativeHandle(), i, &output_state))
      {
        m_output_checkbox_array[i]->setChecked(PTRUE == output_state);
      }
		}
	}

	Wt::WGroupBox* generic_box = new Wt::WGroupBox(Wt::WString::tr("Phidget (Common)"));
	vbox->addWidget(generic_box);

	generic_box->addWidget(WidgetsCommon::CreateWidget());
#endif
	return tab_container;
}
#if 0
void WidgetsInterfaceKit::OnWtRatiometricStateChanged(Wt::WCheckBox* checkbox)
{
	bool ratiometric = checkbox->isChecked();
	CPhidgetInterfaceKit_setRatiometric(m_phidget->GetNativeHandle(), ratiometric ? PTRUE : PFALSE);
	::GetApplicationManager()->OnWtRatiometricChanged(GetApplication(), GetSerial(), ratiometric);

	UpdateSensorFunctionDropdowns(ratiometric);

	GetApplication()->triggerUpdate();
}

void WidgetsInterfaceKit::OnWtOutputStateChanged(Wt::WCheckBox* checkbox)
{
	int i;
	for (i=0; i<m_output_checkbox_array_length; i++)
	{
		if (checkbox == m_output_checkbox_array[i])
		{
			bool check = checkbox->isChecked();
			CPhidgetInterfaceKit_setOutputState(m_phidget->GetNativeHandle(), i, check ? PTRUE : PFALSE);
			::GetApplicationManager()->OnWtDigitalOutputChanged(GetApplication(), GetSerial(), i, check);
			break;
		}
	}
}

void WidgetsInterfaceKit::UpdateSensorFunctionDropdowns(bool ratiometric)
{
	int i;
	for (i=0; m_sensor_widget_array_length>i; i++)
	{
		m_sensor_widget_array[i]->SetRatiometric(ratiometric);
	}
}
#endif