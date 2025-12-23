#ifndef MENUDIRECTOR_H_H_HEAD__FILE__
#define MENUDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class SrackInfo;
class MenuDirector : public QObject {
	Q_OBJECT;
public:
	MenuDirector( QObject *parent = nullptr ) : QObject( parent ) { }
	~MenuDirector() override;
	virtual bool init();
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_obj_ptr 释放对象指针
	/// @param srack_info 信号行
	void release_signal( MenuDirector *release_obj_ptr, const SrackInfo &srack_info );
};

#endif // MENUDIRECTOR_H_H_HEAD__FILE__
