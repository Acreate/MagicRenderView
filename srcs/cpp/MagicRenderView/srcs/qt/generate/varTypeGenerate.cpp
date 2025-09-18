#include "./varTypeGenerate.h"
#include <QDebug>

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
			result->generateCode = index;
			return result;
		}
	vars.emplace_back( result );
	result->generateCode = count;
	return result;
}
