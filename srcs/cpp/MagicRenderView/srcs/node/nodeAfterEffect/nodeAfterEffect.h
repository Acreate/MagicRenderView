#ifndef NODEAFTEREFFECT_H_H_HEAD__FILE__
#define NODEAFTEREFFECT_H_H_HEAD__FILE__

#include <QWidget>

namespace NodeEnum {
	enum class NodeSelctType;
	enum class NodeStatusType;
}
class NodeAfterEffect : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 节点选择类型
	NodeEnum::NodeSelctType nodeSelctType;
	/// @brief 节点当前状态
	NodeEnum::NodeStatusType nodeStatusType;
protected:
	/// @brief 到顶层
	virtual void widgetToTopLayer( ) {
		raise( );
	}
	/// @brief 到底层
	virtual void widgetToBottmLayer( ) {
		lower( );
	}
public:
	NodeAfterEffect( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) ) : QWidget( parent, f ) {
		setAttribute( Qt::WA_TransparentForMouseEvents, true ); // 鼠标穿透，点击无效
		setAttribute( Qt::WA_TranslucentBackground );           // 透明背景（可选）
	}
	virtual NodeEnum::NodeSelctType getNodeSelctType( ) const;
	virtual void setNodeSelctType( NodeEnum::NodeSelctType node_selct_type );
	virtual NodeEnum::NodeStatusType getNodeStatusType( ) const;
	virtual void setNodeStatusType( NodeEnum::NodeStatusType node_status_type );
	virtual bool updateLayout( ) = 0;
};
#endif // NODEAFTEREFFECT_H_H_HEAD__FILE__
