#include "fontsPathInfoNode.h"

#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QStandardPaths>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../tools/pathTools.h"

Def_Entity_NodeTypeName_Function( FontsPathInfoNode, Node::tr( "路径/用户字体目录" ) );

FontsPathInfoNode::FontsPathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathPtr = nullptr;
}
bool FontsPathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, pathOutputPortPtr, pathPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FontsPathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool FontsPathInfoNode::readyNodeRunData( ) {
	*pathPtr = QStandardPaths::writableLocation( QStandardPaths::FontsLocation );
	return true;
}
bool FontsPathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
