#ifndef NORMALAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define NORMALAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#pragma once
#include <QToolBar>

class ApplicationMenuStack;
class NormalApplicationToolBar : public QToolBar {
	Q_OBJECT;
public:
	NormalApplicationToolBar( const QString &title, QWidget *parent )
		: QToolBar( title, parent ) { }
	virtual bool init( ApplicationMenuStack *application_menu_stack ) {
		disconnect( this );
		return true;
	}
	~NormalApplicationToolBar( ) override {
		emit release_signal( this );
		emit destroyed( this );
	}
Q_SIGNALS:
	void release_signal( NormalApplicationToolBar *release_ptr );
};

#endif // NORMALAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
