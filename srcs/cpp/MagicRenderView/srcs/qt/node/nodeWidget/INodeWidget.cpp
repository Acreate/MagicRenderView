#include "./INodeWidget.h"

#include <QLabel>

#include "qt/widget/nodeGraph.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QTimer>

#include "../../application/application.h"

#include "qt/node/nodeComponent/INodeComponent.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"

INodeWidget::INodeWidget( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function, const std_vector< QString > &node_widget_name_s, const std_shared_ptr< IFunctionDeclaration > &function_declaration, QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ), nodeWidgetNames( node_widget_name_s ), getStackFunction( get_stack_function ) {
	if( !getStackFunction )
		getStackFunction = [] { return INodeStack::getStdSharedPtrInstance< BaseNodeStack >( ); };
	componentIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	nodeStack = getStackFunction( );
	mainBoxLayout = new QVBoxLayout( this );
	mainBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	mainBoxLayout->setSpacing( 0 );
	setAttribute( Qt::WA_InputMethodTransparent );
	title = new QLabel( this );
	mainBoxLayout->addWidget( title, 0, Qt::AlignHCenter );
}
void INodeWidget::connectNodeGraphWidget( NodeGraph *node_graph ) {
	connect( this, &INodeWidget::error, node_graph, &NodeGraph::error );
	connect( this, &INodeWidget::finish, node_graph, &NodeGraph::finish );
	connect( this, &INodeWidget::requestNodeWidgetID, node_graph, &NodeGraph::requestNodeWidgetID );
	connect( this, &INodeWidget::requestNodeWidgetAdviseID, node_graph, &NodeGraph::requestNodeWidgetAdviseID );
	connect( this, &INodeWidget::destroyed, [this]( ) {
		emit destoryNodeWidgetID( this );
	} );
}

INodeComponent * INodeWidget::getPosNodeComponent( const QPoint &pos ) const {
	auto childrenList = children( );
	INodeComponent *nodeComponent;
	for( auto child : childrenList ) {
		nodeComponent = qobject_cast< INodeComponent * >( child );
		if( nodeComponent ) {
			auto componentPos = pos - nodeComponent->pos( );
			auto component = nodeComponent->getPosNodeComponent( componentPos );
			if( component )
				return component;
		}
	}

	return nullptr;
}
bool INodeWidget::getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const {
	auto childrenList = children( );
	for( auto child : childrenList )
		if( component == child && component->getComponentLinkPos( component, resulut_pos ) ) {
			resulut_pos = pos( ) + resulut_pos;
			return true;
		}

	return false;
}
void INodeWidget::setNodoTitle( const QString &titile ) {
	setWindowTitle( titile );
	setObjectName( titile );
	title->setText( titile );
}
QString INodeWidget::getNodeTitle( ) const {
	return title->text( );
}
size_t INodeWidget::getID( ) const {
	return Application::getID( this );
}
size_t INodeWidget::getChildNodeCompoentID( const INodeComponent *node_component ) const {
	std_lock_grad_mutex lockGradMutex( *componentIDMutex );
	size_t count = componentID.size( );
	if( count == 0 )
		return 0;
	auto data = componentID.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first == node_component )
			return data[ index ].second;
	return 0;
}
INodeComponent * INodeWidget::getCompoent( const size_t &id ) const {
	std_lock_grad_mutex lockGradMutex( *componentIDMutex );
	size_t count = componentID.size( );
	if( count == 0 )
		return nullptr;
	auto data = componentID.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].second == id )
			return data[ index ].first;
	return 0;
}
void INodeWidget::registerIDFinish( size_t id ) {
	if( id == 0 )
		requestNodeWidgetID( this );
	else
		show( );
}
void INodeWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	/*QPainter painter( this );
	QPen pen;
	QBrush brush;
	pen.setWidth( 5 );
	pen.setColor( Qt::red );
	painter.setPen( pen );
	auto geometry = size( );
	painter.drawRect( QRect( 0, 0, geometry.width( ) - 1, geometry.height( ) - 1 ) );*/
}
