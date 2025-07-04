 {BEGIN_LICENSE}
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
# {END_LICENSE}

get_property(scriptcanvas_gem_root GLOBAL PROPERTY "@GEMROOT:ScriptCanvas@")

set(FILES
    ${scriptcanvas_gem_root}/Code/Include/ScriptCanvas/AutoGen/ScriptCanvasGrammar_Header.jinja
    ${scriptcanvas_gem_root}/Code/Include/ScriptCanvas/AutoGen/ScriptCanvasGrammar_Source.jinja
    ${scriptcanvas_gem_root}/Code/Include/ScriptCanvas/AutoGen/ScriptCanvasNodeable_Header.jinja
    ${scriptcanvas_gem_root}/Code/Include/ScriptCanvas/AutoGen/ScriptCanvasNodeable_Source.jinja

    Include/${Name}.h
    Source/${Name}.ScriptCanvasNodeable.xml
    Source/${Name}.cpp

    Source/AutoGen/ScriptCanvasNodeable.xsd
)
