#include "vectorTypeObject.h"
bool VectorTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	return false;
}
size_t VectorTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	return 0;
}
