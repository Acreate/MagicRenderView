#include "outputPort.h"

#include "../../../director/varDirector.h"

#include "../inputPort/inputPort.h"
OutputPort::OutputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent ) : QObject( parent ), instancePtr( instance_ptr ), varDirector( var_director ), name( name ), node( node ) { }
OutputPort::~OutputPort( ) {
	emit release_node_signal( this );
}