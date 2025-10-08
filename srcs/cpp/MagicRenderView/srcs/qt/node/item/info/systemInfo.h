#ifndef SYSTEMINFO_H_H_HEAD__FILE__
#define SYSTEMINFO_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class SystemInfo : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	SystemInfo(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Root; }
};
#endif // SYSTEMINFO_H_H_HEAD__FILE__
