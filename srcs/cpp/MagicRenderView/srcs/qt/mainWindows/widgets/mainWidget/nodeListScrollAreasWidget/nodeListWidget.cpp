#include "./nodeListWidget.h"

#include <QPainter>
#include <QTreeWidget.h>
#include <qboxlayout.h>
#include <qevent.h>
#include <qfileinfo.h>

#include <qt/application/application.h>

#include <qt/stacks/stackManagement.h>

#include <qt/stacks/funStack/IFunStack.h>

#include "nodeListWidget/nodeGeneraterListWidget.h"
#include "nodeListWidget/nodeTypeTreeListWidget.h"

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	mouseIsPress = false;
	dragWidgetSize = nullptr;
	keyFirst = "Application/MainWindow/MainWidget/NodeListWidget";

	appInstance = Application::getApplicationInstancePtr( );

	nodeTypeTreeListWidget = new NodeTypeTreeListWidget( this );
	nodeGeneraterListWidget = new NodeGeneraterListWidget( this );
	appInstance->syncAppValueIniFile( );

	quint64 nodeTypeListWidth = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeTreeListWidget, "width" ), 30 ).toULongLong( );
	nodeTypeTreeListWidget->setFixedWidth( nodeTypeListWidth );

	quint64 nodeGeneraterListWidth = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterListWidget, "width" ), 80 ).toULongLong( );
	nodeGeneraterListWidget->setFixedWidth( nodeGeneraterListWidth );

	QString showWidget = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterListWidget, "showWidget" ), "" ).toString( );

	auto funStacks = appInstance->getStackManagement( )->getFunStacks( );
	nodeTypeTreeListWidget->setColumnCount( 3 );
	nodeTypeTreeListWidget->setHeaderLabels( { "短名称", "全名称", "说明" } );

	auto topItem = new QTreeWidgetItem( nodeTypeTreeListWidget );
	topItemS.emplace_back( topItem );
	nodeTypeTreeListWidget->addTopLevelItem( topItem );
	topItem->setText( 0, "标准" );
	topItem->setText( 1, "软件常规节点生成器" );
	topItem->setText( 2, "软件自动生成节点" );
	for( auto &item : funStacks ) {
		IFunStack *element = item.get( );
		QString typeName = element->metaObject( )->className( );
		QString name = element->getName( );
		typeName.append( "/" ).append( name );
		QTreeWidgetItem *child = new QTreeWidgetItem( topItem );
		topItem->addChild( child );
		child->setText( 0, name );
		child->setText( 1, typeName );
		child->setText( 2, typeName );

		auto currentFunStack = nodeGeneraterListWidget->appendFunStack( item );
		funStackBind.emplace_back( child, currentFunStack );

		if( showWidget.isEmpty( ) || showWidget != typeName )
			continue;
		if( nodeGeneraterListWidget->setCurrentItem( currentFunStack ) == false )
			tools::debug::printError( "初始化异常" );
		nodeTypeTreeListWidget->setCurrentItem( child );
		nodeGeneraterListWidget->setCurrentItem( currentFunStack );
	}
	NodeGeneraterItem *currentItem = nodeGeneraterListWidget->getCurrentItem( );
	if( currentItem == nullptr )
		itemDoubleClicked( funStackBind[ 0 ].first, 0 );
	connect( nodeTypeTreeListWidget, &QTreeWidget::itemDoubleClicked, this, &NodeListWidget::itemDoubleClicked );
}
NodeListWidget::~NodeListWidget( ) {
	writeHeightIni( );
	appInstance->syncAppValueIniFile( );
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void NodeListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateWidgetListLayout( event->oldSize( ), event->size( ) );
}
void NodeListWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	mouseIsPress = true;
}
void NodeListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	mouseIsPress = false;
}

QWidget * NodeListWidget::mouseToPoint( const QPoint &point ) {
	int y = point.y( );
	int x = point.x( );
	if( x < 0 || y < 0 || height( ) < y || width( ) < x )
		return dragWidgetSize;
	if( mouseIsPress == false ) {
		auto nodeGeneraterListX = nodeGeneraterListWidget->pos( ).x( );
		if( abs( x - nodeGeneraterListX ) < 5 )
			dragWidgetSize = nodeGeneraterListWidget;
		else
			dragWidgetSize = nullptr;
	} else if( dragWidgetSize != nullptr ) {
		if( dragWidgetSize == nodeGeneraterListWidget ) {
			nodeGeneraterListWidget->move( x, 0 ); // 移动到新位置
			nodeTypeTreeListWidget->setFixedWidth( x );
			auto newWidth = width( ) - x;
			nodeGeneraterListWidget->setFixedWidth( newWidth );
		}
	}
	return dragWidgetSize;
}
void NodeListWidget::updateWidgetListLayout( const QSize &old_size, const QSize &current_size ) {

	int newWidth = current_size.width( );

	int nodeTypeListWidth = nodeTypeTreeListWidget->width( );
	int nodeGeneraterListWidth = nodeGeneraterListWidget->width( );

	int width = nodeGeneraterListWidth + nodeTypeListWidth;

	nodeTypeListWidth = nodeTypeListWidth * newWidth / width;

	width = newWidth - nodeTypeListWidth;
	auto height = current_size.height( );
	nodeTypeTreeListWidget->setFixedSize( nodeTypeListWidth, height );
	nodeGeneraterListWidget->setFixedSize( width, height );

	nodeTypeTreeListWidget->move( 0, 0 );
	width = nodeTypeTreeListWidget->width( );
	nodeGeneraterListWidget->move( width, 0 );
}
void NodeListWidget::writeHeightIni( ) const {
	int nodeTypeListWidth = nodeTypeTreeListWidget->width( );
	int nodeGeneraterListWidth = nodeGeneraterListWidget->width( );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeTreeListWidget, "width" ), nodeTypeListWidth );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterListWidget, "width" ), nodeGeneraterListWidth );
}
void NodeListWidget::itemDoubleClicked( QTreeWidgetItem *item, int column ) {

	// 检查看是否顶级

	size_t count = topItemS.size( );
	auto data = topItemS.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == item )
			return;

	// 检查子级

	count = funStackBind.size( );
	auto pair = funStackBind.data( );
	for( size_t index = 0; index < count; ++index )
		if( pair[ index ].first == item )
			if( nodeGeneraterListWidget->setCurrentItem( pair[ index ].second ) == true )
				return;
			else
				break;
	tools::debug::printError( "没有建立正确的绑定关系，该对象无法正确识别" );
}
