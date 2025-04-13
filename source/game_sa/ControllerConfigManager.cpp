#include "StdInc.h"
#include "WinInput.h" // Ensure the correct header file is included for WinInput

#include "ControllerConfigManager.h"

CControllerConfigManager& ControlsManager = *(CControllerConfigManager *) 0xB70198;
GxtChar (&NewStringWithNumber)[32] = *(GxtChar(*)[32])0xB7147C;

void CControllerConfigManager::InjectHooks() {
    RH_ScopedClass(CControllerConfigManager);
    RH_ScopedCategoryGlobal();
    RH_ScopedInstall(Constructor, 0x531EE0);
    RH_ScopedInstall(LoadSettings, 0x530530);
    RH_ScopedInstall(SaveSettings, 0x52D200);
    RH_ScopedInstall(InitDefaultControlConfiguration, 0x530640);
    RH_ScopedInstall(InitDefaultControlConfigJoyPad, 0x530B00);
    RH_ScopedInstall(InitDefaultControlConfigMouse, 0x52F6F0);
    RH_ScopedInstall(InitialiseControllerActionNameArray, 0x52D260);
    RH_ScopedInstall(ReinitControls, 0x531F20);
    RH_ScopedInstall(SetMouseButtonAssociatedWithAction, 0x52F590);
    RH_ScopedInstall(StoreMouseButtonState, 0x52DA30);
    RH_ScopedInstall(UpdateJoyInConfigMenus_ButtonDown, 0x52DAB0);
    RH_ScopedInstall(UpdateJoy_ButtonDown, 0x530ED0);
    RH_ScopedInstall(UpdateJoy_ButtonUp, 0x531070);
    RH_ScopedInstall(StoreJoyButtonStates, 0x52F510);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_DebugStuff, 0x52DC10);
    RH_ScopedInstall(UpdateJoyInConfigMenus_ButtonUp, 0x52DC20);
    RH_ScopedInstall(AffectControllerStateOn_ButtonUp_DebugStuff, 0x52DD80);
    RH_ScopedInstall(ClearSimButtonPressCheckers, 0x52DD90);
    RH_ScopedInstall(GetJoyButtonJustUp, 0x52D1C0);
    RH_ScopedInstall(GetJoyButtonJustDown, 0x52D1E0);
    RH_ScopedInstall(GetIsKeyboardKeyDown, 0x52DDB0);
    RH_ScopedInstall(GetIsKeyboardKeyJustDown, 0x52E450);
    RH_ScopedInstall(GetIsMouseButtonDown, 0x52EF30);
    RH_ScopedInstall(GetIsMouseButtonUp, 0x52F020);
    RH_ScopedInstall(GetIsMouseButtonJustUp, 0x52F110);
    RH_ScopedInstall(GetIsKeyBlank, 0x52F2A0);
    RH_ScopedInstall(GetActionType, 0x52F2F0);
    RH_ScopedInstall(GetControllerKeyAssociatedWithAction, 0x52F4F0);
    RH_ScopedInstall(ResetSettingOrder, 0x52F5F0);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_Driving, 0x52F7B0);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_FirstPersonOnly, 0x52F9E0);
    RH_ScopedInstall(GetControllerSettingTextMouse, 0x52F390);
    RH_ScopedInstall(GetControllerSettingTextJoystick, 0x52F450);
    RH_ScopedInstall(GetIsActionAButtonCombo, 0x52F550);
    RH_ScopedInstall(GetButtonComboText, 0x52F560);
    RH_ScopedInstall(GetMouseButtonAssociatedWithAction, 0x52F580);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_ThirdPersonOnly, 0x52FA20);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_FirstAndThirdPersonOnly, 0x52FAB0);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_AllStates, 0x52FCA0);
    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_VehicleAndThirdPersonOnly, 0x52FD20);
    RH_ScopedInstall(HandleButtonRelease, 0x52FD40);
    RH_ScopedInstall(ClearSettingsAssociatedWithAction, 0x52FD70);
    RH_ScopedInstall(GetKeyNameForKeyboard, 0x52FE10);
    RH_ScopedInstall(UnmapVehicleEnterExit, 0x531BC0);
    RH_ScopedInstall(ClearSniperZoomMappings, 0x531C20);
    RH_ScopedInstall(DeleteMatchingActionInitiators, 0x531C90);
    RH_ScopedInstall(GetControllerSettingText, 0x531E20);
    RH_ScopedInstall(GetActionKeyName, 0x531E90);
    RH_ScopedInstall(GetDefinedKeyByGxtName, 0x5303D0);
    RH_ScopedInstall(AffectPadFromMouse, 0x5314A0);
    RH_ScopedInstall(Clear1st3rdPersonMappings, 0x5318C0);
    RH_ScopedInstall(ClearVehicleMappings, 0x5319D0);
    RH_ScopedInstall(SetControllerKeyAssociatedWithAction, 0x530490);
    RH_ScopedInstall(MakeControllerActionsBlank, 0x530500);
    RH_ScopedInstall(AffectPadFromKeyBoard, 0x531140);
    RH_ScopedInstall(ClearCommonMappings, 0x531670);
    RH_ScopedInstall(ClearPedMappings, 0x531730);
}

// 0x531EE0
CControllerConfigManager::CControllerConfigManager() {
    /* Member variable init done in header */

    MakeControllerActionsBlank();
    InitDefaultControlConfiguration();
    InitialiseControllerActionNameArray();
}

// 0x531730
void CControllerConfigManager::ClearPedMappings(eControllerAction action, KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }

    CheckAndClear(eControllerAction::GO_LEFT, type, button);
    CheckAndClear(eControllerAction::GO_RIGHT, type, button);
    CheckAndClear(eControllerAction::GROUP_CONTROL_FWD, type, button);
    CheckAndClear(eControllerAction::GROUP_CONTROL_BWD, type, button);
    CheckAndClear(eControllerAction::CONVERSATION_NO, type, button);
    CheckAndClear(eControllerAction::CONVERSATION_YES, type, button);
    CheckAndClear(eControllerAction::PED_CYCLE_WEAPON_LEFT, type, button);
    CheckAndClear(eControllerAction::PED_CYCLE_WEAPON_RIGHT, type, button);
    CheckAndClear(eControllerAction::PED_JUMPING, type, button);
    CheckAndClear(eControllerAction::PED_SPRINT, type, button);
    CheckAndClear(eControllerAction::PED_LOOKBEHIND, type, button);
    CheckAndClear(eControllerAction::PED_DUCK, type, button);

    if (action != eControllerAction::PED_FIRE_WEAPON_ALT) {
        CheckAndClear(eControllerAction::PED_ANSWER_PHONE, type, button);
    }

    CheckAndClear(eControllerAction::PED_WALK, type, button);

    if (FrontEndMenuManager.m_ControlMethod) {
        CheckAndClear(eControllerAction::PED_CENTER_CAMERA_BEHIND_PLAYER, type, button);
    }
}


// 0x531670
void CControllerConfigManager::ClearCommonMappings(eControllerAction nop, KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }

    CheckAndClear(eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS, type, button);
    CheckAndClear(eControllerAction::NETWORK_TALK, type, button);
    CheckAndClear(eControllerAction::SWITCH_DEBUG_CAM_ON, type, button);
    CheckAndClear(eControllerAction::TOGGLE_DPAD, type, button);
    CheckAndClear(eControllerAction::TAKE_SCREEN_SHOT, type, button);
    CheckAndClear(eControllerAction::SHOW_MOUSE_POINTER_TOGGLE, type, button);
}

// 0x530490
void CControllerConfigManager::SetControllerKeyAssociatedWithAction(eControllerAction Action, KeyCode KeyCode, eControllerType ControllerArraytoEnter) {
    ResetSettingOrder(Action);
    auto numOfSettings = GetNumOfSettingsForAction(Action);
    m_Actions[Action].Keys[ControllerArraytoEnter].m_uiActionInitiator = KeyCode;
    m_Actions[Action].Keys[ControllerArraytoEnter].m_uiSetOrder = eContSetOrder(numOfSettings + 1);
}


// 0x5319D0
void CControllerConfigManager::ClearVehicleMappings(eControllerAction nop, KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }

    CheckAndClear(eControllerAction::VEHICLE_FIRE_WEAPON_ALT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_FIRE_WEAPON, type, button);
    CheckAndClear(eControllerAction::VEHICLE_STEER_LEFT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_STEER_RIGHT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_STEER_UP, type, button);
    CheckAndClear(eControllerAction::VEHICLE_STEER_DOWN, type, button);
    CheckAndClear(eControllerAction::VEHICLE_ACCELERATE, type, button);
    CheckAndClear(eControllerAction::VEHICLE_BRAKE, type, button);
    CheckAndClear(eControllerAction::VEHICLE_RADIO_STATION_UP, type, button);
    CheckAndClear(eControllerAction::VEHICLE_RADIO_STATION_DOWN, type, button);
    CheckAndClear(eControllerAction::VEHICLE_RADIO_TRACK_SKIP, type, button);
    CheckAndClear(eControllerAction::VEHICLE_HORN, type, button);
    CheckAndClear(eControllerAction::TOGGLE_SUBMISSIONS, type, button);
    CheckAndClear(eControllerAction::VEHICLE_HANDBRAKE, type, button);
    CheckAndClear(eControllerAction::VEHICLE_LOOKLEFT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_LOOKRIGHT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_LOOKBEHIND, type, button);
    CheckAndClear(eControllerAction::VEHICLE_MOUSELOOK, type, button);
    CheckAndClear(eControllerAction::VEHICLE_TURRETLEFT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_TURRETRIGHT, type, button);
    CheckAndClear(eControllerAction::VEHICLE_TURRETUP, type, button);
    CheckAndClear(eControllerAction::VEHICLE_TURRETDOWN, type, button);
}

// 0x5318C0
void CControllerConfigManager::Clear1st3rdPersonMappings(eControllerAction action, KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }

    if (action != eControllerAction::PED_ANSWER_PHONE)
    {
        CheckAndClear(eControllerAction::PED_FIRE_WEAPON_ALT, type, button);
    }

    CheckAndClear(eControllerAction::PED_FIRE_WEAPON, type, button);
    CheckAndClear(eControllerAction::PED_LOCK_TARGET, type, button);
    CheckAndClear(eControllerAction::GO_FORWARD, type, button);
    CheckAndClear(eControllerAction::GO_BACK, type, button);

    if (FrontEndMenuManager.m_ControlMethod) {
        CheckAndClear(eControllerAction::PED_1RST_PERSON_LOOK_LEFT, type, button);
        CheckAndClear(eControllerAction::PED_1RST_PERSON_LOOK_RIGHT, type, button);
        CheckAndClear(eControllerAction::PED_1RST_PERSON_LOOK_DOWN, type, button);
        CheckAndClear(eControllerAction::PED_1RST_PERSON_LOOK_UP, type, button);
    }
}

// 0x52F510
void CControllerConfigManager::StoreJoyButtonStates() {
    for (auto&& [idx, bs] : rngv::enumerate(m_ButtonStates)) {
        bs = (m_NewJoyState.rgbButtons[idx] & 0x80) != 0;
    }
}

// unused
// 0x531E90
const GxtChar* CControllerConfigManager::GetActionKeyName(eControllerAction action) {
    int32 v3 = 0;
    ResetSettingOrder(action);
    for (auto i = (int32)m_Actions[action].Keys[eControllerType::KEYBOARD].m_uiSetOrder; !i; i += 2) {
        if (++v3 >= 2) {
            return 0;
        }
    }
    return GetKeyNameForKeyboard(action, (eControllerType)v3);
}

// 0x531E20
const GxtChar* CControllerConfigManager::GetControllerSettingText(eControllerAction action, eContSetOrder priority) {
    for (auto type = 0u; type < eControllerType::CONTROLLER_NUM; ++type) {
        if (m_Actions[action].Keys[type].m_uiSetOrder == priority) {
            switch (type) {
            case eControllerType::KEYBOARD:
            case eControllerType::OPTIONAL_EXTRA_KEY: return GetKeyNameForKeyboard(action, (eControllerType)type);
            case eControllerType::MOUSE:              return GetControllerSettingTextMouse(action);
            case eControllerType::JOY_STICK:          return GetControllerSettingTextJoystick(action);
            default:                                  NOTSA_UNREACHABLE();
            }
        }
    }
    return 0;
}

// 0x531C20
void CControllerConfigManager::ClearSniperZoomMappings(eControllerAction nop, KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }

    CheckAndClear(eControllerAction::PED_SNIPER_ZOOM_IN, type, button);
    CheckAndClear(eControllerAction::PED_SNIPER_ZOOM_OUT, type, button);
}

// 0x531BC0
void CControllerConfigManager::UnmapVehicleEnterExit(KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }

    CheckAndClear(eControllerAction::VEHICLE_ENTER_EXIT, type, button);
}

// 0x52FD70
void CControllerConfigManager::ClearSettingsAssociatedWithAction(eControllerAction Action, eControllerType ArrayToEnter) {
    constexpr RsKeyCodes arrayToTest[eControllerType::CONTROLLER_NUM] = { rsNULL, rsNULL, (RsKeyCodes)(0), (RsKeyCodes)(0) };
    if (ArrayToEnter >= eControllerType::KEYBOARD && ArrayToEnter <= eControllerType::JOY_STICK) {
        m_Actions[Action].Keys[ArrayToEnter].m_uiActionInitiator  = arrayToTest[ArrayToEnter];
        m_Actions[Action].Keys[ArrayToEnter].m_uiSetOrder = eContSetOrder::NO_ORDER_SET;
    }
    ResetSettingOrder(Action);
}

// unused
// 0x52FD20
eControllerType CControllerConfigManager::AffectControllerStateOn_ButtonDown_VehicleAndThirdPersonOnly(KeyCode button, eControllerType type, CControllerState* state) {
    CheckAndSetButton(eControllerAction::VEHICLE_ENTER_EXIT, type, button, state->ButtonTriangle);
    return type;
}

// 0x52FCA0
CControllerState* CControllerConfigManager::AffectControllerStateOn_ButtonDown_AllStates(KeyCode button, eControllerType type, CControllerState* state) {
    CheckAndSetButton(eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS, type, button, state->Select);
    CheckAndSetPad(eControllerAction::CONVERSATION_NO, type, button, state->DPadLeft, state->DPadRight);
    CheckAndSetPad(eControllerAction::CONVERSATION_YES, type, button, state->DPadRight, state->DPadLeft);
    CheckAndSetButton(eControllerAction::NETWORK_TALK, type, button, state->m_bChatIndicated);
    return state;
}

// 0x52F580
int32 CControllerConfigManager::GetMouseButtonAssociatedWithAction(eControllerAction action) {
    return m_Actions[action].Keys[eControllerType::MOUSE].m_uiActionInitiator;
}

// 0x52FAB0
eControllerType CControllerConfigManager::AffectControllerStateOn_ButtonDown_FirstAndThirdPersonOnly(KeyCode button, eControllerType type, CControllerState* state) {
    const auto CheckAndSetStick = [&](eControllerAction action, int16& stickValue, bool& stickFlag, int16 value) {
        if (m_Actions[action].Keys[type].m_uiActionInitiator == button) {
            if (stickFlag || (stickValue != 0 && stickValue != value)) {
                stickValue = 0;
                stickFlag  = true;
            } else {
                stickValue = value;
            }
        }
    };

    CheckAndSetButton(eControllerAction::PED_FIRE_WEAPON, type, button, state->ButtonCircle);   
    CheckAndSetButton(eControllerAction::PED_FIRE_WEAPON_ALT, type, button, state->LeftShoulder1);  
    CheckAndSetButton(eControllerAction::PED_LOCK_TARGET, type, button, state->RightShoulder1);

    CheckAndSetStick(eControllerAction::GO_FORWARD, state->LeftStickY, m_bStickL_Up_Dwn_MovementBothDown[type], -128);   
    CheckAndSetStick(eControllerAction::GO_BACK, state->LeftStickY, m_bStickL_Up_Dwn_MovementBothDown[type], 128);    
    CheckAndSetStick(eControllerAction::GO_LEFT, state->LeftStickX, m_bStickL_X_Rgh_Lft_MovementBothDown[type], -128);
    CheckAndSetStick(eControllerAction::GO_RIGHT, state->LeftStickX, m_bStickL_X_Rgh_Lft_MovementBothDown[type], 128); 

    CheckAndSetButton(eControllerAction::PED_WALK, type, button, state->m_bPedWalk);

    CheckAndSetPad(eControllerAction::GROUP_CONTROL_FWD, type, button, state->DPadUp, state->DPadDown);
    CheckAndSetPad(eControllerAction::GROUP_CONTROL_BWD, type, button, state->DPadDown, state->DPadUp);    

    CheckAndSetStick(eControllerAction::PED_1RST_PERSON_LOOK_LEFT, state->RightStickX, m_bStickR_X_Rgh_Lft_MovementBothDown[type], -128); 
    CheckAndSetStick(eControllerAction::PED_1RST_PERSON_LOOK_RIGHT, state->RightStickX, m_bStickR_X_Rgh_Lft_MovementBothDown[type], 128);  

    if (FrontEndMenuManager.m_ControlMethod) {
        CheckAndSetStick(eControllerAction::PED_1RST_PERSON_LOOK_UP, state->RightStickY, m_bStickR_Up_Dwn_MovementBothDown[type], 128); 
        CheckAndSetStick(eControllerAction::PED_1RST_PERSON_LOOK_DOWN, state->RightStickY, m_bStickR_Up_Dwn_MovementBothDown[type], -128);
    }

    return type;
}

// 0x52FA20
int32 CControllerConfigManager::AffectControllerStateOn_ButtonDown_ThirdPersonOnly(KeyCode button, eControllerType type, CControllerState* state) {
    CheckAndSetButton(eControllerAction::PED_LOOKBEHIND, type, button, state->ShockButtonR);
    CheckAndSetButton(eControllerAction::PED_JUMPING, type, button, state->ButtonSquare);
    CheckAndSetButton(eControllerAction::PED_ANSWER_PHONE, type, button, state->LeftShoulder1);
    CheckAndSetButton(eControllerAction::PED_CYCLE_WEAPON_LEFT, type, button, state->LeftShoulder2);
    CheckAndSetButton(eControllerAction::PED_CYCLE_WEAPON_RIGHT, type, button, state->RightShoulder2);
    CheckAndSetButton(eControllerAction::PED_SPRINT, type, button, state->ButtonCross);
    CheckAndSetButton(eControllerAction::PED_DUCK, type, button, state->ShockButtonL);

    if (FrontEndMenuManager.m_ControlMethod) {
        CheckAndSetButton(eControllerAction::PED_CENTER_CAMERA_BEHIND_PLAYER, type, button, state->LeftShoulder1);
    }
    return button;
}

// 0x52F550
bool CControllerConfigManager::GetIsActionAButtonCombo(eControllerAction action) {
    // NOP
    return false;
}

// 0x52F4F0
int32 CControllerConfigManager::GetControllerKeyAssociatedWithAction(eControllerAction action, eControllerType type) {
    return m_Actions[action].Keys[type].m_uiActionInitiator;
}

// 0x52F9E0
int32 CControllerConfigManager::AffectControllerStateOn_ButtonDown_FirstPersonOnly(KeyCode button, eControllerType type, CControllerState* state) {
    CheckAndSetButton(eControllerAction::PED_SNIPER_ZOOM_IN, type, button, state->ButtonSquare);
    CheckAndSetButton(eControllerAction::PED_SNIPER_ZOOM_OUT, type, button, state->ButtonCross);
    CheckAndSetButton(eControllerAction::PED_DUCK, type, button, state->ShockButtonL);
    return button;
}

// 0x52FD40
int32 CControllerConfigManager::HandleButtonRelease(KeyCode button, eControllerType type, CControllerState* state) {
    const auto CheckAndReset = [&](eControllerAction action, int16& stateFlag) {
        if (m_Actions[action].Keys[type].m_uiActionInitiator == button) {
            stateFlag = 0;
        }
    };
    CheckAndReset(eControllerAction::NETWORK_TALK, state->m_bChatIndicated);
    CheckAndReset(eControllerAction::VEHICLE_MOUSELOOK, state->m_bVehicleMouseLook);
    return button;
}

// 0x52F7B0
eControllerType CControllerConfigManager::AffectControllerStateOn_ButtonDown_Driving(KeyCode button, eControllerType type, CControllerState* state) {
    const auto CheckAndSetStick = [&](eControllerAction action, int16& stickValue, bool& stickFlag, int16 value) {
        if (m_Actions[action].Keys[type].m_uiActionInitiator == button) {
            if (stickFlag) {
                stickValue = 0;
                stickFlag  = true;
            } else {
                stickValue = value;
            }
        }
    };
    
    CheckAndSetButton(eControllerAction::VEHICLE_FIRE_WEAPON, type, button, state->ButtonCircle);
    CheckAndSetButton(eControllerAction::VEHICLE_FIRE_WEAPON_ALT, type, button, state->LeftShoulder1);

    // why double ? check: if you press both buttons you look behind
    CheckAndSetButton(eControllerAction::VEHICLE_LOOKBEHIND, type, button, state->LeftShoulder2); 
    CheckAndSetButton(eControllerAction::VEHICLE_LOOKBEHIND, type, button, state->RightShoulder2);

    CheckAndSetButton(eControllerAction::VEHICLE_LOOKLEFT, type, button, state->LeftShoulder2);
    CheckAndSetButton(eControllerAction::VEHICLE_LOOKRIGHT, type, button, state->RightShoulder2);
    CheckAndSetButton(eControllerAction::VEHICLE_MOUSELOOK, type, button, state->m_bVehicleMouseLook);
    CheckAndSetButton(eControllerAction::VEHICLE_HORN, type, button, state->ShockButtonL);
    CheckAndSetButton(eControllerAction::VEHICLE_HANDBRAKE, type, button, state->RightShoulder1);
    CheckAndSetButton(eControllerAction::VEHICLE_ACCELERATE, type, button, state->ButtonCross);
    CheckAndSetButton(eControllerAction::VEHICLE_BRAKE, type, button, state->ButtonSquare);
    CheckAndSetStick(eControllerAction::VEHICLE_STEER_UP, state->LeftStickY, m_bStickL_Up_Dwn_MovementBothDown[type], -128);
    CheckAndSetStick(eControllerAction::VEHICLE_STEER_DOWN, state->LeftStickY, m_bStickL_Up_Dwn_MovementBothDown[type], 128);
    CheckAndSetStick(eControllerAction::VEHICLE_STEER_LEFT, state->LeftStickX, m_bStickL_X_Rgh_Lft_MovementBothDown[type], -128);
    CheckAndSetStick(eControllerAction::VEHICLE_STEER_RIGHT, state->LeftStickX, m_bStickL_X_Rgh_Lft_MovementBothDown[type], 128);
    CheckAndSetButton(eControllerAction::VEHICLE_RADIO_STATION_UP, type, button, state->DPadUp);
    CheckAndSetButton(eControllerAction::VEHICLE_RADIO_STATION_DOWN, type, button, state->DPadDown);
    CheckAndSetButton(eControllerAction::VEHICLE_RADIO_TRACK_SKIP, type, button, state->m_bRadioTrackSkip);
    CheckAndSetButton(eControllerAction::TOGGLE_SUBMISSIONS, type, button, state->ShockButtonR);
    CheckAndSetStick(eControllerAction::VEHICLE_TURRETLEFT, state->RightStickX, m_bStickR_X_Rgh_Lft_MovementBothDown[type], -128);
    CheckAndSetStick(eControllerAction::VEHICLE_TURRETRIGHT, state->RightStickX, m_bStickR_X_Rgh_Lft_MovementBothDown[type], 128);
    CheckAndSetStick(eControllerAction::VEHICLE_TURRETUP, state->RightStickY, m_bStickR_Up_Dwn_MovementBothDown[type], 128);
    CheckAndSetStick(eControllerAction::VEHICLE_TURRETDOWN, state->RightStickY, m_bStickR_Up_Dwn_MovementBothDown[type], -128);
    return type;
}

// 0x52F5F0
void CControllerConfigManager::ResetSettingOrder(eControllerAction action) {
    int32 result = 0;
    
    for (int32 priorityLevel = 1; priorityLevel < 5; priorityLevel++) {
        // Check if any key already has this priority level
        bool priorityExists = false;
        
        for (int32 controllerType = 0; controllerType < eControllerType::CONTROLLER_NUM; controllerType++) {
            if (m_Actions[action].Keys[controllerType].m_uiSetOrder == priorityLevel) {
                priorityExists = true;
                break;
            }
        }

        if (!priorityExists) {
            // No key has this priority, find the one with lowest priority > priorityLevel
            bool found = false;
            
            for (int32 controllerType = 0; controllerType < eControllerType::CONTROLLER_NUM; controllerType++) {
                const auto keyPriority = m_Actions[action].Keys[controllerType].m_uiSetOrder;
                
                // Only consider keys with priority > priorityLevel and not 0 (unset)
                if (keyPriority > priorityLevel && keyPriority != 0) {
                    // If no key found yet or this key has lower priority than current best
                    if (!found || keyPriority < m_Actions[action].Keys[result].m_uiSetOrder) {
                        result = controllerType;
                        found = true;
                    }
                }
            }
            
            // If we found a key with higher priority, adjust it to the current level
            if (found) {
                m_Actions[action].Keys[result].m_uiSetOrder = (eContSetOrder)priorityLevel;
            }
        }
    }
}

// NOTSA [Code combined from 0x7448B0 and 0x744930]
void CControllerConfigManager::HandleJoyButtonUpDown(int32 joyNo, bool isDown) {
    StoreJoyButtonStates();
    const auto forceConfigMenuMode = !isDown && notsa::contains({ MODE_FLYBY, MODE_FIXED }, TheCamera.GetActiveCamera().m_nMode); // Probably leftover debug stuff?
    for (auto i = isDown ? 1u : 2u; i < std::size(m_ButtonStates); i++) { // TODO: Why is this starting from 1/2?
        const auto padBtn = ((m_ButtonStates[i - 1] == isDown) ? i : 0); // This doesn't make sense
        if (forceConfigMenuMode || FrontEndMenuManager.m_bMenuActive || joyNo != 0) {
            if (isDown) {
                UpdateJoyInConfigMenus_ButtonDown(padBtn, joyNo);
            } else {
                UpdateJoyInConfigMenus_ButtonUp(padBtn, joyNo);
            }
        } else {
            if (isDown) {
                UpdateJoy_ButtonDown(padBtn, eControllerType::JOY_STICK);
            } else {
                UpdateJoy_ButtonUp(padBtn, eControllerType::JOY_STICK);
            }
        }
    }
}

// 0x530530
bool CControllerConfigManager::LoadSettings(FILE* file) {
    int actionId = 0;
    
    if (!file) {
        return true;
    }
    
    // Check if file has valid header
    char buffer[52] = {0};
    CFileMgr::Read(file, buffer, 29);
    if (!strncmp(buffer, "THIS FILE IS NOT VALID YET", 26)) {
        return true;
    }
    
    // Reset file position to start and read version
    CFileMgr::Seek(file, 0, 0);
    int32 version = 0;
    CFileMgr::Read(file, &version, 4);
    
    if (version < 6) {
        return true;
    }
    
    // Verify file format by checking action IDs
    for (int32 controllerType = 0; controllerType < eControllerType::CONTROLLER_NUM; controllerType++) {
        for (int32 i = 0; i < eControllerAction::NUM_OF_MAX_CONTROLLER_ACTIONS; i++) {
            CFileMgr::Read(file, &actionId, 4);
            if (actionId != i) {
                return false;
            }
            CFileMgr::Seek(file, 8, 1); // Skip key mapping data for validation pass
        }
    }
    
    // Go back to position after version info
    CFileMgr::Seek(file, 4, 0);
    
    // Clear existing settings
    MakeControllerActionsBlank();
    
    // Read key mappings for all controller types
    for (int32 controllerType = 0; controllerType < eControllerType::CONTROLLER_NUM; controllerType++) {
        for (int32 i = 0; i < eControllerAction::NUM_OF_MAX_CONTROLLER_ACTIONS; i++) {
            // Skip action ID
            CFileMgr::Seek(file, 4, 1);
            
            // Read key and order for this action
            CFileMgr::Read(file, &m_Actions[i].Keys[controllerType], 8);
        }
    }

    // NOTSA: Check if there's at least one valid assignment for each action
    for (int32 i = 0; i < eControllerAction::NUM_OF_MAX_CONTROLLER_ACTIONS; i++) {
        bool hasAssignment = false;
        for (int32 j = 0; j < eControllerType::CONTROLLER_NUM; j++) {
            if (!GetIsKeyBlank(m_Actions[i].Keys[j].m_uiActionInitiator, (eControllerType)j)) {
                hasAssignment = true;
                break;
            }
        }

        // NOTSA: If no assignment found, check if it's a special action that can be blank
        if (!hasAssignment && !notsa::contains({NETWORK_TALK, NUM_OF_1ST_PERSON_ACTIONS, TOGGLE_DPAD, SWITCH_DEBUG_CAM_ON, TAKE_SCREEN_SHOT, SHOW_MOUSE_POINTER_TOGGLE, SWITCH_CAM_DEBUG_MENU}, (eControllerAction)i)) {
            return false; // No valid assignment found for this action
        }
    }

    return true;
}

// 0x52D200
bool CControllerConfigManager::SaveSettings(FILE* file) {
    if (!file) {
        return 0;
    }
    
    for (int32 controllerType = 0; controllerType < eControllerType::CONTROLLER_NUM; controllerType++) {
        for (int32 actionId = 0; actionId < eControllerAction::NUM_OF_MAX_CONTROLLER_ACTIONS; actionId++) {
            // Write action ID
            CFileMgr::Write(file, &actionId, eControllerType::CONTROLLER_NUM);
            
            // Write key mapping data
            CFileMgr::Write(file, &m_Actions[actionId].Keys[controllerType], 8);
        }
    }

    return true;
}

// 0x530640
void CControllerConfigManager::InitDefaultControlConfiguration() {
    SetControllerKeyAssociatedWithAction(eControllerAction::GO_FORWARD, rsUP, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::GO_BACK, rsDOWN, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::GO_LEFT, rsLEFT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::GO_RIGHT, rsRIGHT, eControllerType::KEYBOARD);

    if (FrontEndMenuManager.m_nTitleLanguage == 2) {
        SetControllerKeyAssociatedWithAction(eControllerAction::CONVERSATION_YES, (RsKeyCodes)'Z', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_IN, (RsKeyCodes)'Y', eControllerType::OPTIONAL_EXTRA_KEY);
    } else {
        SetControllerKeyAssociatedWithAction(eControllerAction::CONVERSATION_YES, (RsKeyCodes)'Y', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_IN, (RsKeyCodes)'X', eControllerType::OPTIONAL_EXTRA_KEY);
    }

    if (FrontEndMenuManager.m_nTitleLanguage == 1) {
        SetControllerKeyAssociatedWithAction(eControllerAction::GO_FORWARD, (RsKeyCodes)'Z', eControllerType::OPTIONAL_EXTRA_KEY);
        SetControllerKeyAssociatedWithAction(eControllerAction::GO_LEFT, (RsKeyCodes)'Q', eControllerType::OPTIONAL_EXTRA_KEY);
        SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_LEFT, (RsKeyCodes)'A', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_OUT, (RsKeyCodes)'W', eControllerType::OPTIONAL_EXTRA_KEY);
    } else {
        SetControllerKeyAssociatedWithAction(eControllerAction::GO_FORWARD, (RsKeyCodes)'W', eControllerType::OPTIONAL_EXTRA_KEY);
        SetControllerKeyAssociatedWithAction(eControllerAction::GO_LEFT, (RsKeyCodes)'A', eControllerType::OPTIONAL_EXTRA_KEY);
        SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_LEFT, (RsKeyCodes)'Q', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_OUT, (RsKeyCodes)'Z', eControllerType::OPTIONAL_EXTRA_KEY);
    }

    SetControllerKeyAssociatedWithAction(eControllerAction::GO_BACK, (RsKeyCodes)'S', eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::GO_RIGHT, (RsKeyCodes)'D', eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_RIGHT, (RsKeyCodes)'E', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_RIGHT, rsPADENTER, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_LEFT, rsPADDEL, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_FIRE_WEAPON, rsPADINS, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_FIRE_WEAPON, rsLCTRL, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_IN, rsPGUP, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_OUT, rsPGDN, eControllerType::KEYBOARD);
    // WIN98 SetControllerKeyAssociatedWithAction(eControllerAction::PED_FIRE_WEAPON_ALT, (RsKeyCodes)'\\', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_FIRE_WEAPON_ALT, (RsKeyCodes)'0', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::GROUP_CONTROL_FWD, (RsKeyCodes)'G', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::GROUP_CONTROL_BWD, (RsKeyCodes)'H', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::CONVERSATION_NO, (RsKeyCodes)'N', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_ENTER_EXIT, (RsKeyCodes)'F', eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_ENTER_EXIT, rsENTER, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS, (RsKeyCodes)'V', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS, rsHOME, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_JUMPING, rsLSHIFT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_JUMPING, rsRCTRL, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_SPRINT, (RsKeyCodes)' ', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_DUCK, (RsKeyCodes)'C', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_ANSWER_PHONE, rsTAB, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_WALK, rsLALT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_LOCK_TARGET, rsDEL, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_LOCK_TARGET, rsCAPSLK, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_1RST_PERSON_LOOK_LEFT, rsPADLEFT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_1RST_PERSON_LOOK_RIGHT, rsPADRIGHT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_1RST_PERSON_LOOK_UP, rsPADDOWN, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_1RST_PERSON_LOOK_DOWN, rsPADUP, eControllerType::KEYBOARD);
    // WIN98 SetControllerKeyAssociatedWithAction(eControllerAction::PED_CENTER_CAMERA_BEHIND_PLAYER, (RsKeyCodes)'#', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CENTER_CAMERA_BEHIND_PLAYER, (RsKeyCodes)'3', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_LOOKBEHIND, rsPADEND, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_UP, rsUP, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_DOWN, rsDOWN, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_UP, rsINS, eControllerType::KEYBOARD);

    if (FrontEndMenuManager.m_nTitleLanguage == 1) {
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_LEFT, (RsKeyCodes)'Q', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_LOOKLEFT, (RsKeyCodes)'A', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_UP, (RsKeyCodes)'`', eControllerType::OPTIONAL_EXTRA_KEY);
        SetControllerKeyAssociatedWithAction(eControllerAction::TOGGLE_SUBMISSIONS, (RsKeyCodes)233, eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_ACCELERATE, (RsKeyCodes)'Z', eControllerType::KEYBOARD);
    } else {
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_LEFT, (RsKeyCodes)'A', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_LOOKLEFT, (RsKeyCodes)'Q', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_UP, (RsKeyCodes)'4', eControllerType::OPTIONAL_EXTRA_KEY);
        SetControllerKeyAssociatedWithAction(eControllerAction::TOGGLE_SUBMISSIONS, (RsKeyCodes)'2', eControllerType::KEYBOARD);
        SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_ACCELERATE, (RsKeyCodes)'W', eControllerType::KEYBOARD);
    }

    SetControllerKeyAssociatedWithAction(eControllerAction::TOGGLE_SUBMISSIONS, rsPLUS, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_FIRE_WEAPON, rsRCTRL, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_FIRE_WEAPON, rsLALT, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_FIRE_WEAPON_ALT, rsLCTRL, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_FIRE_WEAPON_ALT, rsPADINS, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_BRAKE, (RsKeyCodes)'S', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_RIGHT, (RsKeyCodes)'D', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_LEFT, rsLEFT, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_STEER_RIGHT, rsRIGHT, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_HORN, rsCAPSLK, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_HORN, (RsKeyCodes)'H', eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_HANDBRAKE, (RsKeyCodes)' ', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_HANDBRAKE, rsRCTRL, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_LOOKRIGHT, (RsKeyCodes)'E', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_TURRETLEFT, rsPADLEFT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_TURRETRIGHT, rsPADRIGHT, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_TURRETUP, rsPADDOWN, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_TURRETDOWN, rsPADUP, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_TURRETUP, rsEND, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_TURRETDOWN, rsDEL, eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_RADIO_TRACK_SKIP, rsF5, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_DOWN, rsDEL, eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_DOWN, (RsKeyCodes)'R', eControllerType::OPTIONAL_EXTRA_KEY);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_TARGET_LEFT, (RsKeyCodes)'[', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_TARGET_RIGHT, (RsKeyCodes)']', eControllerType::KEYBOARD);
    SetControllerKeyAssociatedWithAction(eControllerAction::PED_CYCLE_TARGET_RIGHT, (RsKeyCodes)']', eControllerType::KEYBOARD);

    ClearSimButtonPressCheckers();
}

// 0x530B00
void CControllerConfigManager::InitDefaultControlConfigJoyPad(uint32 buttonCount) {
    m_WasJoyJustInitialised = true;
    buttonCount             = std::min(buttonCount, 16u);

    if (buttonCount >= eJOY_BUTTONS::NO_JOYBUTTONS) {
        return;
    }

    // Define all possible button mappings in order from highest to lowest button number
    struct ButtonMapping {
        eJOY_BUTTONS      buttonNum;
        eControllerAction action;
    };

    // Arrays for specific and standard controller configurations
    constexpr ButtonMapping specificMappings[] = {
        { JOYBUTTON_SIXTEEN,   eControllerAction::CONVERSATION_NO                   },
        { JOYBUTTON_FIFTHTEEN, eControllerAction::GROUP_CONTROL_BWD                 },
        { JOYBUTTON_FIFTHTEEN, eControllerAction::VEHICLE_RADIO_STATION_DOWN        },
        { JOYBUTTON_FOURTEEN,  eControllerAction::CONVERSATION_YES                  },
        { JOYBUTTON_THIRTEEN,  eControllerAction::GROUP_CONTROL_FWD                 },
        { JOYBUTTON_THIRTEEN,  eControllerAction::VEHICLE_RADIO_STATION_UP          },
        { JOYBUTTON_ELEVEN,    eControllerAction::PED_LOOKBEHIND                    },
        { JOYBUTTON_ELEVEN,    eControllerAction::TOGGLE_SUBMISSIONS                },
        { JOYBUTTON_TEN,       eControllerAction::VEHICLE_HORN                      },
        { JOYBUTTON_TEN,       eControllerAction::PED_DUCK                          },
        { JOYBUTTON_NINE,      eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS },
        { JOYBUTTON_EIGHT,     eControllerAction::VEHICLE_HANDBRAKE                 },
        { JOYBUTTON_EIGHT,     eControllerAction::PED_LOCK_TARGET                   },
        { JOYBUTTON_SEVEN,     eControllerAction::PED_ANSWER_PHONE                  },
        { JOYBUTTON_SEVEN,     eControllerAction::PED_FIRE_WEAPON_ALT               },
        { JOYBUTTON_SEVEN,     eControllerAction::VEHICLE_FIRE_WEAPON_ALT           },
        { JOYBUTTON_SIX,       eControllerAction::PED_CYCLE_WEAPON_RIGHT            },
        { JOYBUTTON_SIX,       eControllerAction::VEHICLE_LOOKRIGHT                 },
        { JOYBUTTON_FIVE,      eControllerAction::PED_CYCLE_WEAPON_LEFT             },
        { JOYBUTTON_FIVE,      eControllerAction::VEHICLE_LOOKLEFT                  },
        { JOYBUTTON_FOUR,      eControllerAction::VEHICLE_BRAKE                     },
        { JOYBUTTON_FOUR,      eControllerAction::PED_JUMPING                       },
        { JOYBUTTON_FOUR,      eControllerAction::PED_SNIPER_ZOOM_IN                },
        { JOYBUTTON_THREE,     eControllerAction::VEHICLE_ACCELERATE                },
        { JOYBUTTON_THREE,     eControllerAction::PED_SPRINT                        },
        { JOYBUTTON_THREE,     eControllerAction::PED_SNIPER_ZOOM_OUT               },
        { JOYBUTTON_TWO,       eControllerAction::PED_FIRE_WEAPON                   },
        { JOYBUTTON_TWO,       eControllerAction::VEHICLE_FIRE_WEAPON               },
        { JOYBUTTON_ONE,       eControllerAction::VEHICLE_ENTER_EXIT                }
    };

    constexpr ButtonMapping standardMappings[] = {
        { JOYBUTTON_SIXTEEN,   eControllerAction::CONVERSATION_NO                   },
        { JOYBUTTON_FIFTHTEEN, eControllerAction::GROUP_CONTROL_BWD                 },
        { JOYBUTTON_FIFTHTEEN, eControllerAction::VEHICLE_RADIO_STATION_DOWN        },
        { JOYBUTTON_FOURTEEN,  eControllerAction::CONVERSATION_YES                  },
        { JOYBUTTON_THIRTEEN,  eControllerAction::GROUP_CONTROL_FWD                 },
        { JOYBUTTON_THIRTEEN,  eControllerAction::VEHICLE_RADIO_STATION_UP          },
        { JOYBUTTON_ELEVEN,    eControllerAction::PED_LOOKBEHIND                    },
        { JOYBUTTON_ELEVEN,    eControllerAction::TOGGLE_SUBMISSIONS                },
        { JOYBUTTON_TEN,       eControllerAction::VEHICLE_HORN                      },
        { JOYBUTTON_TEN,       eControllerAction::PED_DUCK                          },
        { JOYBUTTON_NINE,      eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS },
        { JOYBUTTON_EIGHT,     eControllerAction::VEHICLE_HANDBRAKE                 },
        { JOYBUTTON_EIGHT,     eControllerAction::PED_LOCK_TARGET                   },
        { JOYBUTTON_SEVEN,     eControllerAction::PED_ANSWER_PHONE                  },
        { JOYBUTTON_SEVEN,     eControllerAction::PED_FIRE_WEAPON_ALT               },
        { JOYBUTTON_SEVEN,     eControllerAction::VEHICLE_FIRE_WEAPON_ALT           },
        { JOYBUTTON_SIX,       eControllerAction::PED_CYCLE_WEAPON_RIGHT            },
        { JOYBUTTON_SIX,       eControllerAction::VEHICLE_LOOKRIGHT                },
        { JOYBUTTON_FIVE,      eControllerAction::PED_CYCLE_WEAPON_LEFT             },
        { JOYBUTTON_FIVE,      eControllerAction::VEHICLE_LOOKLEFT                 },
        { JOYBUTTON_FOUR,      eControllerAction::VEHICLE_ENTER_EXIT                },
        { JOYBUTTON_THREE,     eControllerAction::VEHICLE_BRAKE                     },
        { JOYBUTTON_THREE,     eControllerAction::PED_JUMPING                       },
        { JOYBUTTON_THREE,     eControllerAction::PED_SNIPER_ZOOM_IN                },
        { JOYBUTTON_TWO,       eControllerAction::VEHICLE_ACCELERATE                },
        { JOYBUTTON_TWO,       eControllerAction::PED_SPRINT                        },
        { JOYBUTTON_TWO,       eControllerAction::PED_SNIPER_ZOOM_OUT               },
        { JOYBUTTON_ONE,       eControllerAction::PED_FIRE_WEAPON                   },
        { JOYBUTTON_ONE,       eControllerAction::VEHICLE_FIRE_WEAPON               }
    };

    // Choose which mapping array to use
    bool                 isSpecific   = IsCheckSpecificGamepad();
    const ButtonMapping* mappings     = isSpecific ? specificMappings : standardMappings;
    const size_t         mappingCount = isSpecific ? std::size(specificMappings) : std::size(standardMappings);

    // Apply mappings for available buttons
    for (size_t i = 0; i < mappingCount; i++) {
        if (mappings[i].buttonNum <= (eJOY_BUTTONS)buttonCount) {
            SetControllerKeyAssociatedWithAction(
                mappings[i].action,
                (RsKeyCodes)mappings[i].buttonNum,
                eControllerType::JOY_STICK
            );
        }
    }
}

// 0x52F6F0
// NOTSA: Direct mouse keys assignement.
void CControllerConfigManager::InitDefaultControlConfigMouse(const CMouseControllerState& MouseSetUp, bool bMouseControls) {

#ifdef NOTSA_USE_SDL3
    constexpr bool isForceMouse = true;
#else
    constexpr bool isForceMouse = false;
#endif

    if (MouseSetUp.isMouseLeftButtonPressed || isForceMouse) {
        m_MouseFoundInitSet = bMouseControls; // NOP
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_FIRE_WEAPON,            rsMOUSE_LEFT_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::VEHICLE_FIRE_WEAPON,        rsMOUSE_LEFT_BUTTON);
    }
    if (MouseSetUp.isMouseRightButtonPressed || isForceMouse) {                                                      
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_LOCK_TARGET,            rsMOUSE_RIGHT_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::VEHICLE_MOUSELOOK,          rsMOUSE_RIGHT_BUTTON);
    }
    if (MouseSetUp.isMouseMiddleButtonPressed || isForceMouse) {                                                      
        SetMouseButtonAssociatedWithAction(eControllerAction::VEHICLE_LOOKBEHIND,         rsMOUSE_MIDDLE_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_LOOKBEHIND,             rsMOUSE_MIDDLE_BUTTON);
    }
    if (MouseSetUp.isMouseWheelMovedUp || MouseSetUp.isMouseWheelMovedDown || isForceMouse) {
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_LEFT,      rsMOUSE_WHEEL_UP_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_CYCLE_WEAPON_RIGHT,     rsMOUSE_WHEEL_DOWN_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_UP,   rsMOUSE_WHEEL_UP_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::VEHICLE_RADIO_STATION_DOWN, rsMOUSE_WHEEL_DOWN_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_IN,         rsMOUSE_WHEEL_UP_BUTTON);
        SetMouseButtonAssociatedWithAction(eControllerAction::PED_SNIPER_ZOOM_OUT,        rsMOUSE_WHEEL_DOWN_BUTTON);
    }
}

// 0x52D260
void CControllerConfigManager::InitialiseControllerActionNameArray() {
    const auto SetActionName = [&](eControllerAction action, const GxtChar* name) {
        GxtCharStrcpy(m_ControllerActionName[action], name);
    };

    SetActionName(eControllerAction::PED_LOOKBEHIND, "PED_LOOKBEHIND"_gxt);
    SetActionName(eControllerAction::PED_CYCLE_WEAPON_LEFT, "PED_CYCLE_WEAPON_LEFT"_gxt);
    SetActionName(eControllerAction::PED_CYCLE_WEAPON_RIGHT, "PED_CYCLE_WEAPON_RIGHT"_gxt);
    SetActionName(eControllerAction::PED_LOCK_TARGET, "PED_LOCK_TARGET"_gxt);
    SetActionName(eControllerAction::PED_JUMPING, "PED_JUMPING"_gxt);
    SetActionName(eControllerAction::PED_SPRINT, "PED_SPRINT"_gxt);
    SetActionName(eControllerAction::PED_WALK, "SNEAK_ABOUT"_gxt);
    SetActionName(eControllerAction::PED_CYCLE_TARGET_LEFT, "PED_CYCLE_TARGET_LEFT"_gxt);
    SetActionName(eControllerAction::PED_CYCLE_TARGET_RIGHT, "PED_CYCLE_TARGET_RIGHT"_gxt);
    SetActionName(eControllerAction::PED_CENTER_CAMERA_BEHIND_PLAYER, "PED_CENTER_CAMERA_BEHIND_PLAYER"_gxt);
    SetActionName(eControllerAction::VEHICLE_LOOKBEHIND, "VEHICLE_LOOKBEHIND"_gxt);
    SetActionName(eControllerAction::PED_DUCK, "PED_DUCK"_gxt);
    SetActionName(eControllerAction::PED_ANSWER_PHONE, "PED_ANSWER_PHONE"_gxt);
    SetActionName(eControllerAction::VEHICLE_STEER_LEFT, "VEHICLE_STEERLEFT"_gxt);
    SetActionName(eControllerAction::VEHICLE_STEER_RIGHT, "VEHICLE_STEERRIGHT"_gxt);
    SetActionName(eControllerAction::VEHICLE_STEER_UP, "VEHICLE_STEERUP"_gxt);
    SetActionName(eControllerAction::VEHICLE_STEER_DOWN, "VEHICLE_STEERDOWN"_gxt);
    SetActionName(eControllerAction::VEHICLE_LOOKLEFT, "VEHICLE_LOOKLEFT"_gxt);
    SetActionName(eControllerAction::VEHICLE_LOOKRIGHT, "VEHICLE_LOOKRIGHT"_gxt);
    SetActionName(eControllerAction::VEHICLE_MOUSELOOK, "VEHICLE_MOUSELOOK"_gxt);
    SetActionName(eControllerAction::VEHICLE_HORN, "VEHICLE_HORN"_gxt);
    SetActionName(eControllerAction::VEHICLE_HANDBRAKE, "VEHICLE_HANDBRAKE"_gxt);
    SetActionName(eControllerAction::VEHICLE_ACCELERATE, "VEHICLE_ACCELERATE"_gxt);
    SetActionName(eControllerAction::VEHICLE_BRAKE, "VEHICLE_BRAKE"_gxt);
    SetActionName(eControllerAction::VEHICLE_RADIO_STATION_UP, "VEHICLE_RADIO_STATION_UP"_gxt);
    SetActionName(eControllerAction::VEHICLE_RADIO_STATION_DOWN, "VEHICLE_RADIO_STATION_DOWN"_gxt);
    SetActionName(eControllerAction::VEHICLE_RADIO_TRACK_SKIP, "VEHICLE_RADIO_TRACK_SKIP"_gxt); // Fix: Missing on vanilla game
    SetActionName(eControllerAction::TOGGLE_SUBMISSIONS, "TOGGLE_SUBMISSIONS"_gxt);
    SetActionName(eControllerAction::PED_SNIPER_ZOOM_IN, "PED_SNIPER_ZOOM_IN"_gxt);
    SetActionName(eControllerAction::PED_SNIPER_ZOOM_OUT, "PED_SNIPER_ZOOM_OUT"_gxt);
    SetActionName(eControllerAction::PED_1RST_PERSON_LOOK_LEFT, "PED_1RST_PERSON_LOOK_LEFT"_gxt);
    SetActionName(eControllerAction::PED_1RST_PERSON_LOOK_RIGHT, "PED_1RST_PERSON_LOOK_RIGHT"_gxt);
    SetActionName(eControllerAction::PED_1RST_PERSON_LOOK_UP, "PED_1RST_PERSON_LOOK_UP"_gxt);
    SetActionName(eControllerAction::PED_1RST_PERSON_LOOK_DOWN, "PED_1RST_PERSON_LOOK_DOWN"_gxt);
    SetActionName(eControllerAction::SHOW_MOUSE_POINTER_TOGGLE, "SHOW_MOUSE_POINTER_TOGGLE"_gxt);
    SetActionName(eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS, "CAMERA_CHANGE_VIEW_ALL_SITUATIONS"_gxt);
    SetActionName(eControllerAction::PED_FIRE_WEAPON, "PED_FIREWEAPON"_gxt);
    SetActionName(eControllerAction::PED_FIRE_WEAPON_ALT, "PED_FIREWEAPON_ALT"_gxt);
    SetActionName(eControllerAction::VEHICLE_FIRE_WEAPON, "VEHICLE_FIREWEAPON"_gxt);
    SetActionName(eControllerAction::VEHICLE_FIRE_WEAPON_ALT, "VEHICLE_FIREWEAPON_ALT"_gxt);
    SetActionName(eControllerAction::VEHICLE_ENTER_EXIT, "VEHICLE_ENTER_EXIT"_gxt);
    SetActionName(eControllerAction::CONVERSATION_NO, "CONVERSATION_NO"_gxt);
    SetActionName(eControllerAction::CONVERSATION_YES, "CONVERSATION_YES"_gxt);
    SetActionName(eControllerAction::GROUP_CONTROL_FWD, "GROUP_CONTROL_FWD"_gxt);
    SetActionName(eControllerAction::GROUP_CONTROL_BWD, "GROUP_CONTROL_BWD"_gxt);
    SetActionName(eControllerAction::GO_LEFT, "GO_LEFT"_gxt);
    SetActionName(eControllerAction::GO_RIGHT, "GO_RIGHT"_gxt);
    SetActionName(eControllerAction::GO_FORWARD, "GO_FORWARD"_gxt);
    SetActionName(eControllerAction::GO_BACK, "GO_BACK"_gxt);
    SetActionName(eControllerAction::VEHICLE_TURRETLEFT, "VEHICLE_TURRETLEFT"_gxt);
    SetActionName(eControllerAction::VEHICLE_TURRETRIGHT, "VEHICLE_TURRETRIGHT"_gxt);
    SetActionName(eControllerAction::VEHICLE_TURRETUP, "VEHICLE_TURRETUP"_gxt);
    SetActionName(eControllerAction::VEHICLE_TURRETDOWN, "VEHICLE_TURRETDOWN"_gxt);
    SetActionName(eControllerAction::NETWORK_TALK, "NETWORK_TALK"_gxt);
    SetActionName(eControllerAction::TOGGLE_DPAD, "TOGGLE_DPAD"_gxt);
    SetActionName(eControllerAction::SWITCH_DEBUG_CAM_ON, "SWITCH_DEBUG_CAM_ON"_gxt);
    SetActionName(eControllerAction::TAKE_SCREEN_SHOT, "TAKE_SCREEN_SHOT"_gxt);
}

// 0x531F20
void CControllerConfigManager::ReinitControls() {
    ControlsManager.MakeControllerActionsBlank();
    ControlsManager.InitDefaultControlConfiguration();
#ifdef NOTSA_USE_SDL3
    const auto MouseSetUp = CMouseControllerState{};
#else
    const auto MouseSetUp = WinInput::GetMouseSetUp();
#endif
    ControlsManager.InitDefaultControlConfigMouse(MouseSetUp, !FrontEndMenuManager.m_ControlMethod);
    if (PadConfigs[PAD1].present) {
        ControlsManager.InitDefaultControlConfigJoyPad(44u);
    }
}

// 0x52F590
void CControllerConfigManager::SetMouseButtonAssociatedWithAction(eControllerAction Action, KeyCode MouseAction) {
	auto numOfSettings = GetNumOfSettingsForAction(Action);
    m_Actions[Action].Keys[eControllerType::MOUSE].m_uiActionInitiator = MouseAction;
    m_Actions[Action].Keys[eControllerType::MOUSE].m_uiSetOrder = eContSetOrder(numOfSettings + 1);
}

// unused
// 0x52DA30
void CControllerConfigManager::StoreMouseButtonState(eMouseButtons button, bool state) {
    switch (button) {
    case MOUSE_BUTTON_LEFT:           CPad::TempMouseControllerState.isMouseLeftButtonPressed = state; break;
    case MOUSE_BUTTON_MIDDLE:         CPad::TempMouseControllerState.isMouseMiddleButtonPressed = state; break;
    case MOUSE_BUTTON_RIGHT:          CPad::TempMouseControllerState.isMouseRightButtonPressed = state; break;
    case MOUSE_BUTTON_WHEEL_UP:       CPad::TempMouseControllerState.isMouseWheelMovedUp = state; break;
    case MOUSE_BUTTON_WHEEL_DOWN:     CPad::TempMouseControllerState.isMouseWheelMovedDown = state; break;
    case MOUSE_BUTTON_WHEEL_XBUTTON1: CPad::TempMouseControllerState.isMouseFirstXPressed = state; break;
    case MOUSE_BUTTON_WHEEL_XBUTTON2: CPad::TempMouseControllerState.isMouseSecondXPressed = state; break;
    default:                          NOTSA_UNREACHABLE();
    }
}

// 0x52DAB0
void CControllerConfigManager::UpdateJoyInConfigMenus_ButtonDown(KeyCode ButtonPress, int32 padNumber) {
    CPad* pad = CPad::GetPad(padNumber);
    if (!pad || ButtonPress == 0) {
        return;
    }

    switch (ButtonPress) {
    case eJOY_BUTTONS::JOYBUTTON_FIVE:
        pad->PCTempJoyState.LeftShoulder2 = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_SIX:
        pad->PCTempJoyState.RightShoulder2 = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_SEVEN:
        pad->PCTempJoyState.LeftShoulder1 = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_EIGHT:
        pad->PCTempJoyState.RightShoulder1 = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_NINE:
        pad->PCTempJoyState.Select = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_TEN:
        pad->PCTempJoyState.ShockButtonL = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_ELEVEN:
        pad->PCTempJoyState.ShockButtonR = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_TWELVE:
        if (padNumber == 1 || notsa::IsFixBugs()) {
            pad->PCTempJoyState.Start = 255;
        }
        break;
    case eJOY_BUTTONS::JOYBUTTON_THIRTEEN:
        pad->PCTempJoyState.DPadUp = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_FOURTEEN:
        pad->PCTempJoyState.DPadRight = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_FIFTHTEEN:
        pad->PCTempJoyState.DPadDown = 255;
        break;
    case eJOY_BUTTONS::JOYBUTTON_SIXTEEN:
        pad->PCTempJoyState.DPadLeft = 255;
        break;
    default:
        break;
    }

    if (IsCheckSpecificGamepad()) {
        switch (ButtonPress) {
        case eJOY_BUTTONS::JOYBUTTON_ONE:
            pad->PCTempJoyState.ButtonTriangle = 255;
            break;
        case eJOY_BUTTONS::JOYBUTTON_TWO:
            pad->PCTempJoyState.ButtonCircle = 255;
            break;
        case eJOY_BUTTONS::JOYBUTTON_THREE:
            pad->PCTempJoyState.ButtonCross = 255;
            break;
        case eJOY_BUTTONS::JOYBUTTON_FOUR:
            pad->PCTempJoyState.ButtonSquare = 255;
            break;
        }
    } else {
        switch (ButtonPress) {
        case eJOY_BUTTONS::JOYBUTTON_ONE:
            pad->PCTempJoyState.ButtonCircle = 255;
            break;
        case eJOY_BUTTONS::JOYBUTTON_TWO:
            pad->PCTempJoyState.ButtonCross = 255;
            break;
        case eJOY_BUTTONS::JOYBUTTON_THREE:
            pad->PCTempJoyState.ButtonSquare = 255;
            break;
        case eJOY_BUTTONS::JOYBUTTON_FOUR:
            pad->PCTempJoyState.ButtonTriangle = 255;
            break;
        }
    }
}

// 0x530ED0
void CControllerConfigManager::UpdateJoy_ButtonDown(KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }
    CPad* pad = CPad::GetPad(0);
    if (!pad) {
        return;
    }
    auto* const state = &GetControllerState(*pad, type);
    if (UseDrivingControls()) {
        AffectControllerStateOn_ButtonDown_Driving(button, type, state);
    } else {
        AffectControllerStateOn_ButtonDown_FirstAndThirdPersonOnly(button, type, state);
        if (UseFirstPersonControls()) {
            AffectControllerStateOn_ButtonDown_FirstPersonOnly(button, type, state);
        }
        AffectControllerStateOn_ButtonDown_AllStates(button, type, state);
    }
    AffectControllerStateOn_ButtonDown_VehicleAndThirdPersonOnly(button, type, state);
}

// unused
// 0x52DC10
void CControllerConfigManager::AffectControllerStateOn_ButtonDown_DebugStuff(int32, eControllerType) {
    // NOP
    return;
}

// 0x52DC20
void CControllerConfigManager::UpdateJoyInConfigMenus_ButtonUp(KeyCode ButtonPress, int32 padNumber) {
    CPad* pad = CPad::GetPad(padNumber);
    if (!pad || ButtonPress == 0) {
        return;
    }

    switch (ButtonPress) {
    case eJOY_BUTTONS::JOYBUTTON_FIVE:
        pad->PCTempJoyState.LeftShoulder2 = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_SIX:
        pad->PCTempJoyState.RightShoulder2 = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_SEVEN:
        pad->PCTempJoyState.LeftShoulder1 = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_EIGHT:
        pad->PCTempJoyState.RightShoulder1 = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_NINE:
        pad->PCTempJoyState.Select = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_TEN:
        pad->PCTempJoyState.ShockButtonL = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_ELEVEN:
        pad->PCTempJoyState.ShockButtonR = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_TWELVE:
        if (padNumber == 1 || notsa::IsFixBugs()) {
            pad->PCTempJoyState.Start = 0;
        }
        break;
    case eJOY_BUTTONS::JOYBUTTON_THIRTEEN:
        pad->PCTempJoyState.DPadUp = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_FOURTEEN:
        pad->PCTempJoyState.DPadRight = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_FIFTHTEEN:
        pad->PCTempJoyState.DPadDown = 0;
        break;
    case eJOY_BUTTONS::JOYBUTTON_SIXTEEN:
        pad->PCTempJoyState.DPadLeft = 0;
        break;
    default:
        break;
    }

    if (IsCheckSpecificGamepad()) {
        switch (ButtonPress) {
        case eJOY_BUTTONS::JOYBUTTON_ONE:
            pad->PCTempJoyState.ButtonTriangle = 0;
            break;
        case eJOY_BUTTONS::JOYBUTTON_TWO:
            pad->PCTempJoyState.ButtonCircle = 0;
            break;
        case eJOY_BUTTONS::JOYBUTTON_THREE:
            pad->PCTempJoyState.ButtonCross = 0;
            break;
        case eJOY_BUTTONS::JOYBUTTON_FOUR:
            pad->PCTempJoyState.ButtonSquare = 0;
            break;
        }
    } else {
        switch (ButtonPress) {
        case eJOY_BUTTONS::JOYBUTTON_ONE:
            pad->PCTempJoyState.ButtonCircle = 0;
            break;
        case eJOY_BUTTONS::JOYBUTTON_TWO:
            pad->PCTempJoyState.ButtonCross = 0;
            break;
        case eJOY_BUTTONS::JOYBUTTON_THREE:
            pad->PCTempJoyState.ButtonSquare = 0;
            break;
        case eJOY_BUTTONS::JOYBUTTON_FOUR:
            pad->PCTempJoyState.ButtonTriangle = 0;
            break;
        }
    }
}

// 0x531070
void CControllerConfigManager::UpdateJoy_ButtonUp(KeyCode button, eControllerType type) {
    bool             shouldProcessEvent = false;
    CControllerState p_PCTempKeyState;
    const auto       pad = CPad::GetPad();
    if (pad) {
        switch (type) {
        case eControllerType::KEYBOARD:
        case eControllerType::OPTIONAL_EXTRA_KEY: {
            p_PCTempKeyState   = pad->PCTempKeyState;
            shouldProcessEvent = (button != rsNULL);
            break;
        }
        case eControllerType::MOUSE: {
            p_PCTempKeyState   = pad->PCTempMouseState;
            shouldProcessEvent = (button != 0);
            break;
        }
        case eControllerType::JOY_STICK: {
            p_PCTempKeyState   = pad->PCTempJoyState;
            shouldProcessEvent = (button != 0);
            break;
        }
        default: {
            p_PCTempKeyState = (CControllerState)type;
            break;
        }
        }
    }

    if (shouldProcessEvent && pad && !FrontEndMenuManager.m_bMenuActive) {
        HandleButtonRelease(button, type, &p_PCTempKeyState);
    }
}

// unused
// 0x52DD80
void CControllerConfigManager::AffectControllerStateOn_ButtonUp_DebugStuff(int32, eControllerType) {
    // NOP
    return;
}

// 0x52DD90
void CControllerConfigManager::ClearSimButtonPressCheckers() {
    for (auto i = 0u; i < eControllerType::CONTROLLER_NUM; ++i) {
        m_bStickL_Up_Dwn_MovementBothDown[i]    = false;
        m_bStickL_X_Rgh_Lft_MovementBothDown[i] = false;
        m_bStickR_Up_Dwn_MovementBothDown[i]    = false;
        m_bStickR_X_Rgh_Lft_MovementBothDown[i] = false;
    }
}

// unused
// 0x52D1C0
int32 CControllerConfigManager::GetJoyButtonJustUp() {
    // Check each button from 0 to JOYBUTTON_SIXTEEN-1
    for (int32 buttonIndex = eJOY_BUTTONS::NO_JOYBUTTONS; buttonIndex < eJOY_BUTTONS::JOYBUTTON_SIXTEEN; buttonIndex++) {
        // Check if button is released in current state but was pressed in previous state
        const bool isCurrentlyPressed = (m_NewJoyState.rgbButtons[buttonIndex] & 0x80) != 0;
        const bool wasPreviouslyPressed = (m_OldJoyState.rgbButtons[buttonIndex] & 0x80) != 0;
        
        if (!isCurrentlyPressed && wasPreviouslyPressed) {
            // Return the button ID (1-based index)
            return buttonIndex + eJOY_BUTTONS::JOYBUTTON_ONE;
        }
    }
    // No button was found that was just released
    return eJOY_BUTTONS::NO_JOYBUTTONS;
}

// 0x52D1E0
int32 CControllerConfigManager::GetJoyButtonJustDown() {
    // Check each button from 0 to JOYBUTTON_SIXTEEN-1
    for (int32 buttonIndex = eJOY_BUTTONS::NO_JOYBUTTONS; buttonIndex < eJOY_BUTTONS::JOYBUTTON_SIXTEEN; buttonIndex++) {
        // Check if button is pressed in current state but wasn't pressed in previous state
        const bool isCurrentlyPressed = (m_NewJoyState.rgbButtons[buttonIndex] & 0x80) != 0;
        const bool wasPreviouslyPressed = (m_OldJoyState.rgbButtons[buttonIndex] & 0x80) != 0;
        
        if (isCurrentlyPressed && !wasPreviouslyPressed) {
            // Return the button ID (1-based index)
            return buttonIndex + eJOY_BUTTONS::JOYBUTTON_ONE;
        }
    }
    // No button was found that was just pressed
    return eJOY_BUTTONS::NO_JOYBUTTONS;
}

bool IsKeyboardKeyDownInState(CKeyboardState& state, KeyCode key) {
    if (key >= 0 && key < 0xFF) {
        return state.standardKeys[key] != 0;
    }

    if (key >= rsF1 && key <= rsF12) {
        return state.FKeys[key - rsF1];
    }

    switch (key) {
    case rsESC: return state.esc;
    case rsINS: return state.insert;
    case rsDEL: return state.del;
    case rsHOME: return state.home;
    case rsEND: return state.end;
    case rsPGUP: return state.pgup;
    case rsPGDN: return state.pgdn;
    case rsUP: return state.up;
    case rsDOWN: return state.down;
    case rsLEFT: return state.left;
    case rsRIGHT: return state.right;
    case rsDIVIDE: return state.div;
    case rsTIMES: return state.mul;
    case rsPLUS: return state.add;
    case rsMINUS: return state.sub;
    case rsPADDEL: return state.decimal;
    case rsPADEND: return state.num1;
    case rsPADDOWN: return state.num2;
    case rsPADPGDN: return state.num3;
    case rsPADLEFT: return state.num4;
    case rsPAD5: return state.num5;
    case rsNUMLOCK: return state.numlock;
    case rsPADRIGHT: return state.num6;
    case rsPADHOME: return state.num7;
    case rsPADUP: return state.num8;
    case rsPADPGUP: return state.num9;
    case rsPADINS: return state.num0;
    case rsPADENTER: return state.enter;
    case rsSCROLL: return state.scroll;
    case rsPAUSE: return state.pause;
    case rsBACKSP: return state.back;
    case rsTAB: return state.tab;
    case rsCAPSLK: return state.capslock;
    case rsENTER: return state.extenter;
    case rsLSHIFT: return state.lshift;
    case rsRSHIFT: return state.rshift;
    case rsSHIFT: return state.shift;
    case rsLCTRL: return state.lctrl;
    case rsRCTRL: return state.rctrl;
    case rsLALT: return state.lalt;
    case rsRALT: return state.ralt;
    case rsLWIN: return state.lwin;
    case rsRWIN: return state.rwin;
    case rsAPPS: return state.apps;
    }

    return false;
}

// 0x52DDB0
bool CControllerConfigManager::GetIsKeyboardKeyDown(KeyCode key) {
    return IsKeyboardKeyDownInState(CPad::NewKeyState, key);
}

// 0x52E450
bool CControllerConfigManager::GetIsKeyboardKeyJustDown(KeyCode key) {
    return IsKeyboardKeyDownInState(CPad::NewKeyState, key) && !IsKeyboardKeyDownInState(CPad::OldKeyState, key);
}

// 0x52EF30
bool CControllerConfigManager::GetIsMouseButtonDown(KeyCode key) {
    return CheckMouseButtonState(key);
}
 
// 0x52F020
bool CControllerConfigManager::GetIsMouseButtonUp(KeyCode key) {
    return !CheckMouseButtonState(key);
}

// 0x52F110
bool CControllerConfigManager::GetIsMouseButtonJustUp(KeyCode key) {
    return CheckMouseButtonJustUpState(key);
}
    
// unused
// 0x52F2A0
bool CControllerConfigManager::GetIsKeyBlank(KeyCode key, eControllerType type) {
    switch (type) {
    case eControllerType::KEYBOARD:
    case eControllerType::OPTIONAL_EXTRA_KEY:
        return key == rsNULL;
    case eControllerType::MOUSE:
    case eControllerType::JOY_STICK:
        return key == 0;
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x52F2F0
eActionType CControllerConfigManager::GetActionType(eControllerAction action) {
    switch (action) {
    case eControllerAction::PED_FIRE_WEAPON:
    case eControllerAction::PED_FIRE_WEAPON_ALT:
    case eControllerAction::GO_FORWARD:
    case eControllerAction::GO_BACK:
    case eControllerAction::GO_LEFT:
    case eControllerAction::GO_RIGHT:
    case eControllerAction::PED_SNIPER_ZOOM_IN:
    case eControllerAction::PED_SNIPER_ZOOM_OUT:
    case eControllerAction::PED_1RST_PERSON_LOOK_LEFT:
    case eControllerAction::PED_1RST_PERSON_LOOK_RIGHT:
    case eControllerAction::PED_LOCK_TARGET:
    case eControllerAction::PED_1RST_PERSON_LOOK_UP:
    case eControllerAction::PED_1RST_PERSON_LOOK_DOWN:
        return ACTION_FIRST_THIRD_PERSON;
    case eControllerAction::PED_CYCLE_WEAPON_RIGHT:
    case eControllerAction::PED_CYCLE_WEAPON_LEFT:
    case eControllerAction::PED_JUMPING:
    case eControllerAction::PED_SPRINT:
    case eControllerAction::PED_LOOKBEHIND:
    case eControllerAction::PED_DUCK:
    case eControllerAction::PED_ANSWER_PHONE:
    case eControllerAction::PED_WALK:
    case eControllerAction::PED_CYCLE_TARGET_LEFT:
    case eControllerAction::PED_CYCLE_TARGET_RIGHT:
    case eControllerAction::PED_CENTER_CAMERA_BEHIND_PLAYER:
    case eControllerAction::CONVERSATION_YES:
    case eControllerAction::CONVERSATION_NO:
    case eControllerAction::GROUP_CONTROL_FWD:
    case eControllerAction::GROUP_CONTROL_BWD:
        return ACTION_THIRD_PERSON;
    case eControllerAction::VEHICLE_ENTER_EXIT:
        return ACTION_IN_CAR_THIRD_PERSON;
    case eControllerAction::CAMERA_CHANGE_VIEW_ALL_SITUATIONS:
    case eControllerAction::NETWORK_TALK:
    case eControllerAction::TOGGLE_DPAD:
    case eControllerAction::SWITCH_DEBUG_CAM_ON:
    case eControllerAction::TAKE_SCREEN_SHOT:
    case eControllerAction::SHOW_MOUSE_POINTER_TOGGLE:
        return ACTION_COMMON_CONTROLS;
    case eControllerAction::VEHICLE_FIRE_WEAPON:
    case eControllerAction::VEHICLE_FIRE_WEAPON_ALT:
    case eControllerAction::VEHICLE_STEER_LEFT:
    case eControllerAction::VEHICLE_STEER_RIGHT:
    case eControllerAction::VEHICLE_STEER_UP:
    case eControllerAction::VEHICLE_STEER_DOWN:
    case eControllerAction::VEHICLE_ACCELERATE:
    case eControllerAction::VEHICLE_BRAKE:
    case eControllerAction::VEHICLE_RADIO_STATION_UP:
    case eControllerAction::VEHICLE_RADIO_STATION_DOWN:
    case eControllerAction::VEHICLE_RADIO_TRACK_SKIP:
    case eControllerAction::VEHICLE_HORN:
    case eControllerAction::TOGGLE_SUBMISSIONS:
    case eControllerAction::VEHICLE_HANDBRAKE:
    case eControllerAction::VEHICLE_LOOKLEFT:
    case eControllerAction::VEHICLE_LOOKRIGHT:
    case eControllerAction::VEHICLE_LOOKBEHIND:
    case eControllerAction::VEHICLE_MOUSELOOK:
    case eControllerAction::VEHICLE_TURRETLEFT:
    case eControllerAction::VEHICLE_TURRETRIGHT:
    case eControllerAction::VEHICLE_TURRETUP:
    case eControllerAction::VEHICLE_TURRETDOWN:
        return ACTION_IN_CAR;
    default:
        return ACTION_NOT_TYPE;
    }
}

// 0x52F390
const GxtChar* CControllerConfigManager::GetControllerSettingTextMouse(eControllerAction action) {
    switch (m_Actions[action].Keys[eControllerType::MOUSE].m_uiActionInitiator) {
    case rsMOUSE_LEFT_BUTTON:       return TheText.Get("FEC_MSL");
    case rsMOUSE_MIDDLE_BUTTON:     return TheText.Get("FEC_MSM");
    case rsMOUSE_RIGHT_BUTTON:      return TheText.Get("FEC_MSR");
    case rsMOUSE_WHEEL_UP_BUTTON:   return TheText.Get("FEC_MWF");
    case rsMOUSE_WHEEL_DOWN_BUTTON: return TheText.Get("FEC_MWB");
    case rsMOUSE_X1_BUTTON:         return TheText.Get("FEC_MXO");
    case rsMOUSE_X2_BUTTON:         return TheText.Get("FEC_MXT");
    default:                        return 0;
    }
}

// 0x52F450
const GxtChar* CControllerConfigManager::GetControllerSettingTextJoystick(eControllerAction action) {
    static thread_local GxtChar s_buttonName[64]; // 0xB7147C

    const auto keyCode = (RsKeyCodes)m_Actions[action].Keys[eControllerType::JOY_STICK].m_uiActionInitiator;
    if (!keyCode) {
        return 0;
    }

    const GxtChar* joystickButtonText = TheText.Get("FEC_JBO");

    GxtChar number[8];
    AsciiToGxtChar(std::to_string(keyCode).c_str(), number);

    TextCopy(s_buttonName, joystickButtonText);
    GxtCharStrcat(s_buttonName, " "_gxt);
    GxtCharStrcat(s_buttonName, number);
    return s_buttonName;
}

// 0x530500
void CControllerConfigManager::MakeControllerActionsBlank() {
    for (auto i = 0u; i < eControllerType::CONTROLLER_NUM; ++i) {
        for (auto j = 0u; j < NUM_OF_MAX_CONTROLLER_ACTIONS; ++j) {
            ClearSettingsAssociatedWithAction((eControllerAction)(j), (eControllerType)(i));
        }
    }
}

// 0x531140
void CControllerConfigManager::AffectPadFromKeyBoard() {
    constexpr eControllerType CONTROLLER_TYPES[] = {eControllerType::KEYBOARD, eControllerType::OPTIONAL_EXTRA_KEY};

    //RsKeyCodes keyCode;

    // GTATranslateShiftKey(&keyCode); // No matter what you do, it won't work.
    
    bool inMenu = false;
    if (!CPad::padNumber) {
        inMenu = !FrontEndMenuManager.m_bMenuActive;
    }
    
    for (auto i = 0u; i < NUM_OF_MAX_CONTROLLER_ACTIONS; ++i) {
        // Handle key press logic
        for (const auto& type : CONTROLLER_TYPES) {
            const auto key = m_Actions[i].Keys[type].m_uiActionInitiator;
            
            if (GetIsKeyboardKeyDown(key) && inMenu && key != rsNULL) {
                bool useFirstPersonControls = false;
                CPad* pad = CPad::GetPad(0);
                
                bool useDrivingControls = CControllerConfigManager::UseDrivingControls();
                if (CControllerConfigManager::UseFirstPersonControls()) {
                    useFirstPersonControls = true;
                }
                
                if (pad) {
                    CControllerState* state = &pad->PCTempKeyState;
                    
                    if (useDrivingControls) {
                        AffectControllerStateOn_ButtonDown_Driving(key, type, state);
                    } else {
                        AffectControllerStateOn_ButtonDown_FirstAndThirdPersonOnly(key, type, state);
                        
                        if (useFirstPersonControls) {
                            AffectControllerStateOn_ButtonDown_FirstPersonOnly(key, type, state);
                        } else {
                            AffectControllerStateOn_ButtonDown_ThirdPersonOnly(key, type, state);
                        }
                    }
                    
                    if (m_Actions[eControllerAction::VEHICLE_ENTER_EXIT].Keys[type].m_uiActionInitiator == key) {
                        state->ButtonTriangle = 255;
                    }
                    
                    AffectControllerStateOn_ButtonDown_AllStates(key, type, state);
                }
            }
        }
        
        // Handle key release logic
        CPad* pad = CPad::GetPad(0);
        if (!pad || FrontEndMenuManager.m_bMenuActive) {
            continue;
        }
        
        CControllerState* keyState = &pad->PCTempKeyState;
        
        for (const auto& type : CONTROLLER_TYPES) {
            const auto key = m_Actions[i].Keys[type].m_uiActionInitiator;
            if (!GetIsKeyboardKeyDown(key) && key != rsNULL) {
                if (m_Actions[eControllerAction::NETWORK_TALK].Keys[type].m_uiActionInitiator == key) {
                    keyState->m_bChatIndicated = 0;
                }
                if (m_Actions[eControllerAction::VEHICLE_MOUSELOOK].Keys[type].m_uiActionInitiator == key) {
                    keyState->m_bVehicleMouseLook = 0;
                }
            }
        }
    }
}

// 0x5314A0
void CControllerConfigManager::AffectPadFromMouse() {
    CPad* pad = CPad::GetPad();
    bool controlsEnabled = !CPad::padNumber && !FrontEndMenuManager.m_bMenuActive;
    CControllerState* state = &pad->PCTempMouseState;

    for (auto& action : m_Actions) {
        const auto button = action.Keys[eControllerType::MOUSE].m_uiActionInitiator;

        if (CControllerConfigManager::GetIsMouseButtonDown(button)) {
            if (controlsEnabled && button && pad) {
                if (UseDrivingControls()) {
                    AffectControllerStateOn_ButtonDown_Driving(button, eControllerType::MOUSE, state);
                } else {
                    AffectControllerStateOn_ButtonDown_FirstAndThirdPersonOnly(button, eControllerType::MOUSE, state);
                    if (UseFirstPersonControls()) {
                        AffectControllerStateOn_ButtonDown_FirstPersonOnly(button, eControllerType::MOUSE, state);
                    } else {
                        AffectControllerStateOn_ButtonDown_ThirdPersonOnly(button, eControllerType::MOUSE, state);
                    }
                    AffectControllerStateOn_ButtonDown_AllStates(button, eControllerType::MOUSE, state);

                    AffectControllerStateOn_ButtonDown_VehicleAndThirdPersonOnly(button, eControllerType::MOUSE, state);
                }
            }
        }

        if (GetIsMouseButtonUp(button) && button && pad) {
            if (!FrontEndMenuManager.m_bMenuActive) {
                if (m_Actions[eControllerAction::NETWORK_TALK].Keys[eControllerType::MOUSE].m_uiActionInitiator == button) {
                    state->m_bChatIndicated = 0;
                }
                if (m_Actions[eControllerAction::VEHICLE_MOUSELOOK].Keys[eControllerType::MOUSE].m_uiActionInitiator == button) {
                    state->m_bVehicleMouseLook = 0;
                }
            }
        }
    }
}

// 0x531C90
void CControllerConfigManager::DeleteMatchingActionInitiators(eControllerAction action, KeyCode button, eControllerType type) {
    if (GetIsKeyBlank(button, type)) {
        return;
    }
    switch (GetActionType(action)) {
    case ACTION_FIRST_PERSON:
        ClearCommonMappings(action, button, type);
        ClearSniperZoomMappings(action, button, type);
        Clear1st3rdPersonMappings(action, button, type);
        break;
    case ACTION_THIRD_PERSON:
        ClearCommonMappings(action, button, type);
        Clear1st3rdPersonMappings(action, button, type);
        ClearPedMappings(action, button, type);
        UnmapVehicleEnterExit(button, type);
        break;
    case ACTION_IN_CAR:
        ClearCommonMappings(action, button, type);
        ClearVehicleMappings(action, button, type);
        UnmapVehicleEnterExit(button, type);
        break;
    case ACTION_IN_CAR_THIRD_PERSON:
        ClearCommonMappings(action, button, type);
        Clear1st3rdPersonMappings(action, button, type);
        ClearPedMappings(action, button, type);
        ClearVehicleMappings(action, button, type);
        break;
    case ACTION_COMMON_CONTROLS:
        ClearCommonMappings(action, button, type);
        ClearSniperZoomMappings(action, button, type);
        Clear1st3rdPersonMappings(action, button, type);
        ClearPedMappings(action, button, type);
        ClearVehicleMappings(action, button, type);
        UnmapVehicleEnterExit(button, type);
        break;
    case ACTION_FIRST_THIRD_PERSON:
        ClearCommonMappings(action, button, type);
        ClearSniperZoomMappings(action, button, type);
        Clear1st3rdPersonMappings(action, button, type);
        ClearPedMappings(action, button, type);
        UnmapVehicleEnterExit(button, type);
        break;
    default:
        return;
    }
}

// 0x52FE10
const GxtChar* CControllerConfigManager::GetKeyNameForKeyboard(eControllerAction action, eControllerType type) {
    static thread_local GxtChar s_KeyName[50]; // 0xB714BC

    const auto key = m_Actions[action].Keys[type].m_uiActionInitiator;

    const auto KeyNameWithNumber = [&](const GxtChar* text, int32 key) {
        CMessages::InsertNumberInString(text, key, -1, -1, -1, -1, -1, s_KeyName);
        return s_KeyName;
    };

    if (key == rsNULL) {
        return 0;
    }

    if (key > 0xFF) { /* Non-ASCII keys */
        switch (key) {
        case rsF1:
        case rsF2:
        case rsF3:
        case rsF4:
        case rsF5:
        case rsF6:
        case rsF7:
        case rsF8:
        case rsF9:
        case rsF10:
        case rsF11:
        case rsF12:      return KeyNameWithNumber(TheText.Get("FEC_FNC"), key - rsF1 + 1);
        case rsINS:      return TheText.Get("FEC_IRT");
        case rsDEL:      return TheText.Get("FEC_DLL");
        case rsHOME:     return TheText.Get("FEC_HME");
        case rsEND:      return TheText.Get("FEC_END");
        case rsPGUP:     return TheText.Get("FEC_PGU");
        case rsPGDN:     return TheText.Get("FEC_PGD");
        case rsUP:       return TheText.Get("FEC_UPA");
        case rsDOWN:     return TheText.Get("FEC_DWA");
        case rsLEFT:     return TheText.Get("FEC_LFA");
        case rsRIGHT:    return TheText.Get("FEC_RFA");
        case rsDIVIDE:   return TheText.Get("FEC_FWS");
        case rsTIMES:    return TheText.Get("FECSTAR");
        case rsPLUS:     return TheText.Get("FEC_PLS");
        case rsMINUS:    return TheText.Get("FEC_MIN");
        case rsPADDEL:   return TheText.Get("FEC_DOT");
        case rsPADEND:   return KeyNameWithNumber(TheText.Get("FEC_NMN"), 1);
        case rsPADDOWN:  return KeyNameWithNumber(TheText.Get("FEC_NMN"), 2);
        case rsPADPGDN:  return KeyNameWithNumber(TheText.Get("FEC_NMN"), 3);
        case rsPADLEFT:  return KeyNameWithNumber(TheText.Get("FEC_NMN"), 4);
        case rsPAD5:     return KeyNameWithNumber(TheText.Get("FEC_NMN"), 5);
        case rsPADRIGHT: return KeyNameWithNumber(TheText.Get("FEC_NMN"), 6);
        case rsPADHOME:  return KeyNameWithNumber(TheText.Get("FEC_NMN"), 7);
        case rsPADUP:    return KeyNameWithNumber(TheText.Get("FEC_NMN"), 8);
        case rsPADPGUP:  return KeyNameWithNumber(TheText.Get("FEC_NMN"), 9);
        case rsPADINS:   return KeyNameWithNumber(TheText.Get("FEC_NMN"), 0);
        case rsNUMLOCK:  return TheText.Get("FEC_NLK");
        case rsPADENTER: return TheText.Get("FEC_ETR");
        case rsSCROLL:   return TheText.Get("FEC_SLK");
        case rsPAUSE:    return TheText.Get("FEC_PSB");
        case rsBACKSP:   return TheText.Get("FEC_BSP");
        case rsTAB:      return TheText.Get("FEC_TAB");
        case rsCAPSLK:   return TheText.Get("FEC_CLK");
        case rsENTER:    return TheText.Get("FEC_RTN");
        case rsLSHIFT:   return TheText.Get("FEC_LSF");
        case rsRSHIFT:   return TheText.Get("FEC_RSF");
        case rsSHIFT:    return TheText.Get("FEC_SFT");
        case rsLCTRL:    return TheText.Get("FEC_LCT");
        case rsRCTRL:    return TheText.Get("FEC_RCT");
        case rsLALT:     return TheText.Get("FEC_LAL");
        case rsRALT:     return TheText.Get("FEC_RAL");
        case rsLWIN:     return TheText.Get("FEC_LWD");
        case rsRWIN:     return TheText.Get("FEC_RWD");
        case rsAPPS:     return TheText.Get("FEC_WRC");
        default: return nullptr;
        }
    } else { /* ASCII keys */
        switch (static_cast<char>(key)) {
        case '*': return TheText.Get("FEC_AST");
        case ' ': return TheText.Get("FEC_SPC");
        case '^':
            if (FrontEndMenuManager.m_nTextLanguage == GERMAN) {
                return "|"_gxt;
            }
            break;
        case 178:
            if (FrontEndMenuManager.m_nTextLanguage == FRENCH) {
                return "2"_gxt;
            }
            break;
        default:
            s_KeyName[0] = (GxtChar)(key ? key : '#');
            s_KeyName[1] = '\0';
            return s_KeyName;
        }
    }
    return nullptr;
}

// 0x52F560
const GxtChar* CControllerConfigManager::GetButtonComboText(eControllerAction event) {
    return event == eControllerAction::VEHICLE_LOOKBEHIND
        ? TheText.Get("FEC_LBC")
        : nullptr;
}

// 0x5303D0
const GxtChar* CControllerConfigManager::GetDefinedKeyByGxtName(eControllerAction action) {
    static thread_local GxtChar s_ButtonName[64]; // 0xB7147C
    if (FrontEndMenuManager.m_ControlMethod) {
        if (const auto keyCode = m_Actions[action].Keys[eControllerType::JOY_STICK].m_uiActionInitiator) {
            const auto joyButtonText = TheText.Get("FEC_JBO");
            CMessages::InsertNumberInString(joyButtonText, keyCode, -1, -1, -1, -1, -1, s_ButtonName);
            return s_ButtonName;
        }
    }

    if (const auto keyText = GetControllerSettingTextMouse(action)) {
        return keyText;
    }

    if (const auto keyText = GetKeyNameForKeyboard(action, eControllerType::KEYBOARD)) {
        return keyText;
    }

    if (const auto keyText = GetKeyNameForKeyboard(action, eControllerType::OPTIONAL_EXTRA_KEY)) {
        return keyText;
    }

    if (m_Actions[action].Keys[eControllerType::JOY_STICK].m_uiActionInitiator == (RsKeyCodes)(0)) {
        return GetControllerSettingTextMouse(action);
    }

    return 0;
}

// Missing addresses (inlined)
const int32 CControllerConfigManager::GetNumOfSettingsForAction(eControllerAction Action) {
    int32 num = 0;
    for (auto i = 0u; i < eControllerType::CONTROLLER_NUM; ++i) {
        const auto type = (eControllerType)i;
        const auto key = m_Actions[Action].Keys[type].m_uiActionInitiator;
        if (!GetIsKeyBlank(key, type)) {
            num++;
        }
    }
    return num;
}

// NOTSA
eControllerAction CControllerConfigManager::GetActionIDByName(std::string_view name) {
    for (auto&& [i, actionName] : rngv::enumerate(m_ControllerActionName)) {
        if (std::string_view(reinterpret_cast<const char*>(actionName)) == name) {
            return (eControllerAction)i;
        }
    }
    return (eControllerAction)-1;
}

// NOTSA
bool CControllerConfigManager::CheckMouseButtonState(KeyCode key) {
    const auto* pad = CPad::GetPad();
    switch (key) {
    case rsMOUSE_LEFT_BUTTON:       return pad->IsMouseLButton();
    case rsMOUSE_RIGHT_BUTTON:      return pad->IsMouseRButton();
    case rsMOUSE_MIDDLE_BUTTON:     return pad->IsMouseMButton();
    case rsMOUSE_WHEEL_UP_BUTTON:   return pad->IsMouseWheelUp();
    case rsMOUSE_WHEEL_DOWN_BUTTON: return pad->IsMouseWheelDown();
    case rsMOUSE_X1_BUTTON:         return pad->IsMouseBmx1();
    case rsMOUSE_X2_BUTTON:         return pad->IsMouseBmx2();
    case 0:                         return false; /* unset button */
    default:                        NOTSA_UNREACHABLE("Invalid key ({})", (int32)(key));
    }
}

// NOTSA
bool CControllerConfigManager::CheckMouseButtonJustUpState(KeyCode key) {
    const auto* pad = CPad::GetPad();
    switch (key) {
    case rsMOUSE_LEFT_BUTTON:       return pad->IsMouseLButtonPressed();
    case rsMOUSE_RIGHT_BUTTON:      return pad->IsMouseRButtonPressed();
    case rsMOUSE_MIDDLE_BUTTON:     return pad->IsMouseMButtonPressed();
    case rsMOUSE_WHEEL_UP_BUTTON:   return pad->IsMouseWheelUpPressed();
    case rsMOUSE_WHEEL_DOWN_BUTTON: return pad->IsMouseWheelDownPressed();
    case rsMOUSE_X1_BUTTON:         return pad->IsMouseBmx1Pressed();
    case rsMOUSE_X2_BUTTON:         return pad->IsMouseBmx2Pressed();
    case 0:                         return false; /* unset button */
    default:                        NOTSA_UNREACHABLE("Invalid key ({})", (int32)(key));
    }
}

// NOTSA
bool CControllerConfigManager::IsCheckSpecificGamepad()
{
    // TODO: Reverse CPadConfig
    return (PadConfigs[0].vendorId == 0x3427 && PadConfigs[0].productId == 0x1190);
}

// NOTSA
void CControllerConfigManager::CheckAndClear(eControllerAction action, eControllerType type, KeyCode button) {
    if (m_Actions[action].Keys[type].m_uiActionInitiator == button) {
        ClearSettingsAssociatedWithAction(action, type);
    }
};

// NOTSA
void CControllerConfigManager::CheckAndSetButton(eControllerAction action, eControllerType type, KeyCode button, int16& stateButton) {
    if (m_Actions[action].Keys[type].m_uiActionInitiator == button) {
        stateButton = 255;
    }
}

// NOTSA
void CControllerConfigManager::CheckAndSetPad(eControllerAction action, eControllerType type, KeyCode button, int16& dpad, int16& oppositeDpad) {
    if (m_Actions[action].Keys[type].m_uiActionInitiator == button) {
        if (dpad) {
            dpad         = 0;
            oppositeDpad = 0;
        } else {
            dpad = 255;
        }
    }
}

// NOTSA
bool CControllerConfigManager::UseDrivingControls() {
    // FindPlayerPed() && FindPlayerVehicle() && FindPlayerPed()->GetPedState() == PEDSTATE_DRIVING && !pad->DisablePlayerControls
    if (auto plyr = FindPlayerPed()) {
        if (FindPlayerVehicle()) {
            return plyr->GetPedState() == PEDSTATE_DRIVING && !CPad::GetPad(0)->DisablePlayerControls;
        }
    }
    return false;
}

// NOTSA
bool CControllerConfigManager::UseFirstPersonControls() {
    return notsa::contains({ MODE_1STPERSON, MODE_SNIPER, MODE_ROCKETLAUNCHER, MODE_ROCKETLAUNCHER_HS, MODE_M16_1STPERSON, MODE_CAMERA }, TheCamera.m_aCams[TheCamera.m_nActiveCam].m_nMode);
}

// NOTSA
CControllerState& CControllerConfigManager::GetControllerState(CPad& pad, eControllerType ctrl) {
    switch (ctrl) {
    case eControllerType::KEYBOARD:
    case eControllerType::OPTIONAL_EXTRA_KEY: return pad.PCTempKeyState;
    case eControllerType::MOUSE:     return pad.PCTempMouseState;
    case eControllerType::JOY_STICK:       return pad.PCTempJoyState;
    default:                   NOTSA_UNREACHABLE();
    }
}
