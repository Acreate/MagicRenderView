#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) )
void NodeInputPort::updateProtLayout( ) {
	Application *applicationInstancePtr = Application::getApplicationInstancePtr( );
	auto font = applicationInstancePtr->getFont( );
	auto fontMetrics = QFontMetrics( font );
	auto advance = fontMetrics.boundingRect( title );
	int width = advance.width( ) + advance.y( );
	int drawHeight = fontMetrics.leading( );
	int fontHeight = fontMetrics.height( ) + drawHeight;
	drawHeight = fontHeight - fontMetrics.descent( ) - drawHeight;
	QImage ico = QImage( ":/ico/info_node.png" ).scaledToHeight( fontHeight );
	int imageWidth = width + ico.width( );
	nodePortRender = nodePortRender.scaled( imageWidth, fontHeight );
	QPainter painter( &nodePortRender );
	painter.setFont( font );
	painter.drawImage( 0, 0, ico );
	painter.drawText( ico.width( ), drawHeight, title );
	painter.end( );
	nodeSize = QSize( imageWidth, fontHeight );
}
