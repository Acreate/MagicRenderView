#ifndef VARMOD_H_H_HEAD__FILE__
#define VARMOD_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class VarMod : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarMod(  );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};
#endif // VARMOD_H_H_HEAD__FILE__
