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
bool NodeBuilderTools::findRefBeginNode( NodeRefLinkInfo *analysis_node_ref_link_info, NodeRefLinkInfo *&result_begin_node_ref_link ) {
	size_t count = analysis_node_ref_link_info->refInputVector.size( );
	auto nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( nodeRefLinkInfoArrayPtr[ index ]->currentNode->getNodeType( ) == NodeEnum::NodeType::Begin ) {
			result_begin_node_ref_link = nodeRefLinkInfoArrayPtr[ index ];
			return true;
		}
	for( index = 0; index < count; ++index )
		if( findRefBeginNode( nodeRefLinkInfoArrayPtr[ index ], result_begin_node_ref_link ) )
			return true;
	return false;
}
size_t NodeBuilderTools::filterRepetition( NodeRefLinkInfo **check_array_ptr, const size_t &check_array_count ) {
	size_t maxCount = check_array_count;
	return maxCount;
}
bool NodeBuilderTools::sortProcessNodeRefArray( NodeRefLinkInfo **sort_array_ptr, const size_t &sort_array_count ) {
	PrinterDirector *printerDirector = Application::getInstancePtr( )->getPrinterDirector( );

	QString msg = toQString( sort_array_ptr, sort_array_count );
	printerDirector->info( "开始排序 : " + msg, Create_SrackInfo( ) );
	if( sort_array_count < 2 )
		return true;
	if( sort_array_ptr == nullptr )
		return false;
	// 实现排序下标
	std::vector< NodeRefLinkInfo * > overArraySort;
	std::vector< NodeRefLinkInfo * > standbyArraySort;
	std::vector< NodeRefLinkInfo * > buffArraySort;
	// 当前访问下标
	size_t index;
	// 备用排序数量
	size_t standbyArrayCount;
	// 备用排序序列基址
	NodeRefLinkInfo **standbyArrayptr;
	// 排序完毕的数量
	size_t overArrayCount;
	// 访问排序完毕的数组下标
	size_t overArrayIndex;
	// 排序完毕的序列起始地址
	NodeRefLinkInfo **overArrayptr;
	// 引用输入序列个数
	size_t standbyRefInputArrayCount;
	// 引用序列基址
	NodeRefLinkInfo **standbyRefInputArrayPtr;
	// 引用序列访问下标
	size_t standbyRefInputArrayIndex;
	// 匹配的输入引用节点指针
	NodeRefLinkInfo *compNodeRefPtr;
	// 发现依赖为 begin 节点
	for( index = 0; index < sort_array_count; ++index ) {
		standbyRefInputArrayCount = sort_array_ptr[ index ]->refInputVector.size( );
		standbyRefInputArrayPtr = sort_array_ptr[ index ]->refInputVector.data( );
		for( standbyRefInputArrayIndex = 0; standbyRefInputArrayIndex < standbyRefInputArrayCount; ++standbyRefInputArrayIndex ) {
			compNodeRefPtr = standbyRefInputArrayPtr[ standbyRefInputArrayIndex ];
			if( compNodeRefPtr->currentNode->getNodeType( ) == NodeEnum::NodeType::Begin )
				continue; // 引用到开始节点，则不需检查
			// 引用到非开始节点，则二次检查引用
			standbyArraySort.emplace_back( sort_array_ptr[ index ] );
			break;
		}
		// 把单纯引用到开始节点的节点存放到已经排序上
		if( standbyRefInputArrayIndex == standbyRefInputArrayCount )
			overArraySort.emplace_back( sort_array_ptr[ index ] );
	}
	overArrayCount = overArraySort.size( );

	printerDirector->info( "首次排序 : " + toQString( overArraySort ), Create_SrackInfo( ) );
	if( overArrayCount == 0 )
		return false;
	standbyArrayCount = standbyArraySort.size( );
	if( standbyArrayCount == 0 )
		return true;
	overArrayptr = overArraySort.data( );
	standbyArrayptr = standbyArraySort.data( );
	size_t whileCount = 0;
	do {
		size_t addCount = 0;
		for( index = 0; index < standbyArrayCount; ++index ) {
			standbyRefInputArrayCount = standbyArrayptr[ index ]->refInputVector.size( );
			standbyRefInputArrayPtr = standbyArrayptr[ index ]->refInputVector.data( );
			standbyRefInputArrayIndex;
			for( standbyRefInputArrayIndex = 0; standbyRefInputArrayIndex < standbyRefInputArrayCount; ++standbyRefInputArrayIndex ) {
				compNodeRefPtr = standbyRefInputArrayPtr[ standbyRefInputArrayIndex ];
				if( compNodeRefPtr->currentNode->getNodeType( ) == NodeEnum::NodeType::Begin )
					continue;
				for( overArrayIndex = 0; overArrayIndex < overArrayCount; ++overArrayIndex )
					if( overArrayptr[ overArrayIndex ] == compNodeRefPtr )
						break; // 排序列表已经存在
				if( overArrayIndex < overArrayCount )
					continue; // 排序列表存在
				// 存储到后续比较的缓存当中
				buffArraySort.emplace_back( standbyArrayptr[ index ] );
				break;
			}
			if( standbyRefInputArrayIndex < standbyRefInputArrayCount )
				continue;
			++addCount;
			overArraySort.emplace_back( standbyArrayptr[ index ] );
			overArrayptr = overArraySort.data( );
			standbyArrayptr = standbyArraySort.data( );
		}
		whileCount += 1;
		printerDirector->info( QString( "后续(%1)排序 : " ).arg( whileCount ) + toQString( overArraySort ), Create_SrackInfo( ) );
		addCount = buffArraySort.size( );
		if( addCount == 0 )
			break; // 排序完毕

		standbyArrayCount = standbyArraySort.size( );
		if( addCount == standbyArrayCount )
			return false; // 没有任何减少，说明陷入循环
		standbyArraySort = buffArraySort;
		buffArraySort.clear( );
		standbyArrayptr = standbyArraySort.data( );
	} while( true );
	for( index = 0; index < sort_array_count; ++index )
		sort_array_ptr[ index ] = overArrayptr[ index ];
	printerDirector->info( QString( "完成排序 : " ) + toQString( sort_array_ptr, sort_array_count ), Create_SrackInfo( ) );
	return true;
}
QString NodeBuilderTools::toQString( const NodeRefLinkInfo *const*check_array_ptr, const size_t &check_array_count ) {
	QStringList result;
	result.append( "{" );
	for( size_t index = 0; index < check_array_count; ++index )
		result.append( check_array_ptr[ index ]->currentNode->toQString( ) + ", " );

	result.append( "};" );
	return result.join( "\n" );
}
bool NodeBuilderTools::JumpNodeBuilderTools::findPoint( NodeRefLinkInfo *analysis_node_ref_link_info, std::unordered_map< NodeRefLinkInfo *, NodeRefLinkInfo * > &result_input_node_ref_map, std::vector< NodeRefLinkInfo * > &result_node_ref_link_vector ) {

	if( analysis_node_ref_link_info->getCurrentNode( )->getNodeType( ) == NodeEnum::NodeType::Point ) {
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );
		return true;
	}
	size_t oldCount = result_input_node_ref_map.size( );
	size_t count = analysis_node_ref_link_info->refInputVector.size( );
	auto nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refInputVector.data( );

	size_t index = 0;
	for( ; index < count; ++index )
		if( findPoint( nodeRefLinkInfoArrayPtr[ index ], result_input_node_ref_map, result_node_ref_link_vector ) )
			result_input_node_ref_map.try_emplace( analysis_node_ref_link_info, nodeRefLinkInfoArrayPtr[ index ] );
	return oldCount != result_input_node_ref_map.size( );
}
bool NodeBuilderTools::JumpNodeBuilderTools::analysisJumpNodeRef( NodeRefLinkInfo *analysis_node_ref_link_info, std::vector< std::vector< NodeRefLinkInfo * > > &result_node_ref_link_vector ) {

	// 如果不是 jump 节点，即退出
	if( analysis_node_ref_link_info->getCurrentNode( )->getNodeType( ) != NodeEnum::NodeType::Jump )
		return false;
	std::vector< NodeRefLinkInfo * > nodePath;
	size_t count = analysis_node_ref_link_info->refInputVector.size( );
	auto nodeRefLinkInfoArrayPtr = analysis_node_ref_link_info->refInputVector.data( );
	size_t index = 0;
	std::unordered_map< NodeRefLinkInfo *, NodeRefLinkInfo * > inputNodeRefMap;
	for( ; index < count; ++index )
		if( findPoint( nodeRefLinkInfoArrayPtr[ index ], inputNodeRefMap, nodePath ) )
			Application::getInstancePtr( )->getPrinterDirector( )->info( NodeBuilderTools::toQString( nodePath ), Create_SrackInfo( ) );
	return false;
}
