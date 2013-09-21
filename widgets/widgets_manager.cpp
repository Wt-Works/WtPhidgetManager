/*
 *  widgets_manager.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WHBoxLayout>

#include "widgets_manager.h"

#include "../global.h"


WidgetsManager::WidgetsManager(PhidgetsManager* UNUSED(phidget), PhidgetApplication* application)
: WidgetsCommon(application)
{
}

WidgetsManager::~WidgetsManager()
{
}

Wt::WContainerWidget* WidgetsManager::CreateWidget()
{
	Wt::WContainerWidget* tab_container = new Wt::WContainerWidget();
  Wt::WHBoxLayout* hbox = new Wt::WHBoxLayout(tab_container);
	
	Wt::WTable* table = new Wt::WTable();
	hbox->addWidget(table);
	
	table->columnAt(0)->setWidth(GetLeftColumnWidth());
	table->columnAt(1)->setWidth(Wt::WLength::Auto);

	int row = 0;
	const char* string_value;
	if (EPHIDGET_OK == CPhidget_getLibraryVersion(&string_value))
	{
		table->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::tr("LibraryVersion")));
		table->elementAt(row++, 1)->addWidget(new Wt::WText(Wt::WString(string_value, Wt::UTF8)));
	}

	return tab_container;
}
