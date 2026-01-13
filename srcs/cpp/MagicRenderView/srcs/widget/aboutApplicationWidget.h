#ifndef ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#define ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class AboutApplicationWindow;
class AboutApplicationWidget : public QWidget {
	Q_OBJECT;
protected:
	AboutApplicationWindow *parentWindow;
public:
	AboutApplicationWidget( AboutApplicationWindow *parent_window );
	/// @brief 获取软件信息（协议内容-开发内容）
	/// @return 不存在返回空字符串
	virtual QString getSoftwareProtocolInfo( );
};

#endif // ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
