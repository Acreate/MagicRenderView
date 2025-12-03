#include "inputportLinkOutputPortInfo.h"
InputportLinkOutputPortInfo::InputportLinkOutputPortInfo( InputPort *input_port ) : inputPort( input_port ) { }
bool InputportLinkOutputPortInfo::appendOutputPort( OutputPort *output_port ) {
	size_t count = outputPortVector.size( );
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ] == output_port )
			return true;
	outputPortVector.emplace_back( output_port );
	return true;
}
bool InputportLinkOutputPortInfo::removeOutputPort( OutputPort *output_port ) {
	size_t count = outputPortVector.size( );
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ] == output_port ) {
			outputPortVector.erase( outputPortVector.begin( ) + index );
			return true;
		}
	return false;
}
size_t InputportLinkOutputPortInfo::linkInputPortCount( ) const {
	return outputPortVector.size( );
}
