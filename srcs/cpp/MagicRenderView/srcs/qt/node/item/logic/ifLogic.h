﻿#ifndef IFLOGIC_H_H_HEAD__FILE__
#define IFLOGIC_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class IfLogic : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	IfLogic( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // IFLOGIC_H_H_HEAD__FILE__
