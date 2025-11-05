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
public:
	~NodeItemBuilderObj( ) override;
	virtual nodeItemEnum::Node_Item_Builder_Type builderStatus( ) const;
	virtual nodeItemEnum::Node_Item_Builder_Type runCurrentNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type nextNodeItem( );
	virtual nodeItemEnum::Node_Item_Builder_Type toStartNodeItem( );
	virtual bool getInfo( QString &result_msg ) const;
};

#endif // NODEITEMBUILDEROBJ_H_H_HEAD__FILE__
