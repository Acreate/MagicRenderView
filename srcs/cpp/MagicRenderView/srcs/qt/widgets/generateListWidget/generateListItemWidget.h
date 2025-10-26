#ifndef GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#define GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>
class I_Var;
class VarEditorWidget;
class QHBoxLayout;
class QPushButton;
class QLabel;
class GenerateListItemWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< I_Var > var;
	VarEditorWidget *varEditorWidget;
	QHBoxLayout *mainLayout;
	QLabel *titile;
	QPushButton *delBtn;
public:
	GenerateListItemWidget( const std_shared_ptr< I_Var > &var, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~GenerateListItemWidget( ) override;
	virtual const std_shared_ptr< I_Var > & getVar( ) const { return var; }
	virtual VarEditorWidget * getVarEditorWidget( ) const { return varEditorWidget; }
	virtual bool showVarEditorWidget( ) const;
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getNameCheckFunction( ) const;
	virtual void setNameCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &name_check_function );
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getVarCheckFunction( ) const;
	virtual void setVarCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &var_check_function );
	virtual const std_function< bool( VarEditorWidget *, const QString &, I_Var * ) > & getNormalVarFunction( ) const;
	virtual void setNormalVarFunction( const std_function< bool( VarEditorWidget *, const QString &, I_Var * ) > &normal_var_function );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void releaseThisPtr( GenerateListItemWidget *release_node_item );
	void changeVarOverSignal( GenerateListItemWidget *signal_obj_ptr, VarEditorWidget *change_var_obj_ptr );
};

#endif // GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
