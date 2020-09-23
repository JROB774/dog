#ifndef ERROR_HPP
#define ERROR_HPP

#define LOG_ERROR(...) LogError(__FILE__, __LINE__, __VA_ARGS__)

// Set this callback and it will be called during fatal exception termination.
GLOBAL void(*ErrorTerminateCallback)(void);
GLOBAL void(*ErrorMaximumCallback)(void);

enum ErrorLevel { ERR_MIN, ERR_MED, ERR_MAX };

INTERNAL bool InitErrorSystem ();
INTERNAL void QuitErrorSystem ();

#endif /* ERROR_HPP */
