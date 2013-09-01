#ifndef _PHIDGET_GLOBAL_H_
#define _PHIDGET_GLOBAL_H_

/*
 *  global.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WLogger>

#define UNUSED(x) /*make compiler happy*/

extern Wt::WLogger g_logger;
Wt::WLogEntry Log(const std::string& type);

class PhidgetManager;
extern PhidgetManager* g_phidget_manager;
PhidgetManager* GetPhidgetManager();

class ApplicationManager;
extern ApplicationManager* g_application_manager;
ApplicationManager* GetApplicationManager();

class SensorFunctions;
extern SensorFunctions* g_sensor_functions;
SensorFunctions* GetSensorFunctions();

Wt::WApplication* createApplication(const Wt::WEnvironment& env);

int main(int argc, char** argv);

#endif // _PHIDGET_GLOBAL_H_
