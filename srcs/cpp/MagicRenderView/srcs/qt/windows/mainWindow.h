#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>
#include <QScrollArea>

#include <alias/type_alias.h>

class MainScrollAreaWidget;
class NodeItem;
class ItemWidget;
class Application;
class MainWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
protected:
	/// @brief 应用实例
	Application *appInstance;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 窗口的工具栏菜单
	QMenuBar *mainMenuBar;
	/// @brief 主要滚动视窗
	MainScrollAreaWidget *mainScrollArea;
	/// @brief 主要操作视窗
	MainWidget *mainWidget;
	/// @brief 记录窗口最大化，最小化，全屏之前的坐标位置
	QPoint oldPos, buffPos;
	/// @brief 是否记录坐标
	bool makePos;
	/// @brief 当前使用的路径
	QString currentSaveFilePath;
	/// @brief 文件保存路径 key
	QString savefilePathKey;
public:
	MainWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWindow( ) override;
	void setWindowToIndexScreenCentre( size_t index );
	virtual void overSave();
	virtual void normalSave();
	virtual void overLoadFile();
	virtual void normalLoadFile();
	/// @brief 窗口滚动到指定节点位置-大小不足时进行窗口扩充
	/// @param targetItemNode 目标节点
	virtual void ensureMainWidgetVisibleToItemNode( const NodeItem *targetItemNode );
	/// @brief 更新支持内容
	virtual void updateMainWidgetSupport( );
	/// @brief 对象序列化到二进制
	/// @return 二进制
	virtual size_t objMainWidgetToBin( std_vector< uint8_t > &result_vector ) const;
	/// @brief 加载二进制
	/// @param bin_data_ptr 数据起始位置
	/// @param bin_data_count 数据个数
	/// @return 使用数量
	virtual size_t loadMainWidgetBin( const uint8_t *bin_data_ptr, const size_t &bin_data_count );
	/// @brief 加载二进制
	/// @param bin_data_ptr 数据起始位置
	/// @param bin_data_count 数据个数
	/// @return 使用数量
	virtual size_t loadMainWidgetBin( const char *bin_data_ptr, const size_t &bin_data_count ) {
		return loadMainWidgetBin( ( const uint8_t * ) bin_data_ptr, bin_data_count );
	}
	/// @brief 加载二进制
	/// @param bin_vector 二进制列表
	/// @return 返回使用数据个数
	virtual size_t loadMainWidgetBin( const std_vector< uint8_t > &bin_vector ) {
		return loadMainWidgetBin( bin_vector.data( ), bin_vector.size( ) );
	}
	/// @brief 加载二进制
	/// @param bin_vector 二进制列表
	/// @return 返回使用数据个数
	virtual size_t loadMainWidgetBin( const QByteArray &bin_vector ) {
		return loadMainWidgetBin( bin_vector.data( ), bin_vector.size( ) );
	}
	virtual void quickSave();
	virtual void quickLoadFile();
protected:
	void resizeEvent( QResizeEvent *resize_event ) override;
	void changeEvent( QEvent * ) override;
	bool event( QEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void closeEvent( QCloseEvent *event ) override;
public:
	virtual void createNewItemWidget( ItemWidget *generate_new_item_widget, const QRect &contents_rect, const QRect &contents_item_widget_united_rect );;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
