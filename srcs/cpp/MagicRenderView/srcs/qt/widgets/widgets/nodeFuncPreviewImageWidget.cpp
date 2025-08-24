#include "./nodeFuncPreviewImageWidget.h"

#include <qboxlayout.h>

#include "../../functionDeclaration/IFunctionDeclaration.h"
NodeFuncPreviewImageWidget::NodeFuncPreviewImageWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	auto mainLayout = new QVBoxLayout( this );
	label = new QLabel( this );
	mainLayout->addWidget( label );
	hide( );
}
bool NodeFuncPreviewImageWidget::setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration ) {
	auto element = function_declaration.get( );
	auto image = element->getImage( );
	QPixmap fromImage;
	if( image == nullptr || image->isNull( ) )
		fromImage = QPixmap::fromImage( QImage( ":/function/normal.png" ) );
	else
		fromImage = QPixmap::fromImage( *image );
	if( fromImage.isNull( ) )
		return false;
	label->setPixmap( fromImage );
	functionDeclaration = function_declaration;
	return true;
}
