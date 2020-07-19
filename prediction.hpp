#ifndef __PREDICTION__
#define __PREDICTION__

struct prediction
{
    int predict;
    int successfulcount, totalcount;
    prediction(int tmp = 0) : predict(tmp) {}

    void update(bool jumpresult)
    {
        if (predict == 0b11)
            predict = jumpresult ? 0b11 : 0b10;
        else if (predict == 0b10)
            predict = jumpresult ? 0b01 : 0b00;
        else if (predict == 0b01)
            predict = jumpresult ? 0b11 : 0b10;
        else
            predict = jumpresult ? 0b01 : 0b00;
    }
    bool getprediction();
};

prediction history;

bool prediction::getprediction()
{
    if (predict < 1)
    {
        return false;
    }
    else return true;
}


#endif
