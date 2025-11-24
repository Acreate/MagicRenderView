#ifndef INIDIRECTOR_H_H_HEAD__FILE__
#define INIDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class Application;
class PrinterDirector;
class IniDirector : public QObject {
	Q_OBJECT;
protected:
	Application *instancePtr;
	PrinterDirector *printerDirector;
	std::vector< std::pair< QString, std::vector< uint8_t > > > iniData;
public:
	virtual bool init( );
	virtual bool setVar( const QString &var_key, const std::vector< uint8_t > &var_value );
	virtual bool getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value );
	virtual bool removeVar( const QString &result_var_key );
	virtual bool synchronousFileToVar( const QString &file_path_name );
	virtual bool synchronousVarToFile( const QString &file_path_name );
	virtual void clearVar( ) {
		iniData.clear( );
	}
};

#endif // INIDIRECTOR_H_H_HEAD__FILE__
