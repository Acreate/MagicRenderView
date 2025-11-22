#ifndef INT32ARRAYSTACK_H_H_HEAD__FILE__
#define INT32ARRAYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class Int32ArrayStack : public InfoStack {
	Q_OBJECT;
public:
	using t_current_type = std::vector< int32_t >;
public:
	Int32ArrayStack( );
	~Int32ArrayStack( ) override;
	void * createTypePtr( ) override;
	bool deleteTypePtr( const void *delete_obj_ptr ) override;
	uint64_t toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) override;
	TypeEnum::Type getType( ) override;
};

#endif // INT32ARRAYSTACK_H_H_HEAD__FILE__
