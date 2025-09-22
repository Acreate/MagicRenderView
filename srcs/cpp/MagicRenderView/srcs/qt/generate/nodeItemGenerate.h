#ifndef NODEITEMGENERATE_H_H_HEAD__FILE__
#define NODEITEMGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../node/item/nodeItem.h"

/// @brief 节点生成器
class NodeItemGenerate final {
private:
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
public:
	/// @brief 节点指针类型
	using NodeItem_Type = NodeItem;
	/// @brief 节点字符串类型
	using NodeItem_String_Type = NodeItem_Type::NodeItemString_Type;
	/// @brief 父对象指针类型
	using NodeItem_ParentPtr_Type = NodeItem_Type::NodeItem_ParentPtr_Type;
	/// @brief 节点创建函数指针类型
	using NodeItemGenerateCall_Type = NodeItem_Type *( );
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
	/// @brief 保存生成的节点
	static std_vector< NodeItem_Type * > generateNodeItems;
private:
	/// @brief 追加一个节点生成器
	/// @param dir_name 目录名称
	/// @param item_name 节点名称
	/// @param generate_function 生成调用函数
	/// @return 添加失败返回 false
	static bool appendGenerateNodeItemInfo( const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name, const NodeItemGenerateFunction_Type &generate_function );
	/// @brief 建立信号链接
	/// @param sender_obj 信号对象指针
	static void cnnectSignal( NodeItem_Type *sender_obj );
public:
	/// @brief 获取生成代码
	/// @param sender_obj 生成代码对象 
	/// @return 对象的生成代码
	static size_t getGenerateCode( NodeItem_Type *sender_obj );
	/// @brief 从生成代码当中获取对象指针
	/// @param code 生成代码
	/// @return 对象指针
	static NodeItem_Type * fromGenerateCodeGetNodeItemPtr( const size_t &code );
	/// @brief 获取支持的节点列表
	/// @return 支持的节点列表
	static DirClassItemMapVector_Type getSupperTyeNodes( ) {
		return nodeItemDirClassMetaInfos;
	}
	/// @brief 创建节点对象
	/// @param dir_name 节点目录
	/// @param item_name 节点名称
	/// @return 失败返回 nullptr
	static NodeItem_Type * createNodeItem( const NodeItem_String_Type &dir_name, const NodeItem_String_Type &item_name );
	/// @brief 生成节点
	/// @tparam TItemType 生成的节点类型
	/// @return 失败返回 nullptr
	template< typename TItemType >
		requires requires ( NodeItem_String_Type name, NodeItem_Type *item ) {
			name = TItemType::getStaticMetaObjectName( );
			name = TItemType::getStaticMetaObjectDir( );
			item = new TItemType( );
		}
	static NodeItem_Type * createNodeItem( ) {
		return NodeItemGenerate::createNodeItem( TItemType::getStaticMetaObjectDir( ), TItemType::getStaticMetaObjectName( ) );
	}
	/// @brief 追加节点生成器
	/// @tparam TItemType 追加的节点类型
	template< typename TItemType >
		requires requires ( NodeItem_String_Type name, NodeItem_Type *item ) {
			name = TItemType::getStaticMetaObjectName( );
			name = TItemType::getStaticMetaObjectDir( );
			item = new TItemType( );
		}
	static bool appendGenerateNodeItemInfo( ) {
		return NodeItemGenerate::appendGenerateNodeItemInfo( TItemType::getStaticMetaObjectDir( ), TItemType::getStaticMetaObjectName( ), []( ) {
			return new TItemType( );
		} );
	}
};

#endif // NODEITEMGENERATE_H_H_HEAD__FILE__
