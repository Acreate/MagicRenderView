#include "./readFileImage.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

#include "../../protInputImplementations/inputFilePath.h"

#include "../../protOutputImplementations/outString.h"

Imp_StaticMetaInfo( ReadFileImage, QObject::tr( "ReadFileImage" ) )
ReadFileImage::ReadFileImage( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
	appendProtInputItemWidget( new InputFilePath( ) );
	appendProtOutputItemWidget( new OutString( ) );
}
