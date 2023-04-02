//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/2D_TilemapShader" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
_MaskTex ("Mask Texture", 2D) = "white" { }
_NormalTex ("Normal Texture", 2D) = "white" { }
_AmbientMaskTex ("Ambient Mask Texture", 2D) = "white" { }
_DistAtten ("Atten Rate", Float) = 0
_AngleRate ("Rim Angle", Float) = 0
_ZIntensity ("Z Intensity", Float) = 0
_LightIntensity ("Light Intensity", Float) = 0
_AmbientIntensity ("Ambient Intensity", Float) = 0
_IsFlip ("Is Flip", Float) = 1
_DefaultMask ("Default Mask", 2D) = "white" { }
_DefaultAmbientMask ("Default Ambient Mask", 2D) = "black" { }
_TileSize ("Tile Size", Vector) = (1,1,1,1)
}
SubShader {
 Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalRenderPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZWrite Off
  Cull Off
  GpuProgramID 67749
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
}
}
}