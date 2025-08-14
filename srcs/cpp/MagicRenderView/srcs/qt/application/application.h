#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once

#include <QApplication>
#include <alias/type_alias.h>

#include "../stacks/varStack/IVarStack.h"

class StackManagement;
class NodeListWidget;
class IVarStack;
class MainWidget;
class IFunStack;
class QSettings;
class QBoxLayout;

class Application : public QApplication {
	Q_OBJECT;
public:
	/// @brief 获取布局当中所有的窗口
	/// @param main_widget 布局
	/// @return 窗口列表
	static std_vector< QWidget * > getLayoutWidgets( QBoxLayout *main_widget );
	/// @brief 删除所有布局当中的窗口
	/// @param main_widget 布局
	static void deleteLayoutWidgets( QBoxLayout *main_widget );

	/// @brief 获取实例指针
	/// @return 成功返回 true
	static Application * getApplicationInstancePtr( );
	/// @brief 把全部窗口移动到指定显示器上
	/// @param index 显示器序列
	static void setWindowToIndexScreenCentre( size_t index );
	/// @brief 重启应用
	static void resetApp( );
	/// @brief 退出应用
	static void quitApp( );
	/// @brief 标准化关键字
	/// @param key 自定义关键字列表
	/// @return 返回标准化后的关键字
	static QString normalKey( const QString &key );
	/// @brief 标准化关键字
	/// @param key 自定义关键字列表
	/// @param widget 关键字关联窗口
	/// @return 返回标准化后的关键字
	static QString normalKey( const QString &key, QWidget *widget );
	/// @brief 标准化关键字，并且在标准化关键字后续增加一个自定义字符串
	/// @param key 自定义关键字列表
	/// @param widget 关键字关联窗口
	/// @param append_str 追加的字符串
	/// @return 返回标准化后的关键字
	static QString normalKeyAppendEnd( const QString &key, QWidget *widget, const QString &append_str ) {
		return normalKey( key, widget ).append( "/" ).append( append_str ).append( "/" );
	}
	/// @brief 标准化关键字，并且在末尾追加窗口名称
	/// @param key 自定义关键字列表
	/// @param widget 关键字关联窗口
	/// @return 返回标准化后的关键字
	static QString normalKeyAppendWidgetName( const QString &key, QWidget *widget );
protected:
	QSettings *settings;
	MainWidget *mainWidget;
	NodeListWidget *nodeListWidget;
	StackManagement *stackManagement;
	std_shared_ptr< std_mutex > stdMutex_p;
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;
public:
	virtual StackManagement * getStackManagement() const;
	virtual void setAppIniValue( const QAnyStringView &key, const QVariant &value );
	virtual QVariant getAppIniValue( const QAnyStringView &key, const QVariant &defaultValue ) const;
	virtual QVariant getAppIniValue( const QAnyStringView &key ) const;
	virtual void syncAppValueIniFile( ) const;
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void setMainWidget( MainWidget *const main_widget ) { mainWidget = main_widget; }
	virtual NodeListWidget * getNodeListWidget( ) const { return nodeListWidget; }
	virtual void setNodeListWidget( NodeListWidget *const node_list_widget ) { nodeListWidget = node_list_widget; }
protected:
	bool notify( QObject *, QEvent * ) override;
};

#endif // APPLICATION_H_H_HEAD__FILE__
