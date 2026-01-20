#ifndef NODEBORDERDRAW_H_H_HEAD__FILE__
#define NODEBORDERDRAW_H_H_HEAD__FILE__
#include <QObject>
#include <QSize>
#include <QPoint>

class QPainter;
namespace NodeEnum {
	enum class NodeSelctType;
}
class NodeBorderAfterEffect;
class NodeBorderDraw : public QObject {
	Q_OBJECT;
protected:
	NodeBorderAfterEffect *nodeBorderAfterEffect;
	class StatusTypePen {
		/// @brief 无状态
		QPen *nonePen;
		/// @brief 创建
		QPen *createPen;
		/// @brief 节点正在运行
		QPen *currentRunPen;
		/// @brief 节点警告
		QPen *warningPen;
		/// @brief 节点错误
		QPen *errorPen;
		/// @brief 节点建议
		QPen *advisePen;
	public:
		StatusTypePen( );
		virtual ~StatusTypePen( );
		virtual QPen * getNonePen( ) const { return nonePen; }
		virtual QPen * getCreatePen( ) const { return createPen; }
		virtual QPen * getCurrentRunPen( ) const { return currentRunPen; }
		virtual QPen * getWarningPen( ) const { return warningPen; }
		virtual QPen * getErrorPen( ) const { return errorPen; }
		virtual QPen * getAdvisePen( ) const { return advisePen; }
	};
	struct SelectTypePen {
		/// @brief 没有选择
		QPen *nonePen;
		/// @brief 当前选择
		QPen *selectActivePen;
		/// @brief 以前选择
		QPen *selectOldPen;
		/// @brief 选择输出
		QPen *selectOutputRefPen;
		/// @brief 选择输入
		QPen *selectInputRefPen;
	public:
		SelectTypePen( );
		virtual ~SelectTypePen( );
		virtual QPen * getNonePen( ) const { return nonePen; }
		virtual QPen * getSelectActivePen( ) const { return selectActivePen; }
		virtual QPen * getSelectOldPen( ) const { return selectOldPen; }
		virtual QPen * getSelectOutputRefPen( ) const { return selectOutputRefPen; }
		virtual QPen * getSelectInputRefPen( ) const { return selectInputRefPen; }
	};
	StatusTypePen *statusTypePen;
	SelectTypePen *selectTypePen;
	int nodeBorderAfterEffectWidth;
	int nodeBorderAfterEffectHeight;
	QPen *statusPenPtr;
	QPen *selectPenPtr;
protected:
	virtual void drawRectBorder( QPainter *painter_ptr, QPen *pen_ptr, int x, int y, int width, int height );
	virtual bool selectSelectTypePen( );
	virtual bool selectStatusTypePen( );
public:
	NodeBorderDraw( NodeBorderAfterEffect *node_border_after_effect );
	~NodeBorderDraw( ) override;
	virtual QPen * getStatusPenPtr( ) const { return statusPenPtr; }
	virtual QPen * getSelectPenPtr( ) const { return selectPenPtr; }
	virtual void draw( );
};

#endif // NODEBORDERDRAW_H_H_HEAD__FILE__
