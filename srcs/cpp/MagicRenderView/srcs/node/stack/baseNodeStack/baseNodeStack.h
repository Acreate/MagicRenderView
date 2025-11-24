#ifndef BASENODESTACK_H_H_HEAD__FILE__
#define BASENODESTACK_H_H_HEAD__FILE__
#pragma once
#include "../nodeStack.h"

class BaseNodeStack : public NodeStack {
	Q_OBJECT;
protected:
	bool init( ) override;
public:
	QMenu * toMenu( ) override;
public:
	BaseNodeStack( QObject *parent = nullptr );
};

#endif // BASENODESTACK_H_H_HEAD__FILE__
