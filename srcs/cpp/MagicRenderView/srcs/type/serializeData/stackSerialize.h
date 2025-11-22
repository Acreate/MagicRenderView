#ifndef STACKSERIALIZE_H_H_HEAD__FILE__
#define STACKSERIALIZE_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

class StackSerialize {
	friend class StackSerializeGenerate;
protected:
	QString typeName;
	std::function< uint64_t ( const uint8_t *, const size_t &, std::vector< uint8_t > & ) > toDataFunction;
	std::function< uint64_t ( const uint8_t *, const size_t &, std::vector< void * > & ) > toObjFunction;
public:
	virtual ~StackSerialize( ) = default;
	virtual const QString & getTypeName( ) const { return typeName; }
	virtual uint64_t toData( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< uint8_t > &result_data ) {
		return toDataFunction( obj_start_ptr, obj_memory_size, result_data );
	}
	virtual uint64_t toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
		return toObjFunction( obj_start_ptr, obj_memory_size, result_data );
	}
};

#endif // STACKSERIALIZE_H_H_HEAD__FILE__
