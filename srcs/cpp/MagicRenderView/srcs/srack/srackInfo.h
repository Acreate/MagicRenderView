#ifndef SRACKINFO_H_H_HEAD__FILE__
#define SRACKINFO_H_H_HEAD__FILE__

#include <qstring.h>

class SrackInfo {
	QString fileSourceName;
	QString callFunctionName;
	size_t fileLine;
public:
	virtual ~SrackInfo( ) = default;
	SrackInfo( const QString &file_source_name, const QString &call_function_name, size_t file_line );
	virtual const QString & getFileSourceName( ) const { return fileSourceName; }
	virtual const QString & getCallFunctionName( ) const { return callFunctionName; }
	virtual size_t getFileLine( ) const { return fileLine; }
};
#define Create_SrackInfo() SrackInfo( QString(__FILE__), QString(__func__), (__LINE__) )

#endif // SRACKINFO_H_H_HEAD__FILE__
