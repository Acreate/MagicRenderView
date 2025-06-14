#include "pairtTypeObject.h"

#include "qt/stack/varStack/IVarStack.h"
PairtTypeObject::PairtTypeObject( const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *parnet ): PairtTypeObject( gener_var_stack, alias_type_name, parnet, nullptr, nullptr ) {
}
PairtTypeObject::PairtTypeObject( const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *parent, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond ): ITypeObject( gener_var_stack, alias_type_name, parent ),
	first( first ), scond( scond ) {
	if( this->first == nullptr )
		this->first = varStackSharedPtr.get( )->generateTVar< NullTypeObject >( );
	if( this->scond == nullptr )
		this->scond = varStackSharedPtr.get( )->generateTVar< NullTypeObject >( );
}
PairtTypeObject::PairtTypeObject( const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond ) : PairtTypeObject( gener_var_stack, { }, nullptr, first, scond ) {
}
PairtTypeObject & PairtTypeObject::operator=( const PairtTypeObject &other ) {
	if( this == nullptr || thisPtr == nullptr )
		return *this;
	auto typeObject = &other;
	if( typeObject != nullptr && other.thisPtr != nullptr ) {
		if( this == typeObject )
			return *this;
		ITypeObject::operator =( other );
		first = other.first;
		scond = other.scond;
	} else
		thisPtr = nullptr;
	return *this;
}

bool PairtTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	// 序列化成员对象到数据
	std_vector< uint8_t > firstSerializeDataVector, scondSerializeDataVector;
	if( first->serializeToVectorData( &firstSerializeDataVector ) == false ) {
		tools::debug::printError( "first 序列化失败" );
		return false;
	}
	if( scond->serializeToVectorData( &scondSerializeDataVector ) == false ) {
		tools::debug::printError( "scond 序列化失败" );
		return false;
	}
	size_t firstCount = firstSerializeDataVector.size( );
	size_t scondCount = scondSerializeDataVector.size( );
	size_t appendDataCount = firstCount + scondCount;
	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( result_data_vector, metaObject( ), getStackTypeNames( ), typeNames( ), appendSize + firstCount + appendDataCount );
	size_t resultSize = result_data_vector->size( );
	if( resultSize == 0 )
		return false;
	*( size_t * ) lastPtr = 2;
	lastPtr += appendSize;
	auto sourceDataPtr = firstSerializeDataVector.data( );
	size_t index = 0;
	for( ; index < firstCount; ++index )
		lastPtr[ index ] = sourceDataPtr[ index ];
	sourceDataPtr = scondSerializeDataVector.data( );
	lastPtr += index;
	for( index = 0; index < scondCount; ++index )
		lastPtr[ index ] = sourceDataPtr[ index ];
	return true;
}
size_t PairtTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	// 序列化序列成员
	std_vector< uint8_t > result;
	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( &result, metaObject( ), getStackTypeNames( ), typeNames( ), appendSize );
	size_t resultSize = result.size( );
	if( resultSize == 0 || data_count < resultSize )
		return false;
	auto data = result.data( );
	// 大小端
	bool cond = *data != *read_data_vector;
	auto readDataPtr = read_data_vector + 1;
	size_t unitySize = *( type_size_t * ) readDataPtr;
	if( cond )
		converEndian( unitySize );
	if( unitySize > data_count ) // 所需数据大于提供的参数
		return 0;
	readDataPtr += appendSize;
	data += appendSize + 1;
	size_t index = 0;
	for( ; ( data + index ) != lastPtr; ++index )
		if( data[ index ] != readDataPtr[ index ] )
			return 0;
	readDataPtr += index;
	unitySize = *( type_size_t * ) readDataPtr;
	if( cond )
		converEndian( unitySize );
	if( unitySize != 2 )
		return 0;

	uint8_t en;
	std_vector< QString > typeName, stackName;
	std_shared_ptr< IVarStack > varStack;
	std_shared_ptr< ITypeObject > typeObject;
	std_vector< std_shared_ptr< ITypeObject > > ve;
	uint64_t userDataCount;
	size_t count;
	readDataPtr += appendSize;
	count = data_count - ( readDataPtr - read_data_vector );

	for( index = 0; index < unitySize; ++index ) {
		userDataCount = ISerialize::SerializeInfo::getSerializeInfo( readDataPtr, count, &en, &stackName, nullptr, &typeName );
		if( userDataCount == 0 )
			return 0;
		varStack = IVarStack::getInstance( stackName[ 0 ] );
		if( varStack == nullptr )
			return 0;
		typeObject = varStack->generateVar( typeName[ 0 ] );
		if( typeObject == nullptr )
			return 0;
		userDataCount = typeObject->serializeToObjectData( readDataPtr, count );
		resultSize += userDataCount;
		count -= userDataCount; // 减去用量
		readDataPtr += userDataCount;// 增加偏移
		ve.emplace_back( typeObject );
	}
	first = ve[0];
	scond = ve[1];
	return resultSize;
}
