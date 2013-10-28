#ifndef SAMPLE_H
#define SAMPLE_H

class Sample {
public:
	int x;
	int y;
	static int curr_x;
	static int curr_y;
	Sample(int _x, int _y);
	Sample();
	static bool getSample(Sample* sample, int max_x, int max_y);
};

#endif 