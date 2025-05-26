/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Vector.h"

class CSimpleTransform {
public:
    CSimpleTransform() : m_translate(), m_heading(0.0F) {}

public:
    CVector m_translate;
    float m_heading;

    void UpdateRwMatrix(RwMatrix* out);
    void Invert(const CSimpleTransform& base);
    void UpdateMatrix(class CMatrix* out);
};

VALIDATE_SIZE(CSimpleTransform, 0x10);
