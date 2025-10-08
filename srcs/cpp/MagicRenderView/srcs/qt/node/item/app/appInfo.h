#ifndef APPINFO_H_H_HEAD__FILE__
#define APPINFO_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class AppInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	AppInfo( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Root; }
};
#endif // APPINFO_H_H_HEAD__FILE__
