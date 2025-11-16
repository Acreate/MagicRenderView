#ifndef NODEITEM_H_H_HEAD__FILE__
#define NODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QRect>
#include <QSizeF>
#include <qpoint.h>

#include <alias/type_alias.h>
#include <qt/enums/nodeItemEnum.h>

class I_Type;
class GenerateListScrollArea;
class QScrollArea;
class NodeItemInfoScrollAreaWidget;
class NodePort;
class I_Var;
class NodeOutputPort;
class NodeInputPort;
class NodeItem : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_NodeItem_StaticMetaInfo( );
private:
	friend class MainWidget;
	friend class NodeItemBuilderModule;
	friend class NodeItemBuilderObj;
	friend class I_Stack;
	friend class AppNodeItemStack;
	friend class NodeItemInfoWidget;
	friend class NodeDirector;
	friend class NodeItemBuilderLink;
	friend class NodeItemBuilderModule;
	friend class NodeDirectorStack;
	friend class StartNodeInfoWidget;
	friend class NodeItemInfoVector;
protected:
	/// @brief 输入输入端口之间的空间大小
	static int midPortSpace;
	/// @brief 边缘顶端空间大小
	static int borderTopSpace;
	/// @brief 上下端口之间的空间大小
	static int portSpace;
	/// @brief 标题到端口的空间大小
	static int titleToPortSpace;
	/// @brief 边缘底部空间大小
	static int borderBoomSpace;
	/// @brief 边缘空间左侧空间大小
	static int borderLeftSpace;
	/// @brief 边缘右侧空间大小
	static int borderRightSpace;
public:
	using NodeItem_ParentPtr_Type = QWidget;
	using NodeItemString_Type = QString;
	using TNodePortInputPortPtr = NodeInputPort *;
	using TNodePortOutputPortPtr = NodeOutputPort *;
	using TConstNodePortInputPortPtr = const NodeInputPort *;
	using TConstNodePortOutputPortPtr = const NodeOutputPort *;
	using TNodeProtPoint = std::pair< int, int >;
	/// @brief 端口映射列表
	/// @tparam TPortTypePtr 端口对象指针
	/// @param TNodeProtPoint 对象坐标
	/// @param bool 对象链接是否支持多对象
	template< typename TPortTypePtr >
	using TPortWidgetPort = std_pairt< TPortTypePtr, std_pairt< TNodeProtPoint, bool > >;
private:
	/// @brief 生成编号
	size_t generateCode;
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
	/// @brief 渲染所在窗口
	MainWidget *renderMainWidget;
protected:
	std_shared_ptr< I_Type > nodeTypeInfo = nullptr;
	GenerateListScrollArea *generateListScrollArea;
	/// @brief 节点变量
	std_vector< std_shared_ptr< I_Var > > nodeVarVector;
	/// @brief 应用类指针
	Application *applicationInstancePtr;
	/// @brief 变量值实例
	VarGenerate *varGenerate;
	/// @brief 运行状态
	bool runStatus;
	/// @brief 函数执行
	std_function< nodeItemEnum::Node_Item_Result_Type ( QString & ) > nodeItemFcuntion;
protected:
	NodeItem( );
	NodeItem( GenerateListScrollArea *node_info_scroll_area );
public:
	virtual const I_Type * const getNodeTypeInfo( ) const { return nodeTypeInfo.get( ); }
	virtual MainWidget * getRenderMainWidget( ) const { return renderMainWidget; }
	~NodeItem( ) override;
	virtual void setMainWidget( MainWidget *parent );
	virtual bool getInputPortPos( TConstNodePortInputPortPtr input_port_ptr, QPoint &result_pos ) const;
	virtual bool getOutputPortPos( TConstNodePortOutputPortPtr output_port_ptr, QPoint &result_pos ) const;
	virtual bool getMultiLinkPortStatus( const NodePort *get_node_port_multi_link_obj_ptr, bool &result_node_port_multi_link_status ) const;
	virtual void setPortLinkPort( NodePort *left_node_prot, NodePort *right_node_port ) { }
	virtual bool builderLinkProtValue( ) { return true; }
	virtual void clearPorkLink( ) { }
	virtual bool hasInputPort( const NodePort *node_port );
	virtual bool hasOutputPort( const NodePort *node_port );
	virtual size_t toBinData( std_vector< uint8_t > &result_data ) const;
	virtual size_t loadBinData( const uint8_t *source_data_ptr, const size_t &source_data_count );
	virtual void resetRun( );
	virtual bool getRunStatus( ) const {
		return runStatus;
	}
	/// @brief 从相对坐标获取类型
	/// @param point 基于该节点的相对位置
	/// @return 类型
	virtual nodeItemEnum::Click_Type relativePointType( const QPoint &point ) const;

	/// @brief 从相对坐标获取类型
	/// @param x 基于该节点的 x 相对位置
	/// @param y 基于该节点的 y 相对位置
	/// @return 类型
	virtual nodeItemEnum::Click_Type relativePointType( int x, int y ) const;
	/// @brief 从相对坐标获输入接口
	/// @param point 基于该节点的相对位置
	/// @return 类型
	virtual TNodePortInputPortPtr getNodeInputAtRelativePointType( const QPoint &point ) const;

	/// @brief 从相对坐标获取输入接口
	/// @param x 基于该节点的 x 相对位置
	/// @param y 基于该节点的 y 相对位置
	/// @return 类型
	virtual TNodePortInputPortPtr getNodeInputAtRelativePointType( int x, int y ) const;

	/// @brief 从相对坐标获输出接口
	/// @param point 基于该节点的相对位置
	/// @return 类型
	virtual TNodePortOutputPortPtr getNodeOutputPortAtRelativePointType( const QPoint &point ) const;

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

	virtual void move( const QPoint &point );

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

	Def_First_Mate_Node_Type( None );
protected:
	/// @brief 增加一个输入接口
	/// @param input_prot 输入接口对象指针
	/// @param support_multi_link_status
	/// @return 成功返回 true
	virtual bool appendInputProt( TNodePortInputPortPtr input_prot, bool support_multi_link_status );
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
	virtual QWidget * getNodeItemWidget( ) const;
	/// @brief 更新布局
	void updateLayout( );
	/// @brief 执行节点函数
	/// @param result_msg 错误返回的信息 
	/// @return 执行返回结果
	virtual nodeItemEnum::Node_Item_Result_Type run( QString &result_msg ) const;
Q_SIGNALS:
	void releaseThisPtr( NodeItem *release_node_item );
public: // 二进制相关
	// 扩展功能
protected:
	virtual bool initNodeItem( MainWidget *parent, const std_function< bool( MainWidget *main_widget_parent ) > &init_function );
	// 模版
protected:
	template< typename ttype >
		requires requires ( ttype *p, TNodePortOutputPortPtr port ) {
			port = p;
		}
	ttype * addOutputProt( const QString &prot_name ) {
		auto outputProt = new ttype( this );
		outputProt->setTitle( prot_name );
		if( appendOutputProt( outputProt ) )
			return outputProt;
		delete outputProt;
		return nullptr;
	}
	template< typename ttype >
		requires requires ( ttype *p, TNodePortInputPortPtr port ) {
			port = p;
		}
	ttype * addInputProt( const QString &prot_name, const bool support_multi_link_status ) {
		auto inputProt = new ttype( this );
		inputProt->setTitle( prot_name );
		if( appendInputProt( inputProt, support_multi_link_status ) )
			return inputProt;
		delete inputProt;
		return nullptr;
	}
};

#endif // NODEITEM_H_H_HEAD__FILE__
