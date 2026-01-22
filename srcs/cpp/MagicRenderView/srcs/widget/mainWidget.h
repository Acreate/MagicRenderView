#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class NormalGenerateNodeMenu;
class PrinterDirector;
class OutputPort;
class InputPort;
class NodeClickInfo;
class MainWindow;
class MainWidgetScrollArea;
class Node;
class Application;
class NodeDirector;
class MainWidget : public QWidget {
	Q_OBJECT;
	/// @brief 不可获取成员变量
protected:
	Application *appInstancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	/// @brief 可获取成员变量
	MainWindow *mainWindow;
	MainWidgetScrollArea *mainWidgetScrollArea;
	NodeClickInfo *clickInfoPtr;
	Node *oldSelectNode;
	Node *dragNode;
	InputPort *selectInputPort;
	OutputPort *selectOutputPort;
	QDateTime *oldClickTime;
	QPoint offsetPoint;
	std::vector< Node * > nodeVector;
	QPoint startPoint;
	QPoint endPoint;
	bool isDrawLine;
	virtual void removeNodeObj( Node *remove_node );
	virtual void appendNodeObj( Node *append_node );
	virtual void raiseNode( Node *raise_node );
	virtual void drawBegin( const QPoint &start_point );
	virtual void drawLinePoint( const QPoint &end_point );
	virtual void drawEnd( );
	/// @brief 构造/析构 
public:
	MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	virtual bool addNode( Node *node_ref_link_info );
	virtual bool ensureVisible( Node *target );
	virtual bool init( );
	virtual bool getPointNodeClickInfo( const QPoint &click_point, NodeClickInfo &result_node_click_info );
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	/// @brief 快捷功能
	virtual bool copySelectNodeInfo( );
	virtual bool pastePointNodeInfo( );
	virtual bool cutSelectNodeInfo( );
	virtual bool cancelNodeInfo( );
	virtual bool deleteSelectNodeInfo( );
	virtual bool calculateNodeRenderSize( );
	/// @brief 重载
protected:
	void showEvent( QShowEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	void release_signal( MainWidget *release_ptr );
	void select_node_signal( MainWidget *sender_signal_ptr, Node *select_node_ptr );
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
