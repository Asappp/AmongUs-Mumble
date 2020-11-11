#include <string>
#include <fstream>
#include <iostream>
#include <cstdarg>

// File to use for logging messages from the logging system
#define LOGGING_FILE "ProximityLogFile.txt"

enum class LOG_CODE
{
	// Something went wrong
	LOG_CODE_ERROR = 0,
	ERR = 0,
	// Something bad may have happened
	LOG_CODE_WARNING = 1,
	WRN = 1,
	// Information about what's happening
	LOG_CODE_INFO = 2,
	INF = 2,
	// Telling the user something
	LOG_CODE_MESSAGE = 3,
	MSG = 3,
	// Verbose output
	LOG_CODE_DEBUG = 4,
	DBG = 4,
	// Enum length
	COUNT
};

// Basic logging system
class LoggingSystem
{
public:
	// Opens a console to prepare for logging
	LoggingSystem();

	// Closes the file, if needed
	~LoggingSystem();

	// Enables logging to file
	void EnableFileLogging();

	// Sets the max verbosity to print (anything above will not be printed)
	void SetVerbosity(LOG_CODE verbosity);

	// Logs a message to the console window
	// Newline is ensured (for flushing)
	void Log(LOG_CODE logCode, std::string message);

	// Logs a message to the console window, using the familiar "printf" format
	// Newline is ensured (for flushing)
	void LogVariadic(LOG_CODE logCode, const char* formatString, ...);

private:
	// Returns the string for the code to the log (and possibly the file)
	std::string GetLogCodeString(LOG_CODE logCode);

	// Lookup tabe to be used with the LOG_CODE enum for message prefixes
	std::string logPrefixes[(unsigned) LOG_CODE::COUNT] = {
		"ERR", "WRN", "INF", "MSG", "DBG"
	};

	// If the logging system log to a file
	bool logToFile = false;

	// Output log file
	std::ofstream logFile;

	// Verbosity level, anything above will not be logged
	LOG_CODE verbosity = LOG_CODE::DBG;

	friend class ThreadSafeLogger;
};

// Global extern logging system
extern LoggingSystem logger;
