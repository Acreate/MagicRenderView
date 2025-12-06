#ifndef NODEINFOTITLE_H_H_HEAD__FILE__
#define NODEINFOTITLE_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QLabel;
class NodeInfoTitle : public QWidget {
	Q_OBJECT;
protected:
	QLabel *title;
public:
	NodeInfoTitle( QWidget *parent = nullptr );
	virtual void setTitleText( const QString &new_title_text );
	virtual QString getTitleText( ) const;
};

#endif // NODEINFOTITLE_H_H_HEAD__FILE__
