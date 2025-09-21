#ifndef QIMAGESERIALIZATION_H_H_HEAD__FILE__
#define QIMAGESERIALIZATION_H_H_HEAD__FILE__
#pragma once


#include "../../generate/binGenerate.h"

class QImageSerialization : public BinGenerate::BinGenerateItem {

	using t_current_type = QImage;
public:
	QImageSerialization( ) : BinGenerateItem( ) {
		typeName = typeid( t_current_type ).name( );
	}
	size_t fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const override;
	size_t fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override;
	size_t fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const override;
	size_t fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override;
	size_t fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const override;
	size_t fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const override;
};

#endif // QIMAGESERIALIZTION_H_H_HEAD__FILE__
