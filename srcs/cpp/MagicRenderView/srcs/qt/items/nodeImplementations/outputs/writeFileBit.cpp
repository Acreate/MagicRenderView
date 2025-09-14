#include "./writeFileBit.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

Imp_StaticMetaInfo( WriteFileBit, QObject::tr( "WriteFileBit" ) )
WriteFileBit::WriteFileBit( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
}
