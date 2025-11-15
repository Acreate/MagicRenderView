#ifndef NODEITEMBUILDERMODULE_H_H_HEAD__FILE__
#define NODEITEMBUILDERMODULE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

#include "../../enums/nodeItemEnum.h"

class NodeDirector;
class VarGenerate;
class Application;
class NodeItem;
class NodeItemInfo;
class NodeItemBuilderModule : public QObject {
	Q_OBJECT;
public:
	using TFRunResultFunction = std_function< bool( const size_t &, const NodeItemInfo *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type ) >;
protected:
	nodeItemEnum::Node_Item_Builder_Type moduleBuilderStaus;
	QString msg;
	std_vector< NodeItemInfo * > startNodeItemInfoVector;
	std_vector< NodeItemInfo * > runNodeItemInfoVector;
	size_t currentVectorIndex;
	size_t currentVectorCount;
	NodeItemInfo **runNodeItemInfoArrayPtr;
	Application *applicationInstancePtr;
	VarGenerate *varGenerate;
	NodeDirector *nodeDirector;
protected:
	NodeItemBuilderModule( );
	virtual bool fillCurrentRunNodeItemValue( size_t begin_index, NodeItemInfo *node_item_ptr, nodeItemEnum::Node_Item_Builder_Type &builder_result, nodeItemEnum::Node_Item_Result_Type &error_item_result, QString &error_msg );
	virtual bool runItemNodeInfo( size_t begin_index, NodeItemInfo *node_item_ptr, const TFRunResultFunction &fill_param_run_error_function, const TFRunResultFunction &fill_run_error_function, const std_function<bool(const size_t &, NodeItemInfo *)> &finish_function );
protected:
	static std_vector< NodeItemInfo * > findEndAtStartNode( NodeItemInfo *end_node_info_ptr );
public:
	static std_vector< NodeItemBuilderModule * > generateModuleVector( NodeItemInfo **node_item_info_array_ptr, const size_t &node_item_info_array_count );
public:
	virtual nodeItemEnum::Node_Item_Builder_Type getModuleBuilderStaus( ) const { return moduleBuilderStaus; }
	virtual const QString & getMsg( ) const { return msg; }
	virtual const std_vector< NodeItemInfo * > & getStartNodeItemInfoVector( ) const { return startNodeItemInfoVector; }
	virtual const std_vector< NodeItemInfo * > & getRunNodeItemInfoVector( ) const { return runNodeItemInfoVector; }
	virtual bool builderNodeItemVector( );
	virtual bool runCurrentItemNodeInfo( size_t begin_index, const TFRunResultFunction &fill_param_run_error_function, const TFRunResultFunction &fill_run_error_function, const std_function<bool(const size_t &, NodeItemInfo *)> &finish_function );
	virtual bool isLastNodeItem( ) const;
Q_SIGNALS:
	void error_node_item_signal( NodeItemBuilderModule *sender_sig_obj_ptr, const NodeItem *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type );
	void finish_node_item_signal( NodeItemBuilderModule *sender_sig_obj_ptr, const NodeItem *finish_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result );
};

#endif // NODEITEMBUILDERMODULE_H_H_HEAD__FILE__
