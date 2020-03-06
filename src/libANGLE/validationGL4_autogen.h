// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml and wgl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// validationGL4_autogen.h:
//   Validation functions for the OpenGL 4.0 entry points.

#ifndef LIBANGLE_VALIDATION_GL4_AUTOGEN_H_
#define LIBANGLE_VALIDATION_GL4_AUTOGEN_H_

#include "common/PackedEnums.h"

namespace gl
{
class Context;

bool ValidateBeginQueryIndexed(const Context *context,
                               GLenum target,
                               GLuint index,
                               QueryID idPacked);
bool ValidateDrawTransformFeedback(const Context *context,
                                   GLenum mode,
                                   TransformFeedbackID idPacked);
bool ValidateDrawTransformFeedbackStream(const Context *context,
                                         GLenum mode,
                                         TransformFeedbackID idPacked,
                                         GLuint stream);
bool ValidateEndQueryIndexed(const Context *context, GLenum target, GLuint index);
bool ValidateGetActiveSubroutineName(const Context *context,
                                     ShaderProgramID programPacked,
                                     GLenum shadertype,
                                     GLuint index,
                                     GLsizei bufsize,
                                     const GLsizei *length,
                                     const GLchar *name);
bool ValidateGetActiveSubroutineUniformName(const Context *context,
                                            ShaderProgramID programPacked,
                                            GLenum shadertype,
                                            GLuint index,
                                            GLsizei bufsize,
                                            const GLsizei *length,
                                            const GLchar *name);
bool ValidateGetActiveSubroutineUniformiv(const Context *context,
                                          ShaderProgramID programPacked,
                                          GLenum shadertype,
                                          GLuint index,
                                          GLenum pname,
                                          const GLint *values);
bool ValidateGetProgramStageiv(const Context *context,
                               ShaderProgramID programPacked,
                               GLenum shadertype,
                               GLenum pname,
                               const GLint *values);
bool ValidateGetQueryIndexediv(const Context *context,
                               GLenum target,
                               GLuint index,
                               GLenum pname,
                               const GLint *params);
bool ValidateGetSubroutineIndex(const Context *context,
                                ShaderProgramID programPacked,
                                GLenum shadertype,
                                const GLchar *name);
bool ValidateGetSubroutineUniformLocation(const Context *context,
                                          ShaderProgramID programPacked,
                                          GLenum shadertype,
                                          const GLchar *name);
bool ValidateGetUniformSubroutineuiv(const Context *context,
                                     GLenum shadertype,
                                     GLint location,
                                     const GLuint *params);
bool ValidateGetUniformdv(const Context *context,
                          ShaderProgramID programPacked,
                          UniformLocation locationPacked,
                          const GLdouble *params);
bool ValidatePatchParameterfv(const Context *context, GLenum pname, const GLfloat *values);
bool ValidateUniform1d(const Context *context, UniformLocation locationPacked, GLdouble x);
bool ValidateUniform1dv(const Context *context,
                        UniformLocation locationPacked,
                        GLsizei count,
                        const GLdouble *value);
bool ValidateUniform2d(const Context *context,
                       UniformLocation locationPacked,
                       GLdouble x,
                       GLdouble y);
bool ValidateUniform2dv(const Context *context,
                        UniformLocation locationPacked,
                        GLsizei count,
                        const GLdouble *value);
bool ValidateUniform3d(const Context *context,
                       UniformLocation locationPacked,
                       GLdouble x,
                       GLdouble y,
                       GLdouble z);
bool ValidateUniform3dv(const Context *context,
                        UniformLocation locationPacked,
                        GLsizei count,
                        const GLdouble *value);
bool ValidateUniform4d(const Context *context,
                       UniformLocation locationPacked,
                       GLdouble x,
                       GLdouble y,
                       GLdouble z,
                       GLdouble w);
bool ValidateUniform4dv(const Context *context,
                        UniformLocation locationPacked,
                        GLsizei count,
                        const GLdouble *value);
bool ValidateUniformMatrix2dv(const Context *context,
                              UniformLocation locationPacked,
                              GLsizei count,
                              GLboolean transpose,
                              const GLdouble *value);
bool ValidateUniformMatrix2x3dv(const Context *context,
                                UniformLocation locationPacked,
                                GLsizei count,
                                GLboolean transpose,
                                const GLdouble *value);
bool ValidateUniformMatrix2x4dv(const Context *context,
                                UniformLocation locationPacked,
                                GLsizei count,
                                GLboolean transpose,
                                const GLdouble *value);
bool ValidateUniformMatrix3dv(const Context *context,
                              UniformLocation locationPacked,
                              GLsizei count,
                              GLboolean transpose,
                              const GLdouble *value);
bool ValidateUniformMatrix3x2dv(const Context *context,
                                UniformLocation locationPacked,
                                GLsizei count,
                                GLboolean transpose,
                                const GLdouble *value);
bool ValidateUniformMatrix3x4dv(const Context *context,
                                UniformLocation locationPacked,
                                GLsizei count,
                                GLboolean transpose,
                                const GLdouble *value);
bool ValidateUniformMatrix4dv(const Context *context,
                              UniformLocation locationPacked,
                              GLsizei count,
                              GLboolean transpose,
                              const GLdouble *value);
bool ValidateUniformMatrix4x2dv(const Context *context,
                                UniformLocation locationPacked,
                                GLsizei count,
                                GLboolean transpose,
                                const GLdouble *value);
bool ValidateUniformMatrix4x3dv(const Context *context,
                                UniformLocation locationPacked,
                                GLsizei count,
                                GLboolean transpose,
                                const GLdouble *value);
bool ValidateUniformSubroutinesuiv(const Context *context,
                                   GLenum shadertype,
                                   GLsizei count,
                                   const GLuint *indices);
}  // namespace gl

#endif  // LIBANGLE_VALIDATION_GL4_AUTOGEN_H_
