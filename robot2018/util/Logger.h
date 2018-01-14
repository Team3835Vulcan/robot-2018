#pragma once

#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Logger {
public:
	enum LogType {
		Info,
		Debug,
		Error,
		Critical,
		Fatal
	};

	bool Create(string name);
	bool Log(string msg, LogType type = Info);
	bool Close();

private:
	fstream file;
	string filepath;
	bool opened = false;

	string GetTimeString();
	string GetTypeString(LogType type);
};