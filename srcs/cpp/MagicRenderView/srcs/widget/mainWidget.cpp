#include "mainWidget.h"

#include <QMenu>
#include <QClipboard>
#include <QResizeEvent>
#include <qdatetime.h>

#include "drawLinkWidget.h"
#include "drawNodeWidget.h"
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
#include "drawHighlightWidget.h"

MainWidget::MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), mainWidgetScrollArea( parent ), selectInputPort( nullptr ), selectOutputPort( nullptr ), dragNode( nullptr ), oldSelectNode( nullptr ) {
	clickInfoPtr = new NodeClickInfo( NodeEnum::NodeClickType::None, nullptr, nullptr, nullptr );
	drawHighlightWidget = new DrawHighlightWidget( this );
	drawLinkWidget = new DrawLinkWidget( this );
	drawNodeWidget = new DrawNodeWidget( this );
	oldClickTime = new QDateTime;
}
MainWidget::~MainWidget( ) {
	emit release_signal( this );
	delete drawLinkWidget;
	delete drawHighlightWidget;
	delete drawNodeWidget;
	delete clickInfoPtr;
}
bool MainWidget::addNode( Node *node_ref_link_info ) {
	if( drawNodeWidget->addNode( node_ref_link_info ) == false )
		return false;
	return true;
}
bool MainWidget::ensureVisible( Node *target ) {
	if( target->parent( ) != drawNodeWidget )
		return false;
	auto point = target->pos( );
	auto toGlobal = drawNodeWidget->mapToGlobal( point );
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

	if( drawNodeWidget->init( this ) == false )
		return false;
	if( drawHighlightWidget->init( this ) == false )
		return false;
	if( drawLinkWidget->init( this ) == false )
		return false;
	drawNodeWidget->raise( );
	drawHighlightWidget->raise( );
	drawLinkWidget->raise( );
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
	point = drawNodeWidget->mapFromGlobal( point );
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
	QSize newCurrentSize = this->size( );
	drawNodeWidget->resize( newCurrentSize );
	drawLinkWidget->resize( newCurrentSize );
	drawHighlightWidget->resize( newCurrentSize );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	auto clickPoint = event->pos( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( drawNodeWidget->getPointNodeClickInfo( clickPoint, *clickInfoPtr ) ) {
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
						drawLinkWidget->drawBegin( drawLinkWidget->mapFromGlobal( selectInputPort->getLinkPoint( ) ) );
						dragNode = nullptr;
						break;
					case NodeEnum::NodeClickType::OutputPort :
						selectOutputPort = clickInfoPtr->getOutputPort( );
						drawLinkWidget->drawBegin( drawLinkWidget->mapFromGlobal( selectOutputPort->getLinkPoint( ) ) );
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
	if( drawLinkWidget->isDrawLine ) {
		drawLinkWidget->endPoint = mousePoint;
		drawLinkWidget->update( );
	} else if( dragNode ) {
		auto point = mousePoint - offsetPoint;
		if( point.x( ) < 0 )
			point.setX( 0 );
		if( point.y( ) < 0 )
			point.setY( 0 );
		dragNode->move( point );
		drawLinkWidget->update( );
		drawHighlightWidget->update( );
	}
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( drawNodeWidget->getPointNodeClickInfo( event->pos( ), *clickInfoPtr ) ) {
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
			if( drawNodeWidget->getPointNodeClickInfo( event->pos( ), *clickInfoPtr ) ) {
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
				drawNodeWidget->menuPopPoint = mapToGlobal( event->pos( ) );
				normalGenerateNodeMenu->popup( drawNodeWidget->menuPopPoint );
			}
			break;
		case Qt::MiddleButton :
			break;
	}
	if( selectInputPort != nullptr && selectOutputPort != nullptr )
		nodeDirector->linkPort( selectOutputPort, selectInputPort );
	if( drawLinkWidget->isDrawLine ) {
		drawLinkWidget->isDrawLine = false;
		drawLinkWidget->update( );
	}

	clickInfoPtr->clear( );
	dragNode = nullptr;
	selectInputPort = nullptr;
	selectOutputPort = nullptr;
}
