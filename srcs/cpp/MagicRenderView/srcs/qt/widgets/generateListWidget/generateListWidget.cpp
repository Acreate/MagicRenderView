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

#include "../../tools/tools.h"
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
			emit delVarOverSignal( this, new_list_item_widget, new_list_item_widget->getVarEditorWidget( ) );
			return true;
		}
	return false;
}
void GenerateListWidget::fromComponentAddItemInfo( ) {
	if( varGenerateFunction == nullptr ) {
		tools::debug::printError( QObject::tr( "未配置正确的生成函数，请调用 setVarGenerateFunction" ) );
		return;
	}
	if( varCheckFunction == nullptr ) {
		tools::debug::printError( QObject::tr( "未配置正确的变量值校验函数，请调用 setVarCheckFunction" ) );
		return;
	}
	if( nameCheckFunction == nullptr ) {
		tools::debug::printError( QObject::tr( "未配置正确的变量名称校验函数，请调用 setNameCheckFunction" ) );
		return;
	}
	if( normalVarFunction == nullptr ) {
		tools::debug::printError( QObject::tr( "未配置正确的变量值标准化函数，请调用 setNormalVarFunction" ) );
		return;
	}
	auto var = varGenerateFunction( );
	if( var == nullptr ) {
		tools::debug::printError( QObject::tr( "变量生成失败，请检查变量生成函数，请调用 setVarCheckFunction 重新配置有效生成函数" ) );
		return;
	}
	auto newListItemWidget = new GenerateListItemWidget( var, this );
	newListItemWidget->setVarCheckFunction( varCheckFunction );
	newListItemWidget->setNameCheckFunction( nameCheckFunction );
	newListItemWidget->setNormalVarFunction( normalVarFunction );
	mainLayout->insertWidget( mainLayout->count( ) - 1, newListItemWidget );
	addItem( newListItemWidget );
	connect( newListItemWidget, &GenerateListItemWidget::releaseThisPtr, this, &GenerateListWidget::removeItem );
	connect( newListItemWidget, &GenerateListItemWidget::changeVarOverSignal, [this] ( GenerateListItemWidget *signal_obj_ptr, VarEditorWidget *change_var_obj_ptr ) {
		emit this->changeVarOverSignal( this, signal_obj_ptr, change_var_obj_ptr );
	} );
	newListItemWidget->showVarEditorWidget( );
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
	generateListScrollArea->setGenerateListWidget( this );
	generateListScrollArea->setInit(  );
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
