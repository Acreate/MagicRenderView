#ifndef GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#define GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include "GenerateListWidget.h"

class I_Var;
class GenerateListItemWidget : public QObject {
	Q_OBJECT;
protected:
	std_shared_ptr< I_Var > var;
public:
	GenerateListItemWidget( const std_shared_ptr< I_Var > &var, QObject *parent = nullptr );
	virtual const std_shared_ptr< I_Var > & getVar( ) const { return var; }
};

#endif // GENERATELISTITEMWIDGET_H_H_HEAD__FILE__
