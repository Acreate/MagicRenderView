#include "outputPort.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

#include "../../../srack/srackInfo.h"

#include "../../node/node.h"

#include "../inputPort/inputPort.h"

bool OutputPort::emplaceBackInputPortRef( InputPort *input_port_ptr ) {
	size_t count = refInputPortVector.size( );
	auto arrayPtr = refInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == input_port_ptr )
			return true;
	refInputPortVector.emplace_back( input_port_ptr );
	emit connect_output_port_signal( this, input_port_ptr );
	input_port_ptr->emplaceBackOutputPortRef( this );
	return true;
}
bool OutputPort::eraseInputPortRef( InputPort *input_port_ptr ) {
	size_t count = refInputPortVector.size( );
	auto arrayPtr = refInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == input_port_ptr ) {
			refInputPortVector.erase( refInputPortVector.begin( ) + index );
			emit dis_connect_output_port_signal( this, input_port_ptr );
			input_port_ptr->eraseOutputPortRef( this );
			return true;
		}
	return false;
}
void OutputPort::clearInputPortRef( ) {
	size_t count = refInputPortVector.size( );
	for( size_t index = 0; index < count; ++index ) {
		auto vectorIterator = refInputPortVector.begin( );
		auto inputPort = *vectorIterator;
		refInputPortVector.erase( vectorIterator );
		emit dis_connect_output_port_signal( this, inputPort );
		inputPort->eraseOutputPortRef( this );
	}
}
OutputPort::OutputPort( const QString &name ) : portName( name ), varPtr( nullptr ) {
	ico = new QLabel( this );
	QImage image( ":/nodeitemIco/info_node.png" );
	ico->setPixmap( QPixmap::fromImage( image ) );
	showTitle = new QLabel( this );
	showTitle->setText( portName );
	mainLayout = new QHBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( showTitle );
	mainLayout->addWidget( ico );
	disLinkMenu = new QMenu;
}
OutputPort::~OutputPort( ) {
	emit release_node_signal( this, Create_SrackInfo( ) );
	size_t count = refInputPortVector.size( );
	for( size_t index = 0; index < count; ++index ) {
		auto inputPort = refInputPortVector.begin( );
		auto removeInputPort = *inputPort;
		refInputPortVector.erase( inputPort + index );
		emit dis_connect_output_port_signal( this, removeInputPort );
		removeInputPort->eraseOutputPortRef( this );
	}
	delete disLinkMenu;
}
bool OutputPort::init( Node *parent ) {
	if( parent == nullptr )
		return false;
	instancePtr = Application::getInstancePtr( );
	varDirector = instancePtr->getVarDirector( );
	setParent( parent );
	parentNode = parent;
	disLinkMenu->clear( );
	return true;
}
QPoint OutputPort::getLinkPoint( ) const {
	return ico->mapToGlobal( ico->contentsRect( ).center( ) );
}
QMenu * OutputPort::getDisLinkMenu( ) const {
	// todo : 重构删除链接菜单
	return disLinkMenu;
}
void OutputPort::paintEvent( QPaintEvent *event ) {
	//QWidget::paintEvent( event );
}
bool OutputPort::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Paint :
			return true;
	}
	return QWidget::event( event );
}
