#include "./nodeItemGenerate.h"

NodeItemGenerate::NodeItemGenerateMetaInfoVector_Type NodeItemGenerate::nodeItemGenerateMetaInfos;
NodeItemGenerate::DirClassItemMapVector_Type NodeItemGenerate::nodeItemDirClassMetaInfos;
std_vector< NodeItemGenerate::NodeItem_Type * > NodeItemGenerate::generateNodeItems;

void NodeItemGenerate::cnnectSignal( NodeItemGenerate::NodeItem_Type *sender_obj ) {
	QObject::connect( sender_obj, &NodeItem_Type::releaseThiNodeItem, [] ( NodeItem *release_node_item ) {
		size_t generateNodeItemsCount = generateNodeItems.size( );
		auto generateNodeitemsPtr = generateNodeItems.data( );
		size_t generateNodeItemsIndex = 0;
		for( ; generateNodeItemsIndex < generateNodeItemsCount; ++generateNodeItemsIndex )
			if( release_node_item == generateNodeitemsPtr[ generateNodeItemsIndex ] ) {
				generateNodeitemsPtr[ generateNodeItemsIndex ] = nullptr;
				break;
			}

	} );
}
size_t NodeItemGenerate::getGenerateCode( NodeItem_Type *sender_obj ) {

	size_t generateNodeItemsCount = generateNodeItems.size( );
	auto generateNodeitemsPtr = generateNodeItems.data( );
	size_t generateNodeItemsIndex = 0;
	for( ; generateNodeItemsIndex < generateNodeItemsCount; ++generateNodeItemsIndex )
		if( sender_obj == generateNodeitemsPtr[ generateNodeItemsIndex ] )
			return generateNodeItemsIndex + 1;
	return 0;
}
NodeItemGenerate::NodeItem_Type * NodeItemGenerate::fromGenerateCodeGetNodeItemPtr( const size_t &code ) {
	size_t generateNodeItemsCount = generateNodeItems.size( );
	auto generateNodeitemsPtr = generateNodeItems.data( );
	size_t codeInde = code - 1;
	if( codeInde < generateNodeItemsCount )
		return generateNodeitemsPtr[ codeInde ]; // 优先返回
	// 次要返回
	for( size_t index = 0; index < generateNodeItemsCount; ++index )
		if( generateNodeitemsPtr[ index ]->generateCode == code )
			return generateNodeitemsPtr[ index ];
	// 找不到返回
	return nullptr;
}

NodeItemGenerate::NodeItem_Type * NodeItemGenerate::createNodeItem( const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name ) {

	NodeItemGenerate::NodeItem_Type *result = nullptr;
	auto dirNameTrimmed = dir_name.trimmed( );
	if( dirNameTrimmed.isEmpty( ) ) {
		tools::debug::printError( "文件夹名称为空，不合法，直接返回" );
		return result; // 文件夹名称为空，不合法，直接返回
	}
	auto itemNameTrimmed = item_name.trimmed( );
	if( itemNameTrimmed.isEmpty( ) ) {
		tools::debug::printError( "类名称为空，不合法，直接返回" );
		return result; // 类名称为空，不合法，直接返回
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
					result = classNameMapVectorDataPtr[ classNameMapVectorIndex ].second( );
					if( result ) {
						size_t count = generateNodeItems.size( );
						if( count > 0 ) {
							auto itemsPtr = generateNodeItems.data( );
							size_t index = 0;
							for( ; index < count; ++index )
								if( itemsPtr[ index ] == nullptr ) {
									result->generateCode = index + 1;
									if( result->generateCode == 0 ) {
										delete result;
										result = nullptr;
										break;
									}
									itemsPtr[ index ] = result;
									cnnectSignal( result );
									return result;
								}
						}
						result->generateCode = 1;
						generateNodeItems.emplace_back( result );
						cnnectSignal( result );
					}
					return result;
				}
			return result; // 找到文件夹，但是找不到对应的类，应该直接返回空
		}
	return result;
}

bool NodeItemGenerate::appendGenerateNodeItemInfo( const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name, const NodeItemGenerateFunction_Type &generate_function ) {

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
