#include "scrollNodeGraph.h"

#include <qt/widget/nodeGraph.h>
ScrollNodeGraph::ScrollNodeGraph( QWidget *parent ): QScrollArea( parent ) {
	nodeGraph = new NodeGraph( this );
	setWidget( nodeGraph );
	setWidgetResizable( true );
}
ScrollNodeGraph::~ScrollNodeGraph( ) {
}
size_t ScrollNodeGraph::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	return nodeGraph->serializeToObjectData( read_data_vector, data_count );
}
bool ScrollNodeGraph::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	return nodeGraph->serializeToVectorData( result_data_vector );
}
