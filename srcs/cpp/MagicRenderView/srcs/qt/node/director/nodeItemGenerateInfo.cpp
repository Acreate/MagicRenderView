#include "nodeItemGenerateInfo.h"

#include <qt/varType/I_Type.h>

NodeItemGenerateInfo::~NodeItemGenerateInfo( ) {
	emit releaseThis( this );
}
NodeItem * NodeItemGenerateInfo::createNodeItem( const QString &dir_name, const QString &node_name ) {
	bool cond = dirName == dir_name && nodeName == node_name;
	if( cond == true )
		return ( NodeItem * ) createTypeInstancePtr.get( )->getCreate( ).operator()( );
	return nullptr;
}
