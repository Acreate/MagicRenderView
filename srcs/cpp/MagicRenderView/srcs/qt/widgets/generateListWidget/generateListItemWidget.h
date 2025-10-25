#ifndef GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#define GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include "GenerateListWidget.h"

class I_Var;
class VarEditorWidget;
class GenerateListItemWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< I_Var > var;
	VarEditorWidget *varEditorWidget;
public:
	GenerateListItemWidget( const std_shared_ptr< I_Var > &var, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~GenerateListItemWidget( ) override;
	virtual const std_shared_ptr< I_Var > & getVar( ) const { return var; }
	virtual VarEditorWidget * getVarEditInfo( ) const { return varEditorWidget; }
	virtual bool showVarEditorWidget( ) const;
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getNameCheckFunction( ) const;
	virtual void setNameCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &name_check_function );
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getVarCheckFunction( ) const;
	virtual void setVarCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &var_check_function );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void releaseThisPtr( GenerateListItemWidget *release_node_item );
};

#endif // GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
