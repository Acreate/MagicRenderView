#ifndef WINDOWMENU_H_H_HEAD__FILE__
#define WINDOWMENU_H_H_HEAD__FILE__
#pragma once

#include <QMenu>
class WindowMenu : public QMenu {
	Q_OBJECT;
public:
	virtual bool initWindowMenu( ) {
		return false;
	}
};

#endif // WINDOWMENU_H_H_HEAD__FILE__
