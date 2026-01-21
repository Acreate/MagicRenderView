#include "downloadPathInfoNode.h"

#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QStandardPaths>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../tools/pathTools.h"

Def_Entity_NodeTypeName_Function( DownloadPathInfoNode, Node::tr( "路径/用户下载文件目录" ) );

DownloadPathInfoNode::DownloadPathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathPtr = nullptr;
}
bool DownloadPathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, pathOutputPortPtr, pathPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool DownloadPathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool DownloadPathInfoNode::readyNodeRunData( ) {
	*pathPtr = QStandardPaths::writableLocation( QStandardPaths::DownloadLocation );
	return true;
}
bool DownloadPathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
