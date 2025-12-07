#include "beginNodeItem.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

#include "../../../../nodeInfo/nodeRefLinkInfo.h"
void BeginNodeItem::appendNodeRefItem( NodeRefLinkInfo *item ) {
	size_t count = nodeVector.size( ) + 1;
	QWidget *itemWidget = new QWidget( this );
	QHBoxLayout *itemLayout = new QHBoxLayout( itemWidget );
	QLabel *itemIndex = new QLabel( QString( "[%1]" ).arg( QString::number( count ) ), itemWidget );
	itemLayout->addWidget( itemIndex );
	QLabel *itemName = new QLabel( QString( item->getCurrentNode( )->toQString( ) ), itemWidget );
	itemLayout->addWidget( itemName );
	nodeVector.emplace_back( itemWidget, item );
	mainLayout->addWidget( itemWidget );
	setPenColor = Qt::black;
}
BeginNodeItem::BeginNodeItem( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
}
void BeginNodeItem::setNodeRefVector( const std::vector< NodeRefLinkInfo * > &node_ref_link_infos ) {
	size_t count = nodeVector.size( );
	size_t index;

	if( count != 0 ) {
		auto data = nodeVector.data( );
		for( index = 0; index < count; ++index )
			delete data[ index ].first;
		nodeVector.clear( );
	}
	count = node_ref_link_infos.size( );
	auto nodeRefLinkInfoArrayPtr = node_ref_link_infos.data( );
	for( index = 0; index < count; ++index )
		appendNodeRefItem( nodeRefLinkInfoArrayPtr[ index ] );
}
void BeginNodeItem::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto pen = painter.pen( );
	pen.setWidth( 4 );
	pen.setColor( setPenColor );
	painter.drawRect( 0, 0, width( ) - 4, height( ) - 4 );
}
