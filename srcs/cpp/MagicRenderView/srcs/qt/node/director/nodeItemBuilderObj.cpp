#include "./nodeItemBuilderObj.h"

#include "nodeDirector.h"
#include "nodeItemBuilderModule.h"
#include "nodeItemInfo.h"

#include "../../application/application.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"
NodeItemBuilderObj::NodeItemBuilderObj( QObject *parent ) : QObject( parent ) {
	currentVectorIndex = 0;
	currentVectorCount = 0;
	runNodeItemInfoArrayPtr = nullptr;
	applicationInstancePtr = nullptr;
	varGenerate = nullptr;
	nodeDirector = nullptr;
}
bool NodeItemBuilderObj::addBuilderNodeItem( NodeItemInfo *node_item_info ) {
	if( node_item_info == nullptr )
		return false;
	auto nodeMetaType = node_item_info->nodeItem->getNodeMetaType( );
	if( nodeMetaType != nodeItemEnum::Node_Item_Type::Begin )
		return false;
	currentVectorCount = startNodeItemInfoVector.size( );
	runNodeItemInfoArrayPtr = startNodeItemInfoVector.data( );
	currentVectorIndex = 0;
	for( ; currentVectorIndex < currentVectorCount; ++currentVectorIndex )
		if( runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem == node_item_info->nodeItem )
			return false;
	startNodeItemInfoVector.emplace_back( node_item_info );
	return true;
}
bool NodeItemBuilderObj::builderNodeItemVector( ) {
	currentNodeItemBuilderModuleVectorIndex = 0;
	currentNodeItemBuilderModuleVectorCount = 0;
	runNodeItemBuilderModuleArrayPtr = nullptr;

	currentVectorIndex = 0;
	currentVectorCount = startNodeItemInfoVector.size( );
	for( auto elemt : subNodeItemBuilderModuleVector )
		delete elemt.second;
	subNodeItemBuilderModuleVector.clear( );
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

	currentVectorCount = runNodeItemInfoVector.size( );
	runNodeItemInfoArrayPtr = runNodeItemInfoVector.data( );
	for( auto &item : NodeItemBuilderModule::generateModuleVector( runNodeItemInfoArrayPtr, currentVectorCount ) )
		subNodeItemBuilderModuleVector.emplace_back( 0, item );

	currentNodeItemBuilderModuleVectorCount = subNodeItemBuilderModuleVector.size( );
	runNodeItemBuilderModuleArrayPtr = subNodeItemBuilderModuleVector.data( );

	applicationInstancePtr = Application::getApplicationInstancePtr( );
	varGenerate = applicationInstancePtr->getVarGenerate( );
	nodeDirector = applicationInstancePtr->getNodeDirector( );
	QString infoMsg = NodeItemInfoVector::formatNodeInfoPath( runNodeItemInfoArrayPtr, currentVectorCount, ", " );
	if( currentNodeItemBuilderModuleVectorCount != 0 ) {
		QStringList subModeMsg;
		for( ; currentNodeItemBuilderModuleVectorIndex < currentNodeItemBuilderModuleVectorCount; ++currentNodeItemBuilderModuleVectorIndex ) {
			auto subMode = runNodeItemBuilderModuleArrayPtr[ currentNodeItemBuilderModuleVectorIndex ];
			auto nodeItemInfos = subMode.second->getRunNodeItemInfoVector( );
			subModeMsg.append( "\t" + NodeItemInfoVector::formatNodeInfoPath( nodeItemInfos.data( ), nodeItemInfos.size( ), ", " ) );
		}
		infoMsg += "\n" + subModeMsg.join( "\n" );
		currentNodeItemBuilderModuleVectorIndex = 0;
	}

	tools::debug::printInfo( QString( "生成编译:%1" ).arg( infoMsg ) );
	return true;
}
bool NodeItemBuilderObj::fillCurrentRunNodeItemValue( size_t begin_index, NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg ) {

	NodeItem *outputPortNodeItem = node_item_ptr->nodeItem;
	auto nodeMetaType = outputPortNodeItem->getNodeMetaType( );
	QString msg( "%1(%2) 节点异常，未识别节点" );
	switch( nodeMetaType ) {
		case nodeItemEnum::Node_Item_Type::None :
			tools::debug::printError( msg.arg( outputPortNodeItem->getMetaObjectPathName( ) ).arg( outputPortNodeItem->generateCode ) );
			break;
		case nodeItemEnum::Node_Item_Type::Begin :
		case nodeItemEnum::Node_Item_Type::End :
		case nodeItemEnum::Node_Item_Type::GenerateVar :
		case nodeItemEnum::Node_Item_Type::Mark :
		case nodeItemEnum::Node_Item_Type::Jump :
			return true;
	}

	std_vector_pairt< NodeOutputPort *, std_vector< NodeInputPort * > > resultVector;
	if( nodeDirector->getLinkInputPorts( outputPortNodeItem, resultVector ) == false ) {
		msg = "%1(%2) 节点异常，输入接口为0";
		tools::debug::printError( msg.arg( outputPortNodeItem->getMetaObjectPathName( ) ).arg( outputPortNodeItem->generateCode ) );
		return false;
	}
	if( false ) {
		msg = "%1(%2) 节点异常，输入接口未满足最低要求";
		tools::debug::printError( msg.arg( outputPortNodeItem->getMetaObjectPathName( ) ).arg( outputPortNodeItem->generateCode ) );
		return false;
	}
	return true;
}

NodeItemBuilderObj::~NodeItemBuilderObj( ) { }

nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::runCurrentNodeItem( NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg ) {
	if( currentVectorIndex != currentVectorCount ) {
		NodeItem *nodeItem = runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem;
		error_item_result = nodeItem->run( error_msg );
		emit finish_node_item_signal( this, 0, node_item_ptr );
		return nodeItemEnum::Node_Item_Builder_Type::Finish;
	}
	if( currentNodeItemBuilderModuleVectorIndex != currentNodeItemBuilderModuleVectorCount ) {
		auto fillParamRunErrorFunction = [&] ( const size_t &begin_inde, const NodeItemInfo *node_item, nodeItemEnum::Node_Item_Result_Type type_result, const QString &fill_error_msg, nodeItemEnum::Node_Item_Builder_Type type_builder ) {
			emit error_node_item_signal( this, begin_inde, runNodeItemInfoArrayPtr[ currentVectorIndex ], type_result, fill_error_msg, type_builder );
			return false;
		};
		auto runErrorFunction = [&] ( const size_t &begin_inde, const NodeItemInfo *node_item, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &run_error_msg, nodeItemEnum::Node_Item_Builder_Type node_item_builder ) {
			emit error_node_item_signal( this, begin_inde, runNodeItemInfoArrayPtr[ currentVectorIndex ], node_item_result, run_error_msg, node_item_builder );
			return false;
		};
		auto runFinishFunction = [&] ( const size_t &begin_inde, const NodeItemInfo *node_item ) {
			emit finish_node_item_signal( this, begin_inde, runNodeItemInfoArrayPtr[ currentVectorIndex ] );
			return false;
		};
		if( runNodeItemBuilderModuleArrayPtr[ currentNodeItemBuilderModuleVectorIndex ].second->runCurrentItemNodeInfo( runNodeItemBuilderModuleArrayPtr[ currentNodeItemBuilderModuleVectorIndex ].first, fillParamRunErrorFunction, runErrorFunction, runFinishFunction ) == false )
			return nodeItemEnum::Node_Item_Builder_Type::Error;

		return nodeItemEnum::Node_Item_Builder_Type::Finish;
	}
	return nodeItemEnum::Node_Item_Builder_Type::Error;
}

nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::nextNodeItem( ) {
	if( runNodeItemInfoArrayPtr == nullptr )
		return nodeItemEnum::Node_Item_Builder_Type::None;
	QString errorInfo;
	NodeItemInfo *nodeItemPtr;
	nodeItemEnum::Node_Item_Result_Type nodeItemResult;
	nodeItemEnum::Node_Item_Builder_Type nodeBuilderObjResult;

	nodeItemPtr = this->runNodeItemInfoArrayPtr[ currentVectorIndex ];
	auto runResultBool = runItemNodeInfo( 0, nodeItemPtr, nodeBuilderObjResult, nodeItemResult, errorInfo );
	if( runResultBool == false )
		return nodeBuilderObjResult;
	if( currentVectorIndex != currentVectorCount ) {
		++currentVectorIndex;
		return nodeBuilderObjResult;
	}
	if( runNodeItemBuilderModuleArrayPtr[ currentNodeItemBuilderModuleVectorIndex ].second->isLastNodeItem( ) )
		++currentNodeItemBuilderModuleVectorIndex;
	return nodeBuilderObjResult;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::toStartNodeItem( ) {
	if( nullptr == runNodeItemInfoArrayPtr )
		return nodeItemEnum::Node_Item_Builder_Type::None;
	currentVectorIndex = 0;
	currentVectorCount = runNodeItemInfoVector.size( );
	runNodeItemInfoArrayPtr = runNodeItemInfoVector.data( );
	for( currentNodeItemBuilderModuleVectorIndex = 0; currentNodeItemBuilderModuleVectorIndex < currentNodeItemBuilderModuleVectorCount; ++currentNodeItemBuilderModuleVectorIndex )
		runNodeItemBuilderModuleArrayPtr[ currentNodeItemBuilderModuleVectorIndex ].first = 0;
	currentNodeItemBuilderModuleVectorIndex = 0;
	return nodeItemEnum::Node_Item_Builder_Type::Start;
}
bool NodeItemBuilderObj::runItemNodeInfo( size_t begin_index, NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg ) {
	if( fillCurrentRunNodeItemValue( 0, node_item_ptr, builder_result, error_item_result, error_msg ) == false ) {
		emit error_node_item_signal( this, begin_index, node_item_ptr, error_item_result, error_msg, builder_result );
		return false;
	}
	builder_result = runCurrentNodeItem( node_item_ptr, builder_result, error_item_result, error_msg );
	return true;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::runAllNodeItem( ) {
	if( runNodeItemInfoArrayPtr == nullptr )
		return nodeItemEnum::Node_Item_Builder_Type::None;
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Last;
	QString errorInfo;
	NodeItemInfo *nodeItemPtr;
	nodeItemEnum::Node_Item_Result_Type nodeItemResult;
	nodeItemEnum::Node_Item_Builder_Type nodeBuilderObjResult;
	while( currentVectorIndex != currentVectorCount ) {
		nodeItemPtr = this->runNodeItemInfoArrayPtr[ currentVectorIndex ];
		auto runResultBool = runItemNodeInfo( 0, nodeItemPtr, nodeBuilderObjResult, nodeItemResult, errorInfo );
		if( runResultBool == false )
			return nodeBuilderObjResult;
		++currentVectorIndex;
	}
	// todo : 运行链表
	while( currentNodeItemBuilderModuleVectorIndex < currentNodeItemBuilderModuleVectorCount ) {
		auto nodeItemModePtr = this->runNodeItemBuilderModuleArrayPtr[ currentNodeItemBuilderModuleVectorIndex ];

		auto runResultBool = runItemNodeInfo( 0, nodeItemPtr, nodeBuilderObjResult, nodeItemResult, errorInfo );
		if( runResultBool == false )
			return nodeBuilderObjResult;
		++currentVectorIndex;
	}
	return nodeBuilderObjResult;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::runListNodeItem( ) {
	if( runNodeItemInfoArrayPtr == nullptr )
		return nodeItemEnum::Node_Item_Builder_Type::None;
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Last;
	QString errorInfo;
	NodeItem *nodeItem = runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem;
	nodeItemEnum::Node_Item_Result_Type nodeItemResult = nodeItem->run( errorInfo );
	auto nodeBuilderObjResult = nodeItemEnum::Node_Item_Builder_Type::Error;
	if( nodeItemResult != nodeItemEnum::Node_Item_Result_Type::Finish ) {
		emit error_node_item_signal( this, runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem, nodeItemResult, errorInfo, nodeBuilderObjResult );
	} else {
		emit finish_node_item_signal( this, runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem, nodeItemResult );
		++currentVectorIndex;
	}
	return nodeBuilderObjResult;
}
