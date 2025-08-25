#include "vectorTypeObject.h"

#include <qt/application/application.h>

#include <qt/stacks/stackManagement.h>

#include "qt/stacks/varStack/IVarStack.h"
#include "qt/types/baseType/nullTypeObject.h"
#include "qt/stacks/varStack/base/baseVarStack.h"
ITypeObject * VectorTypeObject::createType( const QString &type_name ) {
	if( generateThisVarStackPtr )
		return generateThisVarStackPtr->generateUbVar( type_name );
	return getStackFunction( )->generateUbVar( type_name );
}
VectorTypeObject::VectorTypeObject( IVarStack *generate_this_var_stack_ptr_ptr, const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *parent ) : ITypeObject( generate_this_var_stack_ptr_ptr, gener_var_stack, alias_type_name, parent ), vector( new std_vector< std_shared_ptr< ITypeObject > >( ) ) {
}
VectorTypeObject & VectorTypeObject::operator=( const VectorTypeObject &other ) {
	if( this == nullptr || thisPtr == nullptr )
		return *this;
	auto typeObject = &other;
	if( typeObject != nullptr && other.thisPtr != nullptr ) {
		if( this == typeObject )
			return *this;
		ITypeObject::operator =( other );
		vector = other.vector;
	} else
		thisPtr = nullptr;
	return *this;
}
void VectorTypeObject::append( const std_shared_ptr< ITypeObject > &append_object ) {
	vector->emplace_back( append_object );
}
size_t VectorTypeObject::count( ) const {
	return vector->size( );
}
size_t VectorTypeObject::size( ) const {
	return vector->size( );
}
void VectorTypeObject::clear( ) {
	vector->clear( );
}
std_shared_ptr< ITypeObject > VectorTypeObject::operator[]( const size_t index ) const {
	size_t count = vector->size( );
	if( count > index )
		return vector->at( index );
	tools::debug::printError( "访问下标越界" );
	auto newCall = [this] { return std_shared_ptr< IVarStack >( new BaseVarStack ); };
	auto nullTypeObject = new NullTypeObject( generateThisVarStackPtr, newCall );
	std_shared_ptr< ITypeObject > shared( nullTypeObject ); // 返回一个空指针
	return shared;
}
void VectorTypeObject::setVector( const std_shared_ptr< std_vector< std_shared_ptr< ITypeObject > > > &vector ) {
	if( vector == nullptr )
		this->clear( );
	else
		this->vector = vector;
}
std_shared_ptr< ITypeObject > VectorTypeObject::find( const std_function< bool( std_shared_ptr< ITypeObject > & ) > &find_function ) const {
	for( auto elemt : *vector )
		if( find_function( elemt ) )
			return elemt;
	NullTypeObject *nullTypeObject = new NullTypeObject(
		generateThisVarStackPtr,
		[] { return std_shared_ptr< IVarStack >( new BaseVarStack ); } );
	std_shared_ptr< ITypeObject > shared( nullTypeObject ); // 返回一个空指针
	return shared;
}
std_vector< std_shared_ptr< ITypeObject > > VectorTypeObject::findAll( const std_function< bool( std_shared_ptr< ITypeObject > & ) > &find_function ) const {
	std_vector< std_shared_ptr< ITypeObject > > result;
	for( auto elemt : *vector )
		if( find_function( elemt ) )
			result.emplace_back( elemt );
	return result;
}
void VectorTypeObject::setVectorTypeObject( const VectorTypeObject *vector_type_object ) const {
	size_t count = vector_type_object->size( );
	vector->resize( count );
	auto typeObject = vector->data( );
	auto sourcePtr = vector_type_object->data( );
	for( size_t index = 0; index < count; ++index )
		typeObject[ index ] = sourcePtr[ index ];
}
bool VectorTypeObject::removeStartElemt( ) {
	if( vector->size( ) == 0 )
		return false;
	vector->erase( vector->begin( ) );
	return true;
}
bool VectorTypeObject::removeLastElemt( ) {
	if( vector->size( ) == 0 )
		return false;
	vector->pop_back( );
	return true;
}
bool VectorTypeObject::removeFirst( const std_shared_ptr< ITypeObject > &remove_elemt ) {
	std_vector< std_shared_ptr< ITypeObject > > result;
	auto iterator = vector->begin( );
	auto end = vector->end( );

	for( ; iterator != end; ++iterator )
		if( remove_elemt->compare( **iterator ) == 0 ) {
			vector->erase( iterator );
			return true;
		}
	return false;
}
size_t VectorTypeObject::removeAll( const std_shared_ptr< ITypeObject > &remove_elemt ) {
	std::vector< std::shared_ptr< ITypeObject > >::iterator iterator;
	std::vector< std::shared_ptr< ITypeObject > >::iterator end;

	iterator = vector->begin( );
	end = vector->end( );
	size_t start = 0, removeCount = 0;
	for( ; iterator != end; ++iterator, ++start )
		if( remove_elemt->compare( **iterator ) == 0 ) {
			vector->erase( iterator );
			iterator = vector->begin( ) + start - 1;
			end = vector->end( );
			++removeCount;
		}
	return removeCount;
}
void VectorTypeObject::removeFind( const std_function< bool( const ITypeObject * ) > &find_function ) {
	std::vector< std::shared_ptr< ITypeObject > >::iterator iterator;
	std::vector< std::shared_ptr< ITypeObject > >::iterator end;

	iterator = vector->begin( );
	end = vector->end( );
	for( ; iterator != end; ++iterator )
		if( find_function( iterator->get( ) ) ) {
			vector->erase( iterator );
			return;
		}
}
void VectorTypeObject::removeFindAll( const std_function< bool( const ITypeObject * ) > &find_function ) {
	std::vector< std::shared_ptr< ITypeObject > >::iterator iterator;
	std::vector< std::shared_ptr< ITypeObject > >::iterator end;

	iterator = vector->begin( );
	end = vector->end( );
	size_t start = 0;
	for( ; iterator != end; ++iterator, ++start )
		if( find_function( iterator->get( ) ) ) {
			vector->erase( iterator );
			iterator = vector->begin( ) + start - 1;
			end = vector->end( );
		}
}
size_t VectorTypeObject::typeMemorySize( ) const {
	size_t result = 0;
	for( auto elemt : *vector )
		result += elemt->typeMemorySize( );
	return result;
}

int VectorTypeObject::compare( const ITypeObject &rhs ) const {
	decltype(this) result_ptr;
	int result = comp( this, &rhs, result_ptr );
	if( result == 0 && result_ptr == this ) {
		auto thisCount = this->vector->size( );
		auto otherCount = result_ptr->vector->size( );
		if( thisCount > otherCount )
			return 1;
		if( thisCount < otherCount )
			return -1;
		for( size_t index = 0; index < otherCount; ++index ) {
			int compare = this->vector->at( index )->compare( *result_ptr->vector->at( index ) );
			if( compare != 0 )
				return compare;
		}
	}
	return result;
}

QString VectorTypeObject::toString( ) const {
	QStringList result;
	for( auto elemt : *vector )
		result.append( elemt->toString( ) );
	return "(" + result.join( "," ) + ")";
}
bool VectorTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	// 序列化成员对象到数据
	uint8_t *dataPtr;
	uint8_t *targetDataPtr;
	size_t copySize;
	size_t copyIndex;

	size_t buffIndex = 0;
	size_t buffSize = 1024;
	size_t thisValVectorIndex = 0;
	std_vector< uint8_t > unityDataVector( buffSize ), serializeBuff;
	size_t thisValVectorCount = vector->size( );
	auto thisValVectorDataPtr = vector->data( );

	for( ; thisValVectorIndex < thisValVectorCount; ++thisValVectorIndex ) {
		auto shared = thisValVectorDataPtr[ thisValVectorIndex ];
		if( shared.get( ) == this )
			return false;
		if( shared->serializeToVectorData( &serializeBuff ) == false )
			return false;
		dataPtr = serializeBuff.data( );
		copySize = serializeBuff.size( );
		copyIndex = buffSize - buffIndex;
		if( copyIndex < copySize ) {
			buffSize = buffSize + copySize;
			unityDataVector.resize( buffSize );
		}
		targetDataPtr = unityDataVector.data( );
		for( copyIndex = 0; copyIndex < copySize; ++copyIndex, ++buffIndex )
			targetDataPtr[ buffIndex ] = dataPtr[ copyIndex ];
	}

	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( result_data_vector, metaObject( ), getStackTypeName( ), typeNames( ), appendSize + buffIndex );
	size_t resultSize = result_data_vector->size( );
	if( resultSize == 0 )
		return false;
	*( size_t * ) lastPtr = thisValVectorCount;
	if( thisValVectorCount == 0 )
		return true;
	lastPtr += appendSize; // 指向数据起始地址
	targetDataPtr = unityDataVector.data( );
	for( size_t index = 0; index < buffIndex; ++index )
		lastPtr[ index ] = targetDataPtr[ index ];
	return true;
}
size_t VectorTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	// 序列化序列成员
	std_vector< uint8_t > result;
	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( &result, metaObject( ), getStackTypeName( ), typeNames( ), appendSize );
	size_t resultSize = result.size( );
	if( resultSize == 0 || data_count < resultSize ) {
		tools::debug::printError( "无法序列化该对象信息" );
		return false;
	}
	auto data = result.data( );
	// 大小端
	bool cond = *data != *read_data_vector;
	auto readDataPtr = read_data_vector + 1;
	size_t unitySize = *( type_size_t * ) readDataPtr;
	if( cond )
		converEndian( unitySize );
	if( unitySize > data_count ) {
		tools::debug::printError( "所需数据大于提供的参数" );
		return false;
	}
	readDataPtr += appendSize;
	data += appendSize + 1;
	size_t index = 0;
	for( ; ( data + index ) != lastPtr; ++index )
		if( data[ index ] != readDataPtr[ index ] ) {
			tools::debug::printError( "类型信息不匹配" );
			return false;
		}
	readDataPtr += index;
	unitySize = *( type_size_t * ) readDataPtr;
	if( cond )
		converEndian( unitySize );
	if( unitySize == 0 )
		return resultSize;

	uint8_t en;
	std_vector< QString > typeName, stackName;
	std_shared_ptr< IVarStack > varStack;
	std_shared_ptr< ITypeObject > typeObject;
	std_vector< std_shared_ptr< ITypeObject > > ve;
	uint64_t userDataCount;
	size_t count;
	readDataPtr += appendSize;
	count = data_count - ( readDataPtr - read_data_vector );
	auto applicationInstancePtr = Application::getApplicationInstancePtr( );
	std_vector< std::shared_ptr< IVarStack > > findResults;
	StackManagement *stackManagement = applicationInstancePtr->getStackManagement( );
	for( index = 0; index < unitySize; ++index ) {
		userDataCount = ISerialize::SerializeInfo::getSerializeInfo( readDataPtr, count, &en, &stackName, nullptr, &typeName );
		if( userDataCount == 0 ) {
			tools::debug::printError( "无法从数据当中反序列化对象的成员类型信息" );
			return 0;
		}
		findResults = stackManagement->findVarStacksAtType( stackName[ 0 ] );
		if( findResults.size( ) == 0 ) {
			findResults = stackManagement->findVarStacksAtName( stackName[ 0 ] );
			if( findResults.size( ) == 0 ) {
				tools::debug::printError( "找不到创建该对象成员类型的匹配堆栈 : " + stackName[ 0 ] );
				return 0;
			}
		}
		varStack = findResults[ 0 ];
		if( varStack == nullptr ) {
			tools::debug::printError( "找不到创建该对象成员类型的匹配堆栈 : " + stackName[ 0 ] );
			return 0;
		}
		typeObject = varStack->generateVar( typeName[ 0 ] );
		if( typeObject == nullptr ) {
			tools::debug::printError( "堆栈当中无法找到匹配的类型 : " + typeName[ 0 ] );
			return 0;
		}
		userDataCount = typeObject->serializeToObjectData( readDataPtr, count );
		resultSize += userDataCount;
		count -= userDataCount; // 减去用量
		readDataPtr += userDataCount;// 增加偏移
		ve.emplace_back( typeObject );
	}
	*vector = ve;
	return resultSize;
}
