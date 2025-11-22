#ifndef STACKSERIALIZEGENERATE_H_H_HEAD__FILE__
#define STACKSERIALIZEGENERATE_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>

class StackSerialize;
class StackSerializeGenerate {
	friend class VarGenerate;
	static StackSerialize * generateStackSerialize( const QString &type_name, const std::function< uint64_t( const uint8_t *, const size_t &, std::vector< uint8_t > & ) > &to_data_function, const std::function< uint64_t( const uint8_t *, const size_t &, std::vector< void * > & ) > &to_obj_function );
};

#endif // STACKSERIALIZEGENERATE_H_H_HEAD__FILE__
