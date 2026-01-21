#include "statePathInfoNode.h"

#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QStandardPaths>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../tools/pathTools.h"

Def_Entity_NodeTypeName_Function( StatePathInfoNode, Node::tr( "路径/用户特定程序状态数据文件目录" ) );

StatePathInfoNode::StatePathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathPtr = nullptr;
}
bool StatePathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, pathOutputPortPtr, pathPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StatePathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool StatePathInfoNode::readyNodeRunData( ) {
	*pathPtr = QStandardPaths::writableLocation( QStandardPaths::StateLocation );
	return true;
}
bool StatePathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
