#ifndef NODEINPUTPROT_H_H_HEAD__FILE__
#define NODEINPUTPROT_H_H_HEAD__FILE__
#pragma once
#include "../NodePort.h"

class NodeInputProt : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
public:
	NodeInputProt( QObject *parent, VarType *bind_var ) : NodePort( parent, bind_var ) {
	}
};
#endif // NODEINPUTPROT_H_H_HEAD__FILE__
