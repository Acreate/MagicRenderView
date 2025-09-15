#include "./nodeOutputPort.h"

#include <QPainter>

#include <qt/application/application.h>

Imp_StaticMetaInfo( NodeOutputPort, QObject::tr( "NodeOutputPort" ), QObject::tr( "outputProt" ) )
void NodeOutputPort::updateProtLayout( ) {
	Application *applicationInstancePtr = Application::getApplicationInstancePtr( );
	auto font = applicationInstancePtr->getFont( );
	auto fontMetrics = QFontMetrics( font );
	QRect boundingRect = fontMetrics.boundingRect( title );
	int width = boundingRect.width( ) + boundingRect.x( );
	int drawHeight = fontMetrics.leading( );
	int fontHeight = fontMetrics.height( ) + drawHeight;
	drawHeight = fontHeight - fontMetrics.descent( ) - drawHeight;
	QImage ico = QImage( ":/ico/info_node.png" ).scaledToHeight( fontHeight );
	int imageWidth = width + ico.width( );
	nodePortRender = nodePortRender.scaled( imageWidth, fontHeight );
	QPainter painter( &nodePortRender );
	painter.setFont( font );
	painter.drawImage( width, 0, ico );
	painter.drawText( 0, drawHeight, title );
	painter.end( );
	nodeSize = QSize( imageWidth, fontHeight );
}
