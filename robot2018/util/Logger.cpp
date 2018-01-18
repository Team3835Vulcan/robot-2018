/*
 * Logger.cpp
 *
 *  Created on: 18 Jan 2018
 *      Author: Gior
 */

#include "Logger.h"

namespace vulcan {
Logger::Logger()
{
	opened = false;
}
/**
* Create a log file.
*
* @param name			The log file name.
* @return				True if created, False otherwise.
*/
bool Logger::Create(std::string name)
{
	file.open(name);

	if (!file.is_open())
		return false;

	filepath = name;
	opened = true;
	return true;
}

/*
* Log to the file.
*
* @param msg			Message to write in the log.
* @param type			Log type.
* @return				True if message was logged, False otherwise.
*/
bool Logger::Log(std::string msg, LogType type)
{
	if (!opened)
		return false;

	std::string sType = GetTypeString(type);
	std::string sTime = GetTimeString();

	file << "[" << sTime << "] " << sType << ": " << msg << "\n";
	return true;
}

std::string Logger::GetTimeString()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);

	return str;
}

std::string Logger::GetTypeString(LogType type)
{
	std::string result = "";

	switch (type)
	{
	case Info:
		result = "Info";
		break;

	case Debug:
		result = "Debug";
		break;

	case Error:
		result = "Error";
		break;

	case Critical:
		result = "Critical";
		break;

	case Fatal:
		result = "Fatal";
		break;
	}

	return result;
}

/*
* Close the log file.
*
* @return			True if closed, False otherwise.
*/
bool Logger::Close()
{
	if (!opened)
		return false;

	file.close();
	return true;
}

}
