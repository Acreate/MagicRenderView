#ifndef READFILETXT_H_H_HEAD__FILE__
#define READFILETXT_H_H_HEAD__FILE__
#pragma once


#include "../../nodeItemWidget.h"

class ReadFileTxt : public NodeItemWidget {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( ReadFileTxt, NodeItemWidget );
protected:
	ReadFileTxt( QWidget *parent );
};

#endif // READFILETXT_H_H_HEAD__FILE__
