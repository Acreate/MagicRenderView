#ifndef UINT64ARRAYSTACK_H_H_HEAD__FILE__
#define UINT64ARRAYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class UInt64ArrayStack : public InfoStack {
	Q_OBJECT;
public:
	UInt64ArrayStack( );
	~UInt64ArrayStack( ) override;
	void * createTypePtr( ) override;
	bool deleteTypePtr( const void *delete_obj_ptr ) override;
	uint64_t toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) override;
	TypeEnum::Type getType( ) override;
};

#endif // UINT64ARRAYSTACK_H_H_HEAD__FILE__
