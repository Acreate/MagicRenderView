#include "./nodeItem.h"

#include <QPainter>
#include <QPainterPath>

#include <qt/application/application.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/node/prot/outputProt/nodeOutputPort.h>

Imp_StaticMetaInfo( NodeItem, QObject::tr( "NodeItem" ), QObject::tr( "item" ) )
NodeItem::NodeItem( NodeItem_ParentPtr_Type *parent ) : QObject( parent ), inputBuff( QImage( 10, 10, QImage::Format_RGBA8888 ) ), outputBuff( QImage( 10, 10, QImage::Format_RGBA8888 ) ), titleBuff( QImage( 10, 10, QImage::Format_RGBA8888 ) ) {
	nodeTitleName = getMetaObjectName( );
	applicationInstancePtr = Application::getApplicationInstancePtr( );
}
void NodeItem::setNodeTitleName( const NodeItemString_Type &node_title_name ) {
	nodeTitleName = node_title_name;

	auto font = applicationInstancePtr->getFont( );
	QFontMetrics fontMetrics( font );
	auto boundingRect = fontMetrics.boundingRect( nodeTitleName );

	int width = boundingRect.width( ) + boundingRect.x( );
	int drawHeight = fontMetrics.leading( );
	int fontHeight = fontMetrics.height( ) + drawHeight;
	drawHeight = fontHeight - fontMetrics.descent( ) - drawHeight;
	titleBuff = titleBuff.scaled( width, drawHeight );

	titleBuff.fill( 0 );
	QPainter painter( &titleBuff );
	painter.setFont( font );
	painter.drawText( 0, drawHeight, nodeTitleName );
	painter.end( );
}

bool NodeItem::appendInputProt( NodeInputPort *input_prot ) {
	nodeInputProtVector.emplace_back( input_prot );
	return true;
}
bool NodeItem::removeInputProt( NodeInputPort *input_prot ) {
	size_t count = nodeInputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ] == input_prot ) {
			nodeInputProtVector.erase( nodeInputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeItem::appendOutputProt( NodeOutputPort *output_prot ) {

	nodeOutputProtVector.emplace_back( output_prot );
	return true;
}
bool NodeItem::removeOutputProt( NodeOutputPort *output_port ) {

	size_t count = nodeOutputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ] == output_port ) {
			nodeOutputProtVector.erase( nodeOutputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
void NodeItem::updateProtLayout( ) {
	// 获取字体
	auto font = applicationInstancePtr->getFont( );

}
NodeOutputPort * NodeItem::formPosNodeOutputPort( const QPoint &pos ) {

	size_t count = nodeOutputProtVector.size( ), index = 0;
	if( count == 0 )
		return nullptr;
	auto data = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ]->getPos( ) == pos )
			return data[ index ];
	return nullptr;
}
NodeOutputPort * NodeItem::formIndexNodeOutputPort( const size_t &index ) {
	size_t count = nodeOutputProtVector.size( );
	if( count < index )
		return nodeOutputProtVector.data( )[ index ];
	return nullptr;
}
NodeInputPort * NodeItem::formPosNodeInputPort( const QPoint &pos ) {
	size_t count = nodeInputProtVector.size( ), index = 0;
	if( count == 0 )
		return nullptr;
	auto data = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ]->getPos( ) == pos )
			return data[ index ];
	return nullptr;
}
NodeInputPort * NodeItem::formIndexNodeInputPort( const size_t &index ) {
	size_t count = nodeInputProtVector.size( );
	if( count < index )
		return nodeInputProtVector.data( )[ index ];
	return nullptr;
}
