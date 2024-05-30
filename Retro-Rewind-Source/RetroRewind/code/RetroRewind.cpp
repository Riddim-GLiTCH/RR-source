#include <MarioKartWii/Race/RaceData.hpp>
#include <PulsarEngine/SlotExpansion/CupsConfig.hpp>
#include <PulsarEngine/Settings/UI/SettingsPanel.hpp>
#include <RetroRewind.hpp>

namespace RetroRewind {
Pulsar::System *System::Create() {
    return new System(); //now Pulsar::sInstance is of type RetroRewind
}
Pulsar::System::Inherit CreateRetroRewind(System::Create); //Create a Inherit that'll get called back by Pulsar::CreatePulsar

void System::AfterInit(){
    ++Pulsar::UI::SettingsPanel::pageCount;
    ++Pulsar::UI::SettingsPanel::pageCount;

    Pulsar::UI::SettingsPanel::radioButtonCount[SETTINGSTYPE_RR]=4;
    Pulsar::UI::SettingsPanel::scrollerCount[SETTINGSTYPE_RR]=1;
    Pulsar::UI::SettingsPanel::radioButtonCount[SETTINGSTYPE_RR2]=2;

    //Transmission
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_RR][0]=4;

    //Impossible CPU's
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_RR][1]=2;

    //Kart Restrictions
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_RR][2]=3;

    //Character Restrictions
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_RR][3]=4;

    //Gamemode
    Pulsar::UI::SettingsPanel::optionsPerPagePerScroller[SETTINGSTYPE_RR][0]=4;
    
    //Custom Music
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_RR2][0]=2;
    
    //Result Display
    Pulsar::UI::SettingsPanel::buttonsPerPagePerRow[SETTINGSTYPE_RR2][1]=2;
}


bool System::Is500cc() {
    return !Pulsar::CupsConfig::IsRegsSituation() && RaceData::sInstance->racesScenario.settings.engineClass == CC_50;
}

bool System::IsBattle() {
    return !Pulsar::CupsConfig::IsRegsSituation() && RaceData::sInstance->racesScenario.settings.engineClass == CC_BATTLE;
}

    System::CharacterRestriction System::GetCharacterRestriction(){
    const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (isFroom){
        return GetsInstance()->charRestrictMode;
    }
    return CHAR_DEFAULTSELECTION;
    }

    System::KartRestriction System::GetKartRestriction(){
    const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
    const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
    if (isFroom){
        return GetsInstance()->kartRestrictMode;
    }
    return KART_DEFAULTSELECTION;
    }

    System::Gamemode System::GetGameMode(){
        const bool isRegs = Pulsar::CupsConfig::IsRegsSituation();
        const GameMode gameMode = RaceData::sInstance->menusScenario.settings.gamemode;
        const bool isFroom = gameMode == MODE_PRIVATE_VS || gameMode == MODE_PRIVATE_BATTLE;
        const bool isRegional = gameMode == MODE_PUBLIC_VS || gameMode == MODE_PUBLIC_BATTLE;
        if (!isRegs){
            if (isFroom){
                return GetsInstance()->hostMode;
            }
            else if (isRegional){
                return GAMEMODE_DEFAULT;
            }
            return static_cast<Gamemode>(Pulsar::Settings::Mgr::GetSettingValue(static_cast<Pulsar::Settings::Type>(System::SETTINGSTYPE_RR), SETTINGRR_SCROLLER_GAMEMODES));
        }
        return GAMEMODE_NONE;
    }

System::WeightClass System::GetWeightClass(const CharacterId id){
    switch (id)
    {
        case BABY_MARIO:
        case BABY_LUIGI:
        case BABY_PEACH:
        case BABY_DAISY:
        case TOAD:
        case TOADETTE:
        case KOOPA_TROOPA:
        case DRY_BONES:
            return LIGHTWEIGHT;
        case MARIO:
        case LUIGI:
        case PEACH:
        case DAISY:
        case YOSHI:
        case BIRDO:
        case DIDDY_KONG:
        case BOWSER_JR:
            return MEDIUMWEIGHT;
        case WARIO:
        case WALUIGI:
        case DONKEY_KONG:
        case BOWSER:
        case KING_BOO:
        case ROSALINA:
        case FUNKY_KONG:
        case DRY_BOWSER:
            return HEAVYWEIGHT;
        default:
            return MIIS;
    }
}

} // namespace RetroRewind