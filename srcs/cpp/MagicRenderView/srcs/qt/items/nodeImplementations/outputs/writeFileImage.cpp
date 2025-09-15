#include "./writeFileImage.h"

#include <QLabel>
#include <qdir.h>
#include <qfileinfo.h>

#include <qt/varType/varType.h>

#include <qt/items/protInputImplementations/inputFilePath.h>

Imp_StaticMetaInfo( WriteFileImage, QObject::tr( "WriteFileImage" ), QObject::tr( "outputs" ) )
WriteFileImage::WriteFileImage( QWidget *parent ) : NodeItemWidget( parent ) {
	setNodeTitle( getStaticMetaObjectName( ) );
	
	var = VarType::templateVarType< QString >( this );
	appendProtInputItemWidget( new InputFilePath( this, var ) );
	applyAdviseSizeToNodeItemWidget( );
}
