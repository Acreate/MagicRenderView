#include "./writeFileImage.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

#include "../../protInputImplementations/inputFilePath.h"

Imp_StaticMetaInfo( WriteFileImage, QObject::tr( "WriteFileImage" ) )
WriteFileImage::WriteFileImage( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
	appendProtInputItemWidget( new InputFilePath( ) );
}
