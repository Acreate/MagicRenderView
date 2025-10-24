#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollBar>
#include <qboxlayout.h>

#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>

#include "GenerateListItemWidget.h"
#include "GenerateListWidget.h"
#include "generateListScrollArea.h"
bool GenerateListWidget::insterToLayout( GenerateListItemWidget *new_list_item_widget ) {
	int count = mainLayout->count( ) - 1;
	size_t index = 1;
	for( ; index < count; ++index ) {
		QLayoutItem *layoutItem = mainLayout->itemAt( index );
		if( layoutItem->isEmpty( ) )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		auto generateListItemWidget = qobject_cast< GenerateListItemWidget * >( widget );
		if( generateListItemWidget == nullptr )
			continue;
		if( generateListItemWidget->y( ) < new_list_item_widget->y( ) )
			continue;
		mainLayout->insertWidget( index, new_list_item_widget );
		return true;
	}
	mainLayout->insertWidget( index, new_list_item_widget );
	return true;

}
bool GenerateListWidget::addItem( GenerateListItemWidget *new_list_item_widget ) {
	size_t count = generateListItemWidgets.size( );
	auto data = generateListItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == new_list_item_widget )
			return true;
		else if( data[ index ] == nullptr ) {
			data[ index ] = new_list_item_widget;
			return true;
		}
	generateListItemWidgets.emplace_back( new_list_item_widget );
	return true;
}
bool GenerateListWidget::removeItem( GenerateListItemWidget *new_list_item_widget ) {
	size_t count = generateListItemWidgets.size( );
	auto data = generateListItemWidgets.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == new_list_item_widget ) {
			++index;
			for( ; index < count; ++index )
				if( data[ index ] == nullptr )
					break;
				else
					data[ index - 1 ] = data[ index ];
			if( index == count )
				data[ index - 1 ] = nullptr;
			return true;
		}
	return false;
}
void GenerateListWidget::fromComponentAddItemInfo( ) {
	using t_current_type = int64_t;
	I_Type *type_info = new I_Type( typeid( t_current_type ), sizeof( typeid( t_current_type ) ), [] ( void *p ) {
		delete ( t_current_type * ) p;
		return true;
	}, [] {
		return new t_current_type( 0 );
	} );
	std_shared_ptr< I_Var > var( new I_Var( type_info ) );

	auto newListItemWidget = new GenerateListItemWidget( var, this );
	mainLayout->insertWidget( mainLayout->count( ) - 1, newListItemWidget );
	addItem( newListItemWidget );
	connect( newListItemWidget, &GenerateListItemWidget::releaseThisPtr, this, &GenerateListWidget::removeItem );
}

GenerateListItemWidget * GenerateListWidget::getPointWidget( const QPoint &pos ) const {
	size_t count = generateListItemWidgets.size( );
	auto data = generateListItemWidgets.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->geometry( ).contains( pos ) )
			return data[ index ];
		else if( data[ index ] == nullptr )
			break;
	return nullptr;
}
GenerateListWidget::GenerateListWidget( GenerateListScrollArea *parent ) : QWidget( parent ) {
	isReleaseWidget = false;
	selectWidget = nullptr;
	mainLayout = new QVBoxLayout( this );
	addItemBtn = new QPushButton( tr( "添加" ), this );
	connect( addItemBtn, &QPushButton::clicked, this, &GenerateListWidget::fromComponentAddItemInfo );
	mainLayout->addWidget( addItemBtn, 0, Qt::AlignHCenter | Qt::AlignTop );
	mainLayout->addSpacerItem( new QSpacerItem( 10, 10, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding ) );
	generateListScrollArea = parent;
	generateListScrollArea->setWidget( this );
	generateListScrollArea->setWidgetResizable( true );
	generateListScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	generateListScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	horizontalScrollBar = generateListScrollArea->horizontalScrollBar( );
	verticalScrollBar = generateListScrollArea->verticalScrollBar( );
}
GenerateListWidget::~GenerateListWidget( ) {
	delete mainLayout;
	delete addItemBtn;
	auto clone = generateListItemWidgets;
	generateListItemWidgets.clear( );
	size_t count = clone.size( );
	auto data = clone.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else
			delete data[ index ];
}
std_vector< std_shared_ptr< I_Var > > GenerateListWidget::getItemVarVector( ) const {
	std_vector< std_shared_ptr< I_Var > > result;
	size_t count = generateListItemWidgets.size( );
	if( count == 0 )
		return result;
	auto data = generateListItemWidgets.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
		else
			result.emplace_back( data[ index ]->getVar( ) );
	return result;
}
std_shared_ptr< I_Var > GenerateListWidget::getItemIndexVar( const size_t &index ) const {
	std_vector< std_shared_ptr< I_Var > > result;
	size_t count = generateListItemWidgets.size( );
	if( count <= index )
		return nullptr;
	auto data = generateListItemWidgets.data( );
	if( data[ index ] == nullptr )
		return nullptr;
	return data[ index ]->getVar( );
}
void GenerateListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
}
void GenerateListWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
}
void GenerateListWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( selectWidget ) {
		if( isReleaseWidget ) {
			mainLayout->removeWidget( selectWidget );
			isReleaseWidget = false;
		}
		selectWidget->move( 0, event->pos( ).y( ) );
	}
}
void GenerateListWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	selectWidget = getPointWidget( event->pos( ) );
	if( selectWidget )
		isReleaseWidget = true;
}
void GenerateListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	if( selectWidget ) {
		selectWidget->move( 0, event->pos( ).y( ) );
		insterToLayout( selectWidget );
	}
	selectWidget = nullptr;
}
