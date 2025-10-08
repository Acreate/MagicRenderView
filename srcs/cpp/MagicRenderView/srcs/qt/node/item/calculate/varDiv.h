#ifndef VARDIV_H_H_HEAD__FILE__
#define VARDIV_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class VarDiv : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	VarDiv( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // VARDIV_H_H_HEAD__FILE__
