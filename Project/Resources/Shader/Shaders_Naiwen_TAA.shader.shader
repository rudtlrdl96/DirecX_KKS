//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shaders/Naiwen/TAA.shader" {
Properties {
_MainTex ("Source", 2D) = "white" { }
}
SubShader {
 LOD 100
 Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
 Pass {
  Name "Stop NaN"
  LOD 100
  Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 20352
Program "vp" {
SubProgram "d3d11 " {
Keywords { "_LOW_TAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_MIDDLE_TAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_HIGH_TAA" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "_LOW_TAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_MIDDLE_TAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_HIGH_TAA" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}