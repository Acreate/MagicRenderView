#include "varDirectorTools.h"

#include <QColor>
#include <QDateTime>

#include "../director/varDirector.h"
#include "../node/nodeType/nodeTypeInfo.h"
#include "imageTools.h"
#include "infoTool.h"
bool VarDirectorTools::isTrue( const VarDirector *varDirectorPtr, const void *var_ptr ) {
	if( varDirectorPtr == nullptr || var_ptr == nullptr )
		return false;

	const QColor *colorPtr;
	if( varDirectorPtr->cast_ptr( var_ptr, colorPtr ) )
		if( colorPtr->red( ) )
			return true;
		else if( colorPtr->green( ) )
			return true;
		else if( colorPtr->blue( ) )
			return true;
		else if( colorPtr->alpha( ) )
			return true;
		else
			return false;

	const QString *stringPtr;
	if( varDirectorPtr->cast_ptr( var_ptr, stringPtr ) )
		if( stringPtr->length( ) == 0 )
			return false;
		else if( stringPtr->isEmpty( ) == false )
			return false;
		else {
			auto trimmed = stringPtr->trimmed( );
			if( stringPtr->length( ) == 0 )
				return false;
			else if( stringPtr->isEmpty( ) == false )
				return false;
			else {
				auto upper = stringPtr->toUpper( );
				QString converUpperString;
				converUpperString = QObject::tr( "false" ).toUpper( );
				if( upper == converUpperString )
					return false;
				converUpperString = QObject::tr( "not" ).toUpper( );
				if( upper == converUpperString )
					return false;
				converUpperString = QObject::tr( "null" ).toUpper( );
				if( upper == converUpperString )
					return false;
				return true;
			}
		}

	const QChar *charPtr;
	if( varDirectorPtr->cast_ptr( var_ptr, charPtr ) )
		return charPtr->unicode( );

	const uint8_t *uint8t;
	const uint16_t *uint16t;
	const uint32_t *uint32t;
	const uint64_t *uint64t;
	if( varDirectorPtr->cast_ptr( var_ptr, uint8t ) )
		return *uint8t;
	if( varDirectorPtr->cast_ptr( var_ptr, uint16t ) )
		return *uint16t;
	if( varDirectorPtr->cast_ptr( var_ptr, uint32t ) )
		return *uint32t;
	if( varDirectorPtr->cast_ptr( var_ptr, uint64t ) )
		return *uint64t;

	const int8_t *int8t;
	const int16_t *int16t;
	const int32_t *int32t;
	const int64_t *int64t;
	if( varDirectorPtr->cast_ptr( var_ptr, int8t ) )
		return *int8t;
	if( varDirectorPtr->cast_ptr( var_ptr, int16t ) )
		return *int16t;
	if( varDirectorPtr->cast_ptr( var_ptr, int32t ) )
		return *int32t;
	if( varDirectorPtr->cast_ptr( var_ptr, int64t ) )
		return *int64t;

	const float *floatPtr;
	const double *doublePtr;
	if( varDirectorPtr->cast_ptr( var_ptr, floatPtr ) )
		return *floatPtr;
	if( varDirectorPtr->cast_ptr( var_ptr, doublePtr ) )
		return *doublePtr;
	const QDateTime *dateTimePtr;
	const QDate *datePtr;
	const QTime *timePtr;
	if( varDirectorPtr->cast_ptr( var_ptr, dateTimePtr ) )
		return ( *dateTimePtr - QDateTime::fromMSecsSinceEpoch( 0 ) ).count( );

	if( varDirectorPtr->cast_ptr( var_ptr, datePtr ) )
		return ( datePtr->toStdSysDays< >( ).time_since_epoch( ) - QDate::fromStdSysDays( std::chrono::sys_days( ) ).toStdSysDays< >( ).time_since_epoch( ) ).count( );

	if( varDirectorPtr->cast_ptr( var_ptr, timePtr ) )
		return timePtr->msecsSinceStartOfDay( ) - 0;

	return true;
}

bool VarDirectorTools::toString( const VarDirector *var_director_ptr, const void *conver_var_ptr, QString &result_string ) {
	if( var_director_ptr == nullptr || conver_var_ptr == nullptr )
		return false;
	// 单元
	const bool *boolPtr;
	const uint8_t *uint8Ptr;
	const uint16_t *uint16Ptr;
	const uint32_t *uint32Ptr;
	const uint64_t *uint64Ptr;

	const int8_t *int8Ptr;
	const int16_t *int16Ptr;
	const int32_t *int32Ptr;
	const int64_t *int64Ptr;

	const QChar *charPtr;
	const QString *stringPtr;

	const QColor *colorPtr;
	const QImage *imagePtr;

	const QDateTime *dateTimePtr;
	const QDate *datePtr;
	const QTime *timePtr;

	const NodeTypeInfo *nodeTypeInfoPtr;

	if( var_director_ptr->cast_ptr( conver_var_ptr, boolPtr ) == true ) {
		result_string = *boolPtr ? QObject::tr( "是" ) : QObject::tr( "否" );
		return true;
	}

	if( var_director_ptr->cast_ptr( conver_var_ptr, uint8Ptr ) == true ) {
		result_string = QString::number( *uint8Ptr );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, uint16Ptr ) == true ) {
		result_string = QString::number( *uint16Ptr );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, uint32Ptr ) == true ) {
		result_string = QString::number( *uint32Ptr );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, uint64Ptr ) == true ) {
		result_string = QString::number( *uint64Ptr );
		return true;
	}

	if( var_director_ptr->cast_ptr( conver_var_ptr, int8Ptr ) == true ) {
		result_string = QString::number( *int8Ptr );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, int16Ptr ) == true ) {
		result_string = QString::number( *int16Ptr );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, int32Ptr ) == true ) {
		result_string = QString::number( *int32Ptr );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, int64Ptr ) == true ) {
		result_string = QString::number( *int64Ptr );
		return true;
	}

	if( var_director_ptr->cast_ptr( conver_var_ptr, charPtr ) == true ) {
		result_string = *charPtr;
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, stringPtr ) == true ) {
		result_string = *stringPtr;
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, colorPtr ) == true && infoTool::toString( colorPtr, result_string ) )
		return true;
	if( var_director_ptr->cast_ptr( conver_var_ptr, imagePtr ) == true && ImageTools::conver::imageToBase64( *imagePtr, result_string ) )
		return true;
	if( var_director_ptr->cast_ptr( conver_var_ptr, nodeTypeInfoPtr ) == true ) {
		result_string = nodeTypeInfoPtr->toString( );
		return true;
	}
	/*
	const QDateTime *dateTimePtr;
	const QDate *datePtr;
	const QTime *timePtr;
	 */
	if( var_director_ptr->cast_ptr( conver_var_ptr, dateTimePtr ) == true ) {
		result_string = dateTimePtr->toString( "yyyy年MM月dd日.hh时mm分ss秒 z" );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, datePtr ) == true ) {
		result_string = datePtr->toString( "yyyy年MM月dd日" );
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, timePtr ) == true ) {
		result_string = datePtr->toString( "hh时mm分ss秒 z" );
		return true;
	}
	// 序列
	const std::vector< uint8_t > *uint8ArrayPtr;
	const std::vector< uint16_t > *uint16ArrayPtr;
	const std::vector< uint32_t > *uint32ArrayPtr;
	const std::vector< uint64_t > *uint64ArrayPtr;

	const std::vector< int8_t > *int8ArrayPtr;
	const std::vector< int16_t > *int16ArrayPtr;
	const std::vector< int32_t > *int32ArrayPtr;
	const std::vector< int64_t > *int64ArrayPtr;

	const std::vector< QChar > *charArrayPtr;
	const std::vector< QString > *stringArrayPtr;

	const std::vector< QColor > *colorArrayPtr;
	const std::vector< QImage > *imageArrayPtr;

	const std::vector< NodeTypeInfo * > *nodeTypeInfoArrayPtr;

	const std::vector< QDateTime * > *dateTimeArrayPtr;
	const std::vector< QDate * > *dateArrayPtr;
	const std::vector< QTime * > *timeArrayPtr;

	if( var_director_ptr->cast_ptr( conver_var_ptr, uint8ArrayPtr ) == true ) {
		size_t count = uint8ArrayPtr->size( );
		auto dataPtr = uint8ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, uint16ArrayPtr ) == true ) {
		size_t count = uint16ArrayPtr->size( );
		auto dataPtr = uint16ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, uint32ArrayPtr ) == true ) {
		size_t count = uint32ArrayPtr->size( );
		auto dataPtr = uint32ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, uint64ArrayPtr ) == true ) {
		size_t count = uint64ArrayPtr->size( );
		auto dataPtr = uint64ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}

	if( var_director_ptr->cast_ptr( conver_var_ptr, int8ArrayPtr ) == true ) {
		size_t count = int8ArrayPtr->size( );
		auto dataPtr = int8ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, int16ArrayPtr ) == true ) {
		size_t count = int16ArrayPtr->size( );
		auto dataPtr = int16ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, int32ArrayPtr ) == true ) {
		size_t count = int32ArrayPtr->size( );
		auto dataPtr = int32ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, int64ArrayPtr ) == true ) {
		size_t count = int64ArrayPtr->size( );
		auto dataPtr = int64ArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( QString::number( dataPtr[ index ] ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}

	if( var_director_ptr->cast_ptr( conver_var_ptr, charArrayPtr ) == true ) {
		size_t count = charArrayPtr->size( );
		auto dataPtr = charArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( dataPtr[ index ] );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, stringArrayPtr ) == true ) {
		size_t count = stringArrayPtr->size( );
		auto dataPtr = stringArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( dataPtr[ index ] );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, colorArrayPtr ) == true ) {
		size_t count = colorArrayPtr->size( );
		auto dataPtr = colorArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			if( infoTool::toString( dataPtr[ index ], result_string ) )
				buffList.append( result_string );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, imageArrayPtr ) == true ) {
		size_t count = imageArrayPtr->size( );
		auto dataPtr = imageArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			if( ImageTools::conver::imageToBase64( dataPtr[ index ], result_string ) )
				buffList.append( result_string );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, nodeTypeInfoArrayPtr ) == true ) {
		size_t count = nodeTypeInfoArrayPtr->size( );
		auto dataPtr = nodeTypeInfoArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( dataPtr[ index ]->toString( ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, dateTimeArrayPtr ) == true ) {
		size_t count = dateTimeArrayPtr->size( );
		auto dataPtr = dateTimeArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( dataPtr[ index ]->toString( "yyyy年MM月dd日.hh时mm分ss秒 z" ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, dateArrayPtr ) == true ) {
		size_t count = dateArrayPtr->size( );
		auto dataPtr = dateArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( dataPtr[ index ]->toString( "yyyy年MM月dd日" ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}
	if( var_director_ptr->cast_ptr( conver_var_ptr, timeArrayPtr ) == true ) {
		size_t count = timeArrayPtr->size( );
		auto dataPtr = timeArrayPtr->data( );
		size_t index = 0;
		QStringList buffList;
		for( ; index < count; ++index )
			buffList.append( dataPtr[ index ]->toString( "hh时mm分ss秒 z" ) );
		result_string = "{" + buffList.join( "," ) + "}";
		return true;
	}

	return false;
}
