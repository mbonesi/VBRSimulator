#ifndef VBRSTATEMACHINE_H
#define VBRSTATEMACHINE_H

#include <QObject>
#include <QTimer>
#include <QAtomicInteger>

#define MAX_SETPOINT 100

class VBRState;

class VBRStateMachine : public QObject
{
    Q_OBJECT

    QTimer tm;

    VBRState *_currState = nullptr;

    QAtomicInteger<uint> DrivenOutput;

    const uint _dly;
    const uint _step;
    const uint _variation;

    uint _setPoint;

private slots:
    void tick();

public:

    uint GetDelay() {return _dly;}
    uint GetStep() {return _step;}
    uint GetVariation() {return _variation;}

    QAtomicInteger<uint> InputsLevel;

    void SetValue(uint newValue) {_setPoint = newValue;}
    uint GetValue() {return _setPoint;}

    void SetOutputValue(int out);
    uint GetOutputValue() {return DrivenOutput;}

    explicit VBRStateMachine(uint interval, uint dly, uint step, uint variation, QObject *parent = nullptr);
    ~VBRStateMachine();
    bool Start();
    bool Stop();

signals:
    void drivenOutputChanged(uint output);

};

class VBRState
{
protected:
    VBRStateMachine *_context=nullptr;
    uint _counts = 0;
    const uint _countsLimit;

public:
    VBRState(VBRStateMachine *pContext, uint countsLimit);
    virtual ~VBRState();

    virtual VBRState *HandleProbes(uint probesReadout) = 0;
};


#endif // VBRSTATEMACHINE_H
