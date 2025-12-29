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
	if( nodeObjPtrArrayCount != 0 ) {
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
	nodeObjPtr.emplace_back( append_node_ptr );
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
bool NodeTypeInfoSerializeion::loadData( NodeDirector *node_director, size_t &use_count, const uint8_t *src_data_ptr, const size_t &src_data_count, const TFCreate_Node_Function &node_create_function, const TFLink_Port_Function &prot_link_fcuntion ) {
	if( node_director == nullptr )
		return false;
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
	if( varDirector.toVar( use_count, src_data_ptr, src_data_count, nodeTypeInfos ) == false )
		return false;
	// 创建节点
	std::vector< Node * > buff;
	size_t count = nodeTypeInfos->size( );
	NodeTypeInfo **nodeTypeInfoArrayPtr = nodeTypeInfos->data( );
	size_t index;
	Node *node;
	for( index = 0; index < count; ++index )
		if( node = node_create_function( nodeTypeInfoArrayPtr[ index ]->nodeName, nodeTypeInfoArrayPtr[ index ]->nodeGeneratorCode, nodeTypeInfoArrayPtr[ index ]->posX, nodeTypeInfoArrayPtr[ index ]->posY ), node == nullptr )
			return false;
		else
			buff.emplace_back( node );
	QString errorMsg;
	if( node_director->sortArchiveCode( errorMsg ) == false )
		return false;
	// 链接端口
	size_t linkPortIndex = 0;
	PortTypeInfo **linkPortArrayPtr;
	for( index = 0; index < count; ++index )
		if( nodeObjPtrArrayCount = nodeTypeInfoArrayPtr[ index ]->portLinkInfoVector.size( ), nodeObjPtrArrayCount != 0 )
			for( linkPortIndex = 0, linkPortArrayPtr = nodeTypeInfoArrayPtr[ index ]->portLinkInfoVector.data( ); linkPortIndex < nodeObjPtrArrayCount; ++linkPortIndex )
				if( prot_link_fcuntion( linkPortArrayPtr[ linkPortIndex ]->outputNodeGeneratorCode, linkPortArrayPtr[ linkPortIndex ]->outputPortGeneratorCode, linkPortArrayPtr[ linkPortIndex ]->inputNodeGeneratorCode, linkPortArrayPtr[ linkPortIndex ]->inputPortGeneratorCode ) == false )
					return false;
	// 配置节点数据
	nodeObjPtrArrayPtr = buff.data( );
	nodeObjPtrArrayCount = 0;
	for( index = 0; index < count; ++index )
		if( nodeObjPtrArrayPtr[ index ]->formUint8ArrayData( nodeObjPtrArrayCount, nodeTypeInfoArrayPtr[ index ]->nodeData.data( ), nodeTypeInfoArrayPtr[ index ]->nodeData.size( ) ) == false )
			return false;
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
	if( varDirector.create( nodeTypeInfos ) == false || nodeTypeInfos == nullptr )
		return false;
	size_t index = 0;
	nodeTypeInfos->resize( nodeObjPtrArrayCount );
	auto nodeTypeInfoArrayPtr = nodeTypeInfos->data( );
	NodeTypeInfo *nodeTypeInfoPtr = nullptr;
	for( ; index < nodeObjPtrArrayCount; ++index, nodeTypeInfoPtr = nullptr )
		if( varDirector.create( nodeTypeInfoPtr ) == false || nodeTypeInfoPtr == nullptr )
			return false;
		else if( nodeTypeInfoArrayPtr[ index ] = nodeTypeInfoPtr, nodeTypeInfoPtr->load( nodeObjPtrArrayPtr[ index ] ) == false )
			return false;
	if( varDirector.toVector( nodeTypeInfos, result_data_vector ) == false )
		return false;
	return true;
}
