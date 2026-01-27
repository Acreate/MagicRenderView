#include "colorUnityStack.h"

#include <define/stackTypeMacro.h>
#include <tools/infoTool.h>
#include <director/varDirector.h>
#include <QColor>
using t_current_unity_type = QColor;

namespace infoTool {

	template<>
	inline bool fillTypeVarAtVector< QColor >( const void *ptr, std::vector< uint8_t > &result ) {
		QColor *colorPtr = ( QColor * ) ptr;
		int r, g, b, a;
		colorPtr->getRgb( &r, &g, &b, &a );
		std::vector< uint8_t > buff;
		std::vector< uint8_t > colorBuff;
		if( fillTypeVarAtVector< uint64_t >( &r, buff ) == false )
			return false;
		colorBuff.append_range( buff );
		if( fillTypeVarAtVector< uint64_t >( &g, buff ) == false )
			return false;
		colorBuff.append_range( buff );
		if( fillTypeVarAtVector< uint64_t >( &b, buff ) == false )
			return false;
		colorBuff.append_range( buff );
		if( fillTypeVarAtVector< uint64_t >( &a, buff ) == false )
			return false;
		colorBuff.append_range( buff );

		auto converVar = colorBuff.size( );
		if( fillTypeVarAtVector< uint64_t >( &converVar, result ) == false )
			return false;
		if( converVar == 0 )
			return true;
		auto *data = colorBuff.data( );
		if( fillVectorTarget( data, converVar, buff ) == false )
			return false;
		result.append_range( buff );
		return true;
	}
	template<>
	inline bool fillTypeVectorAtVar< QColor >( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, QColor *target_var_ptr ) {
		result_count = *( uint64_t * ) source_ptr;
		size_t sizeTypeCount = sizeof( uint64_t );

		if( result_count == 0 ) {// 字符串为空时，直接返回长度匹配大小
			result_count = sizeTypeCount;
			return true;
		}
		size_t mod = source_count - sizeTypeCount;
		if( mod < result_count )
			return false;
		sizeTypeCount = sizeof( int );
		if( mod < ( sizeTypeCount * 4 ) )
			return false;
		auto offset = source_ptr + sizeTypeCount;
		int r, g, b, a;
		r = *( int * ) offset;
		offset = offset + sizeTypeCount;
		g = *( int * ) offset;
		offset = offset + sizeTypeCount;
		b = *( int * ) offset;
		offset = offset + sizeTypeCount;
		a = *( int * ) offset;
		offset = offset + sizeTypeCount;
		target_var_ptr->setRgba( qRgba( r, g, b, a ) );
		result_count = offset - source_ptr;
		return result_count;
	}
}

ColorUnityStack::~ColorUnityStack( ) {

}
bool ColorUnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , QColor, tr ("Color"), tr ("color" ) );
	return true;
}
ColorUnityStack::ColorUnityStack( ) {
}

bool ColorUnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
	if( infoTool::fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
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
TypeEnum::Type ColorUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool ColorUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
