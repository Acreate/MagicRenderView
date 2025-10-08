#ifndef STRREMOVE_H_H_HEAD__FILE__
#define STRREMOVE_H_H_HEAD__FILE__
#pragma once

#include "../nodeItem.h"

class StrRemove : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	StrRemove(  );
public:
	bool intPortItems( MainWidget *parent ) override;
};
#endif // STRREMOVE_H_H_HEAD__FILE__
