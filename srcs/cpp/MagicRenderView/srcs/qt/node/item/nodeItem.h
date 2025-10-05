#ifndef NODEITEM_H_H_HEAD__FILE__
#define NODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QWidget>
#include <qimage.h>

#include <alias/type_alias.h>

#include <qt/tools/tools.h>

#define Def_NodeItem_StaticMetaInfo( ) \
	Def_Last_StaticMetaInfo( );\
	friend class NodeItemGenerate;\
	friend class Application;\
	friend class VarGenerate

#define Def_NodeItem_Last_StaticMetaInfo( ) \
	Def_Last_Firend_StaticMetaInfo( NodeItem );\
	friend class NodeItemGenerate;\
	friend class Application;\
	friend class VarGenerate

class NodeItemInfoScrollAreaWidget;
class NodePort;
class I_Var;
class VarType;
class Application;
class NodeOutputPort;
class NodeInputPort;
class NodeWidgetSerialization;
class NodeItemSerialization;
class MainWidget;

class NodeItem : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_NodeItem_StaticMetaInfo( );
public:
	friend class MainWidget;
	friend class I_Stack;
	friend class AppNodeItemType;
	friend class NodeItemInfoWidget;
public:
	enum class Click_Type {
		None, // 没有
		Space, // 空白
		Title, // 标题
		InputPort, // 输入
		OutputPort, // 输出
	};
	Q_ENUM( Click_Type )
public:
	using NodeItem_ParentPtr_Type = QWidget;
	using NodeItemString_Type = QString;
	using TNodePortInputPortPtr = NodeInputPort *;
	using TNodePortOutputPortPtr = NodeOutputPort *;
	using TConstNodePortInputPortPtr = const NodeInputPort *;
	using TConstNodePortOutputPortPtr = const NodeOutputPort *;
	using TNodeProtPoint = std::pair< int, int >;
	template< typename TPortTypePtr >
	using TPortWidgetPort = std_pairt< TPortTypePtr, TNodeProtPoint >;
private:
	/// @brief 生成编号
	size_t generateCode;
	/// @brief 节点变量
	std_vector< I_Var * > nodeVarVector;
	/// @brief 节点标题名称
	NodeItemString_Type nodeTitleName;
	/// @brief 绑定渲染
	QImage *nodeItemRender;
	/// @brief 相对于父窗口的 X 位置
	int nodePosX;
	/// @brief 相对于父窗口的 Y 位置
	int nodePosY;
	/// @brief 节点宽度
	int nodeItemWidth;
	/// @brief 节点高度
	int nodeItemHeith;
	/// @brief 输出接口序列
	std_vector< TPortWidgetPort< TNodePortInputPortPtr > > nodeInputProtVector;
	/// @brief 输出接口序列
	std_vector< TPortWidgetPort< TNodePortOutputPortPtr > > nodeOutputProtVector;
	/// @brief 输入组件缓存
	QImage *inputBuff;
	/// @brief 输出组件缓存
	QImage *outputBuff;
	/// @brief 标题缓存
	QImage *titleBuff;

	/// @brief 输入面板高度
	int inputBuffHeight;
	/// @brief 输入面板宽度
	int inputBuffWidth;
	/// @brief 输出面板高度
	int outputBuffHeight;
	/// @brief 输出面板宽度
	int outputBuffWidth;
	/// @brief 标题高度
	int titleHeight;
	/// @brief 标题宽度
	int titleWidth;
	/// @brief 上下端口之间的空间大小
	int portSpace;
	/// @brief 标题到端口的空间大小
	int titleToPortSpace;
	/// @brief 输入输入端口之间的空间大小
	int midPortSpace;
	/// @brief 边缘底部空间大小
	int borderBoomSpace;
	/// @brief 边缘空间左侧空间大小
	int borderLeftSpace;
	/// @brief 边缘右侧空间大小
	int borderRightSpace;
	/// @brief 边缘顶端空间大小
	int borderTopSpace;
	/// @brief 渲染所在窗口
	MainWidget *renderMainWidget;
protected:
	/// @brief 应用类指针
	Application *applicationInstancePtr;
	/// @brief 编辑窗口
	NodeItemInfoScrollAreaWidget *editWidget;
protected:
	NodeItem( );
public:
	virtual MainWidget * getRenderMainWidget( ) const { return renderMainWidget; }
	virtual void setRenderMainWidget( MainWidget *const render_main_widget ) { renderMainWidget = render_main_widget; }
	~NodeItem( ) override;
	virtual NodeItemInfoScrollAreaWidget * getEditWidget( ) const { return editWidget; }
	virtual void setMainWidget( MainWidget *parent );
	virtual bool getInputPortPos( TConstNodePortInputPortPtr input_port_ptr, QPoint &result_pos ) const;
	virtual bool getOutputPortPos( TConstNodePortOutputPortPtr output_port_ptr, QPoint &result_pos ) const;
	/// @brief 从相对坐标获取类型
	/// @param point 基于该节点的相对位置
	/// @return 类型
	virtual Click_Type relativePointType( const QPoint &point ) const {
		return relativePointType( point.x( ), point.y( ) );
	}

	/// @brief 从相对坐标获取类型
	/// @param x 基于该节点的 x 相对位置
	/// @param y 基于该节点的 y 相对位置
	/// @return 类型
	virtual Click_Type relativePointType( int x, int y ) const;
	/// @brief 获取链接
	/// @return 链接键值对
	virtual std_vector< std_pairt< TPortWidgetPort< NodePort * >, TPortWidgetPort< NodePort * > > > getLinkPort( ) const;
	/// @brief 从相对坐标获输入接口
	/// @param point 基于该节点的相对位置
	/// @return 类型
	virtual TNodePortInputPortPtr getNodeInputAtRelativePointType( const QPoint &point ) const {
		return getNodeInputAtRelativePointType( point.x( ), point.y( ) );
	}

	/// @brief 从相对坐标获取输入接口
	/// @param x 基于该节点的 x 相对位置
	/// @param y 基于该节点的 y 相对位置
	/// @return 类型
	virtual TNodePortInputPortPtr getNodeInputAtRelativePointType( int x, int y ) const;

	/// @brief 从相对坐标获输出接口
	/// @param point 基于该节点的相对位置
	/// @return 类型
	virtual TNodePortOutputPortPtr getNodeOutputPortAtRelativePointType( const QPoint &point ) const {
		return getNodeOutputPortAtRelativePointType( point.x( ), point.y( ) );
	}

	/// @brief 从相对坐标获取输出接口
	/// @param x 基于该节点的 x 相对位置
	/// @param y 基于该节点的 y 相对位置
	/// @return 类型
	virtual TNodePortOutputPortPtr getNodeOutputPortAtRelativePointType( int x, int y ) const;
	/// @brief 初始化接口选项
	/// @return 成功返回 true
	virtual bool intPortItems( MainWidget *parent );
	virtual const NodeItemString_Type & getNodeTitleName( ) const { return nodeTitleName; }
	virtual void setNodeTitleName( const NodeItemString_Type &node_title_name );

	virtual void move( const QPoint &point ) {
		nodePosX = point.x( );
		nodePosY = point.y( );
	}

	virtual void move( int x, int y ) {
		nodePosX = x;
		nodePosY = y;
	}
	virtual QPoint getPos( ) const { return QPoint( nodePosX, nodePosY ); }
	virtual QSize getSize( ) const { return { nodeItemWidth, nodeItemHeith }; }
	virtual QRect geometry( ) const { return QRect( nodePosX, nodePosY, nodeItemWidth, nodeItemHeith ); }
	virtual QImage * getNodeItemRender( ) const { return nodeItemRender; }
	virtual int getNodePosX( ) const { return nodePosX; }
	virtual void setNodePosX( const int node_pos_x ) { nodePosX = node_pos_x; }
	virtual int getNodePosY( ) const { return nodePosY; }
	virtual void setNodePosY( const int node_pos_y ) { nodePosY = node_pos_y; }
	/// @brief 测试指定坐标是否存在当前节点内
	/// @param point 测试坐标
	/// @return 在当前节点范围内，返回 true
	virtual bool contains( const QPoint &point ) {
		int x = point.x( );
		if( x < nodePosX )
			return false;
		int y = point.x( );
		if( y < nodePosY )
			return false;
		if( x > ( nodeItemWidth + nodePosX ) )
			return false;
		if( y > ( nodeItemHeith + nodePosY ) )
			return false;
		return true;
	}
	virtual size_t getGenerateCode( ) const { return generateCode; }
	virtual NodeOutputPort * getOutputPort( const QString &output_port_name ) const;
protected:
	/// @brief 增加一个输入接口
	/// @param input_prot 输入接口对象指针
	/// @return 成功返回 true
	virtual bool appendInputProt( TNodePortInputPortPtr input_prot );
	/// @brief 删除输入接口
	/// @param input_prot 输入接口对象指针 
	/// @return 成功返回 true
	virtual bool removeInputProt( TConstNodePortInputPortPtr input_prot );
	/// @brief 增加一个输出接口
	/// @param output_prot 输出接口对象指针
	/// @return 成功返回 true
	virtual bool appendOutputProt( TNodePortOutputPortPtr output_prot );
	/// @brief 删除输出接口
	/// @param output_port 
	/// @return 成功返回 true
	virtual bool removeOutputProt( TConstNodePortOutputPortPtr output_port );
	/// @brief 更新输入端布局
	/// @return 成功返回 true
	virtual bool updateInputLayout( );
	/// @brief 更新输出端布局
	/// @return 成功返回 true
	virtual bool updateOutputLayout( );
	/// @brief 更新标题布局
	/// @return 成功返回 true
	virtual bool updateTitleLayout( );
	/// @brief 合并布局-此选项并不更新组件布局
	/// @return 成功返回 true
	virtual bool integrateLayout( );
public:
	/// @brief 从布局存储序列获取输出端口对象指针
	/// @param index 布局序列下标
	/// @return 成功返回输出端口，失败返回 nullptr
	virtual TNodePortOutputPortPtr formIndexNodeOutputPort( const size_t &index );
	/// @brief 从布局存储序列获取输入端口对象指针
	/// @param index 布局序列下标
	/// @return 成功返回输入端口，失败返回 nullptr
	virtual TNodePortInputPortPtr formIndexNodeInputPort( const size_t &index );
	/// @brief 更新连接信息
	/// @return 成功返回 true
	virtual bool updataLinkInfo( );
Q_SIGNALS:
	void releaseThiNodeItem( NodeItem *release_node_item );
public: // 二进制相关

};

#endif // NODEITEM_H_H_HEAD__FILE__
