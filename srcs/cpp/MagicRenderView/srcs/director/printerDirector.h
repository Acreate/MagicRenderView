#ifndef PRINTERDIRECTOR_H_H_HEAD__FILE__
#define PRINTERDIRECTOR_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <stacktrace>
class QDir;
class QString;
class Application;
class PrinterDirector : QObject {
	Q_OBJECT;
	friend class Application;
protected:
	QString applicationName;
	QDir *absPath;
	Application *instancePtr;
	QString sourceDirPathName;
	QString logSaveFilePathName;
public:
	PrinterDirector( );
	~PrinterDirector( ) override;
	virtual bool init( );
	virtual void error( const QString &msg ) const;
	virtual void info( const QString &msg ) const;
	virtual std::vector< std::stacktrace_entry > getStacktrace( ) const;
};

#endif // PRINTERDIRECTOR_H_H_HEAD__FILE__
