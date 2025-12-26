#include "editorNodeMenuStack.h"

#include "../../menu/edit/normalNodeEditorPropertyMenu.h"
EditorNodeMenuStack::EditorNodeMenuStack( QObject *parent ) : QObject( parent ) { }
NormalNodeEditorPropertyMenu * EditorNodeMenuStack::createNormalNodeEditorPropertyMenu( const QString &menu_type_name ) {
	size_t index;
	for( index = 0; index < editorCount; ++index )
		if( editorArrayPtr[ index ].second.first == menu_type_name )
			return editorArrayPtr[ index ].first( );
	QString *stringArray;
	size_t stringCount;
	size_t aliasIndex;
	for( index = 0; index < editorCount; ++index )
		for( stringArray = editorArrayPtr[ index ].second.second.data( ), stringCount = editorArrayPtr[ index ].second.second.size( ),
			aliasIndex = 0; aliasIndex < stringCount; ++aliasIndex )
			if( stringArray[ aliasIndex ] == menu_type_name )
				return editorArrayPtr[ index ].first( );
	return nullptr;
}
#define editorMenuVector_emplace_back( type_, type_name , ...) \
	editorMenuVector.emplace_back([] ( ) ->NormalNodeEditorPropertyMenu * { \
	NormalNodeEditorPropertyMenu *normalNodeEditorPropertyMenu = new type_(  );\
		if( normalNodeEditorPropertyMenu->initNormalNodeEditorPropertyMenu( ) )\
			return normalNodeEditorPropertyMenu;\
		delete normalNodeEditorPropertyMenu;\
		return nullptr;\
	} , std::pair(type_name, std::vector<QString>{#type_, __VA_ARGS__}))
bool EditorNodeMenuStack::initStack( ) {
	editorMenuVector_emplace_back( NormalNodeEditorPropertyMenu, tr( "常规" ) );

	editorCount = editorMenuVector.size( );
	editorArrayPtr = editorMenuVector.data( );
	return editorCount != 0;
}
