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
	Def_Last_Mate_Node_Type( Node_Item_Type::Process );
};
#endif // APPINFO_H_H_HEAD__FILE__
