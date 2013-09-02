/*
 *  widgets_interfacekit.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_interfacekit.h"

#include <Wt/WCheckBox>
#include <Wt/WComboBox>
#include <Wt/WGroupBox>
#include <Wt/WHBoxLayout>
#include <Wt/WLineEdit>
#include <Wt/WServer>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

#include "../app.h"
#include "../app_manager.h"
#include "../phidgets/phidgets_interfacekit.h"
#include "../phidget_manager.h"
#include "../utils/sensor_functions.h"


SensorWidget::SensorWidget(PhidgetsInterfaceKit* phidget, int index)
: m_phidget(phidget),
  m_index(index)
{
}

SensorWidget::~SensorWidget()
{
}

Wt::WContainerWidget* SensorWidget::CreateWidget()
{
	Wt::WContainerWidget* sensor_container = new Wt::WContainerWidget();
  Wt::WHBoxLayout* hbox = new Wt::WHBoxLayout(sensor_container);

  m_raw_value_edit = new Wt::WLineEdit();
	m_raw_value_edit->setEnabled(false);
	hbox->addWidget(m_raw_value_edit);

	m_function_dropdown = new Wt::WComboBox();
	::GetSensorFunctions()->PopulateDropdown(m_function_dropdown);
	hbox->addWidget(m_function_dropdown);

  m_converted_value_edit = new Wt::WLineEdit();
	m_converted_value_edit->setEnabled(false);
	hbox->addWidget(m_converted_value_edit);

	return sensor_container;
}

void SensorWidget::SetValue(int sensor_value)
{
	m_raw_value_edit->setText(Wt::WString::tr("GeneralArg").arg(sensor_value));
	m_converted_value_edit->setText(::GetSensorFunctions()->ConvertSensorValue(m_function_dropdown->currentIndex(), sensor_value));
}



WidgetsInterfaceKit::WidgetsInterfaceKit(PhidgetsInterfaceKit* phidget, PhidgetApplication* application)
: WidgetsCommon(application),
  m_phidget(phidget),
  m_ratiometric_checkbox(NULL),
	m_sensor_widget_array(NULL),
	m_sensor_widget_array_length(0),
  m_input_checkbox_array(NULL),
  m_input_checkbox_array_length(0),
  m_output_checkbox_array(NULL),
  m_output_checkbox_array_length(0)
{
}

WidgetsInterfaceKit::~WidgetsInterfaceKit()
{
	int i;
	for (i=0; i<m_sensor_widget_array_length; i++)
	{
		delete m_sensor_widget_array[i];
	}
	delete[] m_sensor_widget_array;

	//delete[] m_input_checkbox_array; //Deleted by Wt
	//delete[] m_output_checkbox_array; //Deleted by Wt
}

int WidgetsInterfaceKit::GetSerial()
{
	return m_phidget->GetSerial();
}

void WidgetsInterfaceKit::OnDigitalInputChanged(int index, bool state)
{
	if (0<=index && m_input_checkbox_array_length>index)
	{
		m_input_checkbox_array[index]->setChecked(state != 0);
		GetApplication()->triggerUpdate();
	}
}

void WidgetsInterfaceKit::OnDigitalOutputChanged(int index, bool state)
{
	if (0<=index && m_output_checkbox_array_length>index)
	{
		m_output_checkbox_array[index]->setChecked(state != 0);
		GetApplication()->triggerUpdate();
	}
}

void WidgetsInterfaceKit::OnRatiometricChanged(bool state)
{
	m_ratiometric_checkbox->setChecked(state != 0);
	GetApplication()->triggerUpdate();
}

void WidgetsInterfaceKit::OnSensorChanged(int index, int sensor_value)
{
	if (0<=index && m_sensor_widget_array_length>index)
	{
		m_sensor_widget_array[index]->SetValue(sensor_value);
		GetApplication()->triggerUpdate();
	}
}


Wt::WContainerWidget* WidgetsInterfaceKit::CreateWidget()
{
	Wt::WContainerWidget* tab_container = new Wt::WContainerWidget();
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

	/* Ratiometric */
  table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Ratiometric")));
  m_ratiometric_checkbox = new Wt::WCheckBox();
  table->elementAt(row++, 1)->addWidget(m_ratiometric_checkbox);
	m_ratiometric_checkbox->changed().connect(boost::bind(&WidgetsInterfaceKit::OnWtRatiometricStateChanged, this, m_ratiometric_checkbox));
  if (EPHIDGET_OK == CPhidgetInterfaceKit_getRatiometric(m_phidget->GetNativeHandle(), &int_value))
  {
    m_ratiometric_checkbox->setChecked(PTRUE == int_value);
  }

  /* Sensors */
	if (EPHIDGET_OK == CPhidgetInterfaceKit_getSensorCount(m_phidget->GetNativeHandle(), &int_value))
	{
		m_sensor_widget_array_length = int_value;
		m_sensor_widget_array = new SensorWidget*[m_sensor_widget_array_length];

		for (i=0; i<m_sensor_widget_array_length; i++)
		{
			m_sensor_widget_array[i] = new SensorWidget(m_phidget, i);

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

	return tab_container;
}

void WidgetsInterfaceKit::OnWtRatiometricStateChanged(Wt::WCheckBox* checkbox)
{
	bool check = checkbox->isChecked();
	CPhidgetInterfaceKit_setRatiometric(m_phidget->GetNativeHandle(), check ? PTRUE : PFALSE);
	::GetApplicationManager()->OnWtRatiometricChanged(GetApplication(), GetSerial(), check);
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
