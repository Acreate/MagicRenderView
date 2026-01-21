#include "imageToGrayscaleNode.h"

#include <director/varDirector.h>

#include <enums/nodeEnum.h>
#include <node/nodeTools/nodeTools.h>

#include "../../../../../port/inputPort/dynamicTypeInputPort.h"
#include "../../../../../port/outputPort/dynamicTypeOutputPort.h"

Def_Entity_NodeTypeName_Function( ImageToGrayscaleNode, Node::tr( "转换/图像/转灰度" ) );

ImageToGrayscaleNode::ImageToGrayscaleNode( const QString &node_name ) : ProcessNode( node_name ) {
	outImagePtr = nullptr;
}
bool ImageToGrayscaleNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendDynamicInputPortType< QImage >( this, NodeEnum::PortType::Unity, tr( "图像" ), imageInputPortPtr ) == false )
			return false;

		if( nodeToolsPtr->appendDynamicOutputPortType< >( this, NodeEnum::PortType::Unity, tr( "图像" ), imageOutputPortPtr, outImagePtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageToGrayscaleNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ImageToGrayscaleNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
