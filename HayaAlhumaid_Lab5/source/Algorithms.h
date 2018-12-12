#ifndef LAB_ALGORITHMS_H
#define LAB_ALGORITHMS_H

class Algorithms {
public:
	virtual ~Algorithms() {};
	virtual void sel() {};
    virtual void exec() = 0;
    virtual void out() = 0;

};

//Algorithms::~Algorithms() {}

#endif //LAB_ALGORITHMS_H
