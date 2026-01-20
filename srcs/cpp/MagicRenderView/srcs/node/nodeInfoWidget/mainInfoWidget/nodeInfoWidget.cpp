#include "nodeInfoWidget.h"

#include <QPainter>
#include <QMenuBar>
#include <qcoreevent.h>
#include <QScrollBar>

#include "../../../app/application.h"
#include "../../../director/nodeDirector.h"
#include "../../../director/varDirector.h"
#include "../../node/node.h"
#include "../bottomTool/bottomNodeInfoTool.h"

#include "../title/nodeInfoTitle.h"
#include "editorNodeInfoScrollArea.h"

NodeInfoWidget::NodeInfoWidget( ) : editorNodeInfoScrollArea( nullptr ) {
	setMinimumSize( 100, 250 );
	varDirector = new VarDirector;
	hide( );
	titile = new NodeInfoTitle( this );
	bottomButtonTool = new BottomNodeInfoTool( this );
	connect( bottomButtonTool, &BottomNodeInfoTool::ok_signal, [this]( ) {
		this->okButtonEvent( );
		emit ok_signal( this, editorNodeInfoScrollArea );
	} );
	connect( bottomButtonTool, &BottomNodeInfoTool::cancel_signal, [this]( ) {
		this->cancelButtonEvent( );
		emit cancel_signal( this, editorNodeInfoScrollArea );
	} );

	showPosType = WidgetEnum::ShowType::Center;
}
NodeInfoWidget::~NodeInfoWidget( ) {
	emit release_signal( this );
	Node *currentNode;
	if( editorNodeInfoScrollArea ) {
		currentNode = editorNodeInfoScrollArea->getCurrentNode( );
		if( currentNode )
			callNodeReleaseInfoWidgetFunction( currentNode );
		delete editorNodeInfoScrollArea;
		editorNodeInfoScrollArea = nullptr;
	}
	delete varDirector;
}

void NodeInfoWidget::updateLayout( ) {
	int currentHeigth = this->height( );
	int currentWidget = this->width( );
	int bottomHeight = this->bottomButtonTool->height( );
	int titleHeight = this->titile->height( );
	this->bottomButtonTool->setFixedWidth( currentWidget );
	this->titile->setFixedWidth( currentWidget );
	int begWidgetHeight = currentHeigth - bottomHeight - titleHeight;
	currentHeigth = begWidgetHeight + titleHeight;
	this->bottomButtonTool->move( 0, currentHeigth );
	if( editorNodeInfoScrollArea ) {
		editorNodeInfoScrollArea->setFixedSize( currentWidget, begWidgetHeight );
		editorNodeInfoScrollArea->move( 0, titleHeight );
	}
}

bool NodeInfoWidget::checkNodeValid( Node *check_node_ptr ) {
	return false;
}
bool NodeInfoWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr == nullptr || editorNodeInfoScrollArea == nullptr || varDirector->init( ) == false )
		return false;
	if( editorNodeInfoScrollArea->initNode( check_node_ptr ) == false || check_node_ptr->initNodeInfoWidget( this ) == false )
		return false;
	titile->setTitleText( check_node_ptr->toQString( ) );
	return true;
}
Node * NodeInfoWidget::getNode( ) const {
	if( editorNodeInfoScrollArea == nullptr )
		return nullptr;
	return editorNodeInfoScrollArea->getCurrentNode( );
}
QString NodeInfoWidget::getTitleText( ) const {
	return titile->getTitleText( );
}
void NodeInfoWidget::callNodeReleaseInfoWidgetFunction( Node *call_node ) {
	Application::getInstancePtr( )->getNodeDirector( )->releaseBindNodeAtEditroNode( call_node, this );
}
void NodeInfoWidget::okButtonEvent( ) {
	hide( );
}
void NodeInfoWidget::cancelButtonEvent( ) {
	hide( );
}
bool NodeInfoWidget::event( QEvent *event ) {
	bool eventResult = QWidget::event( event );
	auto type = event->type( );
	switch( type ) {
		case QEvent::Resize :
			updateLayout( );
			break;
		case QEvent::Show :
			updateLayout( );
			emit show_signal( this );
			break;
		case QEvent::Hide :
			showPosType = WidgetEnum::ShowType::Center;
			emit hide_signal( this );
	}
	return eventResult;
}
void NodeInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
}
