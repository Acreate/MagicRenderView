#include "outputPort.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

#include "../../../srack/srackInfo.h"

#include "../../node/node.h"

#include "../inputPort/inputPort.h"

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
