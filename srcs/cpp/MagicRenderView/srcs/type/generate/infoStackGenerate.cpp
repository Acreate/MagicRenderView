#include "infoStackGenerate.h"

#include "../stack/infoStack.h"
InfoStack * InfoStackGenerate::generateInfoStack( const QString &type_name, const std::vector< QString > &alias_type_name_s, const std::function< void *( ) > &create_function, const std::function< void( void * ) > &delete_function ) {
	auto infoStack = new InfoStack( );
	infoStack->aliasTypeNames = alias_type_name_s;
	infoStack->createFunction = create_function;
	infoStack->deleteFunction = delete_function;
	infoStack->typeName = type_name;
	return infoStack;
}
