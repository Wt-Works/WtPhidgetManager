/*
 *  global.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "global.h"

#include <Wt/WServer>

#include "app.h"
#include "app_manager.h"
#include "phidget_manager.h"
#include "utils/sensor_functions.h"


Wt::WLogger g_logger;
Wt::WLogEntry Log(const std::string& type)
{
	return g_logger.entry(type);
}


//The one and only Phidget manager
PhidgetManager* g_phidget_manager;
PhidgetManager* GetPhidgetManager() {return g_phidget_manager;}

//The one and only Application manager
ApplicationManager* g_application_manager;
ApplicationManager* GetApplicationManager() {return g_application_manager;}

//The one and only SensorFunctions
SensorFunctions* g_sensor_functions;
SensorFunctions* GetSensorFunctions() {return g_sensor_functions;}

//The one and only ServoUtils
ServoUtils* g_servo_utils;
ServoUtils* GetServoUtils() {return g_servo_utils;}


Wt::WApplication* createApplication(const Wt::WEnvironment& env)
{
  PhidgetApplication* app = new PhidgetApplication(env);
	app->messageResourceBundle().use(app->appRoot() + "strings");
	return app;
}


int main(int argc, char** argv)
{
	g_logger.addField("message", true);
	
	g_sensor_functions = new SensorFunctions();
	g_application_manager = new ApplicationManager();
	g_phidget_manager = new PhidgetManager();

	int ret = Wt::WRun(argc, argv, &createApplication);

	delete g_phidget_manager;
	delete g_application_manager;
	delete g_sensor_functions;

	return ret;
}
