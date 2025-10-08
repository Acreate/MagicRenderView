#ifndef STRAPPEND_H_H_HEAD__FILE__
#define STRAPPEND_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrAppend : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrAppend( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Node_Item_Type getNodeType( ) const override { return Node_Item_Type::Process; }
};
#endif // STRAPPEND_H_H_HEAD__FILE__
