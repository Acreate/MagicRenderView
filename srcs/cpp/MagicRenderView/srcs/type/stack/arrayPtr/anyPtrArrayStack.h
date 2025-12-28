#ifndef ANYPTRARRAYSTACK_H_H_HEAD__FILE__
#define ANYPTRARRAYSTACK_H_H_HEAD__FILE__
#pragma once


#include "../../infoStack.h"

class AnyPtrArrayStack : public InfoStack {
	Q_OBJECT;
public:
	AnyPtrArrayStack( );
	~AnyPtrArrayStack( ) override;
protected:
	bool init( ) override;
public:
	bool toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	bool toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
};
#endif // ANYPTRARRAYSTACK_H_H_HEAD__FILE__
