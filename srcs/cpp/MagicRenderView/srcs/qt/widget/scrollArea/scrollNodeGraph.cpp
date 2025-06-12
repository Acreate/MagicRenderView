#include "scrollNodeGraph.h"

#include <qt/widget/nodeGraph.h>
ScrollNodeGraph::ScrollNodeGraph( QWidget *parent ): QScrollArea( parent ) {
	nodeGraph = new NodeGraph( this );
	setWidget( nodeGraph );
	setWidgetResizable( true );
}
ScrollNodeGraph::~ScrollNodeGraph( ) {
}
size_t ScrollNodeGraph::serializeToObjectData( const std_vector< uchar > &read_data_vector ) const {
	return nodeGraph->serializeToObjectData( read_data_vector );
}
bool ScrollNodeGraph::serializeToVectorData( std_vector< uchar > *result_data_vector ) const {
	return nodeGraph->serializeToVectorData( result_data_vector );
}
