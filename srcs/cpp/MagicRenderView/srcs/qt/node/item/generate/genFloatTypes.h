﻿#ifndef GENFLOATTYPES_H_H_HEAD__FILE__
#define GENFLOATTYPES_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class GenFloatTypes : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	GenFloatTypes( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // GENFLOATTYPES_H_H_HEAD__FILE__
