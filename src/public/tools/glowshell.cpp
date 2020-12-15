#include "glowshell.h"

#include "tools.h"
#include <array>
namespace vec
{
	namespace tools
	{
		namespace glowshell
		{
			struct EntityData
			{
				explicit EntityData(CBaseEntity* entity) : pGlow(nullptr) {}
				~EntityData() {}

				CBaseEntity* GetGlow() { return this->pGlow; }
				void SetGlow(CBaseEntity* glow) { this->pGlow = glow; }

			private:
				CBaseEntity* pGlow;
			};
			EntityData* g_GlowEntityData[MAX_EDICTS];

			EventListener g_GlowShellTransmit;

			void OnClientDisconnected(int client)
			{
				sm::sdkhooks::SDKUnhookRAII(g_GlowShellTransmit);
			}

			sm::Action GlowOnTransmit(CBaseEntity* pGlow, CCheckTransmitInfo*, bool)
			{
				if (pGlow) return sm::Plugin_Continue;

				return sm::Plugin_Handled;
			}

			CBaseEntity* CreateGlowshell(CBaseEntity* parent, Color color, float duration)
			{
				// We must make sure that this parent entity is not nullptr.
				if (parent)
				{
					const char* model = vec::tools::GetModelName(parent);

					Vector position = vec::tools::GetAbsOrigin(parent);

					QAngle angle = vec::tools::GetAbsAngles(parent);

					CBaseEntity* pGlow = vec::utils::CreateDynamic("glow", position, angle, model, "", true, false, false, 0);
					g_GlowEntityData[sm::ent_cast<int>(sm::ent_cast<edict_t*>(parent))]->SetGlow(pGlow);
					
					vec::utils::SetRenderColor(pGlow, RenderColorType_t::Color_Red, 0);
					vec::utils::SetRenderColor(pGlow, RenderColorType_t::Color_Green, 0);
					vec::utils::SetRenderColor(pGlow, RenderColorType_t::Color_Blue, 0);
					vec::utils::SetRenderColor(pGlow, RenderColorType_t::Color_Alpha, 0);
					
					vec::tools::SetEffect(pGlow, EF_BONEMERGE | EF_NOSHADOW | EF_NORECEIVESHADOW);

					sm::sdktools::SetVariantString("!activator");
					sm::sdktools::AcceptEntityInput(pGlow, "SetParent", parent, pGlow);

					sm::sdktools::SetVariantString("primary");
					sm::sdktools::AcceptEntityInput(pGlow, "SetParentAttachment", pGlow, pGlow, 0);

					vec::utils::CreateGlowing(pGlow, true, 1, color.r(), color.g(), color.b(), color.a());

					sm::sdkhooks::SDKHookRAII(pGlow, sm::sdkhooks::SDKHook_SetTransmit, GlowOnTransmit);

					if (duration > 0.0) vec::utils::RemoveEntity(pGlow, duration);

					return pGlow;
				}

				return nullptr;
			}

			inline void RemoveGlowShell(CBaseEntity* entity)
			{
				CBaseEntity* glow = g_GlowEntityData[sm::ent_cast<int>(sm::ent_cast<edict_t*>(entity))]->GetGlow();
				if (glow)
				{
					const char* ed = sm::GetEdictClassname(sm::ent_cast<edict_t*>(glow));
					if (!strcmp(ed, "prop_dynamic")) vec::utils::RemoveEntity(glow, 0.1);
				}
			}
		}
	}
}