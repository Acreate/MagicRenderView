#ifndef FLOAT32UNITYSTACK_H_H_HEAD__FILE__
#define FLOAT32UNITYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class Float32UnityStack : public InfoStack {
	Q_OBJECT;
public:
	using t_current_type = float;
public:
	Float32UnityStack( );
	~Float32UnityStack( ) override;
	void * createTypePtr( ) override;
	bool deleteTypePtr( const void *delete_obj_ptr ) override;
	uint64_t toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) override;
	TypeEnum::Type getType( ) override;
};

#endif // FLOAT32UNITYSTACK_H_H_HEAD__FILE__
