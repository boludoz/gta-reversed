/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "SimpleTransform.h"

// 0x54EF40
void CSimpleTransform::UpdateRwMatrix(RwMatrix* out)
{
    const float sinHeading = std::sin(m_heading);
    const float cosHeading = std::cos(m_heading);

    out->right = { cosHeading, sinHeading, 0.0f };
    out->up = { -sinHeading, cosHeading, 0.0f };
    out->at = { 0.0f, 0.0f, 1.0f };
    out->pos = m_translate;

    RwMatrixUpdate(out);

}

// 0x54EF90
void CSimpleTransform::Invert(const CSimpleTransform& base)
{
    const float cosHeading = cosf(base.m_heading);
    const float sinHeading = sinf(base.m_heading);

    m_translate.x = -(cosHeading * base.m_translate.x) - (sinHeading * base.m_translate.y);
    m_translate.y = (sinHeading * base.m_translate.x) - (cosHeading * base.m_translate.y);
    m_translate.z = -base.m_translate.z;
    m_heading = -base.m_heading;
}

// 0x54F1B0
void CSimpleTransform::UpdateMatrix(CMatrix* out)
{
    out->SetTranslate(m_translate);
    out->SetRotateZOnly(m_heading);
}
