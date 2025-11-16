#ifndef NODEITEMFINISHINFO_H_H_HEAD__FILE__
#define NODEITEMFINISHINFO_H_H_HEAD__FILE__
#pragma once

class NodeItemInfo;
class NodeItemBuilderObj;
class NodeItemFinishInfo {
	friend class NodeDirector;
	NodeItemBuilderObj *senderSigObjPtr;
	size_t beginIndex;
	const NodeItemInfo *finishNodeItemPtr;
public:
	virtual ~NodeItemFinishInfo( ) = default;
	NodeItemFinishInfo( ) : senderSigObjPtr( nullptr ), beginIndex( 0 ), finishNodeItemPtr( nullptr ) { }
	NodeItemFinishInfo( NodeItemBuilderObj *const sender_sig_obj_ptr, const size_t begin_inde, const NodeItemInfo *const finish_node_item_ptr )
		: senderSigObjPtr( sender_sig_obj_ptr ),
		beginIndex( begin_inde ),
		finishNodeItemPtr( finish_node_item_ptr ) { }
	virtual NodeItemBuilderObj * getSenderSigObjPtr( ) const { return senderSigObjPtr; }
	virtual size_t getBeginInde( ) const { return beginIndex; }
	virtual const NodeItemInfo * getFinishNodeItemPtr( ) const { return finishNodeItemPtr; }
	virtual void clear( ) {
		senderSigObjPtr = nullptr;
		beginIndex = 0;
		finishNodeItemPtr = nullptr;
	}
};

#endif // NODEITEMFINISHINFO_H_H_HEAD__FILE__
