#ifndef FREEMENU_H_H_HEAD__FILE__
#define FREEMENU_H_H_HEAD__FILE__
#pragma once
#include <QMenu>
class FreeMenu: public QMenu {
	Q_OBJECT;
public:
	virtual bool initFreeMenu( ) {
		return false;
	}
};


#endif // FREEMENU_H_H_HEAD__FILE__
