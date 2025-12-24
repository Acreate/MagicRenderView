#ifndef APPLICATIONMENUSTACK_H_H_HEAD__FILE__
#define APPLICATIONMENUSTACK_H_H_HEAD__FILE__
#pragma once

#include <QObject>

class ApplicationMenuStack : public QObject {
	Q_OBJECT;
public:
	ApplicationMenuStack( QObject *parent = nullptr );
	virtual bool initStack( );
};
#endif // APPLICATIONMENUSTACK_H_H_HEAD__FILE__
