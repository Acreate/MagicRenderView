#ifndef INT32ARRAYSTACK_H_H_HEAD__FILE__
#define INT32ARRAYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class Int32ArrayStack : public InfoStack {
	Q_OBJECT;
public:
	Int32ArrayStack( );
	~Int32ArrayStack( ) override;

public:
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	uint64_t toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
};

#endif // INT32ARRAYSTACK_H_H_HEAD__FILE__
