//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/Gradient Shader" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
_MaxDist ("Max Dist", Float) = 2
_DistCenter ("Center", Vector) = (0,0,0,0)
_InnerColor ("Inner Color", Color) = (1,1,1,1)
_OuterColor ("Outer Color", Color) = (1,1,1,1)
_LerpValue ("Lerp Value", Range(0, 1)) = 1
}
SubShader {
 Tags { "RenderType" = "Opaque" }
 Pass {
  Tags { "RenderType" = "Opaque" }
  Cull Off
  GpuProgramID 21050
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