/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientWeapon.h
*  PURPOSE:     Weapon entity class header
*  DEVELOPERS:  Jax <>
*
*****************************************************************************/

#ifndef __CCLIENTWEAPON_H
#define __CCLIENTWEAPON_H

#include <game/CWeaponInfo.h>
#include "CClientObject.h"

class CClientManager;
class CObject;
class CModelInfo;
enum eTargetType
{
    TARGET_TYPE_VECTOR,
    TARGET_TYPE_ENTITY,
    TARGET_TYPE_FIXED,
};

struct SWeaponConfiguration
{
    bool bShootIfTargetOutOfRange;
    bool bShootIfTargetBlocked;
    bool bDisableWeaponModel;
    bool bInstantReload;
    SLineOfSightFlags flags;
};

enum eWeaponFlags
{
    WEAPONFLAGS_FLAGS,
    WEAPONFLAGS_SHOOT_IF_OUT_OF_RANGE,
    WEAPONFLAGS_SHOOT_IF_TARGET_BOCKED,
    WEAPONFLAGS_DISABLE_MODEL,
    WEAPONFLAGS_INSTANT_RELOAD,
};
class CClientWeapon : public CClientObject
{
    DECLARE_CLASS( CClientWeapon, CClientObject )
public:
                            CClientWeapon           ( CClientManager * pManager, ElementID ID, eWeaponType type );
                            ~CClientWeapon          ( void );

    inline eClientEntityType        GetType                 ( void ) const                      { return CCLIENTWEAPON; };

    inline eWeaponType      GetWeaponType           ( void )                { return m_Type; }
    inline eWeaponState     GetWeaponState          ( void )                { return m_State; }
    inline void             SetWeaponState          ( eWeaponState state )  { m_State = state; }
    void                    SetWeaponTarget         ( CClientEntity * pTarget, int subTarget );
    void                    SetWeaponTarget         ( CVector vecTarget );
    CVector                 GetWeaponVectorTarget   ( void );
    CClientEntity *         GetWeaponEntityTarget   ( void );
    eTargetType             GetWeaponTargetType     ( void );
    void                    ResetWeaponTarget       ( void );

    void                    DoPulse                 ( void );

    void                    Create                  ( void );
    void                    Destroy                 ( void );

    void                    Fire                    ( bool bServerFire = false );

#ifdef SHOTGUN_TEST
    void                    FireInstantHit          ( CVector & vecOrigin, CVector & vecTarget, CVector & vecRotation, bool bRemote = false );
#else
    void                    FireInstantHit          ( CVector vecOrigin, CVector vecTarget, bool bServerFire = false, bool bRemote = false );
#endif
    void                    FireShotgun             ( CEntity* pFiringEntity, const CVector& vecOrigin, const CVector& vecTarget, CVector & vecRotation );

    void                    GetDirection            ( CVector & vecDirection );
    void                    SetDirection            ( CVector & vecDirection );
    void                    SetTargetDirection      ( CVector & vecDirection );
    void                    LookAt                  ( CVector & vecPosition, bool bInterpolate = false );
    CWeaponStat *           GetWeaponStat           ( void )   { return m_pWeaponStat; }
    CClientPlayer *         GetOwner                ( void )                { return m_pOwner; }
    void                    SetOwner                ( CClientPlayer * pOwner )  { m_pOwner = pOwner; }
    void                    SetFireRotationNoTarget ( const CVector& vecRotation )                  { m_vecFireRotationNoTarget = vecRotation; }
    const CVector&          GetFireRotationNoTarget ( void )                                        { return m_vecFireRotationNoTarget; }

    bool                    SetFlags                ( eWeaponFlags flags, bool bData );
    bool                    SetFlags                ( const SLineOfSightFlags flags );
    void                    SetFlags                ( const SWeaponConfiguration weaponConfig )     { m_weaponConfig = weaponConfig; }

    bool                    GetFlags                ( eWeaponFlags flags, bool &bData );
    bool                    GetFlags                ( SLineOfSightFlags& flags );
    SWeaponConfiguration    GetFlags                ( void )                                        { return m_weaponConfig; }

    void                    DoGunShells             ( CVector vecOrigin, CVector vecDirection );
    static int              GetWeaponFireTime       ( CWeaponStat * pWeaponStat );
    void                    SetWeaponFireTime       ( int iWeaponFireTime );
    int                     GetWeaponFireTime       ( void );
    void                    ResetWeaponFireTime     ( void );

    void                    SetClipAmmo             ( int iAmmo )                                 { m_nAmmoInClip = iAmmo; }
    int                     GetClipAmmo             ( void )                                      { return m_nAmmoInClip; }

    void                    SetAmmo                 ( int iAmmo )                                 { m_nAmmoTotal = iAmmo; }
    int                     GetAmmo                 ( void )                                      { return m_nAmmoTotal; }

private:
    CClientManager *        m_pManager;
    CWeapon *               m_pWeapon;
    CWeaponInfo *           m_pWeaponInfo;
    eWeaponType             m_Type;
    eWeaponState            m_State;
    DWORD                   m_dwAmmoInClip;
    CVector                 m_vecTargetDirection;
    CVector                 m_vecLastDirection;
    bool                    m_bHasTargetDirection;
    CClientMarker *         m_pMarker;
    CClientMarker *         m_pMarker2;
    short                   m_sDamage;
    CWeaponStat *           m_pWeaponStat;
    CClientEntityPtr        m_pTarget;
    CVector                 m_vecTarget;
    eTargetType             m_targetType;
    eBone                   m_targetBone;
    int                     m_itargetWheel;
    SWeaponConfiguration    m_weaponConfig;
    CClientPlayerPtr        m_pOwner;  // For lag compensation
    int                     m_nAmmoTotal;
    int                     m_nAmmoInClip;
    eWeaponState            m_PreviousState;
    CElapsedTime            m_fireTimer;
    CElapsedTime            m_reloadTimer;
    unsigned char           m_ucCounter;
    int                     m_iWeaponFireRate;
    CVector                 m_vecFireRotationNoTarget;      // Rotation adjustment when firing directly forward
};

#endif