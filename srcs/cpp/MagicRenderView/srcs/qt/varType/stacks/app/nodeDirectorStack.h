#ifndef NODEDIRECTORSTACK_H_H_HEAD__FILE__
#define NODEDIRECTORSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../I_Stack.h"

class NodeDirector;
class NodeDirectorStack : public I_Stack {
	using t_current_type = NodeDirector;
public:
	NodeDirectorStack( );
	bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const override;
	bool toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const override;

};

#endif // NODEDIRECTORSTACK_H_H_HEAD__FILE__
