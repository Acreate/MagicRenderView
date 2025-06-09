#include "INodeWidget.h"
#include "INodeWidget.h"

#include <QLabel>

#include "qt/widget/nodeGraph.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QTimer>

#include "qt/tools/tools.h"

INodeWidget::INodeWidget( const std_shared_ptr< IFunctionDeclaration > &function_declaration, QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ), connectNodeWidgets( new std_vector< const INodeWidget * > ) {
	selectComponent = nullptr;
	mouseEvent = MouseEvent::None;
	mainBoxLayout = new QVBoxLayout( this );
	if( function_declaration )
		title = new QLabel( function_declaration->getDeclarationName( ), this );
	else
		title = new QLabel( INodeWidget::staticMetaObject.className( ), this );

	mainBoxLayout->addWidget( title, 0, Qt::AlignCenter );
	setMouseTracking( true );
	timer = new QTimer( this );

	connect( timer, &QTimer::timeout, [=]( ) {
		timer->stop( );
		emit selectNodeComponentPress( this, selectComponent, mouseOffsetPos );
		if( mouseEvent == MouseEvent::Release )
			emit selectNodeComponentRelease( this, selectComponent, mouseOffsetPos );
		mouseEvent = MouseEvent::Over;
		selectComponent = nullptr; // 相应消息之后，重置选择空间
	} );
	doubleClickTimeOutCheck = std::chrono::milliseconds( 250 );
}
void INodeWidget::connectNodeGraphWidget( NodeGraph *node_graph ) {
	connect( this, &INodeWidget::selectNodeComponentRelease, node_graph, &NodeGraph::selectNodeComponentRelease );
	connect( this, &INodeWidget::selectNodeComponentPress, node_graph, &NodeGraph::selectNodeComponentPress );
	connect( this, &INodeWidget::ActionNodeComponentRelease, node_graph, &NodeGraph::ActionNodeComponentRelease );
	connect( this, &INodeWidget::error, node_graph, &NodeGraph::error );
	connect( this, &INodeWidget::finish, node_graph, &NodeGraph::finish );
}
QString INodeWidget::getNodeTitle( ) const {
	return title->text( );
}
void INodeWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	if( mouseEvent != MouseEvent::Release )
		emit selectNodeComponentRelease( this, selectComponent, mouseOffsetPos );
	mouseEvent = MouseEvent::Release;
}

void INodeWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );

	mouseOffsetPos = event->pos( );
	auto currentSelectComponent = childAt( mouseOffsetPos );
	if( selectComponent == nullptr )
		selectComponent = currentSelectComponent;
	if( timer->isActive( ) /* 正在计时 */ ) {
		timer->stop( ); // 终止
		if( mouseEvent == MouseEvent::Release ) {
			// 发送双击指令
			if( selectComponent == currentSelectComponent /* 双击组件 */ )
				emit ActionNodeComponentRelease( this, selectComponent, mouseOffsetPos );
			else // 两次点击了不同的组件
				emit ActionNodeComponentRelease( this, nullptr, mouseOffsetPos );
			selectComponent = nullptr; // 相应消息之后，重置选择空间
			mouseEvent = MouseEvent::Over;
		}
		return; // 结束
	}
	mouseEvent = MouseEvent::Press;
	timer->start( doubleClickTimeOutCheck );
}
void INodeWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( timer->isActive( ) /* 正在计时 */ ) {
		timer->stop( ); // 终止
		if( mouseEvent == MouseEvent::Press )
			emit selectNodeComponentPress( this, selectComponent, mouseOffsetPos );
		selectComponent = nullptr;
	}
	mouseEvent = MouseEvent::Move;
}

void INodeWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPen pen;
	QBrush brush;
	pen.setWidth( 5 );
	pen.setColor( Qt::red );
	painter.setPen( pen );
	auto geometry = size( );
	painter.drawRect( QRect( 0, 0, geometry.width( ) - 1, geometry.height( ) - 1 ) );
}
void INodeWidget::leaveEvent( QEvent *event ) {
	QWidget::leaveEvent( event );
}
