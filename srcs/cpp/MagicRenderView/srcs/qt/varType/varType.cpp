#include "./varType.h"

#include "../generate/varTypeGenerate.h"

VarType::VarType( QObject *parent ) : QObject( parent ) {
	unityTypeName = typeid( *this ).name( );
}
std_vector< uint8_t > VarType::toBin( ) const {
	std_vector< uint8_t > resultBuff;
	if( unitySer == nullptr )
		return resultBuff;

	// 成员类型信息
	std_vector< uint8_t > unityTypeNameVector;
	BinGenerate::toVectorUInt8Data( unityTypeName, unityTypeNameVector );
	size_t unityTypeNameVectorCount = unityTypeNameVector.size( );
	std_vector< uint8_t > unityTypeNameVectorCountVector;
	BinGenerate::toVectorUInt8Data( unityTypeNameVectorCount, unityTypeNameVectorCountVector );
	resultBuff.append_range( unityTypeNameVectorCountVector );
	resultBuff.append_range( unityTypeNameVector );

	size_t serVarCount = varVector.size( );
	std_vector< uint8_t > serVarCountVector;
	BinGenerate::toVectorUInt8Data( serVarCount, serVarCountVector );
	resultBuff.append_range( serVarCountVector );
	auto dataPtr = varVector.data( );
	std_vector< uint8_t > serVarVector;
	for( size_t index = 0; index < serVarCount; ++index )
		if( unitySer( dataPtr[ index ], serVarVector ) != 0 )
			resultBuff.append_range( serVarVector );

	std_vector< uint8_t > result;
	serVarCount = resultBuff.size( );
	BinGenerate::toVectorUInt8Data( serVarCount, serVarCountVector );
	result.append_range( serVarCountVector );
	result.append_range( resultBuff );
	return result;
}
size_t VarType::loadBin( const std_vector< uint8_t > &bin ) {
	if( unitySerRes == nullptr )
		return 0;
	// 反序列化成员
	auto sourcePtr = bin.data( );
	auto sourceCount = bin.size( );
	size_t size_tTypeSize = sizeof( size_t );
	if( sourceCount < size_tTypeSize )
		return 0;
	// 获取需要长度
	size_t needSize = *( size_t * ) sourcePtr;
	size_t modSize = sourceCount - size_tTypeSize;
	if( needSize > modSize )
		return 0;
	auto orgPtr = sourcePtr;
	sourcePtr += size_tTypeSize;
	// 匹配类型信息
	size_t metaSize = *( size_t * ) sourcePtr;
	sourcePtr += size_tTypeSize;
	QString loadMetaInfo;
	BinGenerate::toObj( &loadMetaInfo, sourcePtr, metaSize );
	if( loadMetaInfo != unityTypeName )
		return 0;
	sourcePtr += metaSize;
	// 调到个数
	size_t serVarCount = *( size_t * ) sourcePtr;
	size_t useCount = 0;
	// 释放仓库
	size_t varCount = varVector.size( );
	auto data = varVector.data( );
	size_t index = 0;
	for( ; index < varCount; ++index )
		releaseFunction( data[ index ] );
	varVector.clear( );
	// 偏移到数据
	sourcePtr += size_tTypeSize;
	for( ; index < serVarCount; ++index ) {
		void *serRes = unitySerRes( sourcePtr + useCount, modSize, useCount );
		if( serRes == nullptr )
			break;
		varVector.emplace_back( serRes );
		if( modSize < useCount )
			break;
		modSize -= useCount;
	}

	return sourcePtr - orgPtr;
}
