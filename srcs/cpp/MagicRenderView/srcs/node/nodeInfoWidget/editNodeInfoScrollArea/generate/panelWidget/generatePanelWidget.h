#ifndef GENERATEPANELWIDGET_H_H_HEAD__FILE__
#define GENERATEPANELWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>
#include <QWidget>

class GeneratePanelWidget : public QScrollArea {
	Q_OBJECT;
protected:
	std::function< void*( const QString &type_name, const QString &var_name ) > createTypeVar;
public:
	GeneratePanelWidget( const std::function< void *( const QString &type_name, const QString &var_name ) > &create_type_var, QWidget *parent = nullptr );
	virtual bool appendItem( const QString &type_name, const QString &var_name );
protected:
	void resizeEvent( QResizeEvent * ) override;
};

#endif // GENERATEPANELWIDGET_H_H_HEAD__FILE__
