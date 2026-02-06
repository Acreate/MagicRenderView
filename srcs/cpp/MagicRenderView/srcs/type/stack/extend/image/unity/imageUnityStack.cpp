#include "imageUnityStack.h"

#include <define/stackTypeMacro.h>
#include <tools/infoTool.h>
#include <director/varDirector.h>
#include <QImage>

using t_current_unity_type = QImage;

inline bool fillTypeVarAtVector( const void *ptr, std::vector< uint8_t > &result ) {
	QImage *imagePtr = ( QImage * ) ptr;
	std::vector< uint8_t > buff;

	QByteArray ba;
	QBuffer buffer( &ba );
	buffer.open( QIODevice::WriteOnly );
	imagePtr->save( &buffer, "PNG" );

	auto data = ba.constData( );
	auto converVar = ba.size( );
	if( infoTool::fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
		return false;
	if( converVar == 0 )
		return true;
	if( infoTool::fillVectorTarget( ( uint8_t * ) data, converVar, buff ) == false )
		return false;
	result.append_range( buff );
	return true;
}
inline bool fillTypeVectorAtVar( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QImage *target_var_ptr ) {
	result_count = *( uint64_t * ) source_ptr;
	size_t sizeTypeCount = sizeof( uint64_t );

	if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
		result_count = sizeTypeCount;
		return true;
	}
	size_t mod = source_count - sizeTypeCount;
	if( mod < result_count )
		return false;
	auto offset = source_ptr + sizeTypeCount;
	QByteArray ba( ( const char * ) offset, result_count );
	target_var_ptr->loadFromData( ba );
	result_count = result_count + sizeTypeCount;
	return result_count;
}
ImageUnityStack::~ImageUnityStack( ) {

}
bool ImageUnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , QImage, tr ("QImage"), tr ("Image"), tr ("image"), tr ("png") );
	return true;
}
ImageUnityStack::ImageUnityStack( ) {
}

bool ImageUnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
	if( fillTypeVectorAtVar( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
		return false;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		t_current_unity_type *sourcePtr = nullptr;
		if( varDirector->create( sourcePtr ) == false || sourcePtr == nullptr )
			return false;
		*sourcePtr = buffVar;
		result_obj_ptr = sourcePtr;
		return true;
	}

	auto createPtr = ( t_current_unity_type * ) result_obj_ptr;
	*createPtr = buffVar;
	return true;
}
TypeEnum::Type ImageUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool ImageUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( fillTypeVarAtVector( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
