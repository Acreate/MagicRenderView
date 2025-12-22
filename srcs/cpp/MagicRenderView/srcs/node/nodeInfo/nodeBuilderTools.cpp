#include "nodeBuilderTools.h"

#include "../../app/application.h"

#include "../../director/printerDirector.h"
#include "../../enums/nodeEnum.h"

#include "../../srack/srackInfo.h"
#include "../node/node.h"

class Node;
void NodeBuilderTools::analysisSubNodeRef( Node *analysis_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector ) {
	std::vector< Node * > subNodeVector;
	size_t count;
	size_t index;
	size_t exisCount;
	size_t exisIndex;
	Node **NodeArrayPtr;
	Node **exisNodeRefArrayPtr;
	exisCount = result_node_ref_link_vector.size( );
	exisNodeRefArrayPtr = result_node_ref_link_vector.data( );
	for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
		if( exisNodeRefArrayPtr[ exisIndex ] == analysis_node_ref_link_info )
			break;
	if( exisIndex == exisCount )
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );

	count = analysis_node_ref_link_info->refInputPortNode.size( );
	NodeArrayPtr = analysis_node_ref_link_info->refInputPortNode.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == NodeArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeVector.emplace_back( NodeArrayPtr[ index ] );
	}

	count = analysis_node_ref_link_info->refOutputPortNode.size( );
	NodeArrayPtr = analysis_node_ref_link_info->refOutputPortNode.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == NodeArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeVector.emplace_back( NodeArrayPtr[ index ] );
	}

	count = subNodeVector.size( );
	NodeArrayPtr = subNodeVector.data( );
	for( index = 0; index < count; ++index )
		analysisSubNodeRef( NodeArrayPtr[ index ], result_node_ref_link_vector );
}
bool NodeBuilderTools::analysisNodeRef( Node *analysis_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector ) {
	if( analysis_node_ref_link_info == nullptr )
		return false;

	std::vector< Node * > subNodeVector;

	size_t count;
	size_t index;
	size_t exisCount;
	size_t exisIndex;
	Node **NodeArrayPtr;
	Node **exisNodeRefArrayPtr;
	exisCount = result_node_ref_link_vector.size( );
	exisNodeRefArrayPtr = result_node_ref_link_vector.data( );
	for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
		if( exisNodeRefArrayPtr[ exisIndex ] == analysis_node_ref_link_info )
			break;
	if( exisIndex == exisCount )
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );

	count = analysis_node_ref_link_info->refInputPortNode.size( );
	NodeArrayPtr = analysis_node_ref_link_info->refInputPortNode.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == NodeArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeVector.emplace_back( NodeArrayPtr[ index ] );
	}

	count = analysis_node_ref_link_info->refOutputPortNode.size( );
	NodeArrayPtr = analysis_node_ref_link_info->refOutputPortNode.data( );
	for( index = 0; index < count; ++index ) {
		for( exisIndex = 0; exisIndex < exisCount; ++exisIndex )
			if( exisNodeRefArrayPtr[ exisIndex ] == NodeArrayPtr[ index ] )
				break;
		if( exisIndex != exisCount )
			continue;
		subNodeVector.emplace_back( NodeArrayPtr[ index ] );
	}

	count = subNodeVector.size( );
	NodeArrayPtr = subNodeVector.data( );
	for( index = 0; index < count; ++index )
		analysisSubNodeRef( NodeArrayPtr[ index ], result_node_ref_link_vector );
	count = result_node_ref_link_vector.size( );
	if( count == 0 )
		return false;
	NodeArrayPtr = result_node_ref_link_vector.data( );
	auto converQString = toQString( NodeArrayPtr, count );
	auto printerDirector = Application::getInstancePtr( )->getPrinterDirector( );
	printerDirector->info( converQString, Create_SrackInfo( ) );
	count = filterRepetition( NodeArrayPtr, count );
	result_node_ref_link_vector.resize( count );
	return true;
}
bool NodeBuilderTools::BeginNodeBuilderTools::findRefBeginNode( Node *analysis_node_ref_link_info, Node *&result_begin_node_ref_link ) {
	size_t count = analysis_node_ref_link_info->refInputPortNode.size( );
	auto NodeArrayPtr = analysis_node_ref_link_info->refInputPortNode.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( NodeArrayPtr[ index ]->getNodeType( ) == NodeEnum::NodeType::Begin ) {
			result_begin_node_ref_link = NodeArrayPtr[ index ];
			return true;
		}
	for( index = 0; index < count; ++index )
		if( findRefBeginNode( NodeArrayPtr[ index ], result_begin_node_ref_link ) )
			return true;
	return false;
}
size_t NodeBuilderTools::filterRepetition( Node **check_array_ptr, const size_t &check_array_count ) {
	size_t maxCount = check_array_count;
	return maxCount;
}
bool NodeBuilderTools::sortProcessNodeRefArray( Node **sort_array_ptr, const size_t &sort_array_count ) {
	PrinterDirector *printerDirector = Application::getInstancePtr( )->getPrinterDirector( );

	QString msg = toQString( sort_array_ptr, sort_array_count );
	printerDirector->info( "开始排序 : " + msg, Create_SrackInfo( ) );
	if( sort_array_count < 2 )
		return true;
	if( sort_array_ptr == nullptr )
		return false;
	// 实现排序下标
	std::vector< Node * > overArraySort;
	std::vector< Node * > standbyArraySort;
	std::vector< Node * > buffArraySort;
	// 当前访问下标
	size_t index;
	// 备用排序数量
	size_t standbyArrayCount;
	// 备用排序序列基址
	Node **standbyArrayptr;
	// 排序完毕的数量
	size_t overArrayCount;
	// 访问排序完毕的数组下标
	size_t overArrayIndex;
	// 排序完毕的序列起始地址
	Node **overArrayptr;
	// 引用输入序列个数
	size_t standbyRefInputArrayCount;
	// 引用序列基址
	Node **standbyRefInputArrayPtr;
	// 引用序列访问下标
	size_t standbyRefInputArrayIndex;
	// 匹配的输入引用节点指针
	Node *compNodeRefPtr;
	// 发现依赖为 begin 节点
	for( index = 0; index < sort_array_count; ++index ) {
		standbyRefInputArrayCount = sort_array_ptr[ index ]->refInputPortNode.size( );
		standbyRefInputArrayPtr = sort_array_ptr[ index ]->refInputPortNode.data( );
		for( standbyRefInputArrayIndex = 0; standbyRefInputArrayIndex < standbyRefInputArrayCount; ++standbyRefInputArrayIndex ) {
			compNodeRefPtr = standbyRefInputArrayPtr[ standbyRefInputArrayIndex ];
			if( compNodeRefPtr->getNodeType( ) == NodeEnum::NodeType::Begin )
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
			standbyRefInputArrayCount = standbyArrayptr[ index ]->refInputPortNode.size( );
			standbyRefInputArrayPtr = standbyArrayptr[ index ]->refInputPortNode.data( );
			standbyRefInputArrayIndex;
			for( standbyRefInputArrayIndex = 0; standbyRefInputArrayIndex < standbyRefInputArrayCount; ++standbyRefInputArrayIndex ) {
				compNodeRefPtr = standbyRefInputArrayPtr[ standbyRefInputArrayIndex ];
				if( compNodeRefPtr->getNodeType( ) == NodeEnum::NodeType::Begin )
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
QString NodeBuilderTools::toQString( const Node *const*check_array_ptr, const size_t &check_array_count ) {
	QStringList result;
	result.append( "{" );
	for( size_t index = 0; index < check_array_count; ++index )
		result.append( check_array_ptr[ index ]->toQString( ) + ", " );

	result.append( "};" );
	return result.join( "\n" );
}
bool NodeBuilderTools::JumpNodeBuilderTools::findPoint( Node *analysis_node_ref_link_info, std::vector< std::pair< Node *, Node * > > &result_input_node_ref_map, std::vector< Node * > &result_node_ref_link_vector ) {

	if( analysis_node_ref_link_info->getNodeType( ) == NodeEnum::NodeType::Point ) {
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );
		return true;
	}
	size_t oldCount = result_input_node_ref_map.size( );
	size_t count = analysis_node_ref_link_info->refInputPortNode.size( );
	auto NodeArrayPtr = analysis_node_ref_link_info->refInputPortNode.data( );

	size_t index = 0;
	for( ; index < count; ++index )
		if( findPoint( NodeArrayPtr[ index ], result_input_node_ref_map, result_node_ref_link_vector ) ) {

			size_t mapCount = result_input_node_ref_map.size( );
			auto mapArrayPtr = result_input_node_ref_map.data( );
			size_t mapIndex = 0;
			for( ; mapIndex < mapCount; ++mapIndex )
				if( mapArrayPtr[ mapIndex ].first == analysis_node_ref_link_info && mapArrayPtr[ mapIndex ].first == NodeArrayPtr[ index ] )
					break;
			if( mapIndex == mapCount )
				result_input_node_ref_map.emplace_back( analysis_node_ref_link_info, NodeArrayPtr[ index ] );
		}
	return oldCount != result_input_node_ref_map.size( );
}
bool NodeBuilderTools::JumpNodeBuilderTools::analysisJumpNodeRef( Node *analysis_node_ref_link_info, std::vector< std::vector< Node * > > &result_node_ref_link_vector ) {

	// 如果不是 jump 节点，即退出
	if( analysis_node_ref_link_info->getNodeType( ) != NodeEnum::NodeType::Jump )
		return false;
	std::vector< Node * > nodePath;
	size_t count = analysis_node_ref_link_info->refInputPortNode.size( );
	auto NodeArrayPtr = analysis_node_ref_link_info->refInputPortNode.data( );
	size_t index = 0;
	std::vector< std::pair< Node *, Node * > > inputNodeRefMap;
	for( ; index < count; ++index ) {
		inputNodeRefMap.emplace_back( analysis_node_ref_link_info, NodeArrayPtr[ index ] );
		if( findPoint( NodeArrayPtr[ index ], inputNodeRefMap, nodePath ) ) {
			size_t mapCount;
			size_t mapIndex;
			std::pair< Node *, Node * > *mapArrayPtr;
			mapCount = inputNodeRefMap.size( );
			mapArrayPtr = inputNodeRefMap.data( );
			std::vector< Node * > jumpVector;
			for( auto item : nodePath ) {
				jumpVector.clear( );
				jumpVector.emplace_back( item );
				while( true ) {
					for( mapIndex = 0; mapIndex < mapCount; ++mapIndex )
						if( mapArrayPtr[ mapIndex ].second == item ) {
							jumpVector.emplace_back( mapArrayPtr[ mapIndex ].first );
							item = mapArrayPtr[ mapIndex ].first;
							break;
						}
					if( mapIndex == mapCount )
						return false; // 匹配异常
					if( mapArrayPtr[ mapIndex ].first == analysis_node_ref_link_info )
						break;
				}
				result_node_ref_link_vector.emplace_back( jumpVector );
			}
			nodePath.clear( );
			inputNodeRefMap.clear( );
		}
	}
	return true;
}
bool NodeBuilderTools::Point::findJumNodeRef( Node * analysis_node_ref_link_info, std::vector<Node *> &result_node_ref_link_vector ) {

	std::vector< Node * > foreachOutNodeRef = analysis_node_ref_link_info->refOutputPortNode;
	std::vector< Node * > buffOutNodeRef;
	size_t overCount = result_node_ref_link_vector.size( );
	size_t foreachCount = foreachOutNodeRef.size( );
	auto foreachArrayPtr = foreachOutNodeRef.data( );
	size_t foreachIndex;
	do {
		for( foreachIndex = 0; foreachIndex < foreachCount; ++foreachIndex ) {
			if( foreachArrayPtr[ foreachIndex ]->getNodeType( ) == NodeEnum::NodeType::Jump )
				result_node_ref_link_vector.emplace_back( foreachArrayPtr[ foreachIndex ] );
			else
				buffOutNodeRef.append_range( foreachArrayPtr[ foreachIndex ]->refOutputPortNode );
		}
		foreachCount = buffOutNodeRef.size( );
		if( foreachCount == 0 )
			break;
		foreachOutNodeRef = buffOutNodeRef;
		foreachArrayPtr = foreachOutNodeRef.data( );
		buffOutNodeRef.clear( );
	} while( true );

	return overCount != result_node_ref_link_vector.size( );
}
