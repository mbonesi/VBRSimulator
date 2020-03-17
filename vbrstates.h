#ifndef VBRSTATES_H
#define VBRSTATES_H

#include "vbrstatemachine.h"

class VBRState_A : public VBRState
{
public:
    VBRState_A(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};

class VBRState_B : public VBRState
{
public:
    VBRState_B(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};

class VBRState_C : public VBRState
{
public:
    VBRState_C(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};

class VBRState_D : public VBRState
{
public:
    VBRState_D(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};

class VBRState_E : public VBRState
{
public:
    VBRState_E(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};

class VBRState_F : public VBRState
{
public:
    VBRState_F(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};

class VBRState_G : public VBRState
{
public:
    VBRState_G(VBRStateMachine *pContext, uint countsLimit);

    // VBRState interface
public:
    VBRState *HandleProbes(uint probesReadout);
};






#endif // VBRSTATES_H
