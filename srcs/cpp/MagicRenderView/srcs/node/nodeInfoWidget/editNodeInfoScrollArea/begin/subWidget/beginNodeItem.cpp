#include "beginNodeItem.h"

#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <qcoreevent.h>

#include <node/node/node.h>

void BeginNodeItem::appendNodeRefItem( Node * item ) {
	size_t count = nodeVector.size( ) + 1;
	QWidget *itemWidget = new QWidget( this );
	QHBoxLayout *itemLayout = new QHBoxLayout( itemWidget );
	QLabel *itemIndex = new QLabel( QString( "[%1]" ).arg( QString::number( count ) ), itemWidget );
	itemLayout->addWidget( itemIndex );
	QString nodeTitile = item->toQString( );
	QLabel *itemName = new QLabel( nodeTitile, itemWidget );
	itemLayout->addWidget( itemName );
	auto addActionLeft = new QAction( QString( "左侧显示 [%1]" ).arg( nodeTitile ), this );
	auto addActionRight = new QAction( QString( "右侧显示 [%1]" ).arg( nodeTitile ), this );
	nodeVector.emplace_back( itemWidget, std::pair { new TCurrentAction( addActionLeft, addActionRight ), item } );
	mainLayout->addWidget( itemWidget, 0, Qt::AlignTop );
	itemWidget->installEventFilter( this );

	connect( addActionLeft, &QAction::triggered, [item, this]( ) {
		emit showNodeInfoWidgetLeft( item );
	} );

	connect( addActionRight, &QAction::triggered, [item, this]( ) {
		emit showNodeInfoWidgetRight( item );
	} );
}
void BeginNodeItem::clearCurrentAction( ) {
	if( currentAction == nullptr )
		return;
	popMenu->removeAction( currentAction->first );
	popMenu->removeAction( currentAction->second );
	currentAction = nullptr;
}
void BeginNodeItem::selectionCurrentAction( ) {
	popMenu->addAction( currentAction->first );
	popMenu->addAction( currentAction->second );
}
BeginNodeItem::BeginNodeItem( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
	popMenu = new QMenu( this );
	currentAction = nullptr;
	nodeArrayCount = 0;
	popMenu->installEventFilter( this );
	isPopMenu = true;
}
BeginNodeItem::~BeginNodeItem( ) {
}
void BeginNodeItem::releaseNodeArrayInfo( ) {
	if( nodeArrayCount != 0 ) {
		clearCurrentAction( );
		for( nodeArrayIndex = 0; nodeArrayIndex < nodeArrayCount; ++nodeArrayIndex ) {
			delete nodeArratPtr[ nodeArrayIndex ].first;
			delete nodeArratPtr[ nodeArrayIndex ].second.first->first;
			delete nodeArratPtr[ nodeArrayIndex ].second.first->second;
			delete nodeArratPtr[ nodeArrayIndex ].second.first;
		}
		nodeVector.clear( );
		nodeArrayCount = 0;
	}
}
void BeginNodeItem::setNodeRefVector( const std::vector< Node * > &node_ref_link_infos ) {

	releaseNodeArrayInfo( );
	auto count = node_ref_link_infos.size( );
	if( count == 0 )
		return;
	auto NodeArrayPtr = node_ref_link_infos.data( );
	for( size_t index = 0; index < count; ++index )
		appendNodeRefItem( NodeArrayPtr[ index ] );
	nodeArrayCount = nodeVector.size( );
	nodeArratPtr = nodeVector.data( );
}
void BeginNodeItem::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.setPen( itemPen );
	int autoWidth = itemPen.width( );
	auto subWidth = autoWidth / 2;
	painter.drawRect( subWidth, subWidth, width( ) - autoWidth, height( ) - autoWidth );
}
void BeginNodeItem::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );

	if( isPopMenu && event->button( ) == Qt::RightButton ) {
		auto pos = event->pos( );
		for( nodeArrayIndex = 0; nodeArrayIndex < nodeArrayCount; ++nodeArrayIndex )
			if( nodeArratPtr[ nodeArrayIndex ].first->geometry( ).contains( pos ) ) {
				clearCurrentAction( );
				currentAction = nodeArratPtr[ nodeArrayIndex ].second.first;
				selectionCurrentAction( );
				popMenu->popup( QCursor::pos( ) );
				break;
			}
	}
}
bool BeginNodeItem::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter = QWidget::eventFilter( watched, event );
	QEvent::Type type = event->type( );

	switch( type ) {
		case QEvent::Paint :
			for( nodeArrayIndex = 0; nodeArrayIndex < nodeArrayCount; ++nodeArrayIndex )
				if( nodeArratPtr[ nodeArrayIndex ].first == watched ) {
					auto widget = nodeArratPtr[ nodeArrayIndex ].first;
					QPainter painter( widget );
					painter.setPen( subItemPen );
					int autoWidth = subItemPen.width( );
					auto subWidth = autoWidth / 2;
					painter.drawRect( subWidth, subWidth, widget->width( ) - autoWidth, widget->height( ) - autoWidth );
					break;
				}
			break;
		case QEvent::Hide :
			if( watched == popMenu )
				clearCurrentAction( );
			break;
	}
	return eventFilter;
}
void BeginNodeItem::hideEvent( QHideEvent *event ) {
	QWidget::hideEvent( event );
	releaseNodeArrayInfo( );
}
