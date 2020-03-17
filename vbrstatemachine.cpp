#include "vbrstatemachine.h"
#include "vbrstates.h"
#include <QDebug>

VBRStateMachine::VBRStateMachine(uint interval, uint dly, uint step, uint variation, QObject *parent) : QObject(parent),
    _dly(dly),
    _step(step),
    _variation(variation),
    _setPoint(0)
{    
    _currState = new VBRState_A(this, dly);

    tm.setInterval(static_cast<int>(interval));
    connect(&tm, &QTimer::timeout, this, &VBRStateMachine::tick);
}

VBRStateMachine::~VBRStateMachine()
{
    delete _currState;
    _currState = nullptr;
}

bool VBRStateMachine::Start()
{
    if(_setPoint <= MAX_SETPOINT)
    {
        tm.start();
        return true;
    }
    return false;
}

bool VBRStateMachine::Stop()
{
    if(tm.isActive())
    {
        tm.stop();
        return true;
    }
    return false;
}

void VBRStateMachine::tick()
{
    _currState = _currState->HandleProbes(InputsLevel);
}

void VBRStateMachine::SetOutputValue(uint out)
{
    qDebug() << "FSM SetOutputValue" << out;
    if(out > 100)
        out = 100;
    DrivenOutput = out;
    emit(drivenOutputChanged(out));
}
