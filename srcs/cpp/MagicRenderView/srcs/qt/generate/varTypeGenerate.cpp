#include "./varTypeGenerate.h"

std_vector< VarType * > VarTypeGenerate::vars;
std_vector< std_pairt< QString, VarTypeGenerate::generate_function > > VarTypeGenerate::generates;
VarType * VarTypeGenerate::templateVarType( QObject *parent, const QString &type_name ) {
	VarType *result = new VarType( parent );
	result->unityTypeName = type_name;
	QObject::connect( result, &VarType::deleteObjBefore, [] ( VarType *deleteType ) {
		size_t count = vars.size( );
		auto data = vars.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ] == deleteType )
				data[ index ] = nullptr;
	} );
	size_t count = vars.size( );
	auto data = vars.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = result;
			result->generateCode = index + 1;
			if( result->generateCode != 0 )
				return result;
			delete result;
			data[ index ] = nullptr;
			return nullptr;
		}
	vars.emplace_back( result );
	result->generateCode = count + 1;
	if( result->generateCode != 0 )
		return result;
	delete result;
	vars.pop_back( );
	return nullptr;
}
void VarTypeGenerate::cnnectSignal( VarType *sender_obj ) {
	QObject::connect( sender_obj, &VarType::deleteObjBefore, [] ( VarType *remove_obj ) {
		size_t generateNodeItemsCount = vars.size( );
		auto generateNodeitemsPtr = vars.data( );
		size_t generateNodeItemsIndex = 0;
		for( ; generateNodeItemsIndex < generateNodeItemsCount; ++generateNodeItemsIndex )
			if( remove_obj == generateNodeitemsPtr[ generateNodeItemsIndex ] ) {
				generateNodeitemsPtr[ generateNodeItemsIndex ] = nullptr;
				break;
			}

	} );
}
std_vector< uint8_t > VarTypeGenerate::toBin( const VarType *obj_ptr ) {
	std_vector< uint8_t > result;
	if( obj_ptr->unitySer == nullptr )
		return result;

	std_vector< uint8_t > resultBuff;
	// VarType 类型信息
	std_vector< uint8_t > unityTypeNameVector;
	QString typeName = typeid( VarType ).name( );
	BinGenerate::toBin( typeName, unityTypeNameVector );
	resultBuff.append_range( unityTypeNameVector );
	// VarType 成员类型信息
	BinGenerate::toBin( obj_ptr->unityTypeName, unityTypeNameVector );
	resultBuff.append_range( unityTypeNameVector );
	// VarType 生成代码
	BinGenerate::toBin( obj_ptr->generateCode, unityTypeNameVector );
	resultBuff.append_range( unityTypeNameVector );
	// VarType 成员个数
	size_t unityTypeNameVectorCount = obj_ptr->varVector.size( );
	BinGenerate::toBin( unityTypeNameVectorCount, unityTypeNameVector );
	resultBuff.append_range( unityTypeNameVector );
	// VarType 成员
	auto dataPtr = obj_ptr->varVector.data( );
	std_vector< uint8_t > serVarVector;
	for( size_t index = 0; index < unityTypeNameVectorCount; ++index )
		if( obj_ptr->unitySer( dataPtr[ index ], serVarVector ) != 0 )
			resultBuff.append_range( serVarVector );
	// 整体大小
	BinGenerate::toBin( resultBuff.size( ), unityTypeNameVector );
	result.append_range( unityTypeNameVector );
	result.append_range( resultBuff );
	return result;
}
VarType * VarTypeGenerate::toObj( size_t &reseult_use_count, const uint8_t *source_bin_data_ptr, const size_t &source_bin_data_count ) {
	// 整体大小
	size_t needCount;
	auto offsetPtr = source_bin_data_ptr + BinGenerate::toObj( &needCount, source_bin_data_ptr, source_bin_data_count );
	size_t maxSize = source_bin_data_count - ( offsetPtr - source_bin_data_ptr );
	if( needCount > maxSize )
		return nullptr;
	// VarType 类型信息
	maxSize = source_bin_data_count - ( offsetPtr - source_bin_data_ptr );
	QString meta;
	offsetPtr += BinGenerate::toObj( &meta, offsetPtr, maxSize );
	QString currentTypeName = typeid( VarType ).name( );
	if( meta != currentTypeName )
		return nullptr;
	// VarType 成员类型信息
	maxSize = source_bin_data_count - ( offsetPtr - source_bin_data_ptr );
	offsetPtr += BinGenerate::toObj( &meta, offsetPtr, maxSize );
	// 根据成员信息进行类创建
	VarType *craeteVarType = VarTypeGenerate::craeteVarType( meta, nullptr );
	if( craeteVarType == nullptr )
		return nullptr;

	// 检测创建的类是否存在必须的函数调用
	if( craeteVarType->unitySerRes == nullptr || craeteVarType->releaseFunction == nullptr )
		return 0;
	// VarType 生成代码
	maxSize = source_bin_data_count - ( offsetPtr - source_bin_data_ptr );
	offsetPtr += BinGenerate::toObj( &craeteVarType->generateCode, offsetPtr, maxSize );
	// VarType 成员个数
	size_t needSize;
	maxSize = source_bin_data_count - ( offsetPtr - source_bin_data_ptr );
	offsetPtr += BinGenerate::toObj( &needSize, offsetPtr, maxSize );
	craeteVarType->varVector.resize( needSize, nullptr );
	// VarType 成员
	auto data = craeteVarType->varVector.data( );
	size_t index = 0;
	size_t useCount = 0;
	for( ; index < needSize; ++index ) {
		maxSize = source_bin_data_count - ( offsetPtr - source_bin_data_ptr );
		void *serRes = craeteVarType->unitySerRes( offsetPtr, maxSize, useCount );
		if( serRes == nullptr ) {
			tools::debug::printError( QString( "无法正确进行反序列化 [%1/%2]" ).arg( index ).arg( needSize ), 2, 9 );
			break;
		}
		data[ index ] = serRes;
		offsetPtr += useCount;
	}

	if( reseult_use_count != 0 )
		return craeteVarType;
	delete craeteVarType;
	return nullptr;
}

VarType * VarTypeGenerate::craeteVarType( const QString &generateTypeName, QObject *parent ) {
	size_t count = generates.size( );
	if( count == 0 )
		return nullptr;
	auto data = generates.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first == generateTypeName ) {
			auto &function = data[ index ].second;
			VarType *varType = function( parent, generateTypeName );
			if( varType == nullptr )
				return nullptr;
			VarTypeGenerate::cnnectSignal( varType );
			return varType;
		}
	return nullptr;
}
size_t VarTypeGenerate::genVarTypeCode( const VarType *var_type_ptr ) {
	size_t count = vars.size( );
	auto data = vars.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == var_type_ptr )
			return index + 1;
	return 0;
}
VarType * VarTypeGenerate::fromGenerateCodeGetVarTypObjPtr( const size_t &var_type_generate_code ) {
	size_t count = vars.size( );
	auto data = vars.data( );
	size_t codeInde = var_type_generate_code - 1;
	if( codeInde < count )
		return data[ codeInde ]; // 优先返回
	// 次要返回
	for( size_t index = 0; index < count; ++index )
		if( data[ index ]->generateCode == var_type_generate_code )
			return data[ index ];
	// 找不到返回
	return nullptr;
}
