#ifndef STDWSTRINGSERIALIZATION_H_H_HEAD__FILE__
#define STDWSTRINGSERIALIZATION_H_H_HEAD__FILE__
#pragma once
#include "../generate/binGenerate.h"

class StdWStringSerialization : public BinGenerate::BinGenerateItem {

public:
	StdWStringSerialization( ) {
		typeName = typeid( std::wstring ).name( );
	}
	size_t fillBinVector( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const override {
		return 0;
	}
	size_t fillObjVector( void *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override {
		return 0;
	}
};

#endif // STDWSTRINGSERIALIZATION_H_H_HEAD__FILE__
