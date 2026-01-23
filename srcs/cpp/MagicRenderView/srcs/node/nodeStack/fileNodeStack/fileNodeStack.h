#ifndef FILENODESTACK_H_H_HEAD__FILE__
#define FILENODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class FileNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	FileNodeStack( QObject *parent = nullptr );
};
#endif // FILENODESTACK_H_H_HEAD__FILE__
