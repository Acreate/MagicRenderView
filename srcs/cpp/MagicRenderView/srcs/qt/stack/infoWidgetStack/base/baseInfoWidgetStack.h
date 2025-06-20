#ifndef BASEINFOWIDGETSTACK_H_H_HEAD__FILE__
#define BASEINFOWIDGETSTACK_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidgetStack.h"

class BaseInfoWidgetStack : public IInfoWidgetStack {
	Q_OBJECT;
protected:
	using aliasVector = std_pairt< QString, std_vector< QString > >;
	using generateFcuntion = std_function< IInfoWidget*( ) >;
	using generateNodePairt = std_pairt< aliasVector, generateFcuntion >;
	std_shared_ptr< std_vector< generateNodePairt > > infoWidgetGenerate;
protected:
	IInfoWidget * _newNode( const QString &type_name ) const;
public:
	BaseInfoWidgetStack( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function );
	IInfoWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr ) const override;
	std_vector<std_pairt<QString, std_vector<QString>>> permissionInfoWidget( ) const override;
};

#endif // BASEINFOWIDGETSTACK_H_H_HEAD__FILE__
