﻿#ifndef WRITEIMAGE_H_H_HEAD__FILE__
#define WRITEIMAGE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class WriteImage : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	WriteImage( );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // WRITEIMAGE_H_H_HEAD__FILE__
