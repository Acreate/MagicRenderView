#include "varDirectorTools.h"

#include <QColor>

#include "../director/varDirector.h"
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
			else
				return true;
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
	return true;
}
