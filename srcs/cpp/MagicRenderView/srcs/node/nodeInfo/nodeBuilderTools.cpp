#include "nodeBuilderTools.h"

#include "nodeRefLinkInfo.h"

#include "../../app/application.h"

#include "../../director/printerDirector.h"

#include "../../srack/srackInfo.h"

void NodeBuilderTools::analysisSubNodeRef( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector< NodeRefLinkInfo * > &result_node_ref_link_vector ) {
	std::vector< NodeRefLinkInfo * > subNodeRefLinkInfoVector;
	size_t count;
	size_t index;
	size_t exisCount;
	size_t exisIndex;
	NodeRefLinkInfo **nodeRefLinkInfoArrayPtr;
	NodeRefLinkInfo **exisNodeRefArrayPtr;
	exisCount = result_node_ref_link_vector.size( );
	exisNodeRefArrayPtr = result_node_ref_link_vector.data( );
	for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
		if( exisNodeRefArrayPtr[ exisIndex ] == analysis_node_ref_link_info )
			break;
	if( exisIndex == exisCount )
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );

	count = analysis_node_ref_link_info->refInputVector.size( );
	nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refInputVector.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == nodeRefLinkInfoArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeRefLinkInfoVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
	}

	count = analysis_node_ref_link_info->refOutputVector.size( );
	nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refOutputVector.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == nodeRefLinkInfoArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeRefLinkInfoVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
	}

	count = subNodeRefLinkInfoVector.size( );
	nodeRefLinkInfoArrayPtr = subNodeRefLinkInfoVector.data( );
	for( index = 0; index < count; ++index )
		analysisSubNodeRef( nodeRefLinkInfoArrayPtr[ index ], result_node_ref_link_vector );
}
bool NodeBuilderTools::analysisNodeRef( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector< NodeRefLinkInfo * > &result_node_ref_link_vector ) {
	if( analysis_node_ref_link_info == nullptr )
		return false;

	std::vector< NodeRefLinkInfo * > subNodeRefLinkInfoVector;

	size_t count;
	size_t index;
	size_t exisCount;
	size_t exisIndex;
	NodeRefLinkInfo **nodeRefLinkInfoArrayPtr;
	NodeRefLinkInfo **exisNodeRefArrayPtr;
	exisCount = result_node_ref_link_vector.size( );
	exisNodeRefArrayPtr = result_node_ref_link_vector.data( );
	for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
		if( exisNodeRefArrayPtr[ exisIndex ] == analysis_node_ref_link_info )
			break;
	if( exisIndex == exisCount )
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );

	count = analysis_node_ref_link_info->refInputVector.size( );
	nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refInputVector.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == nodeRefLinkInfoArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeRefLinkInfoVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
	}

	count = analysis_node_ref_link_info->refOutputVector.size( );
	nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refOutputVector.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == nodeRefLinkInfoArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeRefLinkInfoVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
	}

	count = subNodeRefLinkInfoVector.size( );
	nodeRefLinkInfoArrayPtr = subNodeRefLinkInfoVector.data( );
	for( index = 0; index < count; ++index )
		analysisSubNodeRef( nodeRefLinkInfoArrayPtr[ index ], result_node_ref_link_vector );
	count = result_node_ref_link_vector.size( );
	if( count == 0 )
		return false;
	nodeRefLinkInfoArrayPtr = result_node_ref_link_vector.data( );
	auto converQString = toQString( nodeRefLinkInfoArrayPtr, count );
	auto printerDirector = Application::getInstancePtr( )->getPrinterDirector( );
	printerDirector->info( converQString, Create_SrackInfo( ) );
	count = filterRepetition( nodeRefLinkInfoArrayPtr, count );
	result_node_ref_link_vector.resize( count );
	return true;
}
size_t NodeBuilderTools::filterRepetition( NodeRefLinkInfo **check_array_ptr, const size_t &check_array_count ) {
	size_t maxCount = check_array_count;
	return maxCount;
}
QString NodeBuilderTools::toQString( NodeRefLinkInfo **check_array_ptr, const size_t &check_array_count ) {
	QStringList result;
	result.append( "{" );
	for( size_t index = 0; index < check_array_count; ++index )
		result.append( check_array_ptr[ index ]->currentNode->toQString( ) + ", " );

	result.append( "};" );
	return result.join( "\n" );
}
