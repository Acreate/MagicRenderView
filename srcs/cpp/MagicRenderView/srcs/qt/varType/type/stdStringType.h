#ifndef STDSTRINGTYPE_H_H_HEAD__FILE__
#define STDSTRINGTYPE_H_H_HEAD__FILE__
#pragma once


#include "../I_Stack.h"
class StdStringType : public  I_Stack{
	using t_current_type = std::string;
public:
	StdStringType( ) : I_Stack( typeid( t_current_type ) ) { }
	bool createTarget( const type_info &target_type_info, void *&target_ptr ) override;
	bool deleteTarget( const type_info &target_type_info, void *target_ptr ) override;
	bool deleteTarget( void *target_ptr ) override;
	bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector<uint8_t> &result_vector, size_t &result_count ) override;
	bool toOBjVector( const type_info &target_type_info, void *&target_ptr, size_t &result_count, const std_vector<uint8_t> &load_bin_vector ) override;
};


#endif // STDSTRINGTYPE_H_H_HEAD__FILE__
