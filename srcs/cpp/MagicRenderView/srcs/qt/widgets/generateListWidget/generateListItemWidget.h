#ifndef GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#define GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include "GenerateListWidget.h"

class I_Var;
class GenerateListItemWidget : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< I_Var > var;
public:
	GenerateListItemWidget( const std_shared_ptr< I_Var > &var, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual const std_shared_ptr< I_Var > & getVar( ) const { return var; }
};

#endif // GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
