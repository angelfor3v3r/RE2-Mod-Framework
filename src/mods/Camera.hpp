#pragma once

#include "Mod.hpp"

#ifdef RE8

class RenderToneMappingInternal {
public:
    char pad_0000[484]; // 0x0000
    int32_t Vignetting; // 0x01E4
};

class RenderToneMapping : public REComponent {
public:
    RenderToneMappingInternal* toneMappingInternal;
};

class AppPlayerCameraParameter {
public:
    char pad_0000[56]; // 0x0000
    float DefaultFOV;  // 0x0038
    float AimmingFOV;  // 0x003C
};

class AppPlayerCameraConfigurationBase {
public:
    char pad_0000[80];                               // 0x0000
    AppPlayerCameraParameter* playerCameraParameter; // 0x0050
};

class AppPlayerCameraConfiguration {
public:
    char pad_0000[32];                                               // 0x0000
    AppPlayerCameraConfigurationBase* playerCameraConfigurationBase; // 0x0020
};

class AppCameraConfiguration {
public:
    char pad_0000[24];                                       // 0x0000
    AppPlayerCameraConfiguration* playerCameraConfiguration; // 0x0018
};

class AppPlayerConfiguration {
public:
    char pad_0000[232];                          // 0x0000
    AppCameraConfiguration* cameraConfiguration; // 0x00E8
};

class AppPlayerConfigure {
public:
    char pad_0000[80];                           // 0x0000
    AppPlayerConfiguration* playerConfiguration; // 0x0050
};

class Camera : public Mod {
public:
    std::string_view get_name() const override { return "Camera"; };

    void on_config_load(const utility::Config& cfg) override;
    void on_config_save(utility::Config& cfg) override;

    void on_draw_ui() override;

    void on_update_transform(RETransform* transform);

private:
    const ModToggle::Ptr m_enabled{ ModToggle::create(generate_name("Enabled"), false) };
    const ModToggle::Ptr m_disable_vignette{ ModToggle::create(generate_name("DisableVignette"), true) };
    const ModSlider::Ptr m_fov{ ModSlider::create(generate_name("FOV"), 0.0f, 180.0f, 81.0f) };
    const ModSlider::Ptr m_fov_aiming{ ModSlider::create(generate_name("FOVAiming"), 0.0f, 180.0f, 70.0f) };

    ValueList m_options{
        *m_enabled, 
        *m_disable_vignette, 
        *m_fov, 
        *m_fov_aiming
    };

    AppPropsManager* m_props_manager{ nullptr };
    RECamera* m_cam{ nullptr };
    REGameObject* m_player{ nullptr };
    RenderToneMappingInternal* m_tone_map_internal{ nullptr };
    AppPlayerCameraParameter* m_player_camera_params{ nullptr };

    void on_cam_transform(RETransform* transform) noexcept;
    void on_player_transform(RETransform* transform) noexcept;
    void on_disabled() noexcept;
};

#endif