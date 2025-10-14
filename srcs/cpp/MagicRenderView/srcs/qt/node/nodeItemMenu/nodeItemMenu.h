#ifndef NODEITEMMENU_H_H_HEAD__FILE__
#define NODEITEMMENU_H_H_HEAD__FILE__
#pragma once
#include <qmenu.h>

class NodeItemMenu : public QMenu{
	Q_OBJECT;
public:
	NodeItemMenu( const QString &title = "", QWidget *parent = nullptr );
	~NodeItemMenu( ) override;
};

#endif // NODEITEMMENU_H_H_HEAD__FILE__
