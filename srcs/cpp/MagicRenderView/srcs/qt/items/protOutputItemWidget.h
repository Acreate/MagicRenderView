#ifndef PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
#define PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class VarType;
class ProtOutputItemWidget : public QWidget {
	Q_OBJECT;
protected:
	VarType *var;
public:
	virtual const VarType * getVar( ) const {
		return var;
	}
	virtual void bindVar( VarType *bind_var );
public:
	ProtOutputItemWidget( QWidget *parent, VarType *bind_var = nullptr );
protected:
	void paintEvent( QPaintEvent *event ) override;
protected Q_SLOTS:
	virtual void releaseVarType( VarType *release_var_type );
Q_SIGNALS:
	void replaceVar( VarType *old_var, VarType *new_var );
};

#endif // PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
