//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/SubpixelMorphologicalAntialiasing" {
Properties {
_StencilRef ("_StencilRef", Float) = 64
_StencilMask ("_StencilMask", Float) = 64
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   WriteMask 0
   Comp Always
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 51510
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_HIGH" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_HIGH" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  Stencil {
   ReadMask 0
   WriteMask 0
   Comp Equal
   Pass Replace
   Fail Keep
   ZFail Keep
  }
  GpuProgramID 107781
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_HIGH" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_HIGH" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 190300
Program "vp" {
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_HIGH" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_LOW" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_MEDIUM" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Local Keywords { "_SMAA_PRESET_HIGH" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}