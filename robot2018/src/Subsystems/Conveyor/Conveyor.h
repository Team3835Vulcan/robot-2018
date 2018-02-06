#ifndef Conveyor_H
#define Conveyor_H

#include <Commands/Subsystem.h>
#include <memory>
#include <Spark.h>

class Conveyor : public Subsystem {
private:
	Conveyor();

	std::unique_ptr<Spark> m_engine;
public:
	static Conveyor& GetInstance();

	void Set(double val);
};

#endif  // Conveyor_H
