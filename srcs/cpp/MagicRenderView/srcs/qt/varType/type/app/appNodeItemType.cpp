#include "appNodeItemType.h"

#include <qt/tools/tools.h>
#include <qt/node/item/nodeItem.h>

#include "../../../application/application.h"

#include "../../../generate/varGenerate.h"

#include "../../../node/prot/inputProt/nodeInputPort.h"
AppNodeItemType::AppNodeItemType( ) : I_Stack( typeid( t_current_type ) ) {
	childcreateFunction = [this] ( const type_info &target_type_info, const uint8_t *target_data_ptr, const size_t &target_data_count ) ->void * {
		// auto p = new t_current_type( );

		if( target_type_info != generateTypeInfo && generateTypeInfo.before( target_type_info ) == false )
			return nullptr;
		size_t needCount;
		size_t useCount = fillObjVector( &needCount, sizeof( size_t ), target_data_ptr, target_data_count );
		if( useCount == 0 )
			return nullptr;
		size_t mod = target_data_count - useCount;
		if( needCount > mod )
			return nullptr;
		target_data_ptr += useCount;
		QString typeName;
		useCount = fillObjVector( &typeName, target_data_ptr, mod );
		if( useCount == 0 )
			return nullptr;
		std_pairt< std_pairt< std_shared_ptr< I_Type >, std_function< void *( void * ) > >, std_vector< QString > > resultInfo;
		auto generate = Application::getApplicationInstancePtr( )->getVarGenerate( );
		if( generate->getTypeInfoGenerateInfo( typeName, resultInfo ) == false )
			return nullptr;
		auto second = resultInfo.first.second( nullptr );
		return second;
	};
	childDeleteFunction = [] ( void *target_ptr ) {
		delete ( t_current_type * ) target_ptr;
		return true;
	};
}
bool AppNodeItemType::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
	if( target_type_info != generateTypeInfo && generateTypeInfo.before( target_type_info ) == false )
		return false;
	NodeItem *targetPtr = ( NodeItem * ) target_ptr;
	QString metaObjectPathName = targetPtr->getMetaObjectPathName( );
	std_vector< uint8_t > nameBuff;
	// 记录节点名称
	result_count = fillBinVector( metaObjectPathName, nameBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	std_vector< uint8_t > inputPortVectorBuff;

	// 记录节点x坐标
	result_count = fillBinVector( &targetPtr->nodePosX, sizeof( targetPtr->nodePosX ), inputPortVectorBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	nameBuff.append_range( inputPortVectorBuff );

	// 记录节点y坐标
	result_count = fillBinVector( &targetPtr->nodePosX, sizeof( targetPtr->nodePosX ), inputPortVectorBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	nameBuff.append_range( inputPortVectorBuff );
	
	auto &protVector = targetPtr->nodeInputProtVector;
	size_t count = protVector.size( );
	// 记录输入接口个数
	result_count = fillBinVector( &count, sizeof( size_t ), inputPortVectorBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	auto data = protVector.data( );
	size_t index = 0;
	std_vector< uint8_t > inputPortNameBuff;
	std_vector< uint8_t > linkPortVectorBuff;
	std_vector< uint8_t > linkPortGenerateCodeBuff;
	std_vector< uint8_t > linkPortNameBuff;
	for( ; index < count; ++index ) {
		NodeInputPort *nodeInputPort = data[ index ].first;
		// 记录输入接口标题名称
		result_count = fillBinVector( nodeInputPort->title, inputPortNameBuff );
		if( result_count == 0 )
			return false; // 失败，返回
		size_t linkCount = nodeInputPort->linkOutputVector.size( );
		// 记录输出链接个数
		result_count = fillBinVector( &linkCount, sizeof( size_t ), linkPortVectorBuff );
		if( result_count == 0 )
			return false; // 失败，返回
		size_t linkIndex = 0;
		auto linkOutputDataPtr = nodeInputPort->linkOutputVector.data( );
		for( ; linkIndex < linkCount; ++linkIndex ) {
			// 记录输出的生成编号
			result_count = fillBinVector( &linkOutputDataPtr[ linkIndex ].first, sizeof( size_t ), linkPortGenerateCodeBuff );
			if( result_count == 0 )
				return false; // 失败，返回
			// 记录输出的节点名称
			result_count = fillBinVector( linkOutputDataPtr[ linkIndex ].second, linkPortNameBuff );
			if( result_count == 0 )
				return false; // 失败，返回
			linkPortVectorBuff.append_range( linkPortGenerateCodeBuff );
			linkPortVectorBuff.append_range( linkPortNameBuff );
		}
		inputPortVectorBuff.append_range( inputPortNameBuff );
		inputPortVectorBuff.append_range( linkPortVectorBuff );
	}
	nameBuff.append_range( inputPortVectorBuff );
	result_count = nameBuff.size( );
	result_count = fillBinVector( &result_count, sizeof( size_t ), result_vector );
	if( result_count == 0 )
		return false; // 失败，返回
	result_vector.append_range( nameBuff );
	result_count = result_vector.size( );
	return true;
}
bool AppNodeItemType::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_type_info != generateTypeInfo && generateTypeInfo.before( target_type_info ) == false )
		return false;
	return I_Stack::toOBjVector( target_type_info, target_ptr, result_count, source_data_ptr, source_data_count );
}
