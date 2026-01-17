#include "cachePathInfoNode.h"

#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QStandardPaths>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../tools/pathTools.h"

CachePathInfoNode::CachePathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathPtr = nullptr;
}
bool CachePathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		auto nodeTypeName = getVirtualNodeTypeName( );
		auto separatorSplitPath = pathTools::normalPathSeparatorSplitPath( nodeTypeName );
		qint64 count = separatorSplitPath.size( );
		if( count > 0 )
			nodeTypeName = separatorSplitPath.last( );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, pathOutputPortPtr, pathPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool CachePathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool CachePathInfoNode::readyNodeRunData( ) {
	*pathPtr = QStandardPaths::writableLocation( QStandardPaths::AppConfigLocation );
	return true;
}
bool CachePathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
