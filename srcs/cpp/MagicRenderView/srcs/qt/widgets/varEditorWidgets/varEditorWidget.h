#ifndef VAREDITORWIDGET_H_H_HEAD__FILE__
#define VAREDITORWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QLineEdit;
class VarGenerate;
class I_Var;
class VarEditorWidget : public QWidget {
	Q_OBJECT;
protected:
	I_Var *var;
	VarGenerate *varGenerate;
	QLineEdit *varNameEdit;
	QLineEdit *varValueEdit;
public:
	VarEditorWidget( QWidget *parent, I_Var *new_var_ptr );
	~VarEditorWidget( ) override;
	virtual bool getVarName( QString &result_name ) const;
	virtual void setVarName( const QString &new_var_name );
	virtual const type_info & getTypeInfo( ) const;
	virtual bool isNullPtr( ) const;
	virtual bool getVar( I_Var *result_var ) const;
	virtual bool setValue( const type_info &var_type_info, const void *set_var_ptr );
	virtual bool updateEditorContent( );
};
#endif // VAREDITORWIDGET_H_H_HEAD__FILE__
