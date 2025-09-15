#ifndef NODEINPUTPORT_H_H_HEAD__FILE__
#define NODEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../NodePort.h"


#include "../outputProt/nodeOutputPort.h"
class NodeInputPort : public NodePort {
	Q_OBJECT;
	Def_Last_Firend_StaticMetaInfo( NodePort );
protected:
	std_vector< NodeOutputPort * > linkOutputVector;
public:
	NodeInputPort( NodeItem *parent ) : NodePort( parent ) {
	}
	void updateProtLayout( ) override;
	virtual void linkOutputPort( NodeOutputPort *output_port ) = 0;
};
#endif // NODEINPUTPORT_H_H_HEAD__FILE__
