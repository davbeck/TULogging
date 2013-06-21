/*
 TULogging. Simple wrapper macros/functions around ASL (Apple System
 Log). Based on work by Mike Weller: http://doing-it-wrong.mikeweller.com/2012/07/youre-doing-it-wrong-1-nslogdebug-ios.html

 We support a compile-time log level through
 TU_COMPILE_TIME_LOG_LEVEL. This will turn the associated log calls
 into NOPs.

 The log levels are the constants defined in asl.h:

 #define ASL_LEVEL_EMERG   0
 #define ASL_LEVEL_ALERT   1
 #define ASL_LEVEL_CRIT    2
 #define ASL_LEVEL_ERR     3
 #define ASL_LEVEL_WARNING 4
 #define ASL_LEVEL_NOTICE  5
 #define ASL_LEVEL_INFO    6
 #define ASL_LEVEL_DEBUG   7

 For a description of when to use each level, see here:

 http://developer.apple.com/library/mac/#documentation/MacOSX/Conceptual/BPSystemStartup/Chapters/LoggingErrorsAndWarnings.html#//apple_ref/doc/uid/10000172i-SW8-SW1

 Emergency (level 0) - The highest priority, usually reserved for
                       catastrophic failures and reboot notices.

 Alert (level 1)     - A serious failure in a key system.

 Critical (level 2)  - A failure in a key system.

 Error (level 3)     - Something has failed.

 Warning (level 4)   - Something is amiss and might fail if not
                       corrected.

 Notice (level 5)    - Things of moderate interest to the user or
                       administrator.

 Info (level 6)      - The lowest priority that you would normally log, and
                       purely informational in nature.

 Debug (level 7)     - The lowest priority, and normally not logged except
                       for messages from the kernel.


 Note that by default the iOS syslog/console will only record items up
 to level ASL_LEVEL_NOTICE.

 */

#import <Foundation/Foundation.h>

// By default, in non-debug mode we want to disable any logging
// statements except NOTICE and above.
#ifndef TU_COMPILE_TIME_LOG_LEVEL
	#ifdef NDEBUG
		#define TU_COMPILE_TIME_LOG_LEVEL ASL_LEVEL_NOTICE
	#else
		#define TU_COMPILE_TIME_LOG_LEVEL ASL_LEVEL_DEBUG
	#endif
#endif

#include <asl.h>

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_EMERG
void TULogEmergency(NSString *format, ...);
#else
#define TULogEmergency(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_ALERT
void TULogAlert(NSString *format, ...);
#else
#define TULogAlert(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_CRIT
void TULogCritical(NSString *format, ...);
#else
#define TULogCritical(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_ERR
void TULogError(NSString *format, ...);
#else
#define TULogError(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_WARNING
void TULogWarning(NSString *format, ...);
#else
#define TULogWarning(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_NOTICE
void TULogNotice(NSString *format, ...);
#else
#define TULogNotice(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_INFO
void TULogInfo(NSString *format, ...);
#else
#define TULogInfo(...)
#endif

#if TU_COMPILE_TIME_LOG_LEVEL >= ASL_LEVEL_DEBUG
void TULogDebug(NSString *format, ...);
#else
#define TULogDebug(...)
#endif

