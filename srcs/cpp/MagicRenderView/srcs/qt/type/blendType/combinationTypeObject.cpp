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
	// sizeof( size_t );
	size_t sizeSize = sizeof( type_size_t );
	size_t buffIndex = 0;
	size_t buffSize = 1024;
	size_t thisValVectorIndex = 0;
	std_vector< uint8_t > unityDataVector( buffSize ), serializeBuff;
	size_t thisValVectorCount = dataStruct->size( );
	auto thisValVectorDataPtr = dataStruct->data( );
	uint8_t *targetDataPtr = unityDataVector.data( );
	char *utfDataPtr;
	uint8_t *dataPtr;
	size_t copySize;
	size_t copyIndex;

	for( ; thisValVectorIndex < thisValVectorCount; ++thisValVectorIndex ) {
		auto shared = thisValVectorDataPtr[ thisValVectorIndex ];
		auto element = shared.get( );
		ITypeObject *typeObject = element->first.get( );
		if( typeObject == this )
			return false;

		if( typeObject->serializeToVectorData( &serializeBuff ) == false )
			return false;

		dataPtr = serializeBuff.data( );
		copySize = serializeBuff.size( );
		copyIndex = buffSize - buffIndex;
		if( copyIndex < copySize ) {
			buffSize = buffSize + copySize;
			unityDataVector.resize( buffSize );
			targetDataPtr = unityDataVector.data( );
		}
		for( copyIndex = 0; copyIndex < copySize; ++copyIndex, ++buffIndex )
			targetDataPtr[ buffIndex ] = dataPtr[ copyIndex ];

		QString string = element->second.toUtf8( ).toHex( );
		QByteArray byteArray = string.toUtf8( );

		qint64 qsizetype = byteArray.size( );
		copySize = qsizetype + sizeSize;
		copyIndex = buffSize - buffIndex;
		if( copyIndex < copySize ) {
			buffSize = buffSize + copySize;
			unityDataVector.resize( buffSize );
			targetDataPtr = unityDataVector.data( );
		}
		*( size_t * ) ( targetDataPtr + buffIndex ) = qsizetype;
		buffIndex += sizeSize;
		copySize -= sizeSize;

		utfDataPtr = byteArray.data( );
		for( copyIndex = 0; copyIndex < copySize; ++copyIndex, ++buffIndex )
			targetDataPtr[ buffIndex ] = utfDataPtr[ copyIndex ];
	}

	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( result_data_vector, metaObject( ), getStackTypeNames( ), typeNames( ), appendSize + buffIndex );
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
size_t CombinationTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	// 序列化序列成员
	std_vector< uint8_t > result;
	//  sizeof( size_t )
	size_t appendSize = sizeof( type_size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( &result, metaObject( ), getStackTypeNames( ), typeNames( ), appendSize );
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
	for( ; data != lastPtr; ++readDataPtr, ++data )
		if( *data != *readDataPtr ) {
			tools::debug::printError( "类型信息不匹配" );
			return false;
		}
	unitySize = *( type_size_t * ) readDataPtr;
	if( cond )
		converEndian( unitySize );
	if( unitySize == 0 )
		return resultSize;

	uint8_t en;
	std_vector< QString > typeName, stackName;
	std_shared_ptr< IVarStack > varStack;
	std_shared_ptr< ITypeObject > typeObject;
	std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > > ve;
	uint64_t userDataCount;
	size_t count;
	size_t stringDataSize;
	size_t utfIndex;
	QByteArray utf8;
	char *targetPtr;
	readDataPtr += appendSize;
	count = data_count - ( readDataPtr - read_data_vector );

	for( index = 0; index < unitySize; ++index ) {
		userDataCount = ISerialize::SerializeInfo::getSerializeInfo( readDataPtr, count, &en, &stackName, nullptr, &typeName );
		if( userDataCount == 0 ) {
			tools::debug::printError( "无法从数据当中反序列化对象的成员类型信息" );
			return 0;
		}
		varStack = IVarStack::getInstance( stackName[ 0 ] );
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

		stringDataSize = *( size_t * ) readDataPtr;
		if( cond )
			converEndian( stringDataSize );
		readDataPtr += appendSize;
		utf8.resize( stringDataSize );
		targetPtr = utf8.data( );
		for( utfIndex = 0; utfIndex < stringDataSize; ++utfIndex )
			targetPtr[ utfIndex ] = readDataPtr[ utfIndex ];

		resultSize += stringDataSize + appendSize;
		count = count - stringDataSize - appendSize; // 减去用量
		readDataPtr += stringDataSize;// 增加偏移

		QString string(  QByteArray::fromHex( utf8) );
		std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > sharedPtr( new std_pairt< std_shared_ptr< ITypeObject >, QString > );
		sharedPtr->first = typeObject;
		sharedPtr->second = string;
		ve.emplace_back( sharedPtr );
	}
	*dataStruct = ve;
	return resultSize;
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
