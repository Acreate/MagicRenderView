#ifndef INT32SERIALIZATION_H_H_HEAD__FILE__
#define INT32SERIALIZATION_H_H_HEAD__FILE__
#pragma once
#include "../../generate/binGenerate.h"


class Int32Serialization : public BinGenerate::BinGenerateItem {

	using t_current_type = int32_t;
public:
	Int32Serialization( ) {
		typeName = typeid(t_current_type  ).name( );
	}
	size_t fillUnityBin( const void *var_type, std_vector<uint8_t> &result_bin_data_vector ) override;
	size_t fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) override;
	size_t fillVectorBin( const void *var_type, std_vector<uint8_t> &result_bin_data_vector ) override;
	size_t fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) override;
	size_t fillPtrVectorBin( const void *var_type, std_vector<uint8_t> &result_bin_data_vector ) override;
	size_t fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) override;
	bool getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) override;
	bool removeNewObj( void *new_set_ptr ) override;
};

#endif // INT32SERIALIZATION_H_H_HEAD__FILE__
