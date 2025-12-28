#include "nodeTypeInfoSerializeion.h"

#include "../../app/application.h"
#include "../../director/printerDirector.h"
#include "../../director/varDirector.h"
#include "../../srack/srackInfo.h"
#include "../node/node.h"
NodeTypeInfoSerializeion::NodeTypeInfoSerializeion( ) {
	varDirector = new VarDirector;
	nodeObjPtrArrayPtr = nullptr;
	nodeObjPtrArrayCount = 0;
}
NodeTypeInfoSerializeion::~NodeTypeInfoSerializeion( ) {
	delete varDirector;
}
void NodeTypeInfoSerializeion::clearNodeVector( ) {
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
	if( varDirector->init( ) == false )
		return false;
	return true;
}
bool NodeTypeInfoSerializeion::toData( std::vector< uint8_t > &result_data_vector ) {
	if( varDirector->init( ) == false )
		return false;
	QString *nodeNamePtr;
	uint64_t *uint64Ptr;
	uint32_t *uint32Ptr;
	return true;
}
