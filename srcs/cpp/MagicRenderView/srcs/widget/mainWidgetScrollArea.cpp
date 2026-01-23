#include "mainWidgetScrollArea.h"

#include "mainWidget.h"

MainWidgetScrollArea::MainWidgetScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	mainWidget = new MainWidget( this );

	setWidget( mainWidget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
void MainWidgetScrollArea::scrollToTargetPos( QWidget *reference_widget, const QPoint &left_top_pos, const QPoint &right_bottom_pos ) {
	if( reference_widget == nullptr )
		return;

	// 匹配最新大小
	auto minWidth = mainWidget->minimumWidth( );
	auto minHeith = mainWidget->minimumHeight( );
	auto currentWidth = right_bottom_pos.x( );
	auto currentHeight = right_bottom_pos.y( );
	// 最新的宽度
	auto newWidth = minWidth;
	// 最新的高度
	auto newHeight = minHeith;
	if( minWidth < currentWidth )
		newWidth = currentWidth;
	if( minHeith < currentHeight )
		newHeight = currentHeight;
	if( minWidth != newWidth || minHeith != newHeight )
		mainWidget->setMinimumSize( newWidth, newHeight );
	// 转换到全局坐标
	auto globalLeftTopPos = mainWidget->mapToGlobal( left_top_pos );
	auto globalRightBottomPos = mainWidget->mapToGlobal( right_bottom_pos );
	// 转换到参考窗口坐标
	auto windowLeftTopPos = reference_widget->mapFromGlobal( globalLeftTopPos );
	// 超出窗口的左上角
	if( windowLeftTopPos.x( ) < 0 || windowLeftTopPos.y( ) < 0 ) {
		ensureVisible( left_top_pos.x( ), left_top_pos.y( ), 10, 10 );
		return;
	}
	// 参考窗口进行偏移
	auto refWidgetRect = reference_widget->rect( );
	auto bottomRight = refWidgetRect.bottomRight( );
	auto windowRightBottomPos = reference_widget->mapFromGlobal( globalRightBottomPos );
	if( windowRightBottomPos.x( ) > bottomRight.x( ) || windowRightBottomPos.y( ) > bottomRight.y( ) ) {
		ensureVisible( right_bottom_pos.x( ), right_bottom_pos.y( ), 10, 10 );
	}
}
void MainWidgetScrollArea::scrollToTargetPos( QWidget *reference_widget, const QPoint &left_top_pos, const QSize &right_boom_size ) {
	scrollToTargetPos( reference_widget, left_top_pos, QPoint( left_top_pos.x( ) + right_boom_size.width( ), left_top_pos.y( ) + right_boom_size.height( ) ) );
}
