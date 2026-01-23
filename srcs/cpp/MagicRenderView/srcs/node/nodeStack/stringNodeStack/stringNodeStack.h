#ifndef STRINGNODESTACK_H_H_HEAD__FILE__
#define STRINGNODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class StringNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	StringNodeStack( QObject *parent = nullptr );
};

#endif // STRINGNODESTACK_H_H_HEAD__FILE__
