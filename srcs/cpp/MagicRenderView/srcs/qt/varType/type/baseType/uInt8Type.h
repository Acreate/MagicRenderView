#ifndef UINT8TYPE_H_H_HEAD__FILE__
#define UINT8TYPE_H_H_HEAD__FILE__
#pragma once


#include "../../I_Stack.h"


class UInt8Type : public  I_Stack{
	using t_current_type = uint8_t;
public:
	UInt8Type( ) : I_Stack( typeid( t_current_type ) ) { }
	bool createTarget( const type_info &target_type_info, const std_function<void(void *create_obj_ptr)> &create_call_function ) override;
	bool deleteTarget( const type_info &target_type_info, void *target_ptr ) override;
	bool deleteTarget( void *target_ptr ) override;
	bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector<uint8_t> &result_vector, size_t &result_count ) override;
	bool toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) override;
};


#endif // UINT8TYPE_H_H_HEAD__FILE__
