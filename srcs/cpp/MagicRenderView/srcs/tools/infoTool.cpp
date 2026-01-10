#include "infoTool.h"

#include "../director/varDirector.h"
#include "../node/nodeType/nodeTypeInfo.h"
#include "imageTools.h"

bool infoTool::toString( const QColor *conver_color_ptr, QString &result_string ) {
	if( conver_color_ptr == nullptr )
		return false;
	QChar firtChar = '0';
	result_string = QString( "0x%1%2%3%4" ).arg( conver_color_ptr->red( ), 2, 16, firtChar ).arg( conver_color_ptr->green( ), 2, 16, firtChar ).arg( conver_color_ptr->blue( ), 2, 16, firtChar ).arg( conver_color_ptr->alpha( ), 2, 16, firtChar ).toUpper( );
	return true;
}
bool infoTool::toString( const VarDirector *var_director_ptr, const void *conver_var_ptr, QString &result_string ) {
	if( var_director_ptr == nullptr || conver_var_ptr == nullptr )
		return false;
	// 单元
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

	const NodeTypeInfo *nodeTypeInfoPtr;

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
	if( var_director_ptr->cast_ptr( conver_var_ptr, colorPtr ) == true && toString( colorPtr, result_string ) )
		return true;
	if( var_director_ptr->cast_ptr( conver_var_ptr, imagePtr ) == true && ImageTools::imageToBase64( *imagePtr, result_string ) )
		return true;
	if( var_director_ptr->cast_ptr( conver_var_ptr, nodeTypeInfoPtr ) == true ) {
		result_string = nodeTypeInfoPtr->toString( );
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
			if( toString( dataPtr[ index ], result_string ) )
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
			if( ImageTools::imageToBase64( dataPtr[ index ], result_string ) )
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

	return false;
}
bool infoTool::fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
	result.resize( ptr_size );
	auto data = result.data( );
	for( size_t index = 0; index < ptr_size; ++index )
		data[ index ] = ptr[ index ];
	return true;
}
bool infoTool::fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count ) {
	if( source_count < target_var_count )
		return false;
	for( size_t index = 0; index < target_var_count; ++index )
		target_var_ptr[ index ] = source_ptr[ index ];
	result_count = target_var_count;
	return true;
}
