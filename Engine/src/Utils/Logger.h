#pragma once
#include <Windows.h>
#include <iostream>
#include <Bitset>
#include <string>
#include <ctime>
#include <vector>

enum LogStates {			// Binary:
	LOG_MSG = 1 << 0,		// 001
	LOG_WARN = 1 << 1,		// 010
	LOG_ERR = 1 << 2		// 100
};

class Logger {
public:

	static void Init(HANDLE handle); // Takes a handle to the console window
	static void SetLogLevel(int state);

	// Standard message functions (Green text)
	static void LogMsg(const char* msg, const char* from="");
	template<typename T>
	static void LogMsg(const char* msg, T obj, const char* from = "");
	template<typename T>
	static void LogMsg(const char* msg, T objs[], size_t size, const char* from = "");

	// Warning logging functions (Yellow text)
	static void LogWarn(const char* warnMsg, const char* from = "");
	template<typename T>
	static void LogWarn(const char* warnMsg, T obj, const char* from = "");
	template<typename T>
	static void LogWarn(const char* warnMsg, T objs[], size_t size, const char* from = "");

	// Error logging functions (Red text)
	static void LogError(const char* errMsg, const char* from = "");
	template<typename T>
	static void LogError(const char* errMsg, T obj, const char* from = "");
	template<typename T>
	static void LogError(const char* errMsg, T objs[], size_t size, const char* from = "");

	static std::vector<std::string>& GetTextBuffer() { return mTextBuffer; }


private:
	static std::bitset<3> mSet; // Default value of 7 (111 in binary) to enable all logs to be displayed.
	static HANDLE hConsole;

	// For getting the time
	static time_t mRawTime;
	static struct tm* mTimeInfo;

	static void ResetConsoleColor() { SetConsoleTextAttribute(hConsole, 15); }
	static void PrintTime();
	static void FormatFrom(const char* from="");	// Formats the from to not include the abs path

	static std::vector<std::string> mTextBuffer;	// Used for storing the text for ImGui

	// Deleted as its a purely static class and thus not needed
	Logger() = delete;
	~Logger() = delete;
	Logger(const Logger&) = delete;
};


/*
	=================================
	| TEMPLATE IMPLEMENTATION BELOW |
	=================================
*/
template<typename T>
void Logger::LogMsg(const char* msg, T obj, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 10);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[MSG]: ");
		mTextBuffer.emplace_back(msg);
		mTextBuffer.emplace_back(" | [OBJ]: ");
		mTextBuffer.emplace_back(std::to_string(obj));
		mTextBuffer.emplace_back("\n");
		std::cout << "[MSG]: " << msg << " | [OBJ]: " << obj << std::endl;
		ResetConsoleColor();
	}
}

template<typename T>
void Logger::LogMsg(const char* msg, T objs[], size_t size, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 10);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[MSG]: ");
		mTextBuffer.emplace_back(msg);
		mTextBuffer.emplace_back(" | [OBJ_ARR]: {");
		std::cout << "[MSG]: " << msg << " | [OBJ_ARR]: {";
		for (int i = 0; i < size; i++) {
			if (i != size - 1) {
				mTextBuffer.emplace_back(std::to_string(objs[i]));
				mTextBuffer.emplace_back(", ");
				std::cout << objs[i] << ", ";

			} else {
				mTextBuffer.emplace_back(std::to_string(objs[i]));
				std::cout << objs[i];
			}
		}

		mTextBuffer.emplace_back("}\n");
		std::cout << '}' << std::endl;
		ResetConsoleColor();
	}
}



template<typename T>
void Logger::LogWarn(const char* warnMsg, T obj, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 14);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[WRN]: ");
		mTextBuffer.emplace_back(warnMsg);
		mTextBuffer.emplace_back(" | [OBJ]: ");
		mTextBuffer.emplace_back(std::to_string(obj));
		mTextBuffer.emplace_back("\n");
		std::cout << "[WRN]: " << warnMsg << " | [OBJ]: " << obj << std::endl;
		ResetConsoleColor();
	}
}

template<typename T>
void Logger::LogWarn(const char* warnMsg, T objs[], size_t size, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 14);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[WRN]: ");
		mTextBuffer.emplace_back(warnMsg);
		mTextBuffer.emplace_back(" | [OBJ_ARR]: {");
		std::cout << "[WRN]: " << warnMsg << " | [OBJ_ARR]: { ";
		for (int i = 0; i < size; i++) {
			if (i != size - 1) {
				mTextBuffer.emplace_back(std::to_string(objs[i]));
				mTextBuffer.emplace_back(", ");
				std::cout << objs[i] << ", ";

			}
			else {
				mTextBuffer.emplace_back(std::to_string(objs[i]));
				std::cout << objs[i];
			}
		}

		mTextBuffer.emplace_back("}\n");
		std::cout << " }" << std::endl;
		ResetConsoleColor();
	}
}



template<typename T>
void Logger::LogError(const char* errMsg, T obj, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 12);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[ERR]: ");
		mTextBuffer.emplace_back(errMsg);
		mTextBuffer.emplace_back(" | [OBJ]: ");
		mTextBuffer.emplace_back(std::to_string(obj));
		mTextBuffer.emplace_back("\n");
		std::cout << "[ERR]: " << errMsg << " | [OBJ]: " << obj << std::endl;
		ResetConsoleColor();
	}
}

template<typename T>
void Logger::LogError(const char* errMsg, T objs[], size_t size, const char* from) {
	if (mSet.test(0)) {
		SetConsoleTextAttribute(hConsole, 12);
		PrintTime();
		FormatFrom(from);

		mTextBuffer.emplace_back("[ERR]: ");
		mTextBuffer.emplace_back(errMsg);
		mTextBuffer.emplace_back(" | [OBJ_ARR]: {");
		std::cout << "[ERR]: " << errMsg << " | [OBJ_ARR]: { ";
		for (int i = 0; i < size; i++) {
			if (i != size - 1) {
				mTextBuffer.emplace_back(std::to_string(objs[i]));
				mTextBuffer.emplace_back(", ");
				std::cout << objs[i] << ", ";

			}
			else {
				mTextBuffer.emplace_back(std::to_string(objs[i]));
				std::cout << objs[i];
			}
		}

		mTextBuffer.emplace_back("}\n");
		std::cout << " }" << std::endl;
		ResetConsoleColor();
	}
}
