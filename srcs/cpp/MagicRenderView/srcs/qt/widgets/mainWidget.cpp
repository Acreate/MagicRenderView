#include "./mainWidget.h"

#include <QMetaEnum>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qfile.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include <qt/node/prot/inputProt/nodeInputPort.h>

#include <qt/generate/varGenerate.h>

#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>

#include "../node/director/nodeDirector.h"
#include "../node/widgets/nodeItemInfoScrollAreaWidget.h"

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

	removeSelectNodeItemMenu = new QMenu( );
	connect( removeSelectNodeItemMenu, &QMenu::aboutToHide, [this]( ) {
		removeSelectNodeItemMenu->clear( );
	} );
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	nodeDirector->draw( painter );
	// 不在拖拽情况下，绘制动态线
	switch( clickNodeItemType ) {
		case NodeItem::Click_Type::None :
		case NodeItem::Click_Type::Space :
		case NodeItem::Click_Type::Title :
			break;
		case NodeItem::Click_Type::InputPort :
		case NodeItem::Click_Type::OutputPort :
			painter.drawLine( modPoint, mouseMovePoint );
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

void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	auto pos = event->pos( );

	switch( mouseButton ) {
		case Qt::RightButton :
			clickNodeItemType = nodeDirector->getClickNodeItem( pos, rightMouseBtnSelectItem, rightMouseBtnSelectPort );
			switch( clickNodeItemType ) {
				case NodeItem::Click_Type::None :
					rightMouseBtnCreateNodeItemMenu->popup( QCursor::pos( ) );
					break;
				case NodeItem::Click_Type::Space :
				case NodeItem::Click_Type::Title :
					break;
				case NodeItem::Click_Type::InputPort :
					if( nodeDirector->getLinkOutPorts( rightMouseBtnSelectPort, rightMenuRemoveInfo ) ) {
						size_t count = rightMenuRemoveInfo.size( );
						if( count == 0 )
							break;
						auto data = rightMenuRemoveInfo.data( );

						// todo : 添加删除节点
						QString actionTitleFrom( "删除 %1[%2] 输入" );
						QString activeTitle;
						QAction *addAction;
						for( size_t index = 0; index < count; ++index ) {
							activeTitle = actionTitleFrom.arg( data[ index ]->parentItem->nodeTitleName ).arg( data[ index ]->title );
							addAction = removeSelectNodeItemMenu->addAction( activeTitle );
							connect( addAction, &QAction::triggered, [this, index, data] {
								nodeDirector->linkUnInstallPort( rightMouseBtnSelectPort, data[ index ] );
							} );
							//connect( addAction, &QAction::destroyed, [this, index, data, addAction] {
							//	qDebug( ) << QString( "0x%1" ).arg( ( size_t ) addAction, 0, 16 );
							//} );
						}
						removeSelectNodeItemMenu->popup( QCursor::pos( ) );
					}
					tools::debug::printError( "右击输入接口" );
					break;
				case NodeItem::Click_Type::OutputPort :
					tools::debug::printError( "右击输出接口" );
					break;
			}
			break;
		case Qt::LeftButton :

			clickNodeItemType = nodeDirector->getClickNodeItem( pos, leftScondSelectItem, leftScondSelecttPort );
			switch( clickNodeItemType ) {
				case NodeItem::Click_Type::None :
					break;
				case NodeItem::Click_Type::Space :
					break;
				case NodeItem::Click_Type::Title :
					break;
				case NodeItem::Click_Type::InputPort :
				case NodeItem::Click_Type::OutputPort :
					nodeDirector->linkInstallPort( leftFirstSelectPort, leftScondSelecttPort );
					break;
			}
			clickNodeItemType = NodeItem::Click_Type::None;
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
		case NodeItem::Click_Type::Space :
		case NodeItem::Click_Type::Title :
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
		case NodeItem::Click_Type::InputPort :
		case NodeItem::Click_Type::OutputPort :
			update( );
		case NodeItem::Click_Type::None :
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
				case NodeItem::Click_Type::None :
					break;
				case NodeItem::Click_Type::InputPort :
					tools::debug::printError( "左击选中输入接口" );
					nodeDirector->setRaise( leftScondSelectItem );
					leftScondSelecttPort->getPos( modPoint );
					leftFirstSelectItem = leftScondSelectItem;
					leftFirstSelectPort = leftScondSelecttPort;
					break;
				case NodeItem::Click_Type::OutputPort :
					tools::debug::printError( "左击选中输出接口" );
					nodeDirector->setRaise( leftScondSelectItem );
					leftScondSelecttPort->getPos( modPoint );
					leftFirstSelectItem = leftScondSelectItem;
					leftFirstSelectPort = leftScondSelecttPort;
					break;
				case NodeItem::Click_Type::Space :
				case NodeItem::Click_Type::Title :
					nodeDirector->setRaise( leftScondSelectItem );
					modPoint = fromGlobalPressPoint - leftScondSelectItem->getPos( );
					// 相同节点
					if( leftFirstSelectItem == leftScondSelectItem ) {
						long long count = duration_cast< std::chrono::milliseconds >( currentDateTime - sigClickDateTime ).count( );
						if( count < 200 ) {
							tools::debug::printError( QString( "(%1)双击节点 -> %2" ).arg( count ).arg( leftScondSelectItem->getMetaObjectPathName( ) ) );
							clickNodeItemType = NodeItem::Click_Type::None; // 取消移动
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
