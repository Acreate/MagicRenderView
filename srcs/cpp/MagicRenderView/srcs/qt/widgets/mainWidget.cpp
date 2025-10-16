#include "./mainWidget.h"

#include <QMetaEnum>
#include <QMouseEvent>
#include <QPainter>
#include <qboxlayout.h>
#include <qfile.h>
#include <qmenu.h>

#include <qt/application/application.h>
#include <qt/generate/varGenerate.h>
#include <qt/node/director/nodeDirector.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/node/widgets/nodeItemInfoScrollAreaWidget.h>

MainWidget::MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags ) : QWidget( scroll_area, flags ) {
	scrollArea = scroll_area;
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setWidget( this );
	appInstance = Application::getApplicationInstancePtr( );
	varGenerate = appInstance->getVarGenerate( );
	nodeDirector = appInstance->getNodeDirector( );

	keyFirst = "Application/MainWindow/MainWidget";

	appInstance->syncAppValueIniFile( );

	leftFirstSelectItem = leftScondSelectItem = nullptr;
	leftFirstSelectPort = leftScondSelecttPort = nullptr;
	nodeDirector->setContentWidget( this );
	rightMouseBtnCreateNodeItemMenu = nodeDirector->getNodeItemCraeteMenu( );
	sigClickDateTime = QDateTime::currentDateTime( );
	connect( nodeDirector, &NodeDirector::linkNodePortSignal, this, &MainWidget::linkNodePortEvent );
	connect( nodeDirector, &NodeDirector::unlinkNodePortSignal, this, &MainWidget::unlinkNodePortEvent );
	connect( nodeDirector, &NodeDirector::releaseNodeItemInfoSignal, this, &MainWidget::releaseNodeItemInfoObj );
	connect( nodeDirector, &NodeDirector::generateNodeItemSignal, this, &MainWidget::generateNodeItem );
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	//painter.fillRect( contentsRect( ), QColor( 0, 0, 0, 0 ) );
	nodeDirector->draw( painter );
	// 不在拖拽情况下，绘制动态线
	switch( clickNodeItemType ) {
		case nodeItemEnum::Click_Type::None :
		case nodeItemEnum::Click_Type::Space :
		case nodeItemEnum::Click_Type::Title :
			break;
		case nodeItemEnum::Click_Type::InputPort :
		case nodeItemEnum::Click_Type::OutputPort :
			painter.drawLine( modPoint, mouseMovePoint );
			break;
	}
}
void MainWidget::ensureVisibleToItemNode( const NodeItem *targetItemNode ) {
	auto geometry = targetItemNode->geometry( );
	auto newSize = contentsRect( ).united( geometry ).size( );
	if( size( ) != newSize )
		setMinimumSize( newSize );
	auto targetSize = geometry.bottomRight( );
	scrollArea->ensureVisible( targetSize.x( ), targetSize.y( ) );
}
void MainWidget::linkNodePortEvent( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port ) {
}
void MainWidget::unlinkNodePortEvent( NodeDirector *sender_director_ptr, NodePortLinkInfo *control_obj_ptr, NodeInputPort *input_port, NodeOutputPort *link_output_port ) {
	update( );
}
void MainWidget::releaseNodeItemInfoObj( NodeItemInfo *release_ptr ) {
	update( );
}
void MainWidget::generateNodeItem( NodeItem *create_ptr ) {
	ensureVisibleToItemNode( create_ptr );
	update( );
}

void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	auto pos = event->pos( );

	switch( mouseButton ) {
		case Qt::RightButton :
			clickNodeItemType = nodeDirector->getClickNodeItem( pos, rightMouseBtnSelectItem, rightMouseBtnSelectPort );
			switch( clickNodeItemType ) {
				case nodeItemEnum::Click_Type::None :
					rightMouseBtnCreateNodeItemMenu->popup( QCursor::pos( ) );
					break;
				case nodeItemEnum::Click_Type::Space :
				case nodeItemEnum::Click_Type::Title :
					if( nodeDirector->getItemManageMenu( rightMouseBtnSelectItem, removeSelectNodeItemMenu ) ) {
						removeSelectNodeItemMenu->popup( QCursor::pos( ) );
						clickNodeItemType = nodeItemEnum::Click_Type::None;
					}
					break;
				case nodeItemEnum::Click_Type::InputPort :
					if( nodeDirector->getLinkControlMenu( rightMouseBtnSelectPort, removeSelectNodeItemMenu ) ) {
						removeSelectNodeItemMenu->popup( QCursor::pos( ) );
						clickNodeItemType = nodeItemEnum::Click_Type::None;
					}
					break;
				case nodeItemEnum::Click_Type::OutputPort :
					break;
			}
			break;
		case Qt::LeftButton :
			clickNodeItemType = nodeDirector->getClickNodeItem( pos, leftScondSelectItem, leftScondSelecttPort );
			switch( clickNodeItemType ) {
				case nodeItemEnum::Click_Type::None :
					break;
				case nodeItemEnum::Click_Type::Space :
				case nodeItemEnum::Click_Type::Title :
					ensureVisibleToItemNode( leftScondSelectItem );
					break;
				case nodeItemEnum::Click_Type::InputPort :
				case nodeItemEnum::Click_Type::OutputPort :
					nodeDirector->linkInstallPort( leftFirstSelectPort, leftScondSelecttPort );
					break;
			}
			clickNodeItemType = nodeItemEnum::Click_Type::None;
			leftFirstSelectItem = leftScondSelectItem;
			leftFirstSelectPort = leftScondSelecttPort;
			leftScondSelectItem = nullptr;
			leftScondSelecttPort = nullptr;
			update( );
			break;
	}
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	mouseMovePoint = event->pos( );
	switch( clickNodeItemType ) {
		case nodeItemEnum::Click_Type::Space :
		case nodeItemEnum::Click_Type::Title :
			if( leftFirstSelectItem ) {
				QPoint point = mouseMovePoint - modPoint;
				if( point.x( ) < 0 )
					point.setX( 0 );
				if( point.y( ) < 0 )
					point.setY( 0 );
				leftFirstSelectItem->move( point );
				update( );
			}
			break;
		case nodeItemEnum::Click_Type::InputPort :
		case nodeItemEnum::Click_Type::OutputPort :
			update( );
		case nodeItemEnum::Click_Type::None :
			break;
	}
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	auto fromGlobalPressPoint = event->pos( );
	auto currentDateTime = QDateTime::currentDateTime( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			clickNodeItemType = nodeDirector->getClickNodeItem( fromGlobalPressPoint, leftScondSelectItem, leftScondSelecttPort );
			switch( clickNodeItemType ) {
				case nodeItemEnum::Click_Type::None :
					break;
				case nodeItemEnum::Click_Type::InputPort :
					nodeDirector->setRaise( leftScondSelectItem );
					leftScondSelecttPort->getPos( modPoint );
					leftFirstSelectItem = leftScondSelectItem;
					leftFirstSelectPort = leftScondSelecttPort;
					break;
				case nodeItemEnum::Click_Type::OutputPort :
					nodeDirector->setRaise( leftScondSelectItem );
					leftScondSelecttPort->getPos( modPoint );
					leftFirstSelectItem = leftScondSelectItem;
					leftFirstSelectPort = leftScondSelecttPort;
					break;
				case nodeItemEnum::Click_Type::Space :
				case nodeItemEnum::Click_Type::Title :
					nodeDirector->setRaise( leftScondSelectItem );
					modPoint = fromGlobalPressPoint - leftScondSelectItem->getPos( );
					// 相同节点
					if( leftFirstSelectItem == leftScondSelectItem ) {
						long long count = duration_cast< std::chrono::milliseconds >( currentDateTime - sigClickDateTime ).count( );
						if( count < 200 ) {
							clickNodeItemType = nodeItemEnum::Click_Type::None; // 取消移动
							leftScondSelectItem = nullptr;
						}
					}
					leftFirstSelectItem = leftScondSelectItem;
					leftFirstSelectPort = leftScondSelecttPort;
					sigClickDateTime = currentDateTime; // 重新计时
					break;
			}
			break;
	}
}
