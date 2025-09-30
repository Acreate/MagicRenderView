#ifndef NODEITEMTYPESERIALIZATION__H_H_HEAD__FILE__
#define NODEITEMTYPESERIALIZATION__H_H_HEAD__FILE__
#pragma once
#include "../I_Serialization‌.h"

class NodeItemTypeSerialization‌ : public I_Serialization‌ {
public:
	NodeItemTypeSerialization‌( );
	static bool checkTypeInfo( const type_info &type_info );
	bool appendVarType( const I_Type *append_unity ) override;
	bool removeVarType( const I_Type *append_unity ) override;
	bool get( const size_t &index, const I_Type *&result_unity ) const override;
	bool set( const size_t &index, const I_Type *new_unity ) override;
	size_t getBinVector( std_vector< uint8_t > &result_bin ) const override;
	size_t setBinVector( const uint8_t *init_bin_data_ptr, const size_t &init_bin_data_count ) const override;
};

#endif // NODEITEMTYPESERIALIZATION__H_H_HEAD__FILE__
