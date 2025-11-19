#include "nodeItemBuilderModule.h"

#include "nodeDirector.h"
#include "nodeItemInfo.h"

#include "../../application/application.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"
#include "../prot/inputProt/nodeInputPort.h"
#include "../prot/outputProt/nodeOutputPort.h"
NodeItemBuilderModule::NodeItemBuilderModule( ) {

}
bool NodeItemBuilderModule::builderNodeItemVector( ) {
	runCount = 0;
	currentVectorIndex = 0;
	currentVectorCount = startNodeItemInfoVector.size( );
	if( currentVectorCount == 0 ) {
		QString msg( "请加入开始节点到序列当中" );
		tools::debug::printError( msg );
		runNodeItemInfoArrayPtr = nullptr;
		return false;
	}
	const NodeItemInfo *error_node_item = nullptr;
	if( NodeItemInfoVector::builderNodeItemVector( startNodeItemInfoVector, runNodeItemInfoVector, error_node_item ) == false ) {
		if( error_node_item )
			tools::debug::printError( QString( "%1->%2 未存在输入依赖链当中" ).arg( error_node_item->nodeItem->getMetaObjectPathName( ) ).arg( error_node_item->nodeItem->generateCode ) );
		currentVectorCount = 0;
		runNodeItemInfoArrayPtr = nullptr;
		return false;
	}
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	varGenerate = applicationInstancePtr->getVarGenerate( );
	nodeDirector = applicationInstancePtr->getNodeDirector( );

	currentVectorCount = runNodeItemInfoVector.size( );
	runNodeItemInfoArrayPtr = runNodeItemInfoVector.data( );

	QString infoMsg = NodeItemInfoVector::formatNodeInfoPath( runNodeItemInfoArrayPtr, currentVectorCount, ", " );
	tools::debug::printInfo( QString( "生成子模块编译:%1" ).arg( infoMsg ) );
	return true;
}
bool NodeItemBuilderModule::runCurrentItemNodeInfo( size_t begin_index, const TFRunResultFunction &fill_param_run_error_function, const TFRunResultFunction &fill_run_error_function, const std_function< bool ( const size_t &, NodeItemInfo * ) > &finish_function ) {
	if( runNodeItemInfoArrayPtr == nullptr )
		return fill_run_error_function( begin_index, nullptr, nodeItemEnum::Node_Item_Result_Type::NotImplementation, "未实现调用", nodeItemEnum::Node_Item_Builder_Type::None );
	if( runItemNodeInfo( begin_index, runNodeItemInfoArrayPtr[ currentVectorIndex ], fill_param_run_error_function, fill_run_error_function, finish_function ) == false )
		return false;
	++currentVectorIndex;
	return true;
}
bool NodeItemBuilderModule::isLastNodeItem( ) const {
	return currentVectorIndex == currentVectorCount;
}
bool NodeItemBuilderModule::runItemNodeInfo( size_t begin_index, NodeItemInfo *node_item_ptr, const TFRunResultFunction &fill_param_run_error_function, const TFRunResultFunction &fill_run_error_function, const std_function< bool ( const size_t &, NodeItemInfo * ) > &finish_function ) {
	nodeItemEnum::Node_Item_Builder_Type builder_result;
	nodeItemEnum::Node_Item_Result_Type error_item_result;
	QString error_msg;
	if( fillCurrentRunNodeItemValue( begin_index, node_item_ptr, builder_result, error_item_result, error_msg ) == false )
		return fill_param_run_error_function( begin_index, node_item_ptr, error_item_result, error_msg, builder_result );
	NodeItem *nodeItem = node_item_ptr->nodeItem;
	error_item_result = nodeItem->run( runCount, error_msg );
	if( error_item_result != nodeItemEnum::Node_Item_Result_Type::Finish )
		return fill_run_error_function( begin_index, node_item_ptr, error_item_result, error_msg, builder_result );
	return finish_function( begin_index, node_item_ptr );
}
bool NodeItemBuilderModule::fillCurrentRunNodeItemValue( size_t begin_index, NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg ) {
	NodeItem *inputPortNodeItem = node_item_ptr->nodeItem;
	auto nodeMetaType = inputPortNodeItem->getNodeMetaType( );
	QString msg( "%1(%2) 节点异常，未识别节点" );
	switch( nodeMetaType ) {
		case nodeItemEnum::Node_Item_Type::None :
			tools::debug::printError( msg.arg( inputPortNodeItem->getMetaObjectPathName( ) ).arg( inputPortNodeItem->generateCode ) );
			break;
		case nodeItemEnum::Node_Item_Type::Begin :
		case nodeItemEnum::Node_Item_Type::End :
			++runCount;
		case nodeItemEnum::Node_Item_Type::GenerateVar :
		case nodeItemEnum::Node_Item_Type::Mark :
		case nodeItemEnum::Node_Item_Type::Jump :
			return true;
	}

	auto nodeItemInfos = node_item_ptr->inputNodeItemInfoVector;
	for( auto &outNodeItem : nodeItemInfos ) {
		std_vector_pairt< NodeInputPort *, std_vector< NodeOutputPort * > > resultVector;
		if( nodeDirector->getLinkInputPorts( outNodeItem->nodeItem, resultVector ) == false ) {
			msg = "%1(%2) 节点异常，输入接口为0";
			tools::debug::printError( msg.arg( inputPortNodeItem->getMetaObjectPathName( ) ).arg( inputPortNodeItem->generateCode ) );
			return false;
		}
		for( auto &[ input,outputPortVector ] : resultVector ) {
			for( auto &outputPort : outputPortVector )
				if( inputPortNodeItem->setPortLinkPort( input, outputPort ) == false ) {
					msg = "%1(%2) 节点异常，端口非法[%3 <=> %4]";
					tools::debug::printError( msg.arg( inputPortNodeItem->getMetaObjectPathName( ) ).arg( inputPortNodeItem->generateCode ).arg( input->getMetaObjectPathName( ) ).arg( outputPort->getMetaObjectPathName( ) ) );
					return false;
				}
		}
	}

	return true;
}
std_vector< NodeItemInfo * > NodeItemBuilderModule::findEndAtStartNode( NodeItemInfo *end_node_info_ptr ) {

	std_vector< NodeItemInfo * > result;

	if( NodeItemInfoVector::fillInputNodeItemAtVector( end_node_info_ptr, result ) == false )
		return result;

	size_t count = result.size( );
	auto data = result.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ]->nodeItem->getNodeMetaType( ) != nodeItemEnum::Node_Item_Type::Begin )
			data[ index ] = nullptr;
	tools::vector::removeNullPtr( result );
	return result;
}
std_vector< NodeItemBuilderModule * > NodeItemBuilderModule::generateModuleVector( NodeItemInfo **node_item_info_array_ptr, const size_t &node_item_info_array_count ) {

	std_vector< NodeItemBuilderModule * > result; // 返回的模型列表
	NodeItemBuilderModule *element; // 临时操作模块对象指针
	NodeItemBuilderModule **resultArrayPtr; // 遍历用的返回模型列表序列指针
	std_vector< NodeItemInfo * > endAtStartNode; // 保存返回用的开始节点序列
	NodeItemInfo **endAtStartNodeArrayPtr;// 遍历保存返回用的开始节点序列
	NodeItemInfo **existArrayPtr;// 遍历已经生成的模块保存返回用的开始节点序列
	size_t index; // 输入数组下标
	size_t resultIndex; // 返回模块序列下标
	size_t resultCount; // 返回模块数量
	size_t endAtStartNodeIndex; // 返回的开始节点下标
	size_t endAtStartNodeCount; // 返回的开始节点个数
	size_t existIndex; // 遍历模块的开始节点下标
	size_t existStartCount; // 遍历模块的开始节点个数
	for( index = 0; index < node_item_info_array_count; ++index )
		if( node_item_info_array_ptr[ index ]->nodeItem->getNodeMetaType( ) == nodeItemEnum::Node_Item_Type::End ) {
			endAtStartNode = findEndAtStartNode( node_item_info_array_ptr[ index ] );
			if( endAtStartNode.size( ) == 0 )
				continue;
			resultCount = result.size( );
			resultArrayPtr = result.data( );
			endAtStartNodeCount = endAtStartNode.size( );
			endAtStartNodeArrayPtr = endAtStartNode.data( );
			element = nullptr;
			for( resultIndex = 0, endAtStartNodeIndex = 0; resultIndex < resultCount; ++resultIndex ) {
				element = resultArrayPtr[ resultIndex ];
				existStartCount = element->startNodeItemInfoVector.size( );
				existArrayPtr = element->startNodeItemInfoVector.data( );

				for( existIndex = 0; existIndex < existStartCount; ++existIndex ) {
					for( endAtStartNodeIndex = 0; endAtStartNodeIndex < endAtStartNodeCount; ++endAtStartNodeIndex )
						if( existArrayPtr[ existIndex ] == endAtStartNodeArrayPtr[ endAtStartNodeIndex ] )
							break;
					if( endAtStartNodeIndex != endAtStartNodeCount )
						break;
				}

				if( endAtStartNodeIndex != endAtStartNodeCount ) {
					for( existIndex = 0; existIndex < existStartCount; ++existIndex ) {
						for( endAtStartNodeIndex = 0; endAtStartNodeIndex < endAtStartNodeCount; ++endAtStartNodeIndex )
							if( existArrayPtr[ existIndex ] != endAtStartNodeArrayPtr[ endAtStartNodeIndex ] )
								break;
						if( endAtStartNodeIndex != endAtStartNodeCount )
							continue;
						element->startNodeItemInfoVector.emplace_back( endAtStartNodeArrayPtr[ endAtStartNodeIndex ] );
					}

					break;
				}
				element = nullptr;
			}
			if( element != nullptr )
				continue;
			element = new NodeItemBuilderModule;

			element->startNodeItemInfoVector = endAtStartNode;
			if( element->builderNodeItemVector( ) == false ) {
				auto formatNodeInfoPath = NodeItemInfoVector::formatNodeInfoPath( element->startNodeItemInfoVector.data( ), element->startNodeItemInfoVector.size( ), ", " );
				QString msg( "异常列表 : %1(%2)->[%3]" );
				tools::debug::printError( msg.arg( node_item_info_array_ptr[ index ]->nodeItem->getMetaObjectPathName( ) ).arg( node_item_info_array_ptr[ index ]->nodeItem->generateCode ).arg( formatNodeInfoPath ) );
				delete element;
				continue;
			}
			result.emplace_back( element );
		}
	return result;
}
