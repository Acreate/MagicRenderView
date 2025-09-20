#ifndef INT32SERIALIZATION_H_H_HEAD__FILE__
#define INT32SERIALIZATION_H_H_HEAD__FILE__
#pragma once
#include "../generate/binGenerate.h"

class Int32Serialization : public BinGenerate::BinGenerateItem {

public:
	Int32Serialization( ) {
		typeName = typeid( int32_t ).name( );
	}
	size_t fillBin( const Unity *var_type, std_vector<uint8_t> &result_bin_data_vector ) const override;
	size_t fillObj( Unity *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override;
	size_t fillBin( const UnityVector *var_type, std_vector<uint8_t> &result_bin_data_vector ) const override;
	size_t fillObj( UnityVector *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override;
	size_t fillBin( const UnityPtrVector *var_type, std_vector<uint8_t> &result_bin_data_vector ) const override;
	size_t fillObj( UnityPtrVector *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override;
};

#endif // INT32SERIALIZATION_H_H_HEAD__FILE__
