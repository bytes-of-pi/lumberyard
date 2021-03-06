/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef CRYINCLUDE_CRYPHYSICS_RAYGEOM_H
#define CRYINCLUDE_CRYPHYSICS_RAYGEOM_H
#pragma once

#if ENABLE_CRY_PHYSICS

class CRayGeom
    : public CGeometry
{
public:
    CRayGeom() { m_iCollPriority = 0; m_Tree.Build(this); m_Tree.SetRay(&m_ray); m_minVtxDist = 1.0f; }
    CRayGeom(const ray* pray)
    {
        m_iCollPriority = 0;
        m_ray.origin = pray->origin;
        m_ray.dir = pray->dir;
        m_dirn = pray->dir.normalized();
        m_Tree.Build(this);
        m_Tree.SetRay(&m_ray);
        m_minVtxDist = 1.0f;
    }
    CRayGeom(const Vec3& origin, const Vec3& dir)
    {
        m_iCollPriority = 0;
        m_ray.origin = origin;
        m_ray.dir = dir;
        m_dirn = dir.normalized();
        m_Tree.Build(this);
        m_Tree.SetRay(&m_ray);
        m_minVtxDist = 1.0f;
    }
    ILINE CRayGeom* CreateRay(const Vec3& origin, const Vec3& dir, const Vec3* pdirn = 0)
    {
        Vec3* pdirnLocal = (Vec3*)pdirn;
        if (pdirnLocal)
        {
            m_dirn = *pdirn;
        }
        else
        {
            m_dirn = dir.normalized();
        }
        m_ray.origin = origin;
        m_ray.dir = dir;
        return this;
    }
    void PrepareRay(ray* pray, geometry_under_test* pGTest);

    virtual int GetType() { return GEOM_RAY; }
    virtual int IsAPrimitive() { return 1; }
    virtual void SetData(const primitive* pray) { CreateRay(((ray*)pray)->origin, ((ray*)pray)->dir); }

    virtual void GetBBox(box* pbox);
    virtual int PrepareForIntersectionTest(geometry_under_test* pGTest, CGeometry* pCollider, geometry_under_test* pGTestColl, bool bKeepPrevContacts);
    virtual int RegisterIntersection(primitive* pprim1, primitive* pprim2, geometry_under_test* pGTest1, geometry_under_test* pGTest2,
        prim_inters* pinters);
    virtual int GetPrimitiveList(int iStart, int nPrims, int typeCollider, primitive* pCollider, int bColliderLocal,
        geometry_under_test* pGTest, geometry_under_test* pGTestOp, primitive* pRes, char* pResId);
    virtual int GetUnprojectionCandidates(int iop, const contact* pcontact, primitive*& pprim, int*& piFeature, geometry_under_test* pGTest);
    virtual int PreparePrimitive(geom_world_data* pgwd, primitive*& pprim, int iCaller = 0);
    virtual CBVTree* GetBVTree() { return &m_Tree; }
    virtual int GetPrimitive(int iPrim, primitive* pprim) { *(ray*)pprim = m_ray; return sizeof(ray); }
    virtual void PrepareForRayTest(float raylen) { m_dirn = m_ray.dir.normalized(); }

    virtual const primitive* GetData() { return &m_ray; }
    virtual Vec3 GetCenter() { return m_ray.origin + m_ray.dir * 0.5f; }
    virtual int GetSizeFast() { return sizeof(*this); }

    ray m_ray;
    Vec3 m_dirn;
    CRayBV m_Tree;
};

#endif // ENABLE_CRY_PHYSICS

#endif // CRYINCLUDE_CRYPHYSICS_RAYGEOM_H