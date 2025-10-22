#ifndef NODEMODULEITEMWIDGET_H_H_HEAD__FILE__
#define NODEMODULEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class NodeItemInfo;
class NodeModuleItemWidget : public QWidget {
	Q_OBJECT;
protected:
	std_vector< NodeItemInfo * > runNodeItemInfos;
public:
	NodeModuleItemWidget( const std_vector< NodeItemInfo * > &run_node_item_infos, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual const std_vector< NodeItemInfo * > & getRuNodeItemInfos( ) const { return runNodeItemInfos; }
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODEMODULEITEMWIDGET_H_H_HEAD__FILE__
