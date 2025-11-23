#ifndef UINT32ARRAYSTACK_H_H_HEAD__FILE__
#define UINT32ARRAYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class UInt32ArrayStack : public InfoStack {
	Q_OBJECT;
public:
	UInt32ArrayStack( );
	~UInt32ArrayStack( ) override;

public:
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	uint64_t toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
};

#endif // UINT32ARRAYSTACK_H_H_HEAD__FILE__
