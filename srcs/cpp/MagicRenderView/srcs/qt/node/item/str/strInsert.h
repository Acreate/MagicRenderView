#ifndef STRINSERT_H_H_HEAD__FILE__
#define STRINSERT_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrInsert : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrInsert(  );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // STRINSERT_H_H_HEAD__FILE__
