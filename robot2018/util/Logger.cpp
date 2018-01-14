#include "Logger.h"

/**
* Create a log file.
*
* @param name			The log file name.
* @return				True if created, False otherwise.
*/
bool Logger::Create(string name)
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
bool Logger::Log(string msg, LogType type)
{
	if (!opened)
		return false;

	string sType = GetTypeString(type);
	string sTime = GetTimeString();

	file << "[" << sTime << "] " << sType << ": " << msg << "\n";
	return true;
}

string Logger::GetTimeString()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
	string str(buffer);

	return str;
}

string Logger::GetTypeString(LogType type)
{
	string result = "";

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