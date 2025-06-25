#ifndef COMBINATIONWIDGET_H_H_HEAD__FILE__
#define COMBINATIONWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class CombinationTypeObject;
class CombinationWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	std_shared_ptr<CombinationWidget> thisSharper;
	std_shared_ptr<CombinationTypeObject> value;
public:
	CombinationWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	virtual bool remove( const QString &name );
	virtual bool append( const QString &name, const std_shared_ptr< ITypeObject > &value );
	virtual std_shared_ptr< ITypeObject > atName( const QString &name ) const;
	virtual std_vector< std_pairt< QString, std_shared_ptr< ITypeObject > > > getMapValue( ) const;
	virtual void setMapValue( const std_vector< std_pairt< QString, std_shared_ptr< ITypeObject > > > &value_std_vector ) const;
	virtual void setMapValue( const std_shared_ptr< CombinationTypeObject > &value_std_vector ) const;
	virtual void setMapValue( const CombinationTypeObject *value_std_vector ) const;
	std_shared_ptr< ITypeObject > getValue( ) const override;
	bool setValue( const std_shared_ptr< ITypeObject > &value ) const override;
	virtual std_shared_ptr< ITypeObject > operator[]( const QString &name ) const {
		return atName( name );
	}
};

#endif // COMBINATIONWIDGET_H_H_HEAD__FILE__
