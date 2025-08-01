#include "./nodeListWidget.h"

#include <QPainter>
#include <qboxlayout.h>
#include <qfileinfo.h>
#include <QTreeWidget.h>
#include <qevent.h>

#include "nodeGeneraterListWidget.h"

#include "../../application/application.h"

#include "../../stacks/funStack/IFunStack.h"

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
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

	auto funStacks = appInstance->getFunStacks( );
	nodeTypeList->setColumnCount( 3 );
	nodeTypeList->setHeaderLabels( { "短名称", "全名称", "说明" } );
	QTreeWidgetItem *topItem = new QTreeWidgetItem( nodeTypeList );
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

		funStackBind.emplace_back( child, item );
		nodeGeneraterList->appendCurrentFunStack( item );
		if( showWidget.isEmpty( ) || showWidget != typeName )
			continue;
		nodeGeneraterList->setCurrentFunStack( item );
		nodeTypeList->setCurrentItem( child );
	}

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
	size_t count = funStackBind.size( );
	if( count == 0 ) {
		tools::debug::printError( "没有建立正确的绑定关系，生成窗口个数为 0" );
		return;
	}
	auto data = funStackBind.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first == item ) {
			if( nodeGeneraterList->setCurrentFunStack( data[ index ].second ) == false )
				tools::debug::printError( "对象并不在窗口当中，请添加到窗口队列当中" );
			return;
		}
	tools::debug::printError( "没有找到匹配的窗口，请检查是否正确初始化窗口" );
}
