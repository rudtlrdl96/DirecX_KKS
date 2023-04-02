//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Custom/Tearing" {
Properties {
_MainTex ("Base (RGB)", 2D) = "white" { }
_XAxis ("X Axis ", Float) = 0
_YAxis ("Y Axis ", Float) = 0
_GlitchSpeed ("Glitch Speed", Float) = 0
_GlitchIntensity ("Glitch Intensity", Float) = 0
_GlitchMaxDisplace ("Glitch Max Displace", Float) = 0
_Glow ("Glow", Float) = 0
}
SubShader {
 Tags { "RenderType" = "Opaque" }
 Pass {
  Tags { "RenderType" = "Opaque" }
  GpuProgramID 16189
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