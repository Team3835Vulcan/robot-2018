#include <path/IPathMaker.h>

/*
Path Gradianizer according to catmull-rom method
if created with cep = true, you need to supply your own
gradients at the endpoint as degree values
WARNING: PATH MUST HAVE AT LEAST TWO WAYPOINTS
*/

class CatmullRom :
	public IPathMaker {
private:
	bool m_controlEndPoints;
	double m_heading0;
	double m_headingf;

public:
	CatmullRom(bool cep = false, double heading0 = 0, double headingf = 0);

	void operator() (std::vector<Waypoint>& waypoints) override;

};