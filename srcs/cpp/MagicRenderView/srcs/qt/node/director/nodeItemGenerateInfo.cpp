#include "nodeItemGenerateInfo.h"

#include <qt/varType/I_Type.h>

NodeItemGenerateInfo::NodeItemGenerateInfo( const QString &dir_name, const QString &node_name, const std_shared_ptr<I_Type> &create_type_instance_ptr ): dirName( dir_name ),
	nodeName( node_name ),
	createTypeInstancePtr( create_type_instance_ptr ) { }
NodeItemGenerateInfo::~NodeItemGenerateInfo( ) {
	emit releaseThis( this );
}
NodeItem * NodeItemGenerateInfo::createNodeItem( const QString &dir_name, const QString &node_name ) {
	bool cond = dirName == dir_name && nodeName == node_name;
	if( cond == true )
		return ( NodeItem * ) createTypeInstancePtr.get( )->getCreate( ).operator()( );
	return nullptr;
}
