#include "mainWidget.h"

#include <QMenu>
#include <QResizeEvent>

#include "drawLinkWidget.h"
#include "drawNodeWidget.h"
#include "mainWidgetScrollArea.h"

#include "../app/application.h"

#include "../director/nodeDirector.h"

#include "../node/node/node.h"
#include "../node/port/inputPort/inputPort.h"
#include "../node/port/outputPort/outputPort.h"

#include "../win/mainWindow.h"

MainWidget::MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), mainWidgetScrollArea( parent ), drawLinkWidget( nullptr ), drawNodeWidget( nullptr ), clickInfoPtr( nullptr ), selectInputPort( nullptr ), selectOutputPort( nullptr ) {

}
MainWidget::~MainWidget( ) {
	if( drawLinkWidget )
		delete drawLinkWidget;
	if( drawNodeWidget )
		delete drawNodeWidget;
	if( clickInfoPtr )
		delete clickInfoPtr;
}
bool MainWidget::addNode( NodeRefLinkInfo *node_ref_link_info ) {
	if( drawNodeWidget->addNode( node_ref_link_info->getCurrentNode( ) ) == false )
		return false;
	NodeRefLinkInfoTools::setDrawLinkWidget( node_ref_link_info, drawLinkWidget );
	NodeRefLinkInfoTools::setDrawNodeWidget( node_ref_link_info, drawNodeWidget );
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
	if( oldW == fromGlobalX && oldH == fromGlobalY )
		return true;
	setMinimumSize( fromGlobalX, fromGlobalY );
	mainWidgetScrollArea->ensureVisible( fromGlobalX, fromGlobalY );
	return true;
}
bool MainWidget::init( ) {
	if( drawLinkWidget )
		delete drawLinkWidget;
	if( drawNodeWidget )
		delete drawNodeWidget;
	if( clickInfoPtr )
		delete clickInfoPtr;
	clickInfoPtr = new NodeClickInfo( NodeEnum::NodeClickType::None, nullptr, nullptr, nullptr );
	drawLinkWidget = new DrawLinkWidget( this );
	drawNodeWidget = new DrawNodeWidget( this );
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
	mainWindow = appInstancePtr->getMainWindow( );
	nodeCreateMenu = nodeDirector->getNodeCreateMenu( );
	return true;
}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto newSize = event->size( );
	drawNodeWidget->resize( newSize );
	drawLinkWidget->resize( newSize );
	drawNodeWidget->raise( );
	drawLinkWidget->raise( );
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
					case NodeEnum::NodeClickType::Titile :
						offsetPoint = dragNode->mapFromParent( clickPoint );
						break;
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
			}
			break;
		case Qt::MiddleButton :
			break;
	}
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	auto mousePoint = event->pos( );
	if( drawLinkWidget->isDrawLine )
		drawLinkWidget->endPoint = mousePoint;
	else if( dragNode ) {
		auto point = mousePoint - offsetPoint;
		if( point.x( ) < 0 )
			point.setX( 0 );
		if( point.y( ) < 0 )
			point.setY( 0 );
		dragNode->move( point );
	}
	drawLinkWidget->update( );
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
			drawNodeWidget->menuPopPoint = mapToGlobal( event->pos( ) );
			nodeCreateMenu->popup( drawNodeWidget->menuPopPoint );
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
