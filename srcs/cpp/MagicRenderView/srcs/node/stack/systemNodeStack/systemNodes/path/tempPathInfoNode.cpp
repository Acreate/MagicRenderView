#include "tempPathInfoNode.h"

#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QStandardPaths>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../tools/pathTools.h"

Def_Entity_NodeTypeName_Function( TempPathInfoNode, Node::tr( "路径/存储临时文件目录" ) );

TempPathInfoNode::TempPathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathPtr = nullptr;
}
bool TempPathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, pathOutputPortPtr, pathPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool TempPathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool TempPathInfoNode::readyNodeRunData( ) {
	*pathPtr = QStandardPaths::writableLocation( QStandardPaths::TempLocation );
	return true;
}
bool TempPathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
