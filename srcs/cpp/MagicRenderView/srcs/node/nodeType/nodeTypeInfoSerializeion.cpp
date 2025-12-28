#include "nodeTypeInfoSerializeion.h"

#include "../../app/application.h"
#include "../../director/printerDirector.h"
#include "../../director/varDirector.h"
#include "../../srack/srackInfo.h"
#include "../node/node.h"
#include "../portType/portTypeInfo.h"
#include "nodeTypeInfo.h"
NodeTypeInfoSerializeion::NodeTypeInfoSerializeion( ) {
	nodeObjPtrArrayPtr = nullptr;
	nodeObjPtrArrayCount = 0;
}
NodeTypeInfoSerializeion::~NodeTypeInfoSerializeion( ) {

}
void NodeTypeInfoSerializeion::clearNodeVector( ) {
	nodeObjPtr.clear( );
}
bool NodeTypeInfoSerializeion::appendNodePtr( Node *append_node_ptr ) {
	if( nodeObjPtrArrayCount == 0 )
		nodeObjPtr.emplace_back( append_node_ptr );
	else {
		auto compGenerateCode = append_node_ptr->generateCode;
		for( size_t index = 0; index < nodeObjPtrArrayCount; ++index )
			if( append_node_ptr == nodeObjPtrArrayPtr[ index ] ) {
				Application::getInstancePtr( )->getPrinterDirector( )->info( QObject::tr( "重复添加的节点[%1]" ).arg( append_node_ptr->toQString( ) ), Create_SrackInfo( ) );
				return false; // 存在已知对象
			} else if( compGenerateCode == nodeObjPtrArrayPtr[ index ]->generateCode ) {
				Application::getInstancePtr( )->getPrinterDirector( )->info( QObject::tr( "重复添加的节点生成码[%1] -> [%2]" ).arg( append_node_ptr->toQString( ) ).arg( nodeObjPtrArrayPtr[ index ]->toQString( ) ), Create_SrackInfo( ) );
				return false; // 存在已知生成码
			}
	}
	nodeObjPtrArrayPtr = nodeObjPtr.data( );
	nodeObjPtrArrayCount = nodeObjPtr.size( );
	return true;
}
bool NodeTypeInfoSerializeion::removeNodePtr( Node *remove_node_ptr ) {
	if( nodeObjPtrArrayCount == 0 )
		return false;
	for( size_t index = 0; index < nodeObjPtrArrayCount; ++index )
		if( remove_node_ptr == nodeObjPtrArrayPtr[ index ] ) {
			nodeObjPtr.erase( nodeObjPtr.begin( ) + index );
			nodeObjPtrArrayPtr = nodeObjPtr.data( );
			nodeObjPtrArrayCount = nodeObjPtr.size( );
			return true;
		}
	return false;
}
bool NodeTypeInfoSerializeion::loadData( size_t &use_count, const uint8_t *src_data_ptr, const size_t &src_data_count, const TFCreate_Node_Function &node_create_function, const TFLink_Port_Function &prot_link_fcuntion ) {
	if( node_create_function == nullptr )
		return false;
	if( prot_link_fcuntion == nullptr )
		return false;
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	std::vector< NodeTypeInfo * > *nodeTypeInfos = nullptr;
	if( varDirector.create( nodeTypeInfos ) == false || nodeTypeInfos == nullptr )
		return false;
	if( varDirector.toVar( use_count, src_data_ptr, use_count, nodeTypeInfos ) == false )
		return false;
	// 创建节点
	std::vector< Node * > buff;
	size_t count = nodeTypeInfos->size( );
	NodeTypeInfo **nodeTypeInfoArrayPtr = nodeTypeInfos->data( );
	size_t index;
	for( index = 0; index < count; ++index ) {
		auto node = node_create_function( nodeTypeInfoArrayPtr[ index ]->nodeName, nodeTypeInfoArrayPtr[ index ]->nodeGeneratorCode, nodeTypeInfoArrayPtr[ index ]->posX, nodeTypeInfoArrayPtr[ index ]->posY );
		if( node == nullptr )
			return false;
		buff.emplace_back( node );
	}
	// 链接端口
	for( index = 0; index < count; ++index ) {
		size_t linkPortCount = nodeTypeInfoArrayPtr[ index ]->portLinkInfoVector.size( );
		if( linkPortCount == 0 )
			continue;
		auto linkPortArrayPtr = nodeTypeInfoArrayPtr[ index ]->portLinkInfoVector.data( );
		size_t linkPortIndex = 0;
		for( ; linkPortIndex < linkPortCount; ++linkPortIndex ) {
			PortTypeInfo *portTypeInfo = linkPortArrayPtr[ linkPortIndex ];
			auto linkResultOk = prot_link_fcuntion( portTypeInfo->outputNodeGeneratorCode, portTypeInfo->outputPortGeneratorCode, portTypeInfo->inputNodeGeneratorCode, portTypeInfo->inputPortGeneratorCode );
			if( linkResultOk == false )
				return false;
		}

	}
	nodeObjPtr = buff;
	nodeObjPtrArrayCount = nodeObjPtr.size( );
	nodeObjPtrArrayPtr = nodeObjPtr.data( );
	return true;
}
bool NodeTypeInfoSerializeion::toData( std::vector< uint8_t > &result_data_vector ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	std::vector< NodeTypeInfo * > *nodeTypeInfos = nullptr;
	NodeTypeInfo *nodeTypeInfoPtr = nullptr;
	if( varDirector.create( nodeTypeInfos ) == false || nodeTypeInfos == nullptr )
		return false;
	size_t index = 0;
	nodeTypeInfos->resize( nodeObjPtrArrayCount );
	auto nodeTypeInfoArrayPtr = nodeTypeInfos->data( );
	for( ; index < nodeObjPtrArrayCount; ++index ) {
		nodeTypeInfoPtr = nullptr;
		if( varDirector.create( nodeTypeInfoPtr ) == false || nodeTypeInfoPtr == nullptr )
			return false;
		nodeTypeInfoArrayPtr[ index ] = nodeTypeInfoPtr;
		if( nodeTypeInfoPtr->load( nodeObjPtrArrayPtr[ index ] ) == false )
			return false;
	}
	if( varDirector.toVector( nodeTypeInfos, result_data_vector ) )
		return false;
	return true;
}
