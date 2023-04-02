//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Custom/RenderFeature/Z_Write_Shader" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
}
SubShader {
 Tags { "CanUseSpriteAtlas" = "true" "RenderType" = "Opaque" }
 Pass {
  Tags { "CanUseSpriteAtlas" = "true" "RenderType" = "Opaque" }
  ColorMask 0 0
  Cull Off
  GpuProgramID 41946
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