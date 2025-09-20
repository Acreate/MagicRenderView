#ifndef INT64SERIALIZATION_H_H_HEAD__FILE__
#define INT64SERIALIZATION_H_H_HEAD__FILE__
#pragma once
#include "../generate/binGenerate.h"

class Int64Serialization : public BinGenerate::BinGenerateItem {

public:
	Int64Serialization( ) {
		typeName = typeid( int64_t ).name( );
	}
	size_t fillBinVector( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const override {
		return 0;
	}
	size_t fillObjVector( void *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override {
		return 0;
	}
};

#endif // INT64SERIALIZATION_H_H_HEAD__FILE__
