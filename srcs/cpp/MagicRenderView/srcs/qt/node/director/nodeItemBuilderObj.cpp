#include "nodeItemBuilderObj.h"

#include "nodeDirector.h"
#include "nodeItemBuilderModule.h"
#include "nodeItemInfo.h"

#include "../../application/application.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"
NodeItemBuilderObj::NodeItemBuilderObj( QObject *parent ) : QObject( parent ), moduleBuilderStaus( nodeItemEnum::Node_Item_Builder_Type::None ) {
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
	currentVectorIndex = 0;
	currentVectorCount = startNodeItemInfoVector.size( );
	for( auto elemt : subNodeItemBuilderModuleVector )
		delete elemt;
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
	subNodeItemBuilderModuleVector = NodeItemBuilderModule::generateModuleVector( runNodeItemInfoArrayPtr, currentVectorCount );
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	varGenerate = applicationInstancePtr->getVarGenerate( );
	nodeDirector = applicationInstancePtr->getNodeDirector( );
	QString infoMsg = NodeItemInfoVector::formatNodeInfoPath( runNodeItemInfoArrayPtr, currentVectorCount, ", " );
	QStringList subModeMsg;
	for( auto subMode : subNodeItemBuilderModuleVector ) {
		auto nodeItemInfos = subMode->getRunNodeItemInfoVector( );
		subModeMsg.append( "\t" + NodeItemInfoVector::formatNodeInfoPath( nodeItemInfos.data( ), nodeItemInfos.size( ), ", " ) );
	}
	if( subModeMsg.size( ) )
		infoMsg += "\n" + subModeMsg.join( "\n" );
	tools::debug::printInfo( QString( "生成编译:%1" ).arg( infoMsg ) );
	return true;
}
bool NodeItemBuilderObj::fillCurrentRunNodeItemValue( ) {
	if( currentVectorIndex == currentVectorCount || runNodeItemInfoArrayPtr == nullptr )
		return false;
	NodeItem *outputPortNodeItem = runNodeItemInfoArrayPtr[ currentVectorIndex ]->nodeItem;
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
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::builderStatus( ) const {
	return moduleBuilderStaus;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::runCurrentNodeItem( ) {
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Error;

	return nodeItemEnum::Node_Item_Builder_Type::Finish;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::nextNodeItem( ) {
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Last;
	return nodeItemEnum::Node_Item_Builder_Type::Finish;
}
nodeItemEnum::Node_Item_Builder_Type NodeItemBuilderObj::toStartNodeItem( ) {
	if( currentVectorIndex == currentVectorCount )
		return nodeItemEnum::Node_Item_Builder_Type::Last;
	return nodeItemEnum::Node_Item_Builder_Type::Start;
}
bool NodeItemBuilderObj::getInfo( QString &result_msg ) const {
	if( moduleBuilderStaus == nodeItemEnum::Node_Item_Builder_Type::None )
		return false;
	result_msg = msg;
	return true;
}
