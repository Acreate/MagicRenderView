#ifndef DEBUGNODESTACK_H_H_HEAD__FILE__
#define DEBUGNODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class DebugNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	DebugNodeStack( QObject *parent = nullptr );
};
#endif // DEBUGNODESTACK_H_H_HEAD__FILE__
