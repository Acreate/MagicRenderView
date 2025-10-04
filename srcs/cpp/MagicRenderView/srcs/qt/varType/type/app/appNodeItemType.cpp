#include "appNodeItemType.h"

#include <qt/tools/tools.h>
#include <qt/node/item/nodeItem.h>

#include "../../../application/application.h"

#include "../../../generate/varGenerate.h"

#include "../../../node/prot/inputProt/nodeInputPort.h"
AppNodeItemType::AppNodeItemType( ) : I_Stack( typeid( t_current_type ) ), releaseVector( new std_vector_pairt< void *, std_function< bool( void * ) > > ) {

	childcreateFunction = [this] ( const type_info &target_type_info, const uint8_t *target_data_ptr, const size_t &target_data_count ) ->void * {
		if( target_type_info != generateTypeInfo )
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
		//auto generate = Application::getApplicationInstancePtr( )->getVarGenerate( );
		if( varGenerate->getTypeInfoGenerateInfo( typeName, resultInfo ) == false )
			return nullptr;
		auto second = resultInfo.first.second( nullptr );
		releaseVector->emplace_back( second, resultInfo.first.first.get( )->getRelease( ) );
		return second;
	};
	childDeleteFunction = [this] ( void *target_ptr ) {
		size_t count = releaseVector->size( );
		if( count == 0 )
			return false;
		auto data = releaseVector->data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == target_ptr ) {
				if( data[ index ].second == nullptr ) {
					tools::debug::printError( "类型未实体化释放函数" );
					return false;
				}
				bool second = data[ index ].second( target_ptr );
				releaseVector->erase( releaseVector->begin( ) + index );
				return second;
			}
		return false;
	};
}
bool AppNodeItemType::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
	if( target_type_info != generateTypeInfo )
		return false;
	NodeItem *targetPtr = ( NodeItem * ) target_ptr;
	QString metaObjectPathName = targetPtr->getMetaObjectPathName( );
	std_vector< uint8_t > nameBuff;
	// 记录节点名称
	result_count = fillBinVector( metaObjectPathName, nameBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	std_vector< uint8_t > inputPortVectorBuff;

	// 记录节点生成编号
	result_count = fillBinVector( &targetPtr->generateCode, sizeof( targetPtr->generateCode ), inputPortVectorBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	nameBuff.append_range( inputPortVectorBuff );

	// 记录节点x坐标
	result_count = fillBinVector( &targetPtr->nodePosX, sizeof( targetPtr->nodePosX ), inputPortVectorBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	nameBuff.append_range( inputPortVectorBuff );

	// 记录节点y坐标
	result_count = fillBinVector( &targetPtr->nodePosY, sizeof( targetPtr->nodePosY ), inputPortVectorBuff );
	if( result_count == 0 )
		return false; // 失败，返回
	nameBuff.append_range( inputPortVectorBuff );

	auto &protVector = targetPtr->nodeInputProtVector;
	size_t count = protVector.size( );
	// 记录输入接口个数
	result_count = fillBinVector( &count, sizeof( size_t ), inputPortVectorBuff );
	if( result_count != 0 ) {
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
	if( target_type_info != generateTypeInfo )
		return false;
	size_t needCount;
	result_count = fillObjVector( &needCount, sizeof( size_t ), source_data_ptr, source_data_count );
	if( result_count == 0 )
		return false;
	size_t mod = source_data_count - result_count;
	if( needCount > mod )
		return false;
	auto offset = source_data_ptr + result_count;
	QString typeName;
	// 获取路径名称
	result_count = fillObjVector( &typeName, offset, mod );
	if( result_count == 0 )
		return false;

	auto nodeItem = ( NodeItem * ) target_ptr;
	// 比较路径名称
	if( nodeItem->getMetaObjectPathName( ) != typeName )
		return false;

	offset += result_count;
	mod -= result_count;

	result_count = fillObjVector( &nodeItem->generateCode, sizeof( nodeItem->generateCode ), offset, mod );
	if( result_count == 0 )
		return false; // 失败，返回
	offset += result_count;
	mod -= result_count;

	// 获取 x 坐标
	result_count = fillObjVector( &nodeItem->nodePosX, sizeof( nodeItem->nodePosX ), offset, mod );
	if( result_count == 0 )
		return false; // 失败，返回
	offset += result_count;
	mod -= result_count;
	// 获取 y 坐标
	result_count = fillObjVector( &nodeItem->nodePosY, sizeof( nodeItem->nodePosY ), offset, mod );
	if( result_count == 0 )
		return false; // 失败，返回
	offset += result_count;
	mod -= result_count;

	size_t count;
	// 记录输入接口个数
	result_count = fillObjVector( &count, sizeof( size_t ), offset, mod );
	if( result_count == 0 )
		return false; // 失败，返回
	offset += result_count;
	mod -= result_count;
	size_t nodeItemInputCount = nodeItem->nodeInputProtVector.size( );
	if( count != nodeItemInputCount )
		return false;
	else if( nodeItemInputCount > 0 ) {
		auto nodeInputProtVectorDataPtr = nodeItem->nodeInputProtVector.data( );
		size_t index = 0;
		for( ; index < nodeItemInputCount; ++index ) {
			// 获取输入接口标题名称
			result_count = fillObjVector( &typeName, offset, mod );
			if( result_count == 0 )
				return false; // 失败，返回
			offset += result_count;
			mod -= result_count;
			// 获取匹配的输入接口
			NodeInputPort *port = nullptr;
			size_t inputIndex = 0;
			for( ; inputIndex < nodeItemInputCount; ++inputIndex )
				if( nodeInputProtVectorDataPtr[ inputIndex ].first->title == typeName ) {
					port = nodeInputProtVectorDataPtr[ inputIndex ].first;
					break;
				}
			if( port == nullptr )
				return false; // 不是匹配的接口
			// 获取输出链接个数
			result_count = fillObjVector( &count, sizeof( size_t ), offset, mod );
			if( result_count == 0 )
				return false; // 失败，返回
			offset += result_count;
			mod -= result_count;
			// 遍历获取
			inputIndex = 0;
			for( ; inputIndex < count; ++inputIndex ) {
				// 获取输出的生成编号
				result_count = fillObjVector( &needCount, sizeof( size_t ), offset, mod );
				if( result_count == 0 )
					return false; // 失败，返回
				offset += result_count;
				mod -= result_count;
				// 获取输出的节点名称
				result_count = fillObjVector( &typeName, offset, mod );
				offset += result_count;
				mod -= result_count;
				if( result_count == 0 )
					return false; // 失败，返回
				port->linkOutputVector.emplace_back( needCount, typeName );
			}

		}

	}
	result_count = offset - source_data_ptr;
	return true;
}
