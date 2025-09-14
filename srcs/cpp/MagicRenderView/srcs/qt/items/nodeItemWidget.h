#ifndef NODEITEMWIDGET_H_H_HEAD__FILE__
#define NODEITEMWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

#include "protItemWidget.h"

class ProtItemWidget;
class MainWidget;
enum class RunCode :size_t {
	/// @brief 没有错误
	No_Error = 0,
	/// @brief 没有运行
	No_Run,
	/// @brief 重复运行
	Again_Run,
	/// @brief 执行期间发生错误
	Code_Error,
	/// @brief 内部初始化变量时候发生错误
	Var_Error,
	/// @brief 传递错误数量参数个数的错误
	Param_Count_Error,
	/// @brief 传递错误参数类型的错误
	Param_Type_Error,

	/// @brief 其他错误-未界定
	Other_Error = ( ( size_t ) 0 - ( size_t ) 1 ),
};

#define Def_First_StaticMetaInfo(  ) \
protected: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
public: \
	virtual QString getMetaObjectName( ); \
	virtual QString getMetaObjectDir( );\
public:

#define Def_Last_StaticMetaInfo( Imp_Class , Base_Iinterface_Class ) \
public:\
	friend class NodeItemWidget;\
protected: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
public: \
	QString getMetaObjectName( ) override; \
	QString getMetaObjectDir( ) override;\
public:

#define Imp_StaticMetaInfo( Imp_Class , Class_Translate ) \
	QString Imp_Class::getStaticMetaObjectName( ) { \
		return Class_Translate; \
	} \
	QString Imp_Class::getStaticMetaObjectDir( ) { \
		QFileInfo fileInfo( __FILE__ ); \
		auto dirName = fileInfo.dir( ).dirName( ); \
		return dirName; \
	}\
	QString Imp_Class::getMetaObjectName( ) {\
		return Imp_Class::getStaticMetaObjectName( );\
	}\
	QString Imp_Class::getMetaObjectDir( ) {\
		return Imp_Class::getStaticMetaObjectDir( );\
	}

class NodeItemWidget : public QWidget {
	Q_OBJECT;
protected:
	using generateFunction = std_function< NodeItemWidget*( QWidget * ) >;
	using generateInfo = std_pairt< QString, generateFunction >;
	using generatePathClassInfo = std_pairt< QString, std_vector< QString > >;
	using generateInfoVector = std_vector< generateInfo >;
	using generateItem = std_pairt< QString, generateInfoVector >;
	static std_vector< generateItem > generateItemVector;
	static std_mutex generateItemVectorMutex;
	Def_First_StaticMetaInfo( );
protected:
	static bool appendGenerate( const QString &dir_name, const QString &node_name, const generateFunction &generate_function );
public:
	static NodeItemWidget * generateNode( QWidget *parent, const QString &dir_name, const QString &node_name );
	template< typename TNodeItemWidget >
		requires requires ( QString name ) {
			name = TNodeItemWidget::getStaticMetaObjectName( );
		}
	static bool appendGenerate( ) {
		return NodeItemWidget::appendGenerate( TNodeItemWidget::getStaticMetaObjectDir( ), TNodeItemWidget::getStaticMetaObjectName( ), [] ( QWidget *main_widget ) {
			return new TNodeItemWidget( main_widget );
		} );
	}
	static std_vector< generatePathClassInfo > getGenerateItems( );
protected:
	/// @brief 运行代码
	RunCode runCode;
	/// @brief 需求选项
	std_list< NodeItemWidget * > needNodeItems;
	std_vector< ProtItemWidget * > nodeProtItems;
	std_shared_ptr< std_mutex > protItemWidgetVectorMutex;
protected:
	NodeItemWidget( QWidget *parent );
public:
	/// @brief 运行节点
	/// @return 成功返回 true
	virtual RunCode getRunCode( ) const {
		return runCode;
	}
	/// @brief 获取需求选项列表
	/// @return 需求选项
	virtual const std_list< NodeItemWidget * > & getNeedNodeItems( ) const {
		return needNodeItems;
	}
	/// @brief 利用全局坐标匹配接口
	/// @param globle_point 全局坐标
	/// @return 返回接口
	virtual ProtItemWidget * getProtItemWidget( const QPoint &globle_point ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODEITEMWIDGET_H_H_HEAD__FILE__
