#include "./readFileTxt.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

Imp_StaticMetaInfo( ReadFileTxt, QObject::tr( "ReadFileTxt" ), QObject::tr( "inputs" ) )
ReadFileTxt::ReadFileTxt( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
}
