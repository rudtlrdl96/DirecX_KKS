//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-ScreenSpaceShadows" {
Properties {
_ShadowMapTexture ("", any) = "" { }
_ODSWorldTexture ("", 2D) = "" { }
}
SubShader {
 Tags { "ShadowmapFilter" = "HardShadow" }
}
SubShader {
 Tags { "ShadowmapFilter" = "HardShadow_FORCE_INV_PROJECTION_IN_PS" }
}
SubShader {
 Tags { "ShadowmapFilter" = "PCF_SOFT" }
}
SubShader {
 Tags { "ShadowmapFilter" = "PCF_SOFT_FORCE_INV_PROJECTION_IN_PS" }
}
}