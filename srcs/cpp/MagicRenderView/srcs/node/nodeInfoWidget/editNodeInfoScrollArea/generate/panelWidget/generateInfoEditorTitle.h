#ifndef GENERATEINFOEDITORTITLE_H_H_HEAD__FILE__
#define GENERATEINFOEDITORTITLE_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QPushButton;
class QLineEdit;
class QLabel;
class GenerateInfoEditorTitle : public QWidget {
	Q_OBJECT;
public:
	/// @brief 类型名称
	QLabel *varTypeName;
	/// @brief 变量名称
	QLineEdit *varName;
	/// @brief 变量添加到列表按钮
	QPushButton *addendVarListBtn;
public:
	GenerateInfoEditorTitle( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void clearVarName( );
	virtual void setVarTypeName( const QString &new_var_type_name );
public:
Q_SIGNALS:
	void createVar( const QString &var_type, const QString &var_name );
};

#endif // GENERATEINFOEDITORTITLE_H_H_HEAD__FILE__
