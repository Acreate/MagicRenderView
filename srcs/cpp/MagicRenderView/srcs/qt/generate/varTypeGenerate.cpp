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
size_t VarTypeGenerate::toBin( const VarType *obj_ptr, std_vector< uint8_t > &result_bin_vector ) {
	result_bin_vector = obj_ptr->toBin( );
	return result_bin_vector.size( );
}
VarType * VarTypeGenerate::toObj( size_t &reseult_use_count, const uint8_t *result_bin_data, const size_t &result_bin_count ) {
	// 成员类型信息

	size_t sizeTypeUse = sizeof( size_t );
	size_t needCount = *( size_t * ) result_bin_data;
	size_t maxSize = result_bin_count - sizeTypeUse;
	if( needCount > maxSize )
		return nullptr;
	auto orgPtr = result_bin_data;
	result_bin_data += sizeTypeUse;
	needCount = *( size_t * ) result_bin_data;
	QString meta;
	BinGenerate::getMetaInfo( &meta, result_bin_data, needCount );
	VarType *craeteVarType = VarTypeGenerate::craeteVarType( meta, nullptr );
	if( craeteVarType == nullptr )
		return nullptr;
	reseult_use_count = craeteVarType->loadBin( orgPtr, result_bin_count );
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
