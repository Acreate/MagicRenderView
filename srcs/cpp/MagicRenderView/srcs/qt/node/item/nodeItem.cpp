#include "./nodeItem.h"
Imp_StaticMetaInfo( NodeItem, QObject::tr( "NodeItem" ), QObject::tr( "item" ) )
bool NodeItem::appendInputProt( NodeInputPort *input_prot ) {
	nodeInputProtVector.emplace_back( input_prot );
	return true;
}
bool NodeItem::removeInputProt( NodeInputPort *input_prot ) {
	size_t count = nodeInputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ] == input_prot ) {
			nodeInputProtVector.erase( nodeInputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeItem::appendOutputProt( NodeOutputPort *output_prot ) {

	nodeOutputProtVector.emplace_back( output_prot );
	return true;
}
bool NodeItem::removeOutputProt( NodeOutputPort *output_port ) {

	size_t count = nodeOutputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ] == output_port ) {
			nodeOutputProtVector.erase( nodeOutputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
void NodeItem::updateProtLayout( ) {

}
