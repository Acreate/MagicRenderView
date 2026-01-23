#ifndef DATETIMENODESTACK_H_H_HEAD__FILE__
#define DATETIMENODESTACK_H_H_HEAD__FILE__


#include "../nodeStack.h"

class DateTimeNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	DateTimeNodeStack( QObject *parent = nullptr );
};

#endif // DATETIMENODESTACK_H_H_HEAD__FILE__
