#ifndef NODEITEMERRORINFO_H_H_HEAD__FILE__
#define NODEITEMERRORINFO_H_H_HEAD__FILE__
#pragma once
#include "../../enums/nodeItemEnum.h"

class NodeItemBuilderObj;
class NodeItemInfo;
class NodeItemErrorInfo {
	friend class NodeDirector;
private:
	const NodeItemBuilderObj *sender_sig_obj_ptr;
	size_t begin_inde;
	const NodeItemInfo *error_node_item_ptr;
	nodeItemEnum::Node_Item_Result_Type node_item_result;
	QString msg;
	nodeItemEnum::Node_Item_Builder_Type info_type;
public:
	virtual ~NodeItemErrorInfo( ) = default;
	NodeItemErrorInfo( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_inde, const NodeItemInfo *const error_node_item_ptr, const nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, const nodeItemEnum::Node_Item_Builder_Type info_type )
		: sender_sig_obj_ptr( sender_sig_obj_ptr ),
		begin_inde( begin_inde ),
		error_node_item_ptr( error_node_item_ptr ),
		node_item_result( node_item_result ),
		msg( msg ),
		info_type( info_type ) { }
	virtual NodeItemBuilderObj * getSenderSigObjPtr( ) const { return sender_sig_obj_ptr; }
	virtual const size_t & getBeginInde( ) const { return begin_inde; }
	virtual const NodeItemInfo * getErrorNodeItemPtr( ) const { return error_node_item_ptr; }
	virtual nodeItemEnum::Node_Item_Result_Type getNodeItemResult( ) const { return node_item_result; }
	virtual const QString & getMsg( ) const { return msg; }
	virtual nodeItemEnum::Node_Item_Builder_Type getInfoType( ) const { return info_type; }
};

#endif // NODEITEMERRORINFO_H_H_HEAD__FILE__
