#ifndef NODEITEMGENERATE_H_H_HEAD__FILE__
#define NODEITEMGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../node/item/nodeItem.h"

/// @brief 节点生成器
class NodeItemGenerate final {
public:
	/// @brief 节点指针类型
	using NodeItem_Type = NodeItem;
	/// @brief 节点字符串类型
	using NodeItem_String_Type = NodeItem_Type::NodeItemString_Type;
	/// @brief 父对象指针类型
	using NodeItem_ParentPtr_Type = NodeItem_Type::NodeItem_ParentPtr_Type;
	/// @brief 节点创建函数指针类型
	using NodeItemGenerateCall_Type = NodeItem_Type *( NodeItem_ParentPtr_Type * );
	/// @brief 节点创建函数调用类型
	using NodeItemGenerateFunction_Type = std_function< NodeItemGenerateCall_Type >;
	/// @brief 节点名称创建信息类型
	using NodeItemGenerateMateInfoPairt_Type = std_pairt< NodeItem_String_Type, NodeItemGenerateFunction_Type >;
	/// @brief 节点名称映射序列类型
	using NodeItemGenerateNameMateInfoVector_Type = std_vector< NodeItemGenerateMateInfoPairt_Type >;
	/// @brief 节点目录映射创建信息类型
	using NodeItemGenerateDirMateInfoPairt_Type = std_pairt< NodeItem_String_Type, NodeItemGenerateNameMateInfoVector_Type >;
	/// @brief 节点创建信息序列类型
	using NodeItemGenerateMetaInfoVector_Type = std_vector< NodeItemGenerateDirMateInfoPairt_Type >;
	/// @brief 目录与类名映射类型
	using DirClassItemMap_Type = std_pairt< NodeItem_String_Type, std_vector< NodeItem_String_Type > >;
	/// @brief 目录与类名映射序列类型
	using DirClassItemMapVector_Type = std_vector< DirClassItemMap_Type >;
private:
	/// @brief 节点生成建造对象信息列表
	static NodeItemGenerateMetaInfoVector_Type nodeItemGenerateMetaInfos;
	/// @brief 节点目录与节点类名称映射列表
	static DirClassItemMapVector_Type nodeItemDirClassMetaInfos;
private:
	/// @brief 追加一个节点生成器
	/// @param dir_name 目录名称
	/// @param item_name 节点名称
	/// @param generate_function 生成调用函数
	/// @return 添加失败返回 false
	static bool appendNodeItemInfo( const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name, const NodeItemGenerateFunction_Type &generate_function );
public:
	/// @brief 创建节点对象
	/// @param parent 节点对象依赖父节点
	/// @param dir_name 节点目录
	/// @param item_name 节点名称
	/// @return 失败返回 nullptr
	static NodeItem_Type * createNodeItem( NodeItem_ParentPtr_Type *parent, const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name );
	/// @brief 生成节点
	/// @tparam TItemType 生成的节点类型
	/// @param parent 生成节点关联父对象
	/// @return 失败返回 nullptr
	template< typename TItemType >
		requires requires ( NodeItem_String_Type name, NodeItem_Type *item, NodeItem_ParentPtr_Type *parent ) {
			name = TItemType::getStaticMetaObjectName( );
			name = TItemType::getStaticMetaObjectDir( );
			item = new TItemType( parent );
		}
	static NodeItem_Type * createNodeItem( NodeItem_ParentPtr_Type *parent ) {
		return NodeItemGenerate::createNodeItem( parent, TItemType::getStaticMetaObjectDir( ), TItemType::getStaticMetaObjectName( ) );
	}
	/// @brief 追加节点生成器
	/// @tparam TItemType 追加的节点类型
	template< typename TItemType >
		requires requires ( NodeItem_String_Type name, NodeItem_Type *item, NodeItem_ParentPtr_Type *parent ) {
			name = TItemType::getStaticMetaObjectName( );
			name = TItemType::getStaticMetaObjectDir( );
			item = new TItemType( parent );
		}
	static bool appendNodeItemInfo( ) {
		return NodeItemGenerate::appendNodeItemInfo( TItemType::getStaticMetaObjectDir( ), TItemType::getStaticMetaObjectName( ), [] ( NodeItem_ParentPtr_Type *parent ) {
			return new TItemType( parent );
		} );
	}
	/// @brief 获取节点生成器当中的目录与类型映射信息
	/// @return 节点生成器当中的目录与类型映射信息序列
	static const DirClassItemMapVector_Type & getNodeItemDirClassMetaInfos( ) {
		return nodeItemDirClassMetaInfos;
	}
};

#endif // NODEITEMGENERATE_H_H_HEAD__FILE__
