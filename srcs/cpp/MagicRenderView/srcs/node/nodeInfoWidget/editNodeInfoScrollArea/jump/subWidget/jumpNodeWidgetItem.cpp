#include "jumpNodeWidgetItem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>

#include "../../../../nodeInfo/nodeRefLinkInfo.h"
void JumpNodeWidgetItem::appendNodeRefItem( NodeRefLinkInfo *item ) {
	size_t count = nodeVector.size( ) + 1;
	QWidget *itemWidget = new QWidget( this );
	QHBoxLayout *itemLayout = new QHBoxLayout( itemWidget );
	QLabel *itemIndex = new QLabel( QString( "[%1]" ).arg( QString::number( count ) ), itemWidget );
	itemLayout->addWidget( itemIndex );
	QString nodeTitile = item->getCurrentNode( )->toQString( );
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
void JumpNodeWidgetItem::clearCurrentAction( ) {
	if( currentAction == nullptr )
		return;
	popMenu->removeAction( currentAction->first );
	popMenu->removeAction( currentAction->second );
	currentAction = nullptr;
}
void JumpNodeWidgetItem::selectionCurrentAction( ) {
	popMenu->addAction( currentAction->first );
	popMenu->addAction( currentAction->second );
}
void JumpNodeWidgetItem::releaseNodeArrayInfo( ) {
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
JumpNodeWidgetItem::JumpNodeWidgetItem( QWidget *parent ) {
	mainLayout = new QVBoxLayout( this );
	popMenu = new QMenu( this );
	currentAction = nullptr;
	nodeArrayCount = 0;
	popMenu->installEventFilter( this );
	isPopMenu = true;
}
JumpNodeWidgetItem::~JumpNodeWidgetItem( ) {
	releaseNodeArrayInfo( );
}
void JumpNodeWidgetItem::setNodeRefVector( const std::vector< NodeRefLinkInfo * > &node_ref_link_infos ) {
	releaseNodeArrayInfo( );
	auto count = node_ref_link_infos.size( );
	if( count == 0 )
		return;
	auto nodeRefLinkInfoArrayPtr = node_ref_link_infos.data( );
	for( size_t index = 0; index < count; ++index )
		appendNodeRefItem( nodeRefLinkInfoArrayPtr[ index ] );
	nodeArrayCount = nodeVector.size( );
	nodeArratPtr = nodeVector.data( );
}
void JumpNodeWidgetItem::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.setPen( itemPen );
	int autoWidth = itemPen.width( );
	auto subWidth = autoWidth / 2;
	painter.drawRect( subWidth, subWidth, width( ) - autoWidth, height( ) - autoWidth );
}
void JumpNodeWidgetItem::mouseReleaseEvent( QMouseEvent *event ) {
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
bool JumpNodeWidgetItem::eventFilter( QObject *watched, QEvent *event ) {
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
void JumpNodeWidgetItem::hideEvent( QHideEvent *event ) {
	QWidget::hideEvent( event );
	releaseNodeArrayInfo( );
}
