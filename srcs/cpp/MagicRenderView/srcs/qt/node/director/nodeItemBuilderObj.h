#ifndef NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
#define NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <qt/enums/nodeItemEnum.h>

#include <alias/type_alias.h>

class NodeItemInfo;
class NodeItemBuilderObj : public QObject {
	Q_OBJECT;
private:
	friend class NodeDirector;
protected:
	nodeItemEnum::Node_Item_Builder_Type moduleBuilderStaus;
	QString msg;
	std_vector< NodeItemInfo * > startNodeItemInfoVector;
	std_vector< NodeItemInfo * > runNodeItemInfoVector;
	size_t currentVectorIndex;
	size_t currentVectorCount;
	NodeItemInfo **runNodeItemInfoArrayPtr;
protected:
	NodeItemBuilderObj( QObject *parent = nullptr );
	virtual bool addBuilderNodeItem( NodeItemInfo *node_item_info );
	virtual bool builderNodeItemVector( );
	virtual bool fillNodeItemVector( NodeItemInfo *node_item_info, std_vector< NodeItemInfo * > &result_out_node_item_info_ptr );
	virtual size_t sortNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_count );
	virtual void sortNodeItemVector( std_vector< NodeItemInfo * > &result_out_node_item_info_ptr ) {
		sortNodeItemVector( result_out_node_item_info_ptr.data( ), result_out_node_item_info_ptr.size( ) );
	}
	/// @brief 检查编译数组当中的依赖是否完整
	/// @return true 表示完整
	virtual bool checkNodeItemBuilderVector( );
	/// @brief 移动对象到指定位置
	/// @param node_item_info_array_ptr 操作数组
	/// @param inster_node_item_info_source_point 拷贝位置
	/// @param inster_node_item_info_target_point 覆盖位置
	virtual void moveNodeItemVector( NodeItemInfo **node_item_info_array_ptr, const size_t &inster_node_item_info_source_point, const size_t &inster_node_item_info_target_point );
public:
	~NodeItemBuilderObj( ) override;
	virtual nodeItemEnum::Node_Item_Builder_Type builderStatus( ) const;
	virtual nodeItemEnum::Node_Item_Builder_Type runCurrentNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type nextNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type toStartNodeItem( );
	virtual bool getInfo( QString &result_msg ) const;
};

#endif // NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
