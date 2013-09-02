/*
 *  widgets_rfid.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_rfid.h"

#include <Wt/WCheckBox>
#include <Wt/WComboBox>
#include <Wt/WGroupBox>
#include <Wt/WHBoxLayout>
#include <Wt/WLineEdit>
#include <Wt/WMessageBox>
#include <Wt/WPushButton>
#include <Wt/WServer>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

#include "../app_manager.h"
#include "../phidgets/phidgets_rfid.h"
#include "../phidget_manager.h"

#include "../app.h"


WidgetsRFID::WidgetsRFID(PhidgetsRFID* phidget, PhidgetApplication* application)
: WidgetsCommon(application),
  m_phidget(phidget),
  m_antenna_checkbox(NULL),
  m_tag_edit(NULL),
  m_tag_protocol_dropdown(NULL),
  m_lock_tag_checkbox(NULL),
  m_write_tag_button(NULL),
  m_output_checkbox_array(NULL),
  m_output_checkbox_array_length(0),
  m_onboard_led_checkbox(NULL)
{
}

WidgetsRFID::~WidgetsRFID()
{
}

int WidgetsRFID::GetSerial()
{
	return m_phidget->GetSerial();
}

void WidgetsRFID::OnDigitalOutputChanged(int index, bool state)
{
	if (0<=index && m_output_checkbox_array_length>index)
	{
		m_output_checkbox_array[index]->setChecked(state != 0);
		GetApplication()->triggerUpdate();
	}
}

void WidgetsRFID::OnGotRFIDTag(const char* tag, CPhidgetRFID_Protocol protocol)
{
	UpdateTagText(tag, protocol);
	GetApplication()->triggerUpdate();
}

void WidgetsRFID::OnLostRFIDTag()
{
	UpdateTagText();
	GetApplication()->triggerUpdate();
}

void WidgetsRFID::OnOnboardLEDChanged(bool state)
{
	m_onboard_led_checkbox->setChecked(state != 0);
	GetApplication()->triggerUpdate();
}

void WidgetsRFID::OnRFIDAntennaChanged(bool state)
{
	m_antenna_checkbox->setChecked(state != 0);
	UpdateTagText();
	GetApplication()->triggerUpdate();
}

void WidgetsRFID::OnTagWritten(const char* new_tag, CPhidgetRFID_Protocol protocol)
{
	OnGotRFIDTag(new_tag, protocol);
}

Wt::WContainerWidget* WidgetsRFID::CreateWidget()
{
	Wt::WContainerWidget* tab_container = new Wt::WContainerWidget();
  Wt::WVBoxLayout* vbox = new Wt::WVBoxLayout(tab_container);
	
	Wt::WGroupBox* spesific_box = new Wt::WGroupBox(Wt::WString::tr("PhidgetRFID"));
	vbox->addWidget(spesific_box);

  Wt::WHBoxLayout* hbox = new Wt::WHBoxLayout(spesific_box);
	Wt::WTable* table = new Wt::WTable();
	hbox->addWidget(table);

	table->columnAt(0)->setWidth(GetLeftColumnWidth());
	table->columnAt(1)->setWidth(Wt::WLength::Auto);

	int row = 0;
  int i, int_value;

	/* Antenna */
  table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Antenna On")));
  m_antenna_checkbox = new Wt::WCheckBox();
  table->elementAt(row++, 1)->addWidget(m_antenna_checkbox);
	m_antenna_checkbox->changed().connect(boost::bind(&WidgetsRFID::OnWtAntennaStateChanged, this, m_antenna_checkbox));
  if (EPHIDGET_OK == CPhidgetRFID_getAntennaOn(m_phidget->GetNativeHandle(), &int_value))
  {
    m_antenna_checkbox->setChecked(PTRUE == int_value);
  }

  /* Tag */
  table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Tag")));
	
	Wt::WContainerWidget* tag_container = new Wt::WContainerWidget();
  Wt::WHBoxLayout* tagbox = new Wt::WHBoxLayout(tag_container);
	m_tag_edit = new Wt::WLineEdit();
	tagbox->addWidget(m_tag_edit);
	m_tag_protocol_dropdown = new Wt::WComboBox();
	m_tag_protocol_dropdown->addItem("");
	m_tag_protocol_dropdown->addItem(Wt::WString::tr("PHIDGET_RFID_PROTOCOL_EM4100"));
	m_tag_protocol_dropdown->addItem(Wt::WString::tr("PHIDGET_RFID_PROTOCOL_ISO11785_FDX_B"));
	m_tag_protocol_dropdown->addItem(Wt::WString::tr("PHIDGET_RFID_PROTOCOL_PHIDGETS"));
	tagbox->addWidget(m_tag_protocol_dropdown);
	bool can_write_tags = CanWriteTags();
	m_tag_edit->setEnabled(can_write_tags);
	m_tag_protocol_dropdown->setEnabled(can_write_tags);
	if (can_write_tags)
	{
		m_lock_tag_checkbox = new Wt::WCheckBox(Wt::WString::tr("Lock Tag"));
    m_lock_tag_checkbox->setChecked(false);
		tagbox->addWidget(m_lock_tag_checkbox);

		m_write_tag_button = new Wt::WPushButton(Wt::WString::tr("Write Tag"));
		tagbox->addWidget(m_write_tag_button);
		m_write_tag_button->clicked().connect(boost::bind(&WidgetsRFID::OnWtWriteTag, this));
	}
	
  table->elementAt(row++, 1)->addWidget(tag_container);
	UpdateTagText();
	
	/* Output */
	if (EPHIDGET_OK == CPhidgetRFID_getOutputCount(m_phidget->GetNativeHandle(), &int_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("Output")));

		Wt::WTable* output_table = new Wt::WTable();
		table->elementAt(row++, 1)->addWidget(output_table);
		
		m_output_checkbox_array_length = int_value;
		m_output_checkbox_array = new Wt::WCheckBox*[m_output_checkbox_array_length];

		for (i=0; i<m_output_checkbox_array_length; i++)
		{
			m_output_checkbox_array[i] = new Wt::WCheckBox();
			m_output_checkbox_array[i]->changed().connect(boost::bind(&WidgetsRFID::OnWtOutputStateChanged, this, m_output_checkbox_array[i]));

			Wt::WTableCell* cell = output_table->elementAt(0, i);
			cell->addWidget(m_output_checkbox_array[i]);
			cell->setContentAlignment(Wt::AlignCenter|Wt::AlignMiddle);
			
			cell = output_table->elementAt(1, i);
			cell->addWidget(new Wt::WText(Wt::WString::tr("GeneralArg").arg(i)));
			cell->setContentAlignment(Wt::AlignCenter|Wt::AlignMiddle);

      int output_state;
      if (EPHIDGET_OK == CPhidgetRFID_getOutputState(m_phidget->GetNativeHandle(), i, &output_state))
      {
        m_output_checkbox_array[i]->setChecked(PTRUE == output_state);
      }
		}
	}

	/* Onboard LED */
  table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("OnboardLED")));
  m_onboard_led_checkbox = new Wt::WCheckBox();
  table->elementAt(row++, 1)->addWidget(m_onboard_led_checkbox);
	m_onboard_led_checkbox->changed().connect(boost::bind(&WidgetsRFID::OnWtOnboardLEDStateChanged, this, m_onboard_led_checkbox));
  if (EPHIDGET_OK == CPhidgetRFID_getLEDOn(m_phidget->GetNativeHandle(), &int_value))
  {
    m_onboard_led_checkbox->setChecked(PTRUE == int_value);
  }


	Wt::WGroupBox* generic_box = new Wt::WGroupBox(Wt::WString::tr("Phidget (Common)"));
	vbox->addWidget(generic_box);

	generic_box->addWidget(WidgetsCommon::CreateWidget());

	return tab_container;
}

void WidgetsRFID::OnWtAntennaStateChanged(Wt::WCheckBox* checkbox)
{
	bool check = checkbox->isChecked();
	CPhidgetRFID_setAntennaOn(m_phidget->GetNativeHandle(), check ? PTRUE : PFALSE);
	UpdateTagText();
	::GetApplicationManager()->OnWtRFIDAntennaChanged(GetApplication(), GetSerial(), check);
}

void WidgetsRFID::OnWtOutputStateChanged(Wt::WCheckBox* checkbox)
{
	int i;
	for (i=0; i<m_output_checkbox_array_length; i++)
	{
		if (checkbox == m_output_checkbox_array[i])
		{
			bool check = checkbox->isChecked();
			CPhidgetRFID_setOutputState(m_phidget->GetNativeHandle(), i, check ? PTRUE : PFALSE);
			::GetApplicationManager()->OnWtDigitalOutputChanged(GetApplication(), GetSerial(), i, check);
			break;
		}
	}
}

void WidgetsRFID::OnWtOnboardLEDStateChanged(Wt::WCheckBox* checkbox)
{
	bool check = checkbox->isChecked();
	CPhidgetRFID_setLEDOn(m_phidget->GetNativeHandle(), check ? PTRUE : PFALSE);
	::GetApplicationManager()->OnWtOnboardLEDChanged(GetApplication(), GetSerial(), check);
}

void WidgetsRFID::OnWtWriteTag()
{
	int status;
	const char* new_tag = m_tag_edit->text().toUTF8().c_str();
	if (EPHIDGET_OK != (status=CPhidgetRFID_write(m_phidget->GetNativeHandle(), const_cast<char*>(new_tag),
	  static_cast<CPhidgetRFID_Protocol>(m_tag_protocol_dropdown->currentIndex()),
	  m_lock_tag_checkbox->isChecked() ? PTRUE : PFALSE)))
	{
		const char* error_string;
		CPhidget_getErrorDescription(status, &error_string);	 
	  Wt::WMessageBox::show(Wt::WString::tr("ERROR"), Wt::WString::tr("Writing tag failed: ").arg(error_string), Wt::Ok);
	}
	else
	{
		::GetApplicationManager()->OnWtTagWritten(GetApplication(), GetSerial(), new_tag, static_cast<CPhidgetRFID_Protocol>(m_tag_protocol_dropdown->currentIndex()));
	}
}

void WidgetsRFID::UpdateTagText()
{
	if (!m_antenna_checkbox->isChecked())
	{
		UpdateTagText(Wt::WString::tr("Turn antenna On to read tags"), NOT_A_PROTOCOL);
		return;
	}

	int int_value;
	if (EPHIDGET_OK != CPhidgetRFID_getTagStatus(m_phidget->GetNativeHandle(), &int_value) || PTRUE!=int_value)
	{
		UpdateTagText("", NOT_A_PROTOCOL);
	}
	else
	{
		char* tag_string;
		CPhidgetRFID_Protocol protocol;
		if (EPHIDGET_OK == CPhidgetRFID_getLastTag2(m_phidget->GetNativeHandle(), &tag_string, &protocol))
		{
			UpdateTagText(tag_string, protocol);
		}
	}
}

void WidgetsRFID::UpdateTagText(const Wt::WString& tag, CPhidgetRFID_Protocol protocol)
{
	m_tag_edit->setText(tag);
	m_tag_protocol_dropdown->setCurrentIndex(NOT_A_PROTOCOL==protocol ? 0 : protocol);
}

bool WidgetsRFID::CanWriteTags() const
{
	char dummy;
	//Read-only devices will return EPHIDGET_UNSUPPORTED, Read-Write-devices will return EPHIDGET_INVALIDARG
	return (EPHIDGET_INVALIDARG==CPhidgetRFID_write(m_phidget->GetNativeHandle(), &dummy, static_cast<CPhidgetRFID_Protocol>(NOT_A_PROTOCOL), PFALSE));
}
