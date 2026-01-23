#ifndef NUMBERNODESTACK_H_H_HEAD__FILE__
#define NUMBERNODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class NumberNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	NumberNodeStack( QObject *parent = nullptr );
};

#endif // NUMBERNODESTACK_H_H_HEAD__FILE__
