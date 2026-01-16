#include "imageInfoNode.h"

#include <app/application.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/inputPort/unity/imageInputPort.h"
#include "../../../../port/outputPort/unity/uIntOutputPort.h"

ImageInfoNode::ImageInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	width = nullptr;
	height = nullptr;
	fromat = nullptr;
}
bool ImageInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "图像" ), imageInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "宽度" ), widthOutputPortPtr, width ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "长度" ), heightOutputPortPtr, height ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "格式" ), fromatOutputPortPtr, fromat ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ImageInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {

	return true;
}
