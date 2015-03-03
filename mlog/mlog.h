#ifndef MLOG_H
#define MLOG_H

// Define logging levels
#define MLOG_FATAL    -2    // A fatal error has occured: program will exit immediately
#define MLOG_ERROR    -1    // An error has occured: program may not exit
#define MLOG_INFO     0     // Nessessary information regarding program operation
#define MLOG_WARN     1     // Any circumstance that may not affect normal operation
#define MLOG_DEBUG    2     // Standard debug messages
#define MLOG_VERBOSE  3     // All debug messages

typedef struct {
    void ( *const writeLog )( int loglvl, const char* str, ... );
    void ( *const writeStackTrace )( void );
    void ( *const setLogDebugLevel )( int level );
    void ( *const setLogFile )( const char* file );
    void ( *const setLogSilentMode )( unsigned char silent );
    void ( *const setLineWrap )( unsigned char wrap );
    void ( *const flushLog )( void );
    void ( *const loadConfig )( const char* config );
} mlog_namespace;
extern mlog_namespace const mlog;

#endif
