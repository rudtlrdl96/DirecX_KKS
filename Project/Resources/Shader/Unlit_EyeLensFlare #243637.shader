//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/EyeLensFlare" {
Properties {
_Color ("Color", Color) = (1,1,1,1)
_Intensity ("Intensity", Float) = 0.1
_DistAtten ("Dist Atten", Float) = 1
_AngleAtten ("Angle Atten", Float) = 1
_DepthThreshold ("Depth Threshold", Float) = 1
}
SubShader {
 Tags { "RenderType" = "Opaque" }
 Pass {
  Tags { "RenderType" = "Opaque" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZTest Always
  ZWrite Off
  GpuProgramID 38479
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