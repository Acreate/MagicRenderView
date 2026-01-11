#include "toImageNode.h"

#include "../../../../../director/varDirector.h"
#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/imageOutputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

ToImageNode::ToImageNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool ToImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		anyVarInputPortPtr = appendInputPortType< AnyVarInputPort >( tr( "值" ) );
		if( anyVarInputPortPtr == nullptr )
			return false;
		imageOutputPortPtr = appendOutputPortType< ImageOutputPort >( tr( "图像" ) );
		if( imageOutputPortPtr == nullptr )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( imageOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToImageNode::readyNodeRunData( ) {
	*outVarPtr = QImage( );
	return true;
}
bool ToImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
