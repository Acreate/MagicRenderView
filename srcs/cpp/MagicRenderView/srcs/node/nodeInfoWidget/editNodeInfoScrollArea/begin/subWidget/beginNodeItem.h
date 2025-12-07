#ifndef BEGINNODEITEM_H_H_HEAD__FILE__
#define BEGINNODEITEM_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QVBoxLayout;
class NodeRefLinkInfo;
class BeginNodeItem : public QWidget {
	Q_OBJECT;
protected:
	std::vector< std::pair< QWidget *, NodeRefLinkInfo * > > nodeVector;
	QVBoxLayout *mainLayout;
	QColor setPenColor;
protected:
	virtual void appendNodeRefItem( NodeRefLinkInfo *item );
public:
	BeginNodeItem( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setNodeRefVector( const std::vector< NodeRefLinkInfo * > &node_ref_link_infos );
	virtual const QColor & getSetPenColor( ) const { return setPenColor; }
	virtual void setSetPenColor( const QColor &set_pen_color ) {
		setPenColor = set_pen_color;
		repaint( );
	}
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // BEGINNODEITEM_H_H_HEAD__FILE__
