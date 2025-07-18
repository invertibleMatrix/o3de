/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#if !defined(Q_MOC_RUN)
#include <AzFramework/Components/CameraBus.h>
#include <CryCommon/Maestro/Types/AnimParamType.h>
#include <CryCommon/Maestro/Types/AnimValueType.h>
#include "EditorDefs.h"
#include "TrackViewKeyPropertiesDlg.h"
#endif

//////////////////////////////////////////////////////////////////////////
class C2DBezierKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    C2DBezierKeyUIControls()
    : m_skipOnUIChange(false)
    {}

    CSmartVariableArray mv_table;
    CSmartVariable<float> mv_value;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_value, "Value");
    }
    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return trackType == eAnimCurveType_BezierFloat;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 0; }

    static const GUID& GetClassID()
    {
        // {DBD76F4B-8EFC-45b6-AFB8-56F171FA150A}
        static const GUID guid =
        {
            0xdbd76f4b, 0x8efc, 0x45b6, { 0xaf, 0xb8, 0x56, 0xf1, 0x71, 0xfa, 0x15, 0xa }
        };
        return guid;
    }

    bool m_skipOnUIChange;
};

//////////////////////////////////////////////////////////////////////////
class CAssetBlendKeyUIControls
    : public CTrackViewKeyUIControls
{
public:

    AZ::EntityId m_entityId;
    AZ::ComponentId m_componentId;

    CSmartVariableArray mv_table;
    CSmartVariable<QString> mv_asset;
    CSmartVariable<bool> mv_loop;
    CSmartVariable<float> mv_timeScale;
    CSmartVariable<float> mv_blendInTime;
    CSmartVariable<float> mv_blendOutTime;

    void OnCreateVars() override
    {
        // Initialize to an invalid id
        AZ::Data::AssetId assetId;
        assetId.SetInvalid();
        mv_asset->SetUserData(assetId.m_subId);
        mv_asset->SetDisplayValue(assetId.m_guid.ToString<AZStd::string>().c_str());

        AddVariable(mv_table, "Key Properties");
        // In the future, we may have different types of AssetBlends supported. Right now
        // "motion" for the Simple Motion Component is the only instance.
        AddVariable(mv_table, mv_asset, "Motion", IVariable::DT_MOTION);
        AddVariable(mv_table, mv_loop, "Loop");
        AddVariable(mv_table, mv_timeScale, "Time Scale");
        AddVariable(mv_table, mv_blendInTime, "Blend In Time");
        AddVariable(mv_table, mv_blendOutTime, "Blend Out Time");
    }

    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::AssetBlend;
    }

    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {5DC82D28-6C50-4406-8993-06770C640F98}
        static const GUID guid =
        {
            0x5DC82D28, 0x6C50, 0x4406, { 0x89, 0x93, 0x06, 0x77, 0x0C, 0x64, 0x0F, 0x98 }
        };
        return guid;
    }

protected:
    void ResetStartEndLimits(float AssetBlendKeyDuration);
    bool m_skipOnUIChange = false;
};

//////////////////////////////////////////////////////////////////////////
class CCaptureKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariable<float> mv_duration;
    CSmartVariable<float> mv_timeStep;
    CSmartVariable<QString> mv_prefix;
    CSmartVariable<QString> mv_folder;
    CSmartVariable<bool> mv_once;

    void OnCreateVars() override
    {
        mv_duration.GetVar()->SetLimits(0, 100000.0f);
        mv_timeStep.GetVar()->SetLimits(0.001f, 1.0f);

        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_duration, "Duration");
        AddVariable(mv_table, mv_timeStep, "Time Step");
        AddVariable(mv_table, mv_prefix, "Output Prefix");
        AddVariable(mv_table, mv_folder, "Output Folder");
        AddVariable(mv_table, mv_once, "Just one frame?");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::Capture;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {543197BF-5E43-4abc-8F07-B84078846E4C}
        static const GUID guid =
        {
            0x543197bf, 0x5e43, 0x4abc, { 0x8f, 0x7, 0xb8, 0x40, 0x78, 0x84, 0x6e, 0x4c }
        };
        return guid;
    }
};

//////////////////////////////////////////////////////////////////////////
class CCommentKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariable<QString> mv_comment;
    CSmartVariable<float> mv_duration;
    CSmartVariable<float> mv_size;
    CSmartVariable<AZ::Vector3> mv_color;
    CSmartVariableEnum<int> mv_align;
    CSmartVariableEnum<QString> mv_font;


    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_comment, "Comment");
        AddVariable(mv_table, mv_duration, "Duration");

        mv_size->SetLimits(1.f, 10.f);
        AddVariable(mv_table, mv_size, "Size");

        AddVariable(mv_table, mv_color, "Color", IVariable::DT_COLOR);

        mv_align->SetEnumList(nullptr);
        mv_align->AddEnumItem("Left", ICommentKey::eTA_Left);
        mv_align->AddEnumItem("Center", ICommentKey::eTA_Center);
        mv_align->AddEnumItem("Right", ICommentKey::eTA_Right);
        AddVariable(mv_table, mv_align, "Align");

        mv_font->SetEnumList(nullptr);
        IFileUtil::FileArray fa;
        CFileUtil::ScanDirectory((Path::GetEditingGameDataFolder() + "/Fonts/").c_str(), "*.xml", fa, true);
        for (size_t i = 0; i < fa.size(); ++i)
        {
            AZStd::string name = fa[i].filename.toUtf8().data();
            PathUtil::RemoveExtension(name);
            mv_font->AddEnumItem(name.c_str(), name.c_str());
        }
        AddVariable(mv_table, mv_font, "Font");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::CommentText;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {FA250B8B-FC2A-43b1-AF7A-8C3B6672B49D}
        static const GUID guid =
        {
            0xfa250b8b, 0xfc2a, 0x43b1, { 0xaf, 0x7a, 0x8c, 0x3b, 0x66, 0x72, 0xb4, 0x9d }
        };
        return guid;
    }
};

//////////////////////////////////////////////////////////////////////////
class CConsoleKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariable<QString> mv_command;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_command, "Command");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::Console;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {3E9D2C57-BFB1-42f9-82AC-A393C1062634}
        static const GUID guid =
        {
            0x3e9d2c57, 0xbfb1, 0x42f9, { 0x82, 0xac, 0xa3, 0x93, 0xc1, 0x6, 0x26, 0x34 }
        };
        return guid;
    }
};

//////////////////////////////////////////////////////////////////////////
class CEventKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariableArray mv_deprecated;

    CSmartVariableEnum<QString> mv_animation;
    CSmartVariableEnum<QString> mv_event;
    CSmartVariable<QString> mv_value;
    CSmartVariable<bool> mv_notrigger_in_scrubbing;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_event, "Event");
        AddVariable(mv_table, mv_value, "Value");
        AddVariable(mv_table, mv_notrigger_in_scrubbing, "No trigger in scrubbing");
        AddVariable(mv_deprecated, "Deprecated");
        AddVariable(mv_deprecated, mv_animation, "Animation");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::Event;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {ED5A2023-EDE1-4a47-BBE6-7D7BA0E4001D}
        static const GUID guid =
        {
            0xed5a2023, 0xede1, 0x4a47, { 0xbb, 0xe6, 0x7d, 0x7b, 0xa0, 0xe4, 0x0, 0x1d }
        };
        return guid;
    }

private:
};

//////////////////////////////////////////////////////////////////////////
class CGotoKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariable<float> mv_command;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_command, "Goto Time");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        if (paramType == AnimParamType::Goto)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {3E9D2C57-BFB1-42f9-82AC-A393C1062634}
        static const GUID guid =
        {
            0x9b79c8b6, 0xe332, 0x4b9b, { 0xb2, 0x63, 0xef, 0x7e, 0x82, 0x7, 0xa4, 0x47 }
        };
        return guid;
    }
};

//-----------------------------------------------------------------------------
//!
class CScreenFaderKeyUIControls
    : public CTrackViewKeyUIControls
{
    CSmartVariableArray             mv_table;

    CSmartVariable<float>           mv_fadeTime;

    // Could be single item with X,Y,Z fields, reflected AZ::Vector3 <-> CReflectedVarColor3, - as commented out below ...
    //CSmartVariable<AZ::Vector3> mv_fadeColor;
    // ... but properly named full-featured group of three R,G,B items seems more user-friendly.
    CSmartVariableArray             mv_fadeColor;
    CSmartVariable<float>           mv_fadeColorR;
    CSmartVariable<float>           mv_fadeColorG;
    CSmartVariable<float>           mv_fadeColorB;

    CSmartVariable<AZStd::string>   mv_strTexture;

    CSmartVariable<bool>            mv_bUseCurColor;

    CSmartVariableEnum<int>         mv_fadeType;

    CSmartVariableEnum<int>         mv_fadechangeType;

public:
    //-----------------------------------------------------------------------------
    //!
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::ScreenFader;
    }

    //-----------------------------------------------------------------------------
    //!
    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");

        mv_fadeType->SetEnumList(nullptr);
        mv_fadeType->AddEnumItem("FadeIn", IScreenFaderKey::eFT_FadeIn);
        mv_fadeType->AddEnumItem("FadeOut", IScreenFaderKey::eFT_FadeOut);
        AddVariable(mv_table, mv_fadeType, "Type");

        mv_fadechangeType->SetEnumList(nullptr);
        mv_fadechangeType->AddEnumItem("Linear", IScreenFaderKey::eFCT_Linear);
        mv_fadechangeType->AddEnumItem("Square", IScreenFaderKey::eFCT_Square);
        mv_fadechangeType->AddEnumItem("Cubic Square", IScreenFaderKey::eFCT_CubicSquare);
        mv_fadechangeType->AddEnumItem("Square Root", IScreenFaderKey::eFCT_SquareRoot);
        mv_fadechangeType->AddEnumItem("Sin", IScreenFaderKey::eFCT_Sin);
        AddVariable(mv_table, mv_fadechangeType, "ChangeType");

        // For single CSmartVariable<AZ::Vector3> mv_fadeColor; - with XYZ sub-items, code would be as commented out below:
        //AddVariable(mv_table, mv_fadeColor, "Color", IVariable::DT_COLOR);
        // Forming sub-group for R,G,B floats 
        AddVariable(mv_fadeColor, mv_fadeColorR, "Red");
        AddVariable(mv_fadeColor, mv_fadeColorG, "Green");
        AddVariable(mv_fadeColor, mv_fadeColorB, "Blue");
        AddVariable(mv_table, mv_fadeColor, "Color");

        mv_fadeTime->SetLimits(0.f, 100.f);
        AddVariable(mv_table, mv_fadeTime, "Duration");
        AddVariable(mv_table, mv_strTexture, "Texture", IVariable::DT_TEXTURE);
        mv_strTexture.GetVar()->SetDescription("Relative path to an existing texture (.png, .tif, .jpg, ...)");

        AddVariable(mv_table, mv_bUseCurColor, "Use Current Color");
    }

    //-----------------------------------------------------------------------------
    //!
    bool OnKeySelectionChange(const CTrackViewKeyBundle& keys) override;

    //-----------------------------------------------------------------------------
    //!
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& keys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {FBBC2407-C36B-45b2-9A54-0CF9CD3908FD}
        static const GUID guid =
        {
            0xfbbc2407, 0xc36b, 0x45b2, { 0x9a, 0x54, 0xc, 0xf9, 0xcd, 0x39, 0x8, 0xfd }
        };
        return guid;
    }

private:
    bool m_skipOnUIChange = false;

    const float colorMin = 0.0f;
    const float colorMax = 255.0f;
};

//////////////////////////////////////////////////////////////////////////
class CSelectKeyUIControls
    : public CTrackViewKeyUIControls
    , protected Camera::CameraNotificationBus::Handler
    , protected AZ::EntitySystemBus::Handler
{
public:
    CSelectKeyUIControls() = default;

    ~CSelectKeyUIControls() override;

    CSmartVariableArray mv_table;
    CSmartVariableEnum<QString> mv_camera;
    CSmartVariable<float> mv_BlendTime;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_camera, "Camera");
        AddVariable(mv_table, mv_BlendTime, "Blend time");

        Camera::CameraNotificationBus::Handler::BusConnect();
        AZ::EntitySystemBus::Handler::BusConnect();
    }
    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::Select;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {9018D0D1-24CC-45e5-9D3D-16D3F9E591B2}
        static const GUID guid =
        {
            0x9018d0d1, 0x24cc, 0x45e5, { 0x9d, 0x3d, 0x16, 0xd3, 0xf9, 0xe5, 0x91, 0xb2 }
        };
        return guid;
    }

protected:
    ////////////////////////////////////////////////////////////////////////
    // CameraNotificationBus interface implementation
    void OnCameraAdded(const AZ::EntityId& cameraId) override;
    void OnCameraRemoved(const AZ::EntityId& cameraId) override;

    //////////////////////////////////////////////////////////////////////////
    // AZ::EntitySystemBus::Handler
    void OnEntityNameChanged(const AZ::EntityId& entityId, const AZStd::string& name) override;

private:

    void ResetCameraEntries();
    bool m_skipOnUIChange = false;

    static constexpr const char* defaultNoneKeyName = "<None>"; // Name used in menu when no camera is selected
};

//////////////////////////////////////////////////////////////////////////
class CSequenceKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariableEnum<QString> mv_sequence;
    CSmartVariable<bool> mv_overrideTimes;
    CSmartVariable<float> mv_startTime;
    CSmartVariable<float> mv_endTime;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_sequence, "Sequence");
        AddVariable(mv_table, mv_overrideTimes, "Override Start/End Times");
        AddVariable(mv_table, mv_startTime, "Start Time");
        AddVariable(mv_table, mv_endTime, "End Time");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::Sequence;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {68030C46-1402-45d1-91B3-8EC6F29C0FED}
        static const GUID guid =
        {
            0x68030c46, 0x1402, 0x45d1, { 0x91, 0xb3, 0x8e, 0xc6, 0xf2, 0x9c, 0xf, 0xed }
        };
        return guid;
    }

private:
    bool m_skipOnUIChange = false;
};

//////////////////////////////////////////////////////////////////////////
class CSoundKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariableArray mv_options;

    CSmartVariable<QString> mv_startTrigger;
    CSmartVariable<QString> mv_stopTrigger;
    CSmartVariable<float> mv_duration;
    CSmartVariable<AZ::Vector3> mv_customColor;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_startTrigger, "StartTrigger", IVariable::DT_AUDIO_TRIGGER);
        AddVariable(mv_table, mv_stopTrigger, "StopTrigger", IVariable::DT_AUDIO_TRIGGER);
        AddVariable(mv_table, mv_duration, "Duration");
        AddVariable(mv_options, "Options");
        AddVariable(mv_options, mv_customColor, "Custom Color", IVariable::DT_COLOR);
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::Sound;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {AB2226E5-D593-49d2-B7CB-989412CAAEDE}
        static const GUID guid =
        {
            0xab2226e5, 0xd593, 0x49d2, { 0xb7, 0xcb, 0x98, 0x94, 0x12, 0xca, 0xae, 0xde }
        };
        return guid;
    }
};

//////////////////////////////////////////////////////////////////////////
class CTimeRangeKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariable<float> mv_startTime;
    CSmartVariable<float> mv_endTime;
    CSmartVariable<float> mv_timeScale;
    CSmartVariable<bool> mv_bLoop;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_startTime, "Start Time");
        AddVariable(mv_table, mv_endTime, "End Time");
        AddVariable(mv_table, mv_timeScale, "Time Scale");
        AddVariable(mv_table, mv_bLoop, "Loop");
        mv_timeScale->SetLimits(0.001f, 100.f);
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::TimeRanges;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {E977A6F4-CEC1-4c67-8735-28721B3F6FEF}
        static const GUID guid = {
            0xe977a6f4, 0xcec1, 0x4c67, { 0x87, 0x35, 0x28, 0x72, 0x1b, 0x3f, 0x6f, 0xef }
        };
        return guid;
    }
};

//////////////////////////////////////////////////////////////////////////
class CTrackEventKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariableEnum<QString> mv_event;
    CSmartVariable<QString> mv_value;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_event, "Track Event");
        mv_event->SetFlags(mv_event->GetFlags() | IVariable::UI_UNSORTED);
        AddVariable(mv_table, mv_value, "Value");
    }
    bool SupportTrackType(const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, [[maybe_unused]] AnimValueType valueType) const override
    {
        return paramType == AnimParamType::TrackEvent;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {F7D002EB-1FEA-46fa-B857-FC2B1B990B7F}
        static const GUID guid =
        {
            0xf7d002eb, 0x1fea, 0x46fa, { 0xb8, 0x57, 0xfc, 0x2b, 0x1b, 0x99, 0xb, 0x7f }
        };
        return guid;
    }

private:
    void OnEventEdit();
    void BuildEventDropDown(QString& curEvent, const QString& addedEvent = "");

    QString m_lastEvent;

    static const char* GetAddEventString()
    {
        static const char* addEventString = "Add a new event...";

        return addEventString;
    }
};

//////////////////////////////////////////////////////////////////////////
class CStringKeyUIControls
    : public CTrackViewKeyUIControls
{
public:
    CSmartVariableArray mv_table;
    CSmartVariable<QString> mv_value;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_value, "Value");
    }
    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::String;
    }
    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override { return 1; }

    static const GUID& GetClassID()
    {
        // {E056F001-A2DF-4E87-8DBB-980A651940DC}
        static const GUID guid = { 0xe056f001, 0xa2df, 0x4e87, { 0x8d, 0xbb, 0x98, 0x0a, 0x65, 0x19, 0x40, 0xdc } };
        return guid;
    }
};

////////////////////// Compound tracks UI handlers

/**
 * Base class template of Key UI Controls for Compound (Vector?) tracks.
 * @param V AZ::Vector3 or AZ::Vector4.
 */
template <class V> class CVectorKeyUIControlsBase
{
    CVectorKeyUIControlsBase() {}
public:
    /**
     * Template ctor: 
     * @param T AnimValueType type, supported: Vector, RGB, Quat, Vector4.
     */
    explicit CVectorKeyUIControlsBase(AnimValueType valueType) : m_valueType(valueType) { }

    /**
    * Get Compound animation track for a set of selected keys.
    * @param selectedKeys Bundle of selected keys.
    * @return Pointer to existing Compound animation track satisfying conditions, or nullptr.
    */
    IAnimTrack* GetCompoundTrackFromKeys(const CTrackViewKeyBundle& selectedKeys);

    AnimValueType m_valueType;
    V m_vector;
};

/**
 * Get and Set values for a Vector3 compound track key via track properties dialog.
 */
class CVectorKeyUIControls
    : public CTrackViewKeyUIControls
    , public CVectorKeyUIControlsBase<AZ::Vector3>
{
protected:

    explicit CVectorKeyUIControls(AnimValueType valueType) : CVectorKeyUIControlsBase(valueType) {}

public:

    CVectorKeyUIControls() : CVectorKeyUIControlsBase<AZ::Vector3>(AnimValueType::Vector) {}

    CSmartVariableArray mv_table;
    CSmartVariable<float> mv_x;
    CSmartVariable<float> mv_y;
    CSmartVariable<float> mv_z;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_x, "X");
        AddVariable(mv_table, mv_y, "Y");
        AddVariable(mv_table, mv_z, "Z");
    }

    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::Vector;
    }

    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override
    {
        return 1;
    }

    static const GUID& GetClassID()
    {
        // {1F432CD8-D6FA-4C83-B174-55AB4F3D9785}
        static const GUID guid = { 0x1f432cd8, 0xd6fa, 0x4c83, { 0xb1, 0x74, 0x55, 0xab, 0x4f, 0x3d, 0x97, 0x85 } };
        return guid;
    }

protected:
    bool m_skipOnUIChange = false;
};

/**
 * Get and Set values for a Vector3 compound track key treated as RGB via track properties dialog.
 */
class CRgbKeyUIControls
    : public CVectorKeyUIControls
{
public:

    CRgbKeyUIControls() : CVectorKeyUIControls(AnimValueType::RGB) {}

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_x, "Red");
        AddVariable(mv_table, mv_y, "Green");
        AddVariable(mv_table, mv_z, "Blue");
    }

    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::RGB;
    }

    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;

    static const GUID& GetClassID()
    {
        // {8D8EC4F6-7C3A-4DEC-863D-C67D9A0645B9}
        static const GUID guid = { 0x8d8ec4f6, 0x7c3a, 0x4dec, { 0x86, 0x3d, 0xc6, 0x7d, 0x9a, 0x06, 0x45, 0xb9 } };
        return guid;
    }
};

/**
 * Get and Set values (in degrees) for a Vector3 compound track key treated as set of Euler (actually Tait-Bryan) angles of a Quaternion
 * via track properties dialog.
 */
class CQuatKeyUIControls
    : public CVectorKeyUIControls
{
public:

    CQuatKeyUIControls() : CVectorKeyUIControls(AnimValueType::Quat) {}

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        // Names correspond to ZXY order in [Quaternion] <-> [Tait-Bryan angles in Degrees] conversions in <Transform::Rotation> tracks.
        AddVariable(mv_table, mv_x, "Pitch");
        AddVariable(mv_table, mv_y, "Roll");
        AddVariable(mv_table, mv_z, "Yaw");
    }

    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::Quat;
    }

    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;

    static const GUID& GetClassID()
    {
        // {273EBFD3-BED5-41C9-8E2C-F2C0DF53F807}
        static const GUID guid = { 0x273ebfd3, 0xbed5, 0x41c9, { 0x8e, 0x2c, 0xf2, 0xc0, 0xdf, 0x53, 0xf8, 0x07 } };
        return guid;
    }
};

/**
 * Get and Set values for a Vector4 compound track key via track properties dialog.
 */
class CVector4KeyUIControls
    : public CTrackViewKeyUIControls
    , CVectorKeyUIControlsBase<AZ::Vector4>
{
protected:
    explicit CVector4KeyUIControls(AnimValueType valueType) : CVectorKeyUIControlsBase(valueType) { }

public:
    CVector4KeyUIControls() : CVectorKeyUIControlsBase<AZ::Vector4>(AnimValueType::Vector4) {}

    CSmartVariableArray mv_table;
    CSmartVariable<float> mv_x;
    CSmartVariable<float> mv_y;
    CSmartVariable<float> mv_z;
    CSmartVariable<float> mv_w;

    void OnCreateVars() override
    {
        AddVariable(mv_table, "Key Properties");
        AddVariable(mv_table, mv_x, "X");
        AddVariable(mv_table, mv_y, "Y");
        AddVariable(mv_table, mv_z, "Z");
        AddVariable(mv_table, mv_z, "W");
    }

    bool SupportTrackType([[maybe_unused]] const CAnimParamType& paramType, [[maybe_unused]] EAnimCurveType trackType, AnimValueType valueType) const override
    {
        return valueType == AnimValueType::Vector4;
    }

    bool OnKeySelectionChange(const CTrackViewKeyBundle& selectedKeys) override;
    void OnUIChange(IVariable* pVar, CTrackViewKeyBundle& selectedKeys) override;

    unsigned int GetPriority() const override
    {
        return 1;
    }

    static const GUID& GetClassID()
    {
        // {C83EFDC1-927A-4112-8F66-BD53B205E589}                                                       
        static const GUID guid = { 0xc83efdc1, 0x927a, 0x4112, { 0x8f, 0x66, 0xbd, 0x53, 0xb2, 0x05, 0xe5, 0x89 } };
        return guid;
    }

private:
    bool m_skipOnUIChange = false;
};
