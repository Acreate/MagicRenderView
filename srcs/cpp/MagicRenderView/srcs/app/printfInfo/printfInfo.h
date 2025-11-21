#ifndef PRINTFINFO_H_H_HEAD__FILE__
#define PRINTFINFO_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>
#include <stacktrace>
class PrintfInfo {
public:
	virtual ~PrintfInfo( ) { }
	virtual void error( const QString &msg ) const;
	virtual void info( const QString &msg ) const;
	virtual std::vector<std::stacktrace_entry> getStacktrace( ) const;
};

#endif // PRINTFINFO_H_H_HEAD__FILE__
