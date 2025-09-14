#include "./writeFileTxt.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

Imp_StaticMetaInfo( WriteFileTxt, QObject::tr( "WriteFileTxt" ) )
WriteFileTxt::WriteFileTxt( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
}
