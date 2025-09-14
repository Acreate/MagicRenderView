#include "./readFileBit.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

Imp_StaticMetaInfo( ReadFileBit, QObject::tr( "ReadFileBit" ), QObject::tr( "inputs" ) )
ReadFileBit::ReadFileBit( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
}
