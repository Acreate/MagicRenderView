#ifndef NODESTYLETYPEPEN_H_H_HEAD__FILE__
#define NODESTYLETYPEPEN_H_H_HEAD__FILE__
#pragma once
#include <qpen.h>

namespace NodeEnum {
	enum class NodeStyleType;
}
class NodeStyleTypePen {
	/// @brief 默认笔刷
	QPen nonePen;
	/// @brief 创建笔刷
	QPen createPen;
	/// @brief 运行笔刷
	QPen currentRunPen;
	/// @brief 旧运行笔刷
	QPen oldRunPen;
	/// @brief 选中笔刷
	QPen selectActivePen;
	/// @brief 上一次选中笔刷
	QPen selectOldPen;
	/// @brief 输出引用笔刷
	QPen selectOutputRefPen;
	/// @brief 输入引用笔刷
	QPen selectInputRefPen;
	/// @brief 警告笔刷
	QPen warningPen;
	/// @brief 错误笔刷
	QPen errorPen;
	/// @brief 建议笔刷
	QPen advisPen;
protected:
	virtual void setPenInfo( QPen &pen, const QColor &pen_color, const size_t &pen_width ) {
		pen.setWidth( pen_width );
		pen.setColor( pen_color );
	}
public:
	NodeStyleTypePen( );
	virtual ~NodeStyleTypePen( ) = default;
	virtual void renderPainter( QPainter &painter, const NodeEnum::NodeStyleType &node_render_style, const qint64 &node_width, const qint64 &node_height );
};

#endif // NODESTYLETYPEPEN_H_H_HEAD__FILE__
