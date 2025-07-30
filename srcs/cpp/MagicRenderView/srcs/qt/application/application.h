#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once

#include <QApplication>
#include <alias/type_alias.h>

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
	std_vector< std_shared_ptr< IFunStack > > funStacks;
	std_shared_ptr< std_mutex > stdMutex;
	std_shared_ptr< std_mutex > stdMutex_p;
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;
public:
	virtual bool appendFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack );
	template< typename IFunctionStack >
		requires requires ( IFunStack *a, IFunctionStack *b ) {
			a = b;
		}
	bool appendFunctionStack( ) {
		return appendFunctionStack( std_shared_ptr< IFunStack >( new IFunctionStack ) );
	}

	virtual bool removeFunctionStack( const std_shared_ptr< IFunStack > &new_function_stack );
	virtual bool removeFunctionStackAtType( const QString &function_stack_class_name, const QString &function_stack_name );
	virtual bool removeFunctionStackAtType( const std_shared_ptr< IFunStack > &new_function_stack );
	virtual std_vector< std_shared_ptr< IFunStack > > removeFunctionStackAtClassName( const QString &function_stack_class_name );
	virtual std_vector< std_shared_ptr< IFunStack > > removeFunctionStackAtStackName( const QString &function_stack_name );
	virtual const std_vector< std_shared_ptr< IFunStack > > & getFunStacks( ) const {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		return funStacks;
	}
	virtual void setFunStacks( const std_vector< std_shared_ptr< IFunStack > > &fun_stacks ) {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		funStacks = fun_stacks;
	}
	virtual const std_mutex & getStdMutex( ) const {
		std_lock_grad_mutex lock( *stdMutex.get( ) );
		return *stdMutex;
	}
	virtual void setAppIniValue( const QAnyStringView &key, const QVariant &value );
	virtual QVariant getAppIniValue( const QAnyStringView &key, const QVariant &defaultValue ) const;
	virtual QVariant getAppIniValue( const QAnyStringView &key ) const;
	virtual void syncAppValueIniFile( ) const;
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void setMainWidget( MainWidget *const main_widget ) { mainWidget = main_widget; }
protected:
	bool notify( QObject *, QEvent * ) override;
};

#endif // APPLICATION_H_H_HEAD__FILE__
