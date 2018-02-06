#ifndef Conveyor_H
#define Conveyor_H

#include <Commands/Subsystem.h>
#include <memory>
#include <Spark.h>

class Conveyor : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::unique_ptr<Spark> m_engine;
public:
	Conveyor();
	void Set(double val);
};

#endif  // Conveyor_H
