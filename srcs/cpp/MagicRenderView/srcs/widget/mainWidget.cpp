#include "mainWidget.h"

#include <QMenu>
#include <QClipboard>
#include <QResizeEvent>
#include <qdatetime.h>
#include <QPainter>

#include "mainWidgetScrollArea.h"

#include "../app/application.h"

#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../menu/generateNode/normalGenerateNodeMenu.h"

#include "../node/node/node.h"
#include "../node/nodeInfo/nodeClickInfo.h"
#include "../node/port/inputPort/inputPort.h"
#include "../node/port/outputPort/outputPort.h"

#include "../srack/srackInfo.h"

#include "../win/mainWindow.h"

MainWidget::MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), mainWidgetScrollArea( parent ), selectInputPort( nullptr ), selectOutputPort( nullptr ), dragNode( nullptr ), oldSelectNode( nullptr ) {
	clickInfoPtr = new NodeClickInfo( NodeEnum::NodeClickType::None, nullptr, nullptr, nullptr );
	oldClickTime = new QDateTime;
	isDrawLine = false;
}
MainWidget::~MainWidget( ) {
	emit release_signal( this );
	size_t count = nodeVector.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		for( ; index < count; ++index )
			if( nodeArrayPtr[ index ] == nullptr )
				break;
			else {
				nodeArrayPtr[ index ]->hide( );
				nodeArrayPtr[ index ]->setParent( nullptr );
			}
		nodeVector.clear( );
	}
	delete clickInfoPtr;
}

bool MainWidget::getPointNodeClickInfo( const QPoint &click_point, NodeClickInfo &result_node_click_info ) {
	size_t count = nodeVector.size( );
	if( count == 0 )
		return false;
	size_t index = 0;
	auto nodeArrayPtr = nodeVector.data( );
	for( ; index < count; ++index )
		if( nodeArrayPtr[ index ] == nullptr )
			return false;
		else if( nodeArrayPtr[ index ]->geometry( ).contains( click_point ) == true ) {
			auto mapFromParent = nodeArrayPtr[ index ]->mapFromParent( click_point );
			if( nodeArrayPtr[ index ]->getPointInfo( mapFromParent, result_node_click_info ) == false )
				return false;
			return true;
		}
	return false;
}
void MainWidget::removeVector( Node *remove_node ) {
	size_t count = nodeVector.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		for( ; index < count; ++index )
			if( nodeArrayPtr[ index ] == remove_node ) {
				++index;
				for( ; index < count; ++index )
					if( nodeArrayPtr[ index ] == nullptr )
						break;
					else
						nodeArrayPtr[ index - 1 ] = nodeArrayPtr[ index ];
				nodeArrayPtr[ index - 1 ] = nullptr;
				return;
			}
	}
}
void MainWidget::appendVector( Node *append_node ) {
	size_t count = nodeVector.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		for( ; index < count; ++index )
			if( nodeArrayPtr[ index ] == nullptr ) {
				nodeArrayPtr[ index ] = append_node;
				return;
			}
	}
	nodeVector.emplace_back( append_node );
}
bool MainWidget::addNode( Node *node_ref_link_info ) {
	if( node_ref_link_info->initEx( this ) == false )
		return false;
	QPoint fromGlobal = mapFromGlobal( normalGenerateNodeMenu->pos( ) );
	if( fromGlobal.x( ) < 0 )
		fromGlobal.setX( 0 );
	if( fromGlobal.y( ) < 0 )
		fromGlobal.setY( 0 );
	node_ref_link_info->move( fromGlobal );
	appendVector( node_ref_link_info );
	connect( node_ref_link_info, &Node::release_node_signal, this, &MainWidget::removeVector );
	return true;
}

void MainWidget::raiseNode( Node *raise_node ) {
	size_t count = nodeVector.size( );
	if( count > 1 ) {
		size_t index = 0;
		auto nodeArrayPtr = nodeVector.data( );
		if( nodeArrayPtr[ index ] == nullptr ) // 整个列表为空，则退出
			return;
		size_t lastNode = count - 1;
		for( ; index < lastNode; --lastNode )
			if( nodeArrayPtr[ lastNode ] != nullptr )
				break; // 匹配最后一个有效节点
		if( nodeArrayPtr[ lastNode ] == raise_node ) // 末尾就是该节点，则退出
			return;
		index += 1; // 从 1 开始测试
		for( ; index < lastNode; ++index )
			if( nodeArrayPtr[ index ] == raise_node ) {
				// 元素往前推
				count = index + 1;
				for( ; count < lastNode; ++count )
					nodeArrayPtr[ count - 1 ] = nodeArrayPtr[ count ];
				nodeArrayPtr[ lastNode ] = raise_node; // 替换最后一个有效节点
				return;
			}
	}
}
bool MainWidget::ensureVisible( Node *target ) {
	if( target->parent( ) != this )
		return false;
	auto point = target->pos( );
	auto toGlobal = mapToGlobal( point );
	auto fromGlobal = mainWindow->mapFromGlobal( toGlobal );
	int fromGlobalX = fromGlobal.x( );
	int fromGlobalY = fromGlobal.y( );
	QSize renderSize = target->size( );
	if( fromGlobalX < 0 || fromGlobalY < 0 ) {
		mainWidgetScrollArea->ensureVisible( point.x( ), point.y( ) );
		return true;
	}
	fromGlobalX = renderSize.width( ) + point.x( );
	fromGlobalY = renderSize.height( ) + point.y( );
	renderSize = minimumSize( );
	int oldW = renderSize.width( );
	int oldH = renderSize.height( );
	if( oldW > fromGlobalX )
		fromGlobalX = oldW;
	if( oldH > fromGlobalY )
		fromGlobalY = oldH;
	if( oldW > fromGlobalX && oldH > fromGlobalY )
		return true;
	setMinimumSize( fromGlobalX, fromGlobalY );
	mainWidgetScrollArea->ensureVisible( fromGlobalX, fromGlobalY );
	return true;
}
bool MainWidget::init( ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
	mainWindow = appInstancePtr->getMainWindow( );
	printerDirector = appInstancePtr->getPrinterDirector( );
	normalGenerateNodeMenu = nodeDirector->getNormalGenerateNodeMenu( );
	*oldClickTime = QDateTime::currentDateTime( );
	return true;
}
void MainWidget::copySelectNodeInfo( ) {
	if( oldSelectNode == nullptr )
		return;
	QClipboard *clipboard = QApplication::clipboard( );
	clipboard->setText( oldSelectNode->getNodeName( ) );
}
void MainWidget::pastePointNodeInfo( ) {

	QClipboard *clipboard = QApplication::clipboard( );
	auto text = clipboard->text( );
	auto list = text.split( "," );
	if( list.size( ) == 0 )
		return;
	text = list.data( )[ 0 ];
	auto node = nodeDirector->createNode( text );
	if( node == nullptr ) {
		printerDirector->info( tr( "无法匹配 [%1]" ).arg( text ), Create_SrackInfo( ) );
		return;
	}
	auto point = QCursor::pos( );
	point = mapFromGlobal( point );
	node->move( point );
}
void MainWidget::cutSelectNodeInfo( ) {
	if( oldSelectNode == nullptr )
		return;
	copySelectNodeInfo( );
	deleteSelectNodeInfo( );
}
void MainWidget::cancelNodeInfo( ) {
	nodeDirector->cancelNodeHistory( );
}
void MainWidget::deleteSelectNodeInfo( ) {
	if( oldSelectNode == nullptr )
		return;
	delete oldSelectNode;
	oldSelectNode = nullptr;
}

void MainWidget::calculateNodeRenderSize( ) {
	auto buffMaxSize = nodeDirector->getMaxNodeRenderSize( );
	if( buffMaxSize.width( ) > this->width( ) || buffMaxSize.height( ) > this->height( ) )
		setMinimumSize( buffMaxSize );
}
void MainWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
void MainWidget::drawBegin( const QPoint &start_point ) {
	isDrawLine = true;
	startPoint = start_point;
}
void MainWidget::drawLinePoint( const QPoint &end_point ) {
	endPoint = end_point;
}
void MainWidget::drawEnd( ) {
	isDrawLine = false;
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	auto clickPoint = event->pos( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( getPointNodeClickInfo( clickPoint, *clickInfoPtr ) ) {
				dragNode = clickInfoPtr->getClickNode( );
				ensureVisible( dragNode );
				switch( clickInfoPtr->getClickType( ) ) {
					case NodeEnum::NodeClickType::None :
					case NodeEnum::NodeClickType::Titile : {
						QDateTime currentDateTime = QDateTime::currentDateTime( );
						auto sep = currentDateTime - *oldClickTime;
						*oldClickTime = currentDateTime;
						auto second = sep.count( );
						if( second < 200 )
							if( oldSelectNode == dragNode && nodeDirector->showNodeWidgeInfo( oldSelectNode ) ) {
								dragNode = nullptr;
								break;
							}
						offsetPoint = dragNode->mapFromParent( clickPoint );
						oldSelectNode = dragNode;
						break;
					}
					case NodeEnum::NodeClickType::InputPort :
						dragNode = nullptr;
						selectInputPort = clickInfoPtr->getInputPort( );
						drawBegin( mapFromGlobal( selectInputPort->getLinkPoint( ) ) );
						dragNode = nullptr;
						break;
					case NodeEnum::NodeClickType::OutputPort :
						selectOutputPort = clickInfoPtr->getOutputPort( );
						drawBegin( mapFromGlobal( selectOutputPort->getLinkPoint( ) ) );
						dragNode = nullptr;
						break;
				}
				break;
			} else {
				oldSelectNode = dragNode = nullptr;
				nodeDirector->showNodeWidgeInfo( nullptr );
				break;
			}
		case Qt::MiddleButton :
			break;
	}
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	auto mousePoint = event->pos( );
	if( isDrawLine ) {
		endPoint = mousePoint;
		update( );
	} else if( dragNode ) {
		auto point = mousePoint - offsetPoint;
		if( point.x( ) < 0 )
			point.setX( 0 );
		if( point.y( ) < 0 )
			point.setY( 0 );
		dragNode->move( point );
		update( );
	}
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( getPointNodeClickInfo( event->pos( ), *clickInfoPtr ) ) {
				dragNode = clickInfoPtr->getClickNode( );
				if( dragNode )
					ensureVisible( dragNode );
				switch( clickInfoPtr->getClickType( ) ) {
					case NodeEnum::NodeClickType::InputPort :
						if( selectOutputPort == nullptr )
							break;
						selectInputPort = clickInfoPtr->getInputPort( );
						break;
					case NodeEnum::NodeClickType::OutputPort :
						if( selectInputPort == nullptr )
							break;
						selectOutputPort = clickInfoPtr->getOutputPort( );
						break;
				}
			}
			break;
		case Qt::RightButton :
			nodeDirector->showNodeWidgeInfo( nullptr );
			if( getPointNodeClickInfo( event->pos( ), *clickInfoPtr ) ) {
				dragNode = clickInfoPtr->getClickNode( );
				if( dragNode )
					ensureVisible( dragNode );
				switch( clickInfoPtr->getClickType( ) ) {
					case NodeEnum::NodeClickType::None :
					case NodeEnum::NodeClickType::Titile :
						// todo 弹出菜单
						//dragNode->getRemoveMenu( )->popup( mapToGlobal( event->pos( ) ) );
						break;
					case NodeEnum::NodeClickType::InputPort :
						clickInfoPtr->getInputPort( )->getDisLinkMenu( )->popup( mapToGlobal( event->pos( ) ) );
						break;
					case NodeEnum::NodeClickType::OutputPort :
						clickInfoPtr->getOutputPort( )->getDisLinkMenu( )->popup( mapToGlobal( event->pos( ) ) );
						break;
				}
			} else {
				normalGenerateNodeMenu->popup( mapToGlobal( event->pos( ) ) );
			}
			break;
		case Qt::MiddleButton :
			break;
	}
	if( selectInputPort != nullptr && selectOutputPort != nullptr )
		nodeDirector->linkPort( selectOutputPort, selectInputPort );

	clickInfoPtr->clear( );
	dragNode = nullptr;
	selectInputPort = nullptr;
	selectOutputPort = nullptr;
}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	if( isDrawLine == true )
		painter.drawLine( startPoint, endPoint );
	nodeDirector->drawLinkLines( painter );
	nodeDirector->drawLinkLines( painter );
}
