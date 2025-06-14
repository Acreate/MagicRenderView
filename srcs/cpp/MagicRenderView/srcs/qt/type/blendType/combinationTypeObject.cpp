#include "combinationTypeObject.h"

#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/type/baseType/nullTypeObject.h"
std_shared_ptr< ITypeObject > CombinationTypeObject::removeBeginElemnt( ) {
	size_t count = dataStruct->size( );
	if( count > 0 ) {
		auto iterator = dataStruct->begin( ) + count - 1;
		std_shared_ptr< ITypeObject > result = iterator->get( )->first;
		dataStruct->erase( iterator );
		return result;
	}
	std_shared_ptr< ITypeObject > shared( new NullTypeObject( nullptr ) ); // 返回一个空指针
	return shared;
}
std_shared_ptr< ITypeObject > CombinationTypeObject::removeEndElemnt( ) {
	size_t count = dataStruct->size( );
	if( count > 0 ) {
		auto iterator = dataStruct->begin( ) + count - 1;
		std_shared_ptr< ITypeObject > result = iterator->get( )->first;
		dataStruct->erase( iterator );
		return result;
	}
	std_shared_ptr< ITypeObject > shared( new NullTypeObject( [] { return IVarStack::getInstance< BaseVarStackEx >( ); } ) ); // 返回一个空指针
	return shared;
}
std_shared_ptr< ITypeObject > CombinationTypeObject::removeItem( const QString &&var_name ) {
	auto itorater = dataStruct->begin( );
	auto end = dataStruct->end( );
	for( ; itorater != end; ++itorater )
		if( itorater->get( )->second == var_name ) {
			std::shared_ptr< ITypeObject > result = itorater->get( )->first;
			dataStruct->erase( itorater );
			return result;
		}
	std_shared_ptr< ITypeObject > shared( new NullTypeObject( [] { return IVarStack::getInstance< BaseVarStackEx >( ); } ) ); // 返回一个空指针
	return shared;
}
std_shared_ptr< ITypeObject > CombinationTypeObject::setVarObject( const std_shared_ptr< ITypeObject > &new_type, const QString &var_name ) {
	for( auto &pair : *dataStruct )
		if( pair->second == var_name ) {
			std_shared_ptr< ITypeObject > element = pair->first; // 用于覆盖返回
			pair->first = new_type;
			return element;
		}

	auto ptr = std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > >( new std_pairt< std_shared_ptr< ITypeObject >, QString >( ) );
	ptr->first = new_type;
	ptr->second = var_name;
	dataStruct->emplace_back( ptr );
	std_shared_ptr< ITypeObject > shared( new NullTypeObject( [] { return IVarStack::getInstance< BaseVarStackEx >( ); } ) ); // 返回一个空指针
	return shared;
}
std_shared_ptr< ITypeObject > CombinationTypeObject::getVarObject( const QString &var_name ) const {
	for( auto pair : *dataStruct )
		if( pair->second == var_name )
			return pair->first;
	std_shared_ptr< ITypeObject > shared( new NullTypeObject( [] { return IVarStack::getInstance< BaseVarStackEx >( ); } ) ); // 返回一个空指针
	return shared;
}
bool CombinationTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	return false;
}
size_t CombinationTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	return 0;
}
int CombinationTypeObject::compare( const ITypeObject &rhs ) const {
	decltype(this) result_ptr;
	int result = comp( this, &rhs, result_ptr );
	if( result == 0 && result_ptr == this ) {
		size_t thisCount = dataStruct->size( );
		size_t rCount = result_ptr->dataStruct->size( );
		if( thisCount > rCount )
			return 1;
		if( thisCount < rCount )
			return -1;
		for( size_t index = 0; index < thisCount; ++index ) {
			int compare = dataStruct->at( index )->first->compare( *result_ptr->dataStruct->at( index )->first );
			if( compare != 0 )
				return compare;
			compare = dataStruct->at( index )->second.compare( result_ptr->dataStruct->at( index )->second );
			if( compare != 0 )
				return compare;
		}
	}

	return result;
}
size_t CombinationTypeObject::typeMemorySize( ) const {
	size_t result = 0;
	for( auto pair : *dataStruct )
		result += pair->first->typeMemorySize( ) + ( pair->second.size( ) + 1 ) * sizeof( QChar );
	return result;
}
QString CombinationTypeObject::toString( ) const {
	QStringList result;
	for( auto pair : *dataStruct )
		result.append( pair->second + "( " + pair->first->toString( ) + " )" );
	return QString( metaObject( )->className( ) ) + " { " + result.join( ", " ) + " }";
}
