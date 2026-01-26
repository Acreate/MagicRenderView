#include "mainCallFunction.h"
#include <app/application.h>
int MainCallFunction::runCode( int argc, char *argv[ ], char *envp[ ] ) {
	int resultCode;
	// 便于测试内存释放状态
	Application *app = new Application( argc, argv );
	// 初始化 app 实例（使用 static Application * getInstancePtr( )  或 qApp 获取指针）
	// 该初始化会生成窗口等
	if( app->init( ) == false )
		return -1;
	// 运用定义的测试代码
	if( app->runTest( ) == false )
		return -2;
	// 进入进程消息循环
	resultCode = app->exec( );
	// 释放 Application 后便于查看内存泄漏
	delete app;
	return resultCode;
}
