#include "iniDirector.h"

#include <qfile.h>

#include "printerDirector.h"
#include "varDirector.h"

#include "../app/application.h"

bool IniDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	iniData.clear( );
	return true;
}
bool IniDirector::setVar( const QString &var_key, const std::vector< uint8_t > &var_value ) {
	size_t count = iniData.size( );
	auto data = iniData.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == var_key ) {
			data[ index ].second = var_value;
			return true;
		}
	iniData.emplace_back( var_key, var_value );
	return true;
}
bool IniDirector::getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value ) {
	size_t count = iniData.size( );
	auto data = iniData.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == result_var_key ) {
			result_var_value = data[ index ].second;
			return true;
		}
	return false;
}
bool IniDirector::removeVar( const QString &result_var_key ) {
	size_t count = iniData.size( );
	auto data = iniData.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == result_var_key ) {
			iniData.erase( iniData.begin( ) + index );
			return true;
		}
	return false;
}
bool IniDirector::synchronousFileToVar( const QString &file_path_name ) {
	VarDirector newVarDirector;
	if( newVarDirector.init( ) == false ) {
		printerDirector->error( tr( "无法初始化一个新的堆栈管理对象" ) );
		return false;
	} else {
		QFile file( file_path_name );
		if( file.open( QIODeviceBase::ReadWrite ) == false )
			return false;
		QByteArray readAll = file.readAll( );
		file.close( );
		qint64 qsizetype = readAll.size( );
		if( qsizetype == 0 )
			return true;
		size_t readDataCount = qsizetype;
		if( readDataCount != abs( qsizetype ) )
			return false;
		auto readDataArrayPtr = ( uint8_t * ) readAll.data( );
		uint64_t *writeCount;
		QString *writeKey;
		std::vector< uint8_t > *writeData;

		// 键值对数量
		void *buffPtr;
		size_t result;
		if( newVarDirector.toVar( result, readDataArrayPtr, readDataCount, buffPtr ) == false )
			return false;
		if( newVarDirector.cast_ptr( buffPtr, writeCount ) == false )
			return false;
		iniData.resize( *writeCount );
		size_t index = 0;
		auto iniDataArrayPtr = iniData.data( );
		for( ; index < *writeCount; ++index ) {
			readDataArrayPtr += result;
			readDataCount -= result;

			if( newVarDirector.toVar( result, readDataArrayPtr, readDataCount, buffPtr ) == false )
				return false;
			if( newVarDirector.cast_ptr( buffPtr, writeKey ) == false )
				return false;
			readDataArrayPtr += result;
			readDataCount -= result;
			if( newVarDirector.toVar( result, readDataArrayPtr, readDataCount, buffPtr ) == false )
				return false;
			if( newVarDirector.cast_ptr( buffPtr, writeData ) == false )
				return false;
			iniDataArrayPtr[ index ].first = *writeKey;
			iniDataArrayPtr[ index ].second = *writeData;
		}
		return true;
	}

	return false;
}
bool IniDirector::synchronousVarToFile( const QString &file_path_name ) const {
	VarDirector newVarDirector;
	if( newVarDirector.init( ) == false ) {
		printerDirector->error( tr( "无法初始化一个新的堆栈管理对象" ) );
		return false;
	} else {
		QFile file( file_path_name );
		uint64_t *writeCount;
		QString *writeKey;
		std::vector< uint8_t > *writeData;
		std::vector< uint8_t > fileReadWriteData, buff;
		if( newVarDirector.create( writeCount ) == false )
			return false;
		if( newVarDirector.create( writeKey ) == false )
			return false;
		if( newVarDirector.create( writeData ) == false )
			return false;
		// 键值对数量
		*writeCount = iniData.size( );
		if( newVarDirector.toVector( writeCount, fileReadWriteData ) == false )
			return false;
		size_t index = 0;
		auto iniDataArrayPtr = iniData.data( );
		for( ; index < *writeCount; ++index ) {
			*writeKey = iniDataArrayPtr[ index ].first;
			*writeData = iniDataArrayPtr[ index ].second;
			if( newVarDirector.toVector( writeKey, buff ) == false )
				return false;
			fileReadWriteData.append_range( buff );
			if( newVarDirector.toVector( writeData, buff ) == false )
				return false;
			fileReadWriteData.append_range( buff );
		}
		if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Truncate ) == false )
			return false;
		file.write( ( const char * ) fileReadWriteData.data( ), fileReadWriteData.size( ) );
		return true;

	}

	return false;
}
