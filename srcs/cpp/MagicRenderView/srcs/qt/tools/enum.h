#ifndef ENUM_H_H_HEAD__FILE__
#define ENUM_H_H_HEAD__FILE__
#pragma once
namespace tools::emums {
	enum class MouseEvent {
		No_Event, // 没有任何事件操作
		Drag_Event, // 拖拽
		Select_Event, // 选择
		Reset_Event, // 重置
	};
}

#endif // ENUM_H_H_HEAD__FILE__
