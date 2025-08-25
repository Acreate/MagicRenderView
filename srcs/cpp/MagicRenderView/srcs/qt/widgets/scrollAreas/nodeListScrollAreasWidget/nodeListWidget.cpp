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

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	mouseIsPress = false;
	dragWidgetSize = nullptr;
	keyFirst = "Application/MainWindow/MainWidget/NodeListWidget";

	appInstance = Application::getApplicationInstancePtr( );

	nodeTypeList = new QTreeWidget( this );
	nodeGeneraterList = new NodeGeneraterListWidget( this );
	appInstance->syncAppValueIniFile( );

	quint64 nodeTypeListWidth = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeList, "width" ), 30 ).toULongLong( );
	nodeTypeList->setFixedWidth( nodeTypeListWidth );

	quint64 nodeGeneraterListWidth = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterList, "width" ), 80 ).toULongLong( );
	nodeGeneraterList->setFixedWidth( nodeGeneraterListWidth );

	QString showWidget = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterList, "showWidget" ), "" ).toString( );

	auto funStacks = appInstance->getStackManagement( )->getFunStacks( );
	nodeTypeList->setColumnCount( 3 );
	nodeTypeList->setHeaderLabels( { "短名称", "全名称", "说明" } );

	auto topItem = new QTreeWidgetItem( nodeTypeList );
	topItemS.emplace_back( topItem );
	nodeTypeList->addTopLevelItem( topItem );
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

		auto currentFunStack = nodeGeneraterList->appendFunStack( item );
		funStackBind.emplace_back( child, currentFunStack );

		if( showWidget.isEmpty( ) || showWidget != typeName )
			continue;
		if( nodeGeneraterList->setCurrentItem( currentFunStack ) == false )
			tools::debug::printError( "初始化异常" );
		nodeTypeList->setCurrentItem( child );
		nodeGeneraterList->setCurrentItem( currentFunStack );
	}
	NodeGeneraterItem *currentItem = nodeGeneraterList->getCurrentItem( );
	if( currentItem == nullptr )
		itemDoubleClicked( funStackBind[ 0 ].first, 0 );
	connect( nodeTypeList, &QTreeWidget::itemDoubleClicked, this, &NodeListWidget::itemDoubleClicked );
}
NodeListWidget::~NodeListWidget( ) {
	writeHeightIni( );
	appInstance->syncAppValueIniFile( );
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( rect, Qt::blue );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
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
		auto nodeGeneraterListX = nodeGeneraterList->pos( ).x( );
		if( abs( x - nodeGeneraterListX ) < 5 )
			dragWidgetSize = nodeGeneraterList;
		else
			dragWidgetSize = nullptr;
	} else if( dragWidgetSize != nullptr ) {
		if( dragWidgetSize == nodeGeneraterList ) {
			nodeGeneraterList->move( x, 0 ); // 移动到新位置
			nodeTypeList->setFixedWidth( x );
			auto newWidth = width( ) - x;
			nodeGeneraterList->setFixedWidth( newWidth );
		}
	}
	return dragWidgetSize;
}
void NodeListWidget::updateWidgetListLayout( const QSize &old_size, const QSize &current_size ) {

	int newWidth = current_size.width( );

	int nodeTypeListWidth = nodeTypeList->width( );
	int nodeGeneraterListWidth = nodeGeneraterList->width( );

	int width = nodeGeneraterListWidth + nodeTypeListWidth;

	nodeTypeListWidth = nodeTypeListWidth * newWidth / width;

	width = newWidth - nodeTypeListWidth;
	auto height = current_size.height( );
	nodeTypeList->setFixedSize( nodeTypeListWidth, height );
	nodeGeneraterList->setFixedSize( width, height );

	nodeTypeList->move( 0, 0 );
	width = nodeTypeList->width( );
	nodeGeneraterList->move( width, 0 );
}
void NodeListWidget::writeHeightIni( ) const {
	int nodeTypeListWidth = nodeTypeList->width( );
	int nodeGeneraterListWidth = nodeGeneraterList->width( );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeList, "width" ), nodeTypeListWidth );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterList, "width" ), nodeGeneraterListWidth );
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
			if( nodeGeneraterList->setCurrentItem( pair[ index ].second ) == true )
				return;
			else
				break;
	tools::debug::printError( "没有建立正确的绑定关系，该对象无法正确识别" );
}
