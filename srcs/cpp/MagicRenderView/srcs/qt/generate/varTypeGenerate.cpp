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
size_t VarTypeGenerate::genVarTypeCode( const VarType *var_type_ptr ) {
	size_t count = vars.size( );
	auto data = vars.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == var_type_ptr )
			return index + 1;
	return 0;
}
VarType * VarTypeGenerate::genVarTypObjPtr( const size_t &var_type_generate_code ) {
	size_t count = vars.size( );
	auto data = vars.data( );
	if( var_type_generate_code < count )
		return data[ var_type_generate_code ]; // 优先返回
	// 次要返回
	for( size_t index = 0; index < count; ++index )
		if( data[ index ]->generateCode == var_type_generate_code )
			return data[ index ];
	// 找不到返回
	return nullptr;
}
