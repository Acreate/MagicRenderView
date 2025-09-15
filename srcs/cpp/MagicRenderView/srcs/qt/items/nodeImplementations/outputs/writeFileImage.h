#ifndef WRITEFILEIMAGE_H_H_HEAD__FILE__
#define WRITEFILEIMAGE_H_H_HEAD__FILE__
#pragma once

#include "../../nodeItemWidget.h"

class VarType;
class WriteFileImage : public NodeItemWidget {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodeItemWidget );
protected:
	VarType *var;
protected:
	WriteFileImage( QWidget *parent );
};

#endif // WRITEFILEIMAGE_H_H_HEAD__FILE__
