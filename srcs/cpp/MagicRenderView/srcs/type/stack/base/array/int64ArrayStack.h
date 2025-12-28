#ifndef INT64ARRAYSTACK_H_H_HEAD__FILE__
#define INT64ARRAYSTACK_H_H_HEAD__FILE__
#pragma once
#include <type/infoStack.h>

class Int64ArrayStack : public InfoStack {
	Q_OBJECT;
public:
	Int64ArrayStack( );
	~Int64ArrayStack( ) override;
protected:
	bool init( ) override;
public:
	bool toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) override;
	TypeEnum::Type getType( ) override;
protected:
	bool toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) override;
};

#endif // INT64ARRAYSTACK_H_H_HEAD__FILE__
