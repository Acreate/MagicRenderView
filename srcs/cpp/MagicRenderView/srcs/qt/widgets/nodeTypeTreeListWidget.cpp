#include "./nodeTypeTreeListWidget.h"

#include <qt/stacks/funStack/IFunStack.h>

#include "nodeGeneraterListWidget.h"

#include <qt/tools/tools.h>

#include <qt/application/application.h>

#include <qt/stacks/stackManagement.h>
NodeTypeTreeListWidget::NodeTypeTreeListWidget( NodeGeneraterListWidget *node_generater_list_widget, QWidget *parent ) : QTreeWidget( parent ), bindNodeGeneraterListWidget( node_generater_list_widget ) {
	setColumnCount( 3 );
	setHeaderLabels( { "短名称", "全名称", "说明" } );

	keyFirst = "Application/MainWindow/MainWidget/NodeListWidget/NodeTypeTreeListWidget";

	appInstance = Application::getApplicationInstancePtr( );
	appInstance->syncAppValueIniFile( );
	QString showWidget = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "showWidget" ), "" ).toString( );
	initTopItem( appInstance->getStackManagement( )->getFunStacks( ) );
}
QTreeWidgetItem * NodeTypeTreeListWidget::initTopItem( const std_vector< std::shared_ptr< IFunStack > > &fun_stacks ) {
	auto topItem = new QTreeWidgetItem( this );

	addTopLevelItem( topItem );
	topItem->setText( 0, "标准" );
	topItem->setText( 1, "软件常规节点生成器" );
	topItem->setText( 2, "软件自动生成节点" );
	topItemVector.emplace_back( topItem );
	for( auto &item : fun_stacks ) {
		IFunStack *element = item.get( );
		QString typeName = element->metaObject( )->className( );
		QString name = element->getName( );
		typeName.append( "/" ).append( name );
		QTreeWidgetItem *child = new QTreeWidgetItem( topItem );
		topItem->addChild( child );
		child->setText( 0, name );
		child->setText( 1, typeName );
		child->setText( 2, typeName );
		auto currentFunStack = bindNodeGeneraterListWidget->appendFunStack( item );
		funStackBind.emplace_back( child, currentFunStack );
	}
	connect( bindNodeGeneraterListWidget, &QObject::destroyed, [this]( ) {
		this->disconnect( this, &QTreeWidget::itemDoubleClicked, this, &NodeTypeTreeListWidget::typeItemDoubleClicked );
		bindNodeGeneraterListWidget = nullptr;
		clear( );
	} );
	connect( this, &QTreeWidget::itemDoubleClicked, this, &NodeTypeTreeListWidget::typeItemDoubleClicked );
	return topItem;
}

QTreeWidgetItem * NodeTypeTreeListWidget::appendItem( const std_vector< std::shared_ptr< IFunStack > > &fun_stacks, const QString &short_name, const QString &full_name, const QString &info ) {
	if( bindNodeGeneraterListWidget == nullptr )
		return nullptr;
	auto topItem = new QTreeWidgetItem( this );

	addTopLevelItem( topItem );
	topItem->setText( 0, short_name );
	topItem->setText( 1, full_name );
	topItem->setText( 2, info );
	topItemVector.emplace_back( topItem );
	for( auto &item : fun_stacks ) {
		IFunStack *element = item.get( );
		QString typeName = element->metaObject( )->className( );
		QString name = element->getName( );
		typeName.append( "/" ).append( name );
		QTreeWidgetItem *child = new QTreeWidgetItem( topItem );
		topItem->addChild( child );
		child->setText( 0, name );
		child->setText( 1, typeName );
		child->setText( 2, typeName );
		auto currentFunStack = bindNodeGeneraterListWidget->appendFunStack( item );
		funStackBind.emplace_back( child, currentFunStack );
	}
	return topItem;
}
void NodeTypeTreeListWidget::typeItemDoubleClicked( QTreeWidgetItem *item, int column ) {
	// 显示对象已经失去控制
	if( bindNodeGeneraterListWidget == nullptr )
		return;
	size_t count = topItemVector.size( );
	size_t index = 0;
	auto treeWidgetItemPtr = topItemVector.data( );
	// 检查看是否顶级
	for( index = 0; index < count; ++index )
		if( treeWidgetItemPtr[ index ] == item )
			return;
	// 检查子级
	count = funStackBind.size( );
	auto pair = funStackBind.data( );
	for( index = 0; index < count; ++index )
		if( pair[ index ].first == item )
			if( bindNodeGeneraterListWidget->setCurrentItem( pair[ index ].second ) == true ) {
				emit activeItem( pair[ index ] );
				return;
			} else
				break;
	tools::debug::printError( "没有建立正确的绑定关系，该对象无法正确识别" );
}
void NodeTypeTreeListWidget::selectTypeItem( QTreeWidgetItem *item ) {
	// 显示对象已经失去控制
	if( bindNodeGeneraterListWidget == nullptr )
		return;
	size_t count = topItemVector.size( );
	size_t index = 0;
	auto treeWidgetItemPtr = topItemVector.data( );
	// 检查看是否顶级
	for( index = 0; index < count; ++index )
		if( treeWidgetItemPtr[ index ] == item )
			return;
	// 检查子级
	count = funStackBind.size( );
	auto pair = funStackBind.data( );
	for( index = 0; index < count; ++index )
		if( pair[ index ].first == item )
			if( bindNodeGeneraterListWidget->setCurrentItem( pair[ index ].second ) == true ) {
				setCurrentItem( item );
				scrollToItem( item );
				emit activeItem( pair[ index ] );
				return;
			} else
				break;
	tools::debug::printError( "没有建立正确的绑定关系，该对象无法正确识别" );
}
