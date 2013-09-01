/*
 *  widgets_common.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_common.h"

#include <Wt/WHBoxLayout>
#include <Wt/WTable>
#include <Wt/WText>
#include "../phidget_manager.h"
#include "../phidgets/phidgets_common.h"


WidgetsCommon::WidgetsCommon(PhidgetApplication* application)
: m_widget(NULL),
  m_application(application)
{
}

WidgetsCommon::~WidgetsCommon()
{
}

Wt::WContainerWidget* WidgetsCommon::GetWidget()
{
	if (!m_widget)
	{
		m_widget = CreateWidget();
	}

	return m_widget;
}

Wt::WContainerWidget* WidgetsCommon::CreateWidget()
{
	PhidgetsInfo* item = ::GetPhidgetManager()->FindPhidgetBySerial(GetSerial());
	if (!item)
		return NULL;
	
	CPhidgetHandle handle = item->m_phidget->GetHandle();

	Wt::WContainerWidget* tab_container = new Wt::WContainerWidget();
  Wt::WHBoxLayout* hbox = new Wt::WHBoxLayout(tab_container);
	
	Wt::WTable* table = new Wt::WTable();
	hbox->addWidget(table);
	
	table->columnAt(0)->setWidth(GetLeftColumnWidth());
	table->columnAt(1)->setWidth(Wt::WLength::Auto);

	int row = 0;
	const char* string_value;
	int int_value;
	if (EPHIDGET_OK == CPhidget_getDeviceName(handle, &string_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("DeviceName")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString(string_value, Wt::UTF8)));
	}
	
	if (EPHIDGET_OK == CPhidget_getSerialNumber(handle, &int_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("SerialNumber")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString("{1}").arg(int_value)));
	}

	if (EPHIDGET_OK == CPhidget_getDeviceVersion(handle, &int_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("DeviceVersion")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString("{1}").arg(int_value)));
	}

	if (EPHIDGET_OK == CPhidget_getDeviceStatus(handle, &int_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("DeviceStatus")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString("{1}").arg(int_value)));
	}

	if (EPHIDGET_OK == CPhidget_getDeviceType(handle, &string_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("DeviceType")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString(string_value, Wt::UTF8)));
	}

	if (EPHIDGET_OK == CPhidget_getDeviceLabel(handle, &string_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("DeviceLabel")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString(string_value, Wt::UTF8)));
	}

	return tab_container;
}

Wt::WLength WidgetsCommon::GetLeftColumnWidth()
{
	return Wt::WLength(12, Wt::WLength::FontEm);
}
