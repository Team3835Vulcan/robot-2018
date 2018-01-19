/*
 * Logger.cpp
 *
 *  Created on: 18 Jan 2018
 *      Author: Gior
 */

#include "Logger.h"

namespace vulcan {
Logger::Logger(const std::string &filename)
{
	filepath = filename;
	opened = false;
}

bool Logger::Create()
{
	file.open(filepath);

	if (!file.is_open())
		return false;

	opened = true;
	return true;
}

bool Logger::Log(const std::string &msg, LogType type)
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

bool Logger::Close()
{
	if (!opened)
		return false;

	file.close();
	return true;
}

Logger::~Logger()
{
	Close();
}
}
