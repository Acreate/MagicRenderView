#include "stackSerializeGenerate.h"

#include "../serializeData/stackSerialize.h"
StackSerialize * StackSerializeGenerate::generateStackSerialize( const QString &type_name, const std::function< uint64_t( const uint8_t *, const size_t &, std::vector< uint8_t > & ) > &to_data_function, const std::function< uint64_t( const uint8_t *, const size_t &, std::vector< void * > & ) > &to_obj_function ) {
	auto result = new StackSerialize;
	result->typeName = type_name;
	result->toDataFunction = to_data_function;
	result->toObjFunction = to_obj_function;
	return result;
}
