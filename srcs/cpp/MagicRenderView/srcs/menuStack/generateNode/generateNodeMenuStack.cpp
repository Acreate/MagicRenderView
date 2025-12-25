#include "generateNodeMenuStack.h"

#include "../../menu/generateNode/normalGenerateNodeMenu.h"

#define generateMenuVector_emplace_back( type_, type_name , ...) \
	generateMenuVector.emplace_back([] ( ) ->NormalGenerateNodeMenu * { \
	NormalGenerateNodeMenu *normalGenerateNodeMenu = new type_(  );\
		if( normalGenerateNodeMenu->initNormalGenerateNodeMenu( ) )\
			return normalGenerateNodeMenu;\
		delete normalGenerateNodeMenu;\
		return nullptr;\
	} , std::pair(type_name, std::vector<QString>{#type_, __VA_ARGS__}))
GenerateNodeMenuStack::GenerateNodeMenuStack( ) {
	generateArrayPtr = nullptr;
	generateCount = 0;
}
bool GenerateNodeMenuStack::initStack( ) {
	generateMenuVector_emplace_back( NormalGenerateNodeMenu, tr( "常规" ) );

	generateCount = generateMenuVector.size( );
	generateArrayPtr = generateMenuVector.data( );
	return generateCount != 0;
}
NormalGenerateNodeMenu * GenerateNodeMenuStack::createGenerateNodeMenu( const QString &menu_name ) {
	size_t index;
	for( index = 0; index < generateCount; ++index )
		if( generateArrayPtr[ index ].second.first == menu_name )
			return generateArrayPtr[ index ].first( );
	QString *stringArray;
	size_t stringCount;
	size_t aliasIndex;
	for( index = 0; index < generateCount; ++index )
		for( stringArray = generateArrayPtr[ index ].second.second.data( ), stringCount = generateArrayPtr[ index ].second.second.size( ),
			aliasIndex = 0; aliasIndex < stringCount; ++aliasIndex )
			if( stringArray[ aliasIndex ] == menu_name )
				return generateArrayPtr[ index ].first( );
	return nullptr;
}
