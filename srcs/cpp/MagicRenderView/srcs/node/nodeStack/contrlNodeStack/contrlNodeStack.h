#ifndef CONTRLNODESTACK_H_H_HEAD__FILE__
#define CONTRLNODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class ContrlNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	ContrlNodeStack( QObject *parent = nullptr );
};

#endif // CONTRLNODESTACK_H_H_HEAD__FILE__
