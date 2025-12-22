#include "inputPort.h"

#include <QHBoxLayout>

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

#include "../../node/node.h"
#include <QLabel>
#include <QMenu>

#include "../../../srack/srackInfo.h"
#include "../outputPort/outputPort.h"
bool InputPort::emplaceBackOutputPortRef( OutputPort *output_port_ptr ) {
	size_t count = refOutputPortVector.size( );
	auto arrayPtr = refOutputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == output_port_ptr )
			return true;
	refOutputPortVector.emplace_back( output_port_ptr );
	emit connect_input_port_signal( this, output_port_ptr );
	output_port_ptr->emplaceBackInputPortRef( this );
	return true;
}
bool InputPort::eraseOutputPortRef( OutputPort *output_port_ptr ) {
	size_t count = refOutputPortVector.size( );
	auto arrayPtr = refOutputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == output_port_ptr ) {
			refOutputPortVector.erase( refOutputPortVector.begin( ) + index );
			emit dis_connect_input_port_signal( this, output_port_ptr );
			output_port_ptr->eraseInputPortRef( this );
			return true;
		}
	return false;
}
void InputPort::clearOutputPortRef( ) {
	size_t count = refOutputPortVector.size( );
	for( size_t index = 0; index < count; ++index ) {
		auto vectorIterator = refOutputPortVector.begin( );
		refOutputPortVector.erase( vectorIterator );
		auto outputPort = *vectorIterator;
		emit dis_connect_input_port_signal( this, outputPort );
		outputPort->eraseInputPortRef( this );
	}
}
InputPort::InputPort( const QString &name ) : portName( name ), varPtr( nullptr ) {
	ico = new QLabel( this );
	QImage image( ":/nodeitemIco/info_node.png" );
	ico->setPixmap( QPixmap::fromImage( image ) );
	showTitle = new QLabel( this );
	showTitle->setText( portName );

	mainLayout = new QHBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( ico );
	mainLayout->addWidget( showTitle );
	disLinkMenu = new QMenu;
}
bool InputPort::init( Node *parent ) {
	if( parent == nullptr )
		return false;
	disLinkMenu->clear( );
	instancePtr = Application::getInstancePtr( );
	varDirector = instancePtr->getVarDirector( );
	setParent( parent );
	parentNode = parent;
	return true;
}
InputPort::~InputPort( ) {
	emit release_node_signal( this, Create_SrackInfo( ) );
	clearOutputPortRef( );
	delete disLinkMenu;
}
bool InputPort::hasOutputPortRef( const OutputPort *output_port_ptr ) const {
	size_t count = refOutputPortVector.size( );
	if( count == 0 )

		return false;
	auto outputPortArray = refOutputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( outputPortArray[ index ] == output_port_ptr )
			return true;
	return false;

}
QPoint InputPort::getLinkPoint( ) const {
	return ico->mapToGlobal( ico->contentsRect( ).center( ) );
}
QMenu * InputPort::getDisLinkMenu( ) const {
	// todo : 重构断开链接菜单
	return disLinkMenu;
}
void InputPort::paintEvent( QPaintEvent *event ) {
	//QWidget::paintEvent( event );
}
bool InputPort::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Paint :
			return true;
	}
	return QWidget::event( event );
}
