#include "Logger.h"

std::bitset<3> Logger::mSet = 7; // Default value of 7 (111 in binary) to enable all logs to be displayed.
HANDLE Logger::hConsole = NULL;
time_t Logger::mRawTime;
struct tm* Logger::mTimeInfo;
std::vector<std::string> Logger::mTextBuffer;

void Logger::Init(HANDLE handle)
{
	if (handle)
		hConsole = handle; // Grab handle to console (so we can change colors)
	else
		std::cout << "NO HANDLE TO CONSOLE PROVIDED.\nDid you pass in 'GetStdHandle(STD_OUTPUT_HANDLE)'?" << std::endl;
}


void Logger::SetLogLevel(int state) {
	Logger::mSet = state;
}


void Logger::LogMsg(const char* msg, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 10);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[MSG]: ");
		mTextBuffer.emplace_back(msg);
		mTextBuffer.emplace_back("\n");
		std::cout << "[MSG]: " << msg << std::endl;
		ResetConsoleColor();
	}
}


void Logger::LogWarn(const char* warnMsg, const char* from) {
	if (mSet.test(1)) {
		SetConsoleTextAttribute(hConsole, 14);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[WRN]: ");
		mTextBuffer.emplace_back(warnMsg);
		mTextBuffer.emplace_back("\n");
		std::cout << "[WRN]: " << warnMsg << std::endl;
		ResetConsoleColor();
	}
}


void Logger::LogError(const char* errMsg, const char* from) {
	if (mSet.test(2)) {
		SetConsoleTextAttribute(hConsole, 12);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[ERR]: ");
		mTextBuffer.emplace_back(errMsg);
		mTextBuffer.emplace_back("\n");
		std::cout << "[ERR]: " << errMsg << std::endl;
		ResetConsoleColor();
	}
}



void Logger::PrintTime()
{
	time(&mRawTime);
	mTimeInfo = localtime(&mRawTime);
	std::cout << "[" << mTimeInfo->tm_hour << ":" << mTimeInfo->tm_min << ":" << mTimeInfo->tm_sec << "]";

	mTextBuffer.emplace_back("[" + std::to_string(mTimeInfo->tm_hour));
	mTextBuffer.emplace_back(":" + std::to_string(mTimeInfo->tm_min));
	mTextBuffer.emplace_back(":" + std::to_string(mTimeInfo->tm_sec));
	mTextBuffer.emplace_back("]");
}

void Logger::FormatFrom(const char* from)
{
	std::string f(from);
	std::size_t found = f.find_last_of("/\\");
	if (found != std::string::npos) {
		mTextBuffer.emplace_back("[");
		mTextBuffer.emplace_back(f.substr(found + 1));
		mTextBuffer.emplace_back("]");
	}
}
