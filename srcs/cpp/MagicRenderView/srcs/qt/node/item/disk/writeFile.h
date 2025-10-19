#ifndef WRITEFILE_H_H_HEAD__FILE__
#define WRITEFILE_H_H_HEAD__FILE__
#pragma once
#include "../nodeItem.h"

class WriteFile : public NodeItem {
	Q_OBJECT;
	Def_NodeItem_Last_StaticMetaInfo( );
protected:
	WriteFile( );
public:
	bool intPortItems( MainWidget *parent ) override;
	Def_Last_Mate_Node_Type( Process );
};

#endif // WRITEFILE_H_H_HEAD__FILE__
