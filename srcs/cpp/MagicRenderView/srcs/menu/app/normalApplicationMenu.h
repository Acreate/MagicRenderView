#ifndef NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
#define NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
#pragma once
#include <QMenu>
#include <QObject>

class ApplicationMenuStack;
class NormalApplicationMenu : public QMenu {
	Q_OBJECT;
public:
	NormalApplicationMenu( const QString &title, QWidget *parent )
		: QMenu( title, parent ) { }
	virtual bool init( ApplicationMenuStack *application_menu_stack ) {
		disconnect( this );
		return true;
	}
	~NormalApplicationMenu( ) override {
		emit release_signal( this );
		emit destroyed( this );
		disconnect( this );
	}
Q_SIGNALS:
	void release_signal( NormalApplicationMenu *release_ptr );
};

#endif // NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
