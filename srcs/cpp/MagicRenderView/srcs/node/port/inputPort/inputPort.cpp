#include "inputPort.h"

#include <QHBoxLayout>

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

#include "../../node/node.h"
#include <QLabel>
#include <QMenu>
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
	delete disLinkMenu;
}
QPoint InputPort::getLinkPoint( ) const {
	return ico->mapToGlobal( ico->contentsRect( ).center( ) );
}
