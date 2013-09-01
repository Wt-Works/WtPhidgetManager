#ifndef _WIDGETS_MANAGER_H_
#define _WIDGETS_MANAGER_H_

/*
 *  widgets_manager.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_common.h"


class PhidgetsManager;

class WidgetsManager : public WidgetsCommon
{
public:
  WidgetsManager(PhidgetsManager* phidget, PhidgetApplication* application);
  virtual ~WidgetsManager();

public: //From WidgetsCommon
	virtual int GetSerial() {return 0;}

protected:
	virtual Wt::WContainerWidget* CreateWidget();

};

#endif // _WIDGETS_MANAGER_H_
