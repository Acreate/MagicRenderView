#ifndef WRITEFILETXT_H_H_HEAD__FILE__
#define WRITEFILETXT_H_H_HEAD__FILE__
#pragma once



#include "../../nodeItemWidget.h"

class WriteFileTxt : public NodeItemWidget {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( WriteFileTxt, NodeItemWidget );
protected:
	WriteFileTxt(QWidget* parent) : NodeItemWidget( parent ){}
};
#endif // WRITEFILETXT_H_H_HEAD__FILE__
