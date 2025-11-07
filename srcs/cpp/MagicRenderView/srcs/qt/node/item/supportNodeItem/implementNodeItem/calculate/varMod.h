#ifndef VARMOD_H_H_HEAD__FILE__
#define VARMOD_H_H_HEAD__FILE__
#pragma once


#include "../../processNodeItem.h"

class VarMod : public ProcessNodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarMod(  );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // VARMOD_H_H_HEAD__FILE__
