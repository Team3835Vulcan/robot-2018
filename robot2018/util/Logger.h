/*
 * Logger.h
 *
 *  Created on: 18 Jan 2018
 *      Author: Gior
 */

#include <string>
#include <fstream>
#include <ctime>

namespace vulcan{
class Logger {
public:
	enum LogType {
		Info,
		Debug,
		Error,
		Critical,
		Fatal
	};

	Logger(const std::string &name);
	virtual ~Logger();

	bool Create();
	bool Log(const std::string &msg, LogType type = Info);
	bool Close();

private:
	std::fstream file;
	std::string filepath;
	bool opened;

	std::string GetTimeString();
	std::string GetTypeString(LogType type);
};
}
