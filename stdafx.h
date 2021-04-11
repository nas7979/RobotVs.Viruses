#pragma once
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <functional>
#include <io.h>
#include <dsound.h>
#include "SDKsound.h"
#include "SDKwavefile.h"
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "dsound.lib")

#define g_Device DXUTGetD3D9Device()
#define DT SYSTEM->m_DT
#define NSDT SYSTEM->m_NSDT
#define GC(a) GetComponent<a>()
#define AC(a) AddComponent<a>()
#define SetAnim(Key) GC(cAnimation)->SetAnimation(Key)
#define PartAnim(Pos, Scale, Rot, Depth, Color) PART->AddParticle<cPartAnim>(NULL, Pos, Scale, Rot, Depth, Color)
#define Part(Key, Pos, Scale, Rot, Depth, Color) PART->AddParticle<cPart>(IMAGE->Find(Key), Pos, Scale, Rot, Depth, Color)
#define PartText(Pos, Scale, Rot, Depth, Color) PART->AddParticle<cPartText>(NULL, Pos, Scale, Rot, Depth, Color)
#define PartFunc(Key, Pos, Scale, Rot, Depth, Color) PART->AddParticle<cPartFunc>(IMAGE->Find(Key), Pos, Scale, Rot, Depth, Color)

using namespace std;
using Vec2 = D3DXVECTOR2;
using Matrix = D3DXMATRIX;


#include "cSystemManager.h"
#include "Math.h"
using namespace Math;
#include "cImageManager.h"
#include "cObjectManager.h"
#include "cSoundManager.h"
#include "cParticleManager.h"
#include "cInputManager.h"
#include "cCameraManager.h"
#include "cScheduleManager.h"
#include "cSceneManager.h"

#include "cRenderer.h"
#include "cAnimation.h"
#include "cCollider.h"
#include "cBoxCollider.h"
#include "cLight.h"
#include "cRigidBody.h"