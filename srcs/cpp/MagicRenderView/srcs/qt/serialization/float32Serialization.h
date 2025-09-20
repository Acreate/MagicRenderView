#ifndef FLOAT32SERIALIZATION_H_H_HEAD__FILE__
#define FLOAT32SERIALIZATION_H_H_HEAD__FILE__
#pragma once
#include "../generate/binGenerate.h"

class Float32Serialization : public BinGenerate::BinGenerateItem {

public:
	Float32Serialization( ) {
		typeName = typeid( float_t ).name( );
	}
	size_t fillBinVector( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const override {
		return 0;
	}
	size_t fillObjVector( void *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override {
		return 0;
	}
};

#endif // FLOAT32SERIALIZATION_H_H_HEAD__FILE__
