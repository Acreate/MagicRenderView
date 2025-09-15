#ifndef PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
#define PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../../alias/type_alias.h"
class VarType;
class ProtOutputItemWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< VarType > var;
public:
	virtual const std_shared_ptr< VarType > & getVar( ) const {
		return var;
	}
public:
	ProtOutputItemWidget( QWidget *parent = nullptr );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
