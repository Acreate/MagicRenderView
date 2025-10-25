#ifndef VAREDITORWIDGET_H_H_HEAD__FILE__
#define VAREDITORWIDGET_H_H_HEAD__FILE__
#pragma once
#include "GenerateListItemWidget.h"

class Application;
class VarGenerate;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class VarEditorWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< I_Var > editorVar;
	/*QVBoxLayout *mainLayout;
	QHBoxLayout *varVarEditorLayout;
	QHBoxLayout *varNameEditorLayout;*/

	QLabel *titile;

	QLabel *varVarTitile;
	QLineEdit *varVarLineEdit;

	QLabel *varNameTitile;
	QLineEdit *varNameLineEdit;

	QPushButton *applyVarChange;
	Application *application;
	VarGenerate *varGenerate;
	std_function< bool( VarEditorWidget *, const QString & ) > nameCheckFunction;
	std_function< bool( VarEditorWidget *, const QString & ) > varCheckFunction;
	std_function< bool( VarEditorWidget *, const QString &, QString & ) > normalVarFunction;
	bool toolTipShowStatus;
protected:
	virtual void updateLayout( );
	virtual void initVarEditorInfo( );
	virtual void nameLineEditorChanged( const QString &new_text );
	virtual void varLineEditorChanged( const QString &new_text );
	virtual void setVarValue( );
public:
	~VarEditorWidget( ) override;
	VarEditorWidget( const std_shared_ptr< I_Var > &editor_var );
	virtual const std_shared_ptr< I_Var > & getEditorVar( ) const { return editorVar; }
	virtual void setEditorVar( const std_shared_ptr< I_Var > &editor_var ) {
		editorVar = editor_var;
		initVarEditorInfo( );
	}
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getNameCheckFunction( ) const { return nameCheckFunction; }
	virtual void setNameCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &name_check_function ) { nameCheckFunction = name_check_function; }
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getVarCheckFunction( ) const { return varCheckFunction; }
	virtual void setVarCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &var_check_function ) { varCheckFunction = var_check_function; }
	virtual const std_function<bool(VarEditorWidget *, const QString &, QString &)> & getNormalVarFunction( ) const { return normalVarFunction; }
	virtual void setNormalVarFunction( const std_function<bool(VarEditorWidget *, const QString &, QString &)> &normal_var_function ) { normalVarFunction = normal_var_function; }
	virtual void setNameEditorMsg( const QString &msg );
	virtual void setValueEditorMsg( const QString &msg );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
Q_SIGNALS:
	void changeVarOverSignal( VarEditorWidget *signal_obj_ptr );
};

#endif // VAREDITORWIDGET_H_H_HEAD__FILE__
