#ifndef NODEITEMGENERATE_H_H_HEAD__FILE__
#define NODEITEMGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../item/nodeItem.h"
/// @brief 节点生成器
class NodeItemGenerate {
public:
	/// @brief 节点字符串类型
	using NodeItemString_Type = QString;
	/// @brief 节点指针类型
	using NodeItem_Type = NodeItem;
	/// @brief 父对象指针类型
	using ParentPtr_Type = QObject;
	/// @brief 节点创建函数指针类型
	using NodeItemGenerateCall_Type = NodeItem_Type *( ParentPtr_Type * );
	/// @brief 节点创建函数调用类型
	using NodeItemGenerateFunction_Type = std_function< NodeItemGenerateCall_Type >;
	/// @brief 节点名称创建信息类型
	using NodeItemGenerateMateInfoPairt_Type = std_pairt< NodeItemString_Type, NodeItemGenerateFunction_Type >;
	/// @brief 节点名称映射序列类型
	using NodeItemGenerateNameMateInfoVector_Type = std_vector< NodeItemGenerateMateInfoPairt_Type >;
	/// @brief 节点目录映射创建信息类型
	using NodeItemGenerateDirMateInfoPairt_Type = std_pairt< NodeItemString_Type, NodeItemGenerateNameMateInfoVector_Type >;
	/// @brief 节点创建信息序列类型
	using NodeItemGenerateMetaInfoVector_Type = std_vector< NodeItemGenerateDirMateInfoPairt_Type >;
	/// @brief 目录与类名映射类型
	using DirClassItemMap_Type = std_pairt< NodeItemString_Type, NodeItemString_Type >;
	/// @brief 目录与类名映射序列类型
	using DirClassItemMapVector_Type = std_vector< DirClassItemMap_Type >;
private:
	/// @brief 节点生成建造对象信息列表
	static NodeItemGenerateMetaInfoVector_Type nodeItemGenerateMetaInfos;
	/// @brief 节点目录与节点类名称映射列表
	static DirClassItemMapVector_Type nodeItemDirClassMetaInfos;
private:
	/// @brief 创建节点对象
	/// @param parent 节点对象依赖父节点
	/// @param dir_name 节点目录
	/// @param item_name 节点名称
	/// @return 失败返回 nullptr
	static NodeItem_Type * createNodeItem( ParentPtr_Type *parent, const NodeItemString_Type &dir_name, const NodeItemString_Type &item_name );
	/// @brief 追加一个节点生成器
	/// @param dir_name 目录名称
	/// @param item_name 节点名称
	/// @param generate_function 生成调用函数
	/// @return 添加失败返回 false
	static bool appendNodeItemInfo( const NodeItemString_Type &dir_name, const NodeItemString_Type &item_name, const NodeItemGenerateFunction_Type &generate_function );
public:
	/// @brief 生成节点
	/// @tparam TItemType 生成的节点类型
	/// @param parent 生成节点关联父对象
	/// @return 失败返回 nullptr
	template< typename TItemType >
		requires requires ( QString name, NodeItem *item, ParentPtr_Type *parent ) {
			name = TItemType::getStaticMetaObjectName( );
			name = TItemType::getStaticMetaObjectDir( );
			item = new TItemType( parent );
		}
	static NodeItem_Type * createNodeItem( ParentPtr_Type *parent ) {
		return NodeItemGenerate::createNodeItem( parent, TItemType::getStaticMetaObjectDir( ), TItemType::getStaticMetaObjectName( ) );
	}
	/// @brief 追加节点生成器
	/// @tparam TItemType 追加的节点类型
	template< typename TItemType >
		requires requires ( QString name, NodeItem *item, ParentPtr_Type *parent ) {
			name = TItemType::getStaticMetaObjectName( );
			name = TItemType::getStaticMetaObjectDir( );
			item = new TItemType( parent );
		}
	static bool appendNodeItemInfo( ) {
		return NodeItemGenerate::appendNodeItemInfo( TItemType::getStaticMetaObjectDir( ), TItemType::getStaticMetaObjectName( ), [] ( ParentPtr_Type *parent ) {
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
