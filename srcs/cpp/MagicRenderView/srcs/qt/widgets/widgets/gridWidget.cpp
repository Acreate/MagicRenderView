#include "./gridWidget.h"

#include <QMenuBar>
#include <QMouseEvent>
#include <QScrollArea>
#include <qgridlayout.h>

#include "../../nodes/nodeGeneraterItems/INodeGeneraterItem.h"

void GridWidget::updateLayout( ) {
	if( mainLayout )
		delete mainLayout;

	mainLayout = new QGridLayout( mainContentWidget );
	std::sort( nodeGeneraterItems.begin( ), nodeGeneraterItems.end( ), [] ( const std::shared_ptr< INodeGeneraterItem > &item ) {
		return item->sortCode( );
	} );
	int currentRowCount = 0;
	int currentColumnCount = 0;

	for( auto item : nodeGeneraterItems ) {
		mainLayout->addWidget( item.second, currentRowCount, currentColumnCount );
		++currentRowCount;
		if( currentColumnCount < columnCount )
			continue;
		currentColumnCount = 0;
		++currentRowCount;
	}
}
void GridWidget::removeItem( const INodeGeneraterItem *node_generater_item ) {
	auto iterator = nodeGeneraterItems.begin( );
	auto end = nodeGeneraterItems.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->first.get( ) == node_generater_item ) {
			delete iterator->second;
			nodeGeneraterItems.erase( iterator );
			break;
		}
	if( iterator != end )
		updateLayout( );
}
GridWidget::GridWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {

	auto currentWidgetLayout = new QVBoxLayout( this );
	currentWidgetLayout->setSpacing( 0 );
	currentWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	auto menuBar = currentWidgetLayout->menuBar( );
	if( menuBar == nullptr ) {
		menuBar = new QMenuBar( this );
		currentWidgetLayout->setMenuBar( menuBar );
		menuBar->addAction( "数量" );
	}
	QScrollArea *scrollArea = new QScrollArea( this );
	scrollArea->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
	currentWidgetLayout->addWidget( scrollArea );
	scrollArea->setWidgetResizable( true );

	mainContentWidget = new QWidget( scrollArea );
	scrollArea->setWidget( mainContentWidget );
	mainContentWidget->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
	mainLayout = new QGridLayout( mainContentWidget );
	columnCount = 4;
}
bool GridWidget::addNode( const IFunctionDeclaration &function_declaration ) {
	if( function_declaration.isIsValid( ) == false )
		return false;
	std::shared_ptr< INodeGeneraterItem > nodeGeneraterItem( new INodeGeneraterItem( function_declaration ) );
	QWidget *listNodeWidget = nodeGeneraterItem->createListNodeWidget( );
	if( listNodeWidget == nullptr )
		return false;
	nodeGeneraterItems.emplace_back( nodeGeneraterItem, listNodeWidget );
	mainLayout->setParent( mainContentWidget );
	updateLayout( );
	return true;
}
void GridWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( selectItem )
		emit dragNode( selectItem );
}
void GridWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	auto point = event->pos( );
	for( auto item : nodeGeneraterItems )
		if( item.second->geometry( ).contains( point ) ) {
			selectItem = item.first;
			emit selectNode( selectItem );
			break;
		}
}
void GridWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	selectItem = nullptr;
}
void GridWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
