#include "stdWStringStack.h"


#include <qt/generate/varGenerate.h>

StdWStringStack::StdWStringStack( ) : I_Stack( typeid( t_current_type ) ) {

}
bool StdWStringStack::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {

	if( target_type_info != stackTypeInfo )
		return false;
	// 转换到 qstring，使用 qstring 去实现
	QString buff = QString::fromStdWString( *( std::wstring * ) target_ptr );
	return varGenerate->toBinVector( typeid( QString ), &buff, result_vector, result_count );
}
bool StdWStringStack::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_type_info != stackTypeInfo )
		return false;
	QString buff;
	void *strPtr = &buff;
	void **targetPtr = &strPtr;
	bool oBjVector = varGenerate->toOBjVector( typeid( QString ), *targetPtr, result_count, source_data_ptr, source_data_count );
	if( oBjVector == false )
		return false;
	*( std::wstring * ) target_ptr = buff.toStdWString( );
	return true;
}
