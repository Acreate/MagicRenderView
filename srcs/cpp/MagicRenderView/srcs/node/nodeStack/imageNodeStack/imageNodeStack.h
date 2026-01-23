#ifndef IMAGENODESTACK_H_H_HEAD__FILE__
#define IMAGENODESTACK_H_H_HEAD__FILE__

#include "../nodeStack.h"

class ImageNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	ImageNodeStack( QObject *parent = nullptr );
};

#endif // IMAGENODESTACK_H_H_HEAD__FILE__
