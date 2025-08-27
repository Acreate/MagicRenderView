#ifndef DRAGINFOWINDOW_H_H_HEAD__FILE__
#define DRAGINFOWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>

class NodeFuncPreviewImageWidget;
class QLabel;
class DragInfoWindow : public QMainWindow {
	Q_OBJECT;
protected:
	QLabel *draw;
	bool isShowInfo;
public:
	DragInfoWindow( );
	virtual void setDragFunctionPreviewWidget( const NodeFuncPreviewImageWidget *drag_function_preview_widget );
	virtual bool isIsShowInfo( ) const { return isShowInfo; }
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void hideEvent( QHideEvent *event ) override;
};

#endif // DRAGINFOWINDOW_H_H_HEAD__FILE__
