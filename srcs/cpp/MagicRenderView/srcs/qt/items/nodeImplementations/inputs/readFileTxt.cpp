#include "./readFileTxt.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

Imp_StaticMetaInfo( ReadFileTxt, QObject::tr( "ReadFileTxt" ) )
ReadFileTxt::ReadFileTxt( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
}
