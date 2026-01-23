#ifndef SYSTEMNODESTACK_H_H_HEAD__FILE__
#define SYSTEMNODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class SystemNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	SystemNodeStack( QObject *parent = nullptr );
};

#endif // SYSTEMNODESTACK_H_H_HEAD__FILE__
