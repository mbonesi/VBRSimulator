#include "vbrstates.h"

#include <QDebug>

VBRState_A::VBRState_A(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRState_A";}
VBRState *VBRState_A::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_A";

    bool bDelete = false;
    int val = 0;
    VBRState *pNewState = this;

    switch(probesReadout)
    {
    case 0:
        pNewState = this;
        break;
    case 1:
    case 2:
    case 3:
        pNewState = new VBRState_B(_context, _countsLimit);
        bDelete = true;
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

VBRState_B::VBRState_B(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRState_B";}
VBRState *VBRState_B::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_B";

    bool bDelete = false;
    int val = static_cast<int>(_context->GetOutputValue());
    VBRState *pNewState = this;
    switch(probesReadout)
    {
    case 0:
        val = 0;
        pNewState = new VBRState_A(_context, _countsLimit);
        bDelete = true;
        break;
    case 1:
    case 2:
    case 3:
        _counts++;
        if(_counts > _context->GetDelay()) {
            pNewState = new VBRState_C(_context, _countsLimit);
            bDelete = true;
        }
        else {
            pNewState = this;
        }
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

VBRState_C::VBRState_C(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRState_C";}
VBRState *VBRState_C::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_C";

    bool bDelete = false;
    int val = static_cast<int>(_context->GetOutputValue());
    VBRState *pNewState = this;
    switch(probesReadout)
    {
    case 0:
        val = 0;
        pNewState = new VBRState_A(_context, _countsLimit);
        bDelete = true;
        break;
    case 1:
        val =  _context->GetValue() - _context->GetVariation();
        break;
    case 2:
        val = _context->GetValue() - _context->GetVariation();
        pNewState = new VBRState_D(_context, _countsLimit);
        bDelete = true;
        break;
    case 3:
        val = _context->GetValue() - _context->GetVariation();
        pNewState = new VBRState_E(_context, _countsLimit);
        bDelete = true;
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

VBRState_D::VBRState_D(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRState_D";}
VBRState *VBRState_D::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_D";

    bool bDelete = false;
    uint val =_context->GetOutputValue();
    VBRState *pNewState = this;
    switch(probesReadout)
    {
    case 0:
        val = 0;
        pNewState = new VBRState_A(_context, _countsLimit);
        bDelete = true;
        break;
    case 1:
        val = _context->GetOutputValue() - _context->GetStep();
        if(val < (_context->GetValue() - _context->GetVariation()))
        {
            val = _context->GetValue() - _context->GetVariation();
            pNewState = new VBRState_C(_context, _countsLimit);
            bDelete = true;
        }                
        break;
    case 2:
        val = _context->GetOutputValue() + _context->GetStep();
        if(val > _context->GetValue())
        {
            val = _context->GetValue();
            pNewState = new VBRState_E(_context, _countsLimit);
            bDelete = true;
        }
        break;
    case 3:
        pNewState = new VBRState_F(_context, _countsLimit);
        bDelete = true;
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

VBRState_E::VBRState_E(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRState_E";}
VBRState *VBRState_E::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_E";

    bool bDelete = false;
    uint val =_context->GetOutputValue();
    VBRState *pNewState = this;
    switch(probesReadout)
    {
    case 0:
        val = 0;
        pNewState = new VBRState_A(_context, _countsLimit);
        bDelete = true;
        break;
    case 1:
        val = _context->GetValue();
        pNewState = new VBRState_D(_context, _countsLimit);
        bDelete = true;
        break;
    case 2:
        val = _context->GetValue();
        break;
    case 3:
        val  = _context->GetValue();
        pNewState = new VBRState_F(_context, _countsLimit);
        bDelete = true;
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

VBRState_F::VBRState_F(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRStateF";}
VBRState *VBRState_F::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_F";

    bool bDelete = false;
    uint val =_context->GetOutputValue();
    VBRState *pNewState = this;
    switch(probesReadout)
    {
    case 0:
        val = 0;
        pNewState = new VBRState_A(_context, _countsLimit);
        bDelete = true;
        break;
    case 1:
        pNewState = new VBRState_C(_context, _countsLimit);
        bDelete = true;
        break;
    case 2:
        val = val - _context->GetStep();
        if(val < _context->GetValue())
        {
            val = _context->GetValue();
            pNewState = new VBRState_E(_context, _countsLimit);
            bDelete = true;
        }
        break;
    case 3:
        val = val + _context->GetStep();
        if(val > (_context->GetValue() - _context->GetVariation()))
        {
            val = _context->GetValue() + _context->GetVariation();
            pNewState = new VBRState_G(_context, _countsLimit);
            bDelete = true;
        }
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

VBRState_G::VBRState_G(VBRStateMachine *pContext, uint countsLimit) : VBRState(pContext, countsLimit){qDebug() << "Created VBRState_G";}
VBRState *VBRState_G::HandleProbes(uint probesReadout)
{
    qDebug() << probesReadout << "handled by VBRState_G";

    bool bDelete = false;
    uint val =_context->GetOutputValue();
    VBRState *pNewState = this;
    switch(probesReadout)
    {
    case 0:
        val = 0;
        pNewState = new VBRState_A(_context, _countsLimit);
        bDelete = true;
        break;
    case 1:
        val = _context->GetValue() + _context->GetVariation();
        pNewState = new VBRState_D(_context, _countsLimit);
        bDelete = true;
        break;
    case 2:
        val = _context->GetValue() + _context->GetVariation();
        pNewState = new VBRState_F(_context, _countsLimit);
        bDelete = true;
        break;
    case 3:
        val = _context->GetValue() + _context->GetVariation();
        break;
    }
    _context->SetOutputValue(val);
    if(bDelete)
        delete this;
    return pNewState;
}

