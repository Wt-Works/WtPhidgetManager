#ifndef _PHIDGETS_MANAGER_H_
#define _PHIDGETS_MANAGER_H_

/*
 *  phidgets_manager.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_common.h"


class PhidgetsManager : public PhidgetsCommon
{
public:
  PhidgetsManager();
  virtual ~PhidgetsManager() {}

public: //From PhidgetsCommon
	virtual bool Init();
	virtual CPhidgetHandle GetHandle() {return NULL;}
	virtual Wt::WString GetPhidgetName();
	virtual WidgetsCommon* CreateWidget(PhidgetApplication* application);
};

#endif // _PHIDGETS_INTERFACEKIT_H_
