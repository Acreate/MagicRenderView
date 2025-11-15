#ifndef NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
#define NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <qt/enums/nodeItemEnum.h>

#include <alias/type_alias.h>

class NodeItem;
class VarGenerate;
class Application;
class NodeItemBuilderModule;
class NodeItemInfo;
class NodeItemBuilderObj : public QObject {
	Q_OBJECT;
private:
	friend class NodeDirector;
protected:
	std_vector< NodeItemInfo * > startNodeItemInfoVector;
	std_vector< NodeItemInfo * > runNodeItemInfoVector;
	std_vector_pairt< size_t, NodeItemBuilderModule * > subNodeItemBuilderModuleVector;
	size_t currentNodeItemBuilderModuleVectorIndex;
	size_t currentNodeItemBuilderModuleVectorCount;
	std_vector_pairt< size_t, NodeItemBuilderModule * >::pointer runNodeItemBuilderModuleArrayPtr;

	size_t currentVectorIndex;
	size_t currentVectorCount;
	NodeItemInfo **runNodeItemInfoArrayPtr;
	Application *applicationInstancePtr;
	VarGenerate *varGenerate;
	NodeDirector *nodeDirector;
protected:
	NodeItemBuilderObj( QObject *parent = nullptr );
	virtual bool addBuilderNodeItem( NodeItemInfo *node_item_info );
	virtual bool builderNodeItemVector( );
	virtual bool fillCurrentRunNodeItemValue( size_t begin_index, NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg );
	virtual bool runItemNodeInfo( size_t begin_index, NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg );
	virtual nodeItemEnum::Node_Item_Builder_Type runCurrentNodeItem( NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg );
public:
	~NodeItemBuilderObj( ) override;
	virtual nodeItemEnum::Node_Item_Builder_Type nextNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type toStartNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type runAllNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type runListNodeItem( );
Q_SIGNALS:
	void error_node_item_signal( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_inde, const NodeItemInfo *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type );
	void finish_node_item_signal( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_inde, const NodeItemInfo *finish_node_item_ptr );
};

#endif // NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
