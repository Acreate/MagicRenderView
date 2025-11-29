#include "inputPort.h"

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

InputPort::InputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QWidget *parent ) : QWidget( parent ), instancePtr( instance_ptr ), varDirector( var_director ), name( name ), node( node ) { }
InputPort::~InputPort( ) {
	emit release_node_signal( this );
}
