#include "./nodeItemGenerate.h"

#include "../../tools/tools.h"

NodeItemGenerate::NodeItemGenerateMetaInfoVector_Type NodeItemGenerate::nodeItemGenerateMetaInfos;
NodeItemGenerate::DirClassItemMapVector_Type NodeItemGenerate::nodeItemDirClassMetaInfos;
NodeItemGenerate::NodeItem_Type * NodeItemGenerate::createNodeItem( NodeItem_ParentPtr_Type *parent, const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name ) {
	auto dirNameTrimmed = dir_name.trimmed( );
	if( dirNameTrimmed.isEmpty( ) ) {
		tools::debug::printError( "文件夹名称为空，不合法，直接返回" );
		return nullptr; // 文件夹名称为空，不合法，直接返回
	}
	auto itemNameTrimmed = item_name.trimmed( );
	if( itemNameTrimmed.isEmpty( ) ) {
		tools::debug::printError( "类名称为空，不合法，直接返回" );
		return nullptr; // 类名称为空，不合法，直接返回
	}
	// 匹配文件夹
	size_t findDirVectorCount = nodeItemGenerateMetaInfos.size( ), findDirVectorIndex = 0;
	auto findDirVectorDataPtr = nodeItemGenerateMetaInfos.data( );
	for( ; findDirVectorIndex < findDirVectorCount; ++findDirVectorIndex )
		if( findDirVectorDataPtr[ findDirVectorIndex ].first == dir_name ) {
			// 类名与创建调用的映射列表
			auto &classNameMapVector = findDirVectorDataPtr[ findDirVectorIndex ].second;
			size_t classNameMapVectorCount = classNameMapVector.size( ), classNameMapVectorIndex = 0;
			auto classNameMapVectorDataPtr = classNameMapVector.data( );
			for( ; classNameMapVectorIndex < classNameMapVectorCount; ++classNameMapVectorIndex )
				if( classNameMapVectorDataPtr[ classNameMapVectorIndex ].first == itemNameTrimmed )
					return classNameMapVectorDataPtr[ classNameMapVectorIndex ].second( parent );
			return nullptr; // 找到文件夹，但是找不到对应的类，应该直接返回空
		}
	return nullptr;
}
bool NodeItemGenerate::appendNodeItemInfo( const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name, const NodeItemGenerateFunction_Type &generate_function ) {

	auto dirNameTrimmed = dir_name.trimmed( );
	if( dirNameTrimmed.isEmpty( ) ) {
		tools::debug::printError( "文件夹名称为空，不合法，直接返回" );
		return false; // 文件夹名称为空，不合法，直接返回
	}
	auto itemNameTrimmed = item_name.trimmed( );
	if( itemNameTrimmed.isEmpty( ) ) {
		tools::debug::printError( "类名称为空，不合法，直接返回" );
		return false; // 类名称为空，不合法，直接返回
	}
	// 匹配文件夹
	size_t findDirVectorCount = nodeItemGenerateMetaInfos.size( ), findDirVectorIndex = 0;
	auto findDirVectorDataPtr = nodeItemGenerateMetaInfos.data( );
	for( ; findDirVectorIndex < findDirVectorCount; ++findDirVectorIndex )
		if( findDirVectorDataPtr[ findDirVectorIndex ].first == dir_name ) {
			// 类名与创建调用的映射列表
			auto &classNameMapVector = findDirVectorDataPtr[ findDirVectorIndex ].second;
			size_t classNameMapVectorCount = classNameMapVector.size( ), classNameMapVectorIndex = 0;
			auto classNameMapVectorDataPtr = classNameMapVector.data( );
			for( ; classNameMapVectorIndex < classNameMapVectorCount; ++classNameMapVectorIndex )
				if( classNameMapVectorDataPtr[ classNameMapVectorIndex ].first == itemNameTrimmed ) {
					classNameMapVectorDataPtr[ classNameMapVectorIndex ].second = generate_function;
					return true;
				}
			NodeItemGenerateMateInfoPairt_Type info( itemNameTrimmed, generate_function );
			classNameMapVector.emplace_back( info );
			// 匹配目录与类名映射

			size_t count = nodeItemDirClassMetaInfos.size( );
			auto pair = nodeItemDirClassMetaInfos.data( );
			for( size_t index = 0; index < count; ++index )
				if( pair[ index ].first == dirNameTrimmed ) {
					pair[ index ].second.emplace_back( itemNameTrimmed );
					return true;
				}

			DirClassItemMap_Type dirClassItem( dirNameTrimmed, { itemNameTrimmed } );
			nodeItemDirClassMetaInfos.emplace_back( dirClassItem );
			return true; // 找到文件夹，但是找不到对应的类，应该直接返回空
		}
	NodeItemGenerateMateInfoPairt_Type info( itemNameTrimmed, generate_function );
	NodeItemGenerateDirMateInfoPairt_Type dirMateInfoPairt( dirNameTrimmed, { info } );
	nodeItemGenerateMetaInfos.emplace_back( dirMateInfoPairt );
	DirClassItemMap_Type dirClassItem( dirNameTrimmed, { itemNameTrimmed } );
	nodeItemDirClassMetaInfos.emplace_back( dirClassItem );
	return true;
}
