#include "./readFile.h"

Imp_StaticMetaInfo( ReadFile, QObject::tr( "ReadFile" ), QObject::tr( "disk" ) )
ReadFile::ReadFile( NodeItem_ParentPtr_Type *parent ) : NodeItem( parent ) {
	nodeTitleName = getMetaObjectName( );

}
