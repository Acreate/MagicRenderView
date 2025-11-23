#ifndef INT64UNITYSTACK_H_H_HEAD__FILE__
#define INT64UNITYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class Int64UnityStack : public InfoStack {
	Q_OBJECT;
public:
	Int64UnityStack( );
	~Int64UnityStack( ) override;
protected:
	bool init( ) override;
public:
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	uint64_t toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
};

#endif // INT64UNITYSTACK_H_H_HEAD__FILE__
