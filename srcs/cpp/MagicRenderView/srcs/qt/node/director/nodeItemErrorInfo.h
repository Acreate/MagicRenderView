#ifndef NODEITEMERRORINFO_H_H_HEAD__FILE__
#define NODEITEMERRORINFO_H_H_HEAD__FILE__
#pragma once
#include "../../enums/nodeItemEnum.h"

class NodeItemBuilderObj;
class NodeItemInfo;
class NodeItemErrorInfo {
	friend class NodeDirector;
private:
	const NodeItemBuilderObj *senderSigObjPtr;
	size_t beginIndex;
	const NodeItemInfo *errorNodeItemPtr;
	nodeItemEnum::Node_Item_Result_Type nodeItemResult;
	QString msg;
	nodeItemEnum::Node_Item_Builder_Type infoType;
public:
	virtual ~NodeItemErrorInfo( ) = default;
	NodeItemErrorInfo( ) : nodeItemResult( nodeItemEnum::Node_Item_Result_Type::NotImplementation ), senderSigObjPtr( nullptr ), beginIndex( 0 ), errorNodeItemPtr( nullptr ), msg( ), infoType( nodeItemEnum::Node_Item_Builder_Type::None ) { }
	NodeItemErrorInfo( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_inde, const NodeItemInfo *const error_node_item_ptr, const nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, const nodeItemEnum::Node_Item_Builder_Type info_type )
		: senderSigObjPtr( sender_sig_obj_ptr ),
		beginIndex( begin_inde ),
		errorNodeItemPtr( error_node_item_ptr ),
		nodeItemResult( node_item_result ),
		msg( msg ),
		infoType( info_type ) { }
	virtual const NodeItemBuilderObj * getSenderSigObjPtr( ) const { return senderSigObjPtr; }
	virtual size_t getBeginIndex( ) const { return beginIndex; }
	virtual const NodeItemInfo * getErrorNodeItemPtr( ) const { return errorNodeItemPtr; }
	virtual nodeItemEnum::Node_Item_Result_Type getNodeItemResult( ) const { return nodeItemResult; }
	virtual const QString & getMsg( ) const { return msg; }
	virtual nodeItemEnum::Node_Item_Builder_Type getInfoType( ) const { return infoType; }
};

#endif // NODEITEMERRORINFO_H_H_HEAD__FILE__
