#include "./nodeListWidget.h"

#include <QPainter>
#include <qboxlayout.h>
#include <qfileinfo.h>
#include <QTreeWidget.h>
#include <qevent.h>

#include "gridWidget.h"

#include "../../application/application.h"

#include "../../stacks/funStack/IFunStack.h"

NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	mouseIsPress = false;
	dragWidgetSize = nullptr;

	keyFirst = "Application/MainWindow/MainWidget/NodeListWidget";

	appInstance = Application::getApplicationInstancePtr( );

	nodeTypeList = new QTreeWidget( this );
	nodeGeneraterList = new GridWidget( this );
	appInstance->syncAppValueIniFile( );

	quint64 nodeTypeListWidget = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeList, "width" ), 30 ).toULongLong( );
	nodeTypeList->setFixedWidth( nodeTypeListWidget );

	quint64 nodeGeneraterListWidget = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterList, "width" ), 80 ).toULongLong( );
	nodeGeneraterList->setFixedWidth( nodeGeneraterListWidget );

	auto funStacks = appInstance->getFunStacks( );

	nodeTypeList->setColumnCount( 2 );
	nodeTypeList->setHeaderLabels( { "名称", "说明" } );
	QTreeWidgetItem *topItem = new QTreeWidgetItem( nodeTypeList );
	nodeTypeList->addTopLevelItem( topItem );
	topItem->setText( 0, "标准" );
	topItem->setText( 1, "软件自动生成节点" );
	for( auto &item : funStacks ) {
		IFunStack *element = item.get( );
		QString typeName = element->metaObject( )->className( );
		QString name = element->getName( );
		typeName.append( "/" ).append( name );
		QTreeWidgetItem *child = new QTreeWidgetItem( topItem );
		topItem->addChild( child );
		child->setText( 0, name );
		child->setText( 1, typeName );
	}
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
	if( cursor( ) != Qt::ArrowCursor )
		setCursor( Qt::ArrowCursor );
}

void NodeListWidget::mouseToPoint( const QPoint &point ) {
	int y = point.y( );
	int x = point.x( );
	if( x < 0 || y < 0 || height( ) < y || width( ) < x )
		return;
	if( mouseIsPress == false ) {
		auto nodeGeneraterListX = nodeGeneraterList->pos( ).x( );
		if( abs( x - nodeGeneraterListX ) < 5 )
			dragWidgetSize = nodeGeneraterList;
		else
			dragWidgetSize = nullptr;
		if( dragWidgetSize && cursor( ) != Qt::SizeHorCursor )
			setCursor( Qt::SizeHorCursor ); // 设置鼠标样式
		else if( dragWidgetSize == nullptr && cursor( ) != Qt::ArrowCursor )
			setCursor( Qt::ArrowCursor ); // 设置鼠标样式

	} else if( dragWidgetSize != nullptr ) {
		if( dragWidgetSize == nodeGeneraterList ) {
			nodeGeneraterList->move( x, 0 ); // 移动到新位置
			nodeTypeList->setFixedWidth( x );
			auto newWidth = width( ) - x;
			nodeGeneraterList->setFixedWidth( newWidth );
		}
	}
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
	writeHeightIni( );
	appInstance->syncAppValueIniFile( );
}
void NodeListWidget::writeHeightIni( ) const {
	int nodeTypeListWidth = nodeTypeList->width( );
	int nodeGeneraterListWidth = nodeGeneraterList->width( );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeTypeList, "width" ), nodeTypeListWidth );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, nodeGeneraterList, "width" ), nodeGeneraterListWidth );
}
