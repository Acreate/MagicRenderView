#include "genericConfigPathInfoNode.h"

#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QStandardPaths>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../tools/pathTools.h"

Def_Entity_NodeTypeName_Function( GenericConfigPathInfoNode, Node::tr( "路径/应用程序共享配置目录" ) );

GenericConfigPathInfoNode::GenericConfigPathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathPtr = nullptr;
}
bool GenericConfigPathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, pathOutputPortPtr, pathPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool GenericConfigPathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool GenericConfigPathInfoNode::readyNodeRunData( ) {
	*pathPtr = QStandardPaths::writableLocation( QStandardPaths::GenericConfigLocation );
	return true;
}
bool GenericConfigPathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
