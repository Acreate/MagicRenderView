#include "imageToGrayscaleNode.h"

#include <functional>
#include <qmetatype.h>
#include <node/node/node.h>
#include <node/node/processNode.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/inputPort/unity/imageInputPort.h"

ImageToGrayscaleNode::ImageToGrayscaleNode( const QString &node_name ) : ProcessNode( node_name ) {
	outImagePtr = nullptr;
}
bool ImageToGrayscaleNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendDynamicInputPortType( QImage, NodeEnum::PortType::Unity, tr( "图像" ), imageInputPortPtr );
		Def_AppendDynamicBindVarOutputPortType( QImage, NodeEnum::PortType::Unity, tr( "图像" ), imageOutputPortPtr, outImagePtr );
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
