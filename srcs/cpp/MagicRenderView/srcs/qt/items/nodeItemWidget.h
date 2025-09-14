#ifndef NODEITEMWIDGET_H_H_HEAD__FILE__
#define NODEITEMWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

class QSpacerItem;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class ProtOutputItemWidget;
class ProtInputItemWidget;
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
private:
	/// @brief 运行代码
	RunCode runCode;
	/// @brief 需求选项
	std_list< NodeItemWidget * > needNodeItems;
	/// @brief 输入接口
	std_vector< ProtInputItemWidget * > nodeProtInputItems;
	/// @brief 输出接口
	std_vector< ProtOutputItemWidget * > nodeProtOutputItems;
	/// @brief 输入接口锁
	std_shared_ptr< std_mutex > protInputItemWidgetVectorMutex;
	/// @brief 输出接口锁
	std_shared_ptr< std_mutex > protOutputItemWidgetVectorMutex;
	/// @brief 标题
	QLabel *titile;
	/// @brief 主要布局
	QVBoxLayout *mainLayout;
	/// @brief 接口布局
	QHBoxLayout *protItemLayout;
	/// @brief 输入接口布局
	QVBoxLayout *protInputItemLayout;
	/// @brief 输出接口布局
	QVBoxLayout *protOutputItemLayout;
	/// @brief 输入接口空间占位项
	QSpacerItem *protInputItemLayoutSpacerItem;
	/// @brief 输出接口空间占位项
	QSpacerItem *protOutputItemLayoutSpacerItem;
protected:
	NodeItemWidget( QWidget *parent );
protected:
	/// @brief 设置运行代码
	/// @param run_code 新的运行代码
	void setRunCode( RunCode run_code ) {
		runCode = run_code;
	}
	void setNodeTitle( const QString &new_titile );
	/// @brief 追加一个输入接口
	/// @param prot_input_item_widget 输入的接口
	/// @return 成功返回 true
	bool appendProtInputItemWidget( ProtInputItemWidget *prot_input_item_widget );
	/// @brief 追加一个输出接口
	/// @param prot_output_item_widget 输出接口
	/// @return 成功返回 true
	bool appendProtOutputItemWidget( ProtOutputItemWidget *prot_output_item_widget );
	/// @brief 删除一个输入接口
	/// @param prot_input_item_widget 输入的接口
	/// @return 成功返回 true
	bool removeProtInputItemWidget( const ProtInputItemWidget *prot_input_item_widget );
	/// @brief 删除一个输出接口
	/// @param prot_output_item_widget 输出接口
	/// @return 成功返回 true
	bool removeProtOutputItemWidget( const ProtOutputItemWidget *prot_output_item_widget );
public:
	~NodeItemWidget( ) override;
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
	/// @brief 利用全局坐标匹配输入接口
	/// @param globle_point 全局坐标
	/// @return 返回输入接口
	virtual ProtInputItemWidget * getProtInputItemWidget( const QPoint &globle_point ) const;
	/// @brief 利用全局坐标匹配输出接口
	/// @param globle_point 全局坐标
	/// @return 返回输出接口
	virtual ProtOutputItemWidget * getProtOutputItemWidget( const QPoint &globle_point ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODEITEMWIDGET_H_H_HEAD__FILE__
