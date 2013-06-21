
// We need all the log functions visible so we set this to DEBUG
#ifdef TU_COMPILE_TIME_LOG_LEVEL
#undef TU_COMPILE_TIME_LOG_LEVEL
#define TU_COMPILE_TIME_LOG_LEVEL ASL_LEVEL_DEBUG
#endif

#define TU_COMPILE_TIME_LOG_LEVEL ASL_LEVEL_DEBUG

#import "TULogging.h"

static dispatch_queue_t _logging_qeueu;

static void AddStderrOnce()
{
	static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^{
		asl_add_log_file(NULL, STDERR_FILENO);
        
        _logging_qeueu = dispatch_queue_create("com.ThinkUltimate.Log", DISPATCH_QUEUE_SERIAL);
	});
}

#define __TU_MAKE_LOG_FUNCTION(LEVEL, NAME) \
void NAME (NSString *format, ...) \
{ \
    AddStderrOnce(); \
    va_list args; \
    va_start(args, format); \
    NSString *message = [[NSString alloc] initWithFormat:format arguments:args]; \
    dispatch_async(_logging_qeueu, ^{ \
        asl_log(NULL, NULL, (LEVEL), "%s", [message UTF8String]); \
    }); \
    va_end(args); \
}

__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_EMERG, TULogEmergency)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_ALERT, TULogAlert)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_CRIT, TULogCritical)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_ERR, TULogError)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_WARNING, TULogWarning)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_NOTICE, TULogNotice)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_INFO, TULogInfo)
__TU_MAKE_LOG_FUNCTION(ASL_LEVEL_DEBUG, TULogDebug)

#undef __TU_MAKE_LOG_FUNCTION
