#include "imageInfoNode.h"

#include <app/application.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/inputPort/unity/imageInputPort.h"
#include "../../../../port/outputPort/unity/uIntOutputPort.h"

ImageInfoNode::ImageInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	width = nullptr;
	height = nullptr;
	fromat = nullptr;
}
bool ImageInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( appendInputPortType< >( tr( "输出" ), imageInputPortPtr ) == false )
			return false;
		if( appendOutputPortType< >( tr( "宽度" ), widthOutputPortPtr ) == false )
			return false;
		if( appendOutputPortType< >( tr( "长度" ), heightOutputPortPtr ) == false )
			return false;
		if( appendOutputPortType< >( tr( "格式" ), fromatOutputPortPtr ) == false )
			return false;
		if( width )
			varDirector->release( width );
		if( varDirector->create( width ) == false )
			return false;
		if( height )
			varDirector->release( height );
		if( varDirector->create( height ) == false )
			return false;
		if( fromat )
			varDirector->release( fromat );
		if( varDirector->create( fromat ) == false )
			return false;
		if( setPortVar( widthOutputPortPtr, width ) == false )
			return false;
		if( setPortVar( heightOutputPortPtr, height ) == false )
			return false;
		if( setPortVar( fromatOutputPortPtr, fromat ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ImageInfoNode::readyNodeRunData( ) {
	return true;
}
bool ImageInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	return true;
}
