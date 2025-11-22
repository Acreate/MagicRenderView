#ifndef UINT32UNITYSTACK_H_H_HEAD__FILE__
#define UINT32UNITYSTACK_H_H_HEAD__FILE__
#pragma once
#include "../../infoStack.h"

class UInt32UnityStack : public InfoStack {
	Q_OBJECT;
public:
	UInt32UnityStack( );
	~UInt32UnityStack( ) override;
	void * createTypePtr( ) override;
	bool deleteTypePtr( const void *delete_obj_ptr ) override;
	uint64_t toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
	uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) override;
	TypeEnum::Type getType( ) override;
};

#endif // UINT32UNITYSTACK_H_H_HEAD__FILE__
