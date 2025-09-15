#include "./writeFile.h"

Imp_StaticMetaInfo( WriteFile, QObject::tr( "WriteFile" ), QObject::tr( "disk" ) )
WriteFile::WriteFile( NodeItem_ParentPtr_Type *parent ) : NodeItem( parent ) {
	nodeTitleName = getMetaObjectName( );
}
