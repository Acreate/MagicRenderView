#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) )
void NodeInputPort::updateProtLayout( ) {
	Application *applicationInstancePtr = Application::getApplicationInstancePtr( );
	auto font = applicationInstancePtr->getFont( );
	auto fontMetrics = QFontMetrics( font );
	QRect boundingRect = fontMetrics.boundingRect( title );
	int width = boundingRect.width( ) + boundingRect.x( );
	int drawHeight = fontMetrics.leading( );
	int fontHeight = fontMetrics.height( ) + drawHeight;
	drawHeight = fontHeight - fontMetrics.descent( ) - drawHeight;
	QImage ico = QImage( ":/ico/info_node.png" ).scaledToHeight( fontHeight );
	int icoWidth = ico.width( );
	int imageWidth = width + icoWidth;
	nodePortRender = nodePortRender.scaled( imageWidth, fontHeight );
	QPainter painter( &nodePortRender );
	painter.setFont( font );
	painter.drawImage( 0, 0, ico );
	painter.drawText( icoWidth, drawHeight, title );
	painter.end( );
	nodeSize = QSize( imageWidth, fontHeight );
	nodePortRender.save( "./NodeInputPort.png" );
}
