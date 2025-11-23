#ifndef INT32UNITYSTACK_H_H_HEAD__FILE__
#define INT32UNITYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class Int32UnityStack : public InfoStack {
	Q_OBJECT;
public:
	Int32UnityStack( );
	~Int32UnityStack( ) override;

public:
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	uint64_t toVectorData( void *obj_start_ptr, std::vector<uint8_t> &result_data ) override;
};

#endif // INT32UNITYSTACK_H_H_HEAD__FILE__
