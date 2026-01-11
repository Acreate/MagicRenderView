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
	VarDirector *varDirector;
	size_t index = 0;
	std::vector< InputPort * >::iterator vectorIterator;
	InputPort *inputPort;
	for( ; index < count; ++index ) {
		vectorIterator = refInputPortVector.begin( );
		inputPort = *vectorIterator;
		refInputPortVector.erase( vectorIterator );
		emit dis_connect_output_port_signal( this, inputPort );
		inputPort->eraseOutputPortRef( this );
	}
	if( varPtr ) {
		varDirector = parentNode->getVarDirector( );
		if( varDirector )
			varDirector->release( varPtr );
	}
}
bool OutputPort::bindPortInfo( ) {
	auto varDirector = getVarDirector( );
	if( varDirector == nullptr )
		return false;
	if( varDirector->create( varTypeName, varPtr ) == false )
		return false;
	return true;
}
bool OutputPort::releasePortInfo( ) {
	if( varPtr == nullptr )
		return true;
	auto varDirector = getVarDirector( );
	if( varDirector )
		return varDirector->release( varPtr );
	return false;
}
OutputPort::OutputPort( const QString &name ) : portName( name ) {
	generateCode = 0;
	multiple = true;
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
}
OutputPort::~OutputPort( ) {
	emit release_node_signal( this, Create_SrackInfo( ) );
	clearInputPortRef( );
}
bool OutputPort::hasInputPortRef( InputPort *input_port_ptr ) const {
	size_t count = refInputPortVector.size( );
	if( count == 0 )
		return false;
	auto inputPortArray = refInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( inputPortArray[ index ] == input_port_ptr )
			return true;
	return false;
}
bool OutputPort::init( Node *parent ) {
	if( parent == nullptr )
		return false;
	setParent( parent );
	parentNode = parent;
	return true;
}
QPoint OutputPort::getLinkPoint( ) const {
	return ico->mapToGlobal( ico->contentsRect( ).center( ) );
}

VarDirector * OutputPort::getVarDirector( ) const {
	if( varDirectorPtr )
		return varDirectorPtr;
	if( parentNode )
		return parentNode->getVarDirector( );
	return nullptr;
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
