#ifndef NORMALAPPLICATIONACTION_H_H_HEAD__FILE__
#define NORMALAPPLICATIONACTION_H_H_HEAD__FILE__
#pragma once
#include <QAction>
#include <QWidget>

class ApplicationMenuStack;
class NormalApplicationAction : public QAction {
	Q_OBJECT;
protected:
	std::function< bool ( QWidget * ) > actionFunction;
private:
	void triggered();
public:
	~NormalApplicationAction( ) override;
	virtual bool init( ApplicationMenuStack *application_menu_stack_ptr );
	virtual bool run( QWidget *parent ) const;
Q_SIGNALS:
	void release_signal( NormalApplicationAction *action );
	void trigg_signal( NormalApplicationAction *action );
};

#endif // NORMALAPPLICATIONACTION_H_H_HEAD__FILE__
