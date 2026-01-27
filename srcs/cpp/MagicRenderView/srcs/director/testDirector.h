#ifndef TESTDIRECTOR_H_H_HEAD__FILE__
#define TESTDIRECTOR_H_H_HEAD__FILE__
#include <QObject>

class TestDirector : public QObject {
	Q_OBJECT;
	friend class Application;
protected:
	TestDirector( QObject *parent = nullptr ) : QObject( parent ) { }
	/// @brief 测试全局节点的创建
	/// @return 成功返回 true
	virtual bool testAllNodeCreate( );
public:
	~TestDirector( ) override { }
};

#endif // TESTDIRECTOR_H_H_HEAD__FILE__
