#include "I_IsType.h"

#include "../application/application.h"
I_IsType::I_IsType( ) : aliasTypeNameDataPtr( nullptr ), aliasTypeNameDataCount( 0 ), currentTypeInfo( nullptr ) {
	application = Application::getApplicationInstancePtr( );
	varGenerate = application->getVarGenerate( );
}
void I_IsType::updateNameVectorInfo( const std_vector< QString > &type_name_vector ) {
	aliasTypeName = type_name_vector;
	aliasTypeNameDataPtr = aliasTypeName.data( );
	aliasTypeNameDataCount = aliasTypeName.size( );
}
I_IsType::~I_IsType( ) {
	if( currentTypeInfo )
		delete currentTypeInfo;
	currentTypeInfo = nullptr;
}
