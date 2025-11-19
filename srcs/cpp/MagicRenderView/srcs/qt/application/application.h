#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once

#include <QApplication>
#include <QDateTime>
#include <QVariant>
#include <qfont.h>

#include <alias/type_alias.h>

class NodeDirector;
class VarGenerate;
class Stack;
class QLabel;
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
	std_shared_ptr< std_mutex > stdMutex_p;
	std_shared_ptr< std_mutex > stdMutexWidgetSelectLock;
	QString writeSettingPath;
	VarGenerate *varGenerate;
	NodeDirector *nodeDirector;
	std_shared_ptr< QFont > font;
	QImage *nodeItemWidgetIco;
	QDateTime dateTime;
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;
	virtual bool init( );
public:
	virtual const QString & getWriteSettingPath( ) const { return writeSettingPath; }
	virtual void setAppIniValue( const QAnyStringView &key, const QVariant &value );
	virtual QVariant getAppIniValue( const QAnyStringView &key, const QVariant &defaultValue ) const;
	virtual QVariant getAppIniValue( const QAnyStringView &key ) const;
	virtual void syncAppValueIniFile( ) const;
	virtual VarGenerate * getVarGenerate( ) const { return varGenerate; }
	virtual const QFont & getFont( ) const { return *font; }
	virtual QImage * getNodeItemWidgetIco( ) const { return nodeItemWidgetIco; }
	virtual void setFont( const QFont &new_font ) {
		*font = new_font;
	}
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual const QDateTime & getAppInstanceDateTime( ) const { return dateTime; }
	virtual QImage * renderTextToImage( QPainter *painter, const QString &render_text ) const;
	virtual QImage * renderTextToImageAtRectBound( QPainter *painter, const QString &render_text, const QColor &rect_bound_color, const int &bound_width ) const;
	virtual QImage * renderTextToImageAtFontColor( QPainter *painter, const QString &render_text, const QColor &pen_color ) const;
	virtual QImage * renderTextToImageAtFontColorAndRectBound( QPainter *painter, const QString &render_text, const QColor &pen_color, const QColor &rect_bound_color, const int &bound_width ) const;
	/// @brief 水平合成
	/// @param first 第一个填充
	/// @param scond 第二个填充
	/// @param space 间距
	/// @param result_image 合成后的图像返回
	virtual void mergeHorizontalImage( const QImage *first, const QImage *scond, int space, QImage &result_image ) const;
protected:
	bool notify( QObject *, QEvent * ) override;
};

#endif // APPLICATION_H_H_HEAD__FILE__
